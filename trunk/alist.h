// alist.h -- attribute list

#ifndef ALIST_H
#define ALIST_H

#include "common.h"

#include <std/stdexcept.h>
#include <std/string.h>
#include <vector.h>
#include <list.h>

struct Time;
struct Rules;
struct CSMP;
struct AttributeList;

class Sequence : public list <const AttributeList*>
{ };

class Layers : public list <pair <double, const AttributeList*> >
{ };

class AttributeList
{
  // Content.
  struct Implementation;
  Implementation& impl;
public:
  static const AttributeList empty;

  // Exceptions.
#ifdef HANDLE_EXCEPTIONS
  struct Invalid : runtime_error
  { 
    // Tried to extract the wrong type from a Value object.
    const char* what () const;
  };

  struct Uninitialized : runtime_error
  { 
    // Tried to lookup an uninitialized value in an AttributeList.
    const char* what () const;
  };
#endif HANDLE_EXCEPTIONS

  // Use.
  bool check (string) const 
       throw0 ();
  double number (string) const
       throw2 (Invalid, Uninitialized);
  string name (string) const
       throw2 (Invalid, Uninitialized);
  bool flag (string) const
       throw2 (Invalid, Uninitialized);
  const vector<double>& array (string) const
       throw2 (Invalid, Uninitialized);
  const Rules& rules (string) const
       throw2 (Invalid, Uninitialized);
  const CSMP& csmp (string) const 
       throw2 (Invalid, Uninitialized);
  const AttributeList& list (string) const
       throw2 (Invalid, Uninitialized);
  int integer (string) const
       throw2 (Invalid, Uninitialized);
  const Time& time (string) const
       throw2 (Invalid, Uninitialized);
  const Sequence& sequence (string) const
       throw2 (Invalid, Uninitialized);
  const Layers& layers (string) const
       throw2 (Invalid, Uninitialized);
       
    // Create and Destroy.
  void add (string, double);
  void add (string, AttributeList&);
  void add (string, const Rules*);
  void add (string, const CSMP*);
  void add (string, string);
  void add (string, const vector<double>&);
  void add (string, bool);
  void add (string, int);
  void add (string, const Time&);
  void add (string, const Sequence&);
  void add (string, const Layers&);

  void operator += (const AttributeList&);
  AttributeList (const AttributeList& old);
  AttributeList ();
  ~AttributeList ();
};

#endif ALIST_H

// alist.h ends here
