#include "zGetOpt.h"


zGetOpt::zGetOpt(int argc,char** argv) {
  _command_line = new zArray<zString>(NO, 32);
  _arguments = new zArray<Argument*>(NO, 32);
  _parsed = new zArray<Argument*>(NO, 32);

  parse_argv(argv, argc);

  _index = 0;
  _valid = false;
}


zGetOpt::~zGetOpt(void) {
  while(_arguments->get_count() > 0) {
    Argument* arg = NULL;
    if (_arguments->remove(0, &arg)) {
      delete arg;
    }
  }
  while(_parsed->get_count() > 0) {
    Argument* arg = NULL;
    if (_parsed->remove(0, &arg)) {
      delete arg;
    }
  }
  
  delete _command_line;
  delete _arguments;
  delete _parsed;
}


void zGetOpt::add_arg(char  arg, zString const& long_arg, bool mandatory, bool has_param, zString const& description, zString const& param_description) {
  Argument* argument = new Argument();
  argument->arg = arg;
  argument->long_arg = long_arg;
  argument->mandatory = mandatory;
  argument->has_param = has_param;
  argument->description = description;
  argument->param_description = param_description;

  _arguments->append(argument);
}


zString zGetOpt::get_user_friendly_help(void) {
  return "";
}


zString zGetOpt::get_user_friendly_error(void) {
  return "";
}


zGetOpt::Argument* zGetOpt::next(void) {
  Argument* argument = NULL;
  if (_parsed->get(_index, &argument)) {
    _index++;
    return argument;
  }
  return NULL;
}


void zGetOpt::parse(void) {
  for (int i = 1; i < _command_line->get_count(); i++) {
    zString str;
    _command_line->get(i, &str);
    // Search cur in the argument table.
    Argument* arg = search(str);
    
    if (arg != NULL) {
      // Validate param
      // if ok add in parsed.
      Argument* parsed = new Argument(*arg);
      if (arg->has_param) {
        // Check if next arg is available (is expected)
        if ((i  + 1) < _command_line->get_count()) {
          i++;
          _command_line->get(i, &(parsed->param));
        }
        else {
          // Error missing parameters.
          break;
        }
      }
      //
      _parsed->append(parsed);
    }
    else {
      // Unhandled param ... ignore or interupt.
    }
  }
}


zGetOpt::Argument* zGetOpt::search(zString const& arg) {
  if (arg.is_empty()) return NULL;

  for (int i = 0; i < _arguments->get_count(); i++) {
    Argument* argument = NULL;
    if (_arguments->get(i, &argument)) {
      if (arg.start_with("--")) {
        if (argument->long_arg. equals(arg.substring(2, arg.get_length() - 2))) {
          return argument;
        }
      }
      else if (arg.get_length() == 2 && (arg.start_with("-"))) {
        if (argument->arg == arg.get_buffer()[1]) {
          return argument;
        }
      }
      else {
        // Exit invalid argument.
        break;
      }
    }
  }
  return NULL;
}


void zGetOpt::parse_argv(char** argv, int argc) {
  // Get first arg as program path.

  for (int i = 1; i < argc; i++) {
    zString cur(argv[i]);

    if (cur.start_with("--")) {
      // Extended mode it is single token
      _command_line->append(cur);
    }
    else if (cur.start_with("-")) {
      // Multiple tokens in  this token, split.
      char token[3] = { '-', ' ', 0 };
      char* buffer = cur.get_buffer();
      for (int x = 1; x < cur.get_length(); x++) {
        token[1] = buffer[x];
        _command_line->append(zString(token));
      }
    }
    else {
      // Extended mode it is single token
      _command_line->append(cur);
    }
  }
}
