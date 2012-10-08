#include "zGetOpt.h"

#include "zStringBuilder.h"


zGetOpt::zGetOpt(int argc,char const** argv) {
  _command_line = new zArray<zString>(NO, 32);
  _arguments = new zArray<Argument*>(NO, 32);
  
  parse_argv(argv, argc);

  _index = 0;
  _error = ERR_NO_ERROR;
}


zGetOpt::~zGetOpt(void) {
  while(_arguments->get_count() > 0) {
    Argument* arg = NULL;
    if (_arguments->remove(0, &arg)) {
      delete arg;
    }
  }
  
  delete _command_line;
  delete _arguments;
}


void zGetOpt::add_arg(char  arg, zString const& long_arg, bool has_param, zString const& description, zString const& param_description) {
  Argument* argument = new Argument();
  argument->arg = arg;
  argument->long_arg = long_arg;
  argument->has_param = has_param;
  argument->description = description;
  argument->param_description = param_description;

  _arguments->append(argument);
}


zString zGetOpt::get_help_message(void) {
  // printf("  -v --version          show version information and exit.\\n");
  // printf("  -f --file input.out   Input file.\n");

  zStringBuilder message;
  for (int i = 0; i < _arguments->get_count(); i++) {
    Argument* arg = NULL;
    if (_arguments->get(i, &arg)) {
      zStringBuilder line;
      line.appendf("  -%c --%s %s ", arg->arg, arg->long_arg.get_buffer(), arg->param_description.get_buffer());
      int delta = 25 - line.get_length();
      if (delta > 0) {
        line.append_space(delta);
      }
      line.append(arg->description);
      message.appendf("%s\n", line.to_string().get_buffer());
    }
  }
  return message.to_string();
}


zString zGetOpt::get_usage_message(void) {
  // printf("  -v --version          show version information and exit.\\n");
  // printf("  -f --file input.out   Input file.\n");

  zStringBuilder message;
  message.append("Usage: ");
  for (int i = 0; i < _arguments->get_count(); i++) {
    Argument* arg = NULL;
    if (_arguments->get(i, &arg)) {
      message.appendf(" [-%c|--%s", arg->arg, arg->long_arg.get_buffer());
      if (arg->has_param) {
        message.appendf(" %s",  arg->param_description.get_buffer());
      }
      message.append(']');
    }
  }
  return message.to_string();
}


zString zGetOpt::get_error_message(void) {
  if (_error == ERR_NO_ERROR) {
    return "No error.";
  }
  else if (_error == ERR_MISSING_PARAM) {
    zString str;
    if (_command_line->get(_index, &str)) {
      zStringBuilder strb;
      strb.appendf("Argument %s is not recornized.", str.get_buffer());
      return strb.to_string();
    }
  }
  else if (_error == ERR_UNKNOWN_ARG) {
    zString str;
    if (_command_line->get(_index, &str)) {
      zStringBuilder strb;
      strb.appendf("Argument %s is not recornized.", str.get_buffer());
      return strb.to_string();
    }
  }

  return "";
}


zGetOpt::Argument const* zGetOpt::next(void) {
  if (_error != ERR_NO_ERROR) {
    // Don't continue if it is in error. PArsing terminated.
    return NULL;
  }
  if (_index >= _command_line->get_count()) {
    // Terminated, arguments.
    return NULL;
  }

  zString str;
  _command_line->get(_index, &str);
  // Search cur in the argument table.
  Argument* arg = search(str);
  if (arg != NULL) {
    _index++;
    // Validate param
    // if ok add in parsed.
    if (arg->has_param) {
      // Check if next arg is available (is expected)
      if ((_index) < _command_line->get_count()) {
        _command_line->get(_index, &(arg->param));
        _index++;
      }
      else {
        _index--;
        _error = ERR_MISSING_PARAM;
      }
    }
    // Return argument.
    return arg;
  }
  else {
    // Unhandled param ... ignore or interupt.
    _error = ERR_UNKNOWN_ARG;
  }
  return NULL;
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


void zGetOpt::parse_argv(char const** argv, int argc) {
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
