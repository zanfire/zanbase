/******************************************************************************
 * Copyright 2012 Matteo Valdina
 *      
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *      
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef ZGETOPT_H__
#define ZGETOPT_H__

#include "zCommon.h"

#include "zString.h"
#include "zArray.h"


/// This class handles the validation and parsing of a command line arguments.
/// NOTE: This class is not thread-safe.
///
/// @author Matteo Valdina
class zGetOpt {
public:
  struct Argument {
    // Definitions
    char arg;
    zString long_arg;
    bool has_param;
    zString description;
    zString param_description;;
    // Value
    zString param;
  };

  enum ErrorType {
    ERR_NO_ERROR,
    ERR_MISSING_PARAM,
    ERR_UNKNOWN_ARG
  };

protected:
  zString _program_name;
  // Parsed (splitted) command line.
  zArray<zString>* _command_line;
  /// Table of arguments of know args.
  zArray<Argument*>* _arguments;
  /// The index of current command line argument.
  int _index;
  ErrorType _error;

public:
  zGetOpt(int argc,char const** argv);
  virtual ~zGetOpt(void);

  /// Add an arguments that zGetOpt can handle.
  /// @param arg in the shortener form.
  /// @param long_arg in the long form.
  /// @param mandatory is true if argument is mandatory.
  /// @param description is an optional description for the argument.
  void add_arg(char arg, zString const& long_arg, bool has_param = false, zString const& description = "", zString const& param_description = "");
  //// Returns an user friendly string that describe handled arguments.
  zString get_help_message(void);
  //// Returns an user friendly string that describe handled arguments.
  zString get_usage_message(void);
  /// Get the error message.
  zString get_error_message(void);
  /// Returns if the arguments are valid.
  ErrorType get_error(void) const { return _error; }
  /// Retuns the next argument.
  /// The returned Argument instance is safe between the next method invokation.
  Argument const* next(void);

  zString get_program_name(void) const { return _program_name; }
private:
  /// Parse argv and argc.
  void parse_argv(char const** argv, int argc);
  /// Search the argument "arg" in the command line and returns the Argument instance.
  Argument* search(zString const& arg);
};

#endif // ZGETOPT_H__
