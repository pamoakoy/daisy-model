// lexer.h --- Lexical analysis

#ifndef LEXER_H
#define LEXER_H

#include "common.h"

#ifdef BORLAND
struct istream;
#else
#include <iosfwd>
#endif

using namespace std;

class Treelog;

class Lexer
{
  // State.
private:
  static std::istream& open_file (const string& name);
  std::istream& in;
public:
  Treelog& err;
private:
  int line;
  int column;
public:
  const string file;
  int error_count;

  // Operations.
public:
  int get ();
  int peek ();
  bool good ();
  void error (const string& str);
  void eof ();

  // Create and destroy.
public:
  Lexer (const string&, Treelog&);
  ~Lexer ();
};

#endif // LEXER_H