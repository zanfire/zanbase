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


/// This class handles the validation and parsing of a command line argument.
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
    zString param_description;
    bool mandatory;
    // Value
    zString param;
  };

protected:
  // Parsed (splitted) command line.
  zArray<zString>* _command_line;
  /// Table of arguments of know args.
  zArray<Argument*>* _arguments;
  /// Table of arguments parsed from argc, argv.
  zArray<Argument*>* _parsed;
  /// The index of parsed argument.
  /// TODO: It is needed?
  int _index;
  bool _valid;

public:
  zGetOpt(int argc,char** argv);
  virtual ~zGetOpt(void);

  /// Add an arguments that zGetOpt can handle.
  /// @param arg in the shortener form.
  /// @param long_arg in the long form.
  /// @param mandatory is true if argument is mandatory.
  /// @param description is an optional description for the argument.
  void add_arg(char arg, zString const& long_arg, bool mandatory = false, bool has_param = false, zString const& description = "", zString const& param_description = "");

  //// Returns an user friendly string that describe handled arguments.
  zString get_user_friendly_help(void);

  /// Returns if the arguments are valid.
  bool is_valid(void) const { return _valid; }

  ///
  zString get_user_friendly_error(void);

  /// Retuns the parsed argument
  Argument* next(void);

  void parse(void);

  Argument* search(zString const& arg);

private:
  void parse_argv(char** argv, int argc);
};

#endif // ZGETOPT_H__
