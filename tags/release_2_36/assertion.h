// assertion.h -- Managed assertions.
// 
// Copyright 2002 Per Abrahamsen and KVL.
//
// This file is part of Daisy.
// 
// Daisy is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
// 
// Daisy is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.
// 
// You should have received a copy of the GNU Lesser Public License
// along with Daisy; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// We want a copy of assertion failures in daisy.log, yet we don't
// want to drag the correspondig treelog into every function.

#ifndef ASSERTION_H
#define ASSERTION_H

#include <string>
using namespace std;

class Treelog;

namespace Assertion
{
  void failure (const char* file, int line, const char* fun, const char* test);
  void bug (const char* file, int line, const char* fun, const string& msg);
  class Register
  {
    Treelog& treelog;
  public:
    Register (Treelog&);
    ~Register ();
  };
}

#if defined (__BORLANDC__) && __BORLANDC__ < 0x0550
#define daisy_assert(condition) \
  while (!(condition)) \
    Assertion::failure (__FILE__, __LINE__, NULL, #condition)
#define daisy_bug(msg) Assertion::bug (__FILE__, __LINE__, NULL, msg)
#else
#define daisy_assert(condition) \
  while (!(condition)) \
    Assertion::failure (__FILE__, __LINE__, __FUNCTION__, #condition)
#define daisy_bug(msg) Assertion::bug (__FILE__, __LINE__, __FUNCTION__, msg)
#endif

#endif // ASSERTION_H
