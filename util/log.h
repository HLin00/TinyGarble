/*
 This file is part of TinyGarble. It is modified version of JustGarble
 under GNU license.

 TinyGarble is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TinyGarble is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TinyGarble.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTIL_LOG_H_
#define UTIL_LOG_H_

#include <fstream>
#include <string>

#include "util/common.h"
#include "crypto/block.h"

using std::ostream;
using std::string;

class DummyLog {
  typedef ostream& (*ostreamManipulator)(ostream&);
 public:
  template<class T>
  DummyLog& operator <<(const T& v) {
    return *this;
  }

  DummyLog& operator<<(ostreamManipulator manip) {
    return *this;
  }

};

#define ERROR 0
#define INFO 1
// Error: red, info:green
#define LOG_COLOR(X) (((X)==ERROR)?31:32)

#ifdef ENABLE_LOG

#define DUMP(X) Dump(X)
#define LOG(X) LogStream((X)) << __FILE__ << ":" <<  __LINE__ << " \033[" \
  << LOG_COLOR(X) << "m" << #X << "\033[0m: "
#define CHECK_EXPR(X) if((X)==true) { LOG(ERROR) << #X << " failed" \
  << std::endl; return FAILURE; }
#define CHECK(X) if((X)==FAILURE) { LOG(ERROR) << #X << " failed" \
  << std::endl; return FAILURE; }
#define BN_CHECK(X) if((X)==0) { LOG(ERROR) << #X << " failed" \
  << std::endl; return FAILURE; }

#else /* ENABLE_LOG */

#define DUMP(X) DummyLogStream()
#define LOG(X) DummyLogStream()
#define CHECK_EXPR(X) X
#define CHECK(X) X
#define BN_CHECK(X) X

#endif /* ENABLE_LOG */

void LogInitial(int argc, char *argv[]);
void LogFinish();
ostream& Dump(const string& dump_file);
ostream& LogStream(int log_code);
ostream& operator <<(ostream & o, const block& v);
DummyLog& DummyLogStream();

#endif /* UTIL_LOG_H_ */
