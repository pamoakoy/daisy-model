// options.h -- Parsing command line options.

#ifndef OPTIONS_H
#define OPTIONS_H

#include "common.h"

#ifdef MISSING_OSTREAM
#include <iostream.h>
#elif defined (BROKEN_HEADERS)
#include <ostream.h>
#else
#include <ostream>
#endif

struct Syntax;
struct AttributeList;

class Options
{
  static string get_arg (int& argc, char**& argv);
public: 
  static const char *const log_name;
  static const char *const path_name;
  const string program_name;
  void usage () const;
  Options (int& argc, char**& argv, 
	   Syntax& syntax, AttributeList& alist);
};

#endif // OPTIONS_H
