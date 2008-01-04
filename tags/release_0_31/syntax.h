// syntax.h

#ifndef SYNTAX_H
#define SYNTAX_H

#include "common.h"
#include <vector>

struct AttributeList;
struct Library;

class Syntax
{ 
  struct Implementation;
  friend struct Implementation;
  Implementation& impl;
public:
  // A syntax entry has an associated size.  If the size is a positive
  // integer, the syntax entry specifies an array of that size.  The
  // default size `Singleton' indicating that the syntax entry match a
  // single item of the specified type, while the `Sequence' used for
  // entries that contain an array of unspecified length. 
  static const int Singleton;	
  static const int Sequence;
  static const int Unspecified;

  // A syntax may have a dimension associated.
  static const string& Unknown ();
  static const string& None ();

  // Each syntax entry should have an associated type.
  enum type 
  { Number, AList, CSMP, Boolean, String,
    Date, Integer, Object, Library, Error };
  static const char* type_name (type);
  static type type_number (const char* name);
    
  // The requirements with regard to input and output varies with each
  // syntax entry.
  enum category
  {
    // This is a parameter, i.e. its value doesn't change during the
    // compilation, and it cannot be written to the log.
    Const,
    // This a state variable, it must be provided at initialization
    // and can be written to the log.
    State,
    // This is a state variable that can be computer from other state
    // variables, and therefore does not need to be specified before
    // the simulation starts. 
    Optional, 
    // This is a variable that is only computed for logging purposes
    // and not a part of the simulation state. 
    LogOnly
  };
  static const char* category_name (category);
  static int category_number (const char* name);

  // These functions will check that an alist conform to the syntax.
  bool check (const AttributeList&, const string& = "<unknown>") const;

  // These functions will allow you to lookup information about a
  // specific syntax entry. 
  bool is_const (const string&) const;
  bool is_optional (const string&) const;
  type lookup (const string&) const;
  const Syntax& syntax (const string&) const;
public:
  ::Library& library (const string&) const;
  int  size (const string&) const;
  const string& dimension (const string&) const;
  const string& description (const string&) const;
  bool ordered () const;
  const vector<string>& order () const;
  int order (const string& name) const;	// Return index in order, or -1.
  bool total_order () const;	// True iff all members are ordered.
  
  // Print whole syntax table.
  void dump (int indent = 0) const;

  // Get a list of all entries.
  void entries (vector<string>&) const;
  unsigned int entries () const;

  // Add syntax entries
  void add (const string& key,	// Generic.
	    type t, 
	    category cat,
	    int size,
	    const string& description);
  void add (const string& key,
	    type t, 
	    category cat,
	    const string& description)
    { add (key, t, cat, Singleton, description); }
  void add (const string& key,  // Compatibility, remove.
	    type t, category cat, int size = Singleton)
    { add (key, t, cat, size, Unknown ()); }

  void add (const string& key, // Number.
	    const string& dim,
	    category cat,
	    int size,
	    const string& description);
  void add (const string& key, 
	    const string& dim,
	    category cat,
	    const string& description)
    { add (key, dim, cat, Singleton, description); } 

  void add (const string& key,  // AList
	    const Syntax& syntax,
	    int size,
	    const string& description)
    { add (key, syntax, State, size, description); }
  void add (const string& key,  // AList
	    const Syntax& syntax,
	    const string& description)
    { add (key, syntax, State, Singleton, description); }
  void add (const string&, const Syntax&, // Compatibility, remove.
	    category = State, int size = Singleton, 
	    const string& description = Unknown ());

  void add (const string& key, // Object
	    ::Library& lib, 
	    int size,
	    const string& description)
    { add (key, lib, State, size, description); }
  void add (const string& key,
	    ::Library& lib, 
	    const string& description)
    { add (key, lib, State, Singleton, description); }
  void add (const string&, ::Library&, // Compatibility, remove.
	    category = State, int size = Singleton, 
	    const string& description = Unknown ());

  void add_library (const string&, ::Library&);

  // It is possible to impose an order on the syntax entries, which
  // will allow the input module to parse the entries without the user
  // having to specify the names of the entries.  It is recommended
  // *not* to use this in general, as it makes it more difficult to
  // add new entries.
  void order (const vector<string>&);
  void order (const string&);
  void order (const string&, const string&);
  void order (const string&, const string&, const string&);
  void order (const string&, const string&, const string&, const string&);
  void order (const string&, const string&, const string&, const string&,
	      const string&);

  // Create and Destroy.

  // A check_fun is a function used for extra syntax checking.
  typedef bool (*check_fun)(const AttributeList&);
  typedef bool (*check_list_fun)(const vector<AttributeList*>&);

  Syntax ();
  Syntax (check_fun);
  Syntax (check_list_fun);
  ~Syntax ();
private:
  Syntax (Syntax&);
  Syntax& operator= (Syntax&);
};

template <class T> 
struct add_submodule
{
  add_submodule (const char* name, Syntax& syntax, AttributeList& alist,
		 Syntax::category cat = Syntax::State, 
		 int size = Syntax::Singleton, 
		 const string& description = Syntax::Unknown ())
  {
    Syntax& s = *new Syntax ();
    AttributeList& a = *new AttributeList ();
    T::load_syntax (s, a);
    syntax.add (name, s, cat, size, description);
    // KLUDGE: This is *incorrect* for sequences.  The specified alist
    // currently works as a _default_ for each member of a derived
    // object.  However, both the parser and the pretty printer must
    // know this kludge.
    alist.add (name, a);
  }
};

void check (const AttributeList& al, const string& s, bool& ok);
void non_negative (double v, const string& s, bool& ok, int index = -1);
void non_positive (double v, const string& s, bool& ok, int index = -1);
void is_fraction (double v, const string& s, bool& ok, int index = -1);

#endif SYNTAX_H