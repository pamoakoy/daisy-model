// log.h
// 
// Copyright 1996-2001 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2001 KVL.
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


#ifndef LOG_H
#define LOG_H

#include "librarian.h"

class Daisy;
class Time;
class PLF;
class Geometry;

class Log
{
  // Content.
private:
  struct Implementation;
  Implementation& impl;
public:
  const string name;
  static const char *const description;

  // Filter
public:
  virtual bool check_member (const string&) const = 0;
  virtual bool check_entry (const string&, const Library& library) const;
  virtual bool check_derived (const string& field, const string& name, 
			      const Library& library) const = 0;

  // Use.  
public:
  // Called at the start of each time step.
  virtual bool match (const Daisy&, Treelog&) = 0;
  // Called at the end of each time step.
  virtual void done ();

  // Normal items.
public:
  struct Open
  {
  private:
    Log& ll;
  public:
    Open (Log& l, const string& name)
      : ll (l)
    { ll.open (name); }
    ~Open ()
    { ll.close (); }
  };
private:
  virtual void open (const string&) = 0;
  virtual void close () = 0;
  friend struct Log::Open;

public:

  // Backward compatible lists.
public:
  struct Unnamed
  {
  private:
    Log& ll;
  public:
    Unnamed (Log& l)
      : ll (l)
    { ll.open_unnamed (); }
    ~Unnamed ()
    { ll.close_unnamed (); }
  };
private:
  virtual void open_unnamed () = 0;
  virtual void close_unnamed () = 0;
  friend struct Log::Unnamed;
  
  // Named lists.
public:
  struct Named
  {
  private:
    Log& ll;
  public:
    Named (Log& l, const string& name)
      : ll (l)
    { ll.open_named (name); }
    ~Named ()
    { ll.close_named (); }
  };
private:
  virtual void open_named (const string& name);
  virtual void close_named ();
  friend struct Log::Named;

  // Ordered lists.
public:
  struct Ordered
  {
  private:
    Log& ll;
  public:
    Ordered (Log& l, int index)
      : ll (l)
    { ll.open_ordered (index); }
    ~Ordered ()
    { ll.close_ordered (); }
  };
private:
  virtual void open_ordered (int index);
  virtual void close_ordered ();
  friend struct Log::Ordered;

  // AList singletons variant.
public:
  struct AList
  {
  private:
    Log& ll;
  public:
    AList (Log& l, const string& name, const AttributeList& alist)
      : ll (l)
    { ll.open_alist (name, alist); }
    ~AList ()
    { ll.close_alist (); }
  };
private:
  virtual void open_alist (const string& name, const AttributeList& alist);
  virtual void close_alist ();
  friend struct Log::AList;

  // Derived objects.
public:
  struct Derived
  {
  private:
    Log& ll;
  public:
    Derived (Log& l, const string& field, const string& type)
      : ll (l)
    { ll.open_derived (field, type); }
    ~Derived ()
    { ll.close_derived (); }
  };
private:
  virtual void open_derived (const string& field, const string& type) = 0;
  virtual void close_derived () = 0;
  friend struct Log::Derived;

  // Derived objects in a variable length list.
public:
  struct Entry
  {
  private:
    Log& ll;
  public:
    Entry (Log& l, const string& type, 
	   const AttributeList& alist)
      : ll (l)
    { ll.open_entry (type, alist); }
    ~Entry ()
    { ll.close_entry (); }
  };
private:
  virtual void open_entry (const string& type, const AttributeList&) = 0;
  virtual void close_entry () = 0;
  friend struct Log::Entry;

  // Named derived objects in a variable length list.
public:
  struct NamedEntry
  {
  private:
    Log& ll;
  public:
    NamedEntry (Log& l, const string& name, const string& type, 
		const AttributeList& alist)
      : ll (l)
    { ll.open_named_entry (name, type, alist); }
    ~NamedEntry ()
    { ll.close_named_entry (); }
  };
private:
  virtual void open_named_entry (const string& name, const string& type,
				 const AttributeList&) = 0;
  virtual void close_named_entry () = 0;
  friend struct Log::NamedEntry;

  // The data.
public:
  virtual void output (const string&, const Time&) = 0;
  virtual void output (const string&, const bool) = 0;
  virtual void output (const string&, const double) = 0;
  virtual void output (const string&, const int) = 0;
  virtual void output (const string&, const string&) = 0;
  virtual void output (const string&, const vector<double>&) = 0;
  virtual void output (const string&, const PLF&) = 0;

  // Keep track of geometry for logging arrays.
public:
  struct Geo
  {
  private:
    Log& ll;
  public:
    Geo (Log& l, const Geometry& geo)
      : ll (l)
    { ll.open_geometry (geo); }
    ~Geo ()
    { ll.close_geometry (); }
  };
private:
  void open_geometry (const Geometry&);
  void close_geometry ();
  friend struct Log::Geo;
public:
  const Geometry* geometry ();

  // Utilities
public:
  static void print_dlf_header (ostream& out, const AttributeList& al);

  // Create and Destroy.
public:
  virtual bool check (const Syntax&, Treelog& err) const = 0;
protected:
  Log (const AttributeList& al);
public:
  virtual ~Log ();
};

EMPTY_TEMPLATE
Librarian<Log>::Content* Librarian<Log>::content;

static Librarian<Log> Log_init ("log");

// Output an alist.
template <class T> void
output_submodule (const T& submodule, 
		  const char* name, Log& log)
{
  if (log.check_member (name))
    {
      Log::Open open (log, name);
      submodule.output (log);
    }
}

// Output an object.
template <class T> void
output_derived (const T& submodule, const char* name, Log& log)
{
  const Library& library = Librarian<T>::library ();

  if (log.check_derived (name, submodule.name, library))
    {
      Log::Derived derived (log, name, submodule.name);
      submodule.output (log);
    }
}

// Output a list of objects.
template <class T> void
output_list (T const& items, const char* name, Log& log, 
	     const Library& library)
{
  if (log.check_member (name))
    {
      Log::Open open (log, name);
      for (typename T::const_iterator item = items.begin(); 
	   item != items.end();
	   item++)
	{
	  if (log.check_entry ((*item)->name, library))
	    {
	      Log::Entry entry (log, (*item)->name, (*item)->alist);
	      (*item)->output (log);
	    }
	}
    }
}

// Output a list of named alists.
template <class T> void
output_named (T const& items, const char* name, Log& log)
{
  if (log.check_member (name))
    {
      Log::Open open (log, name);
      for (typename T::const_iterator item = items.begin ();
	   item != items.end ();
	   item++)
	{
	  Log::Named named (log, (*item)->name);
	  (*item)->output (log);
	}
    }
}

// Output an ordered list of alists.
template <class T> void
output_ordered (T const& items, const char* name, Log& log)
{
  if (log.check_member (name))
    {
      Log::Open open (log, name);
      int i = 0;
      for (typename T::const_iterator item = items.begin ();
	   item != items.end ();
	   item++)
	{
	  Log::Ordered ordered (log, i);
	  (*item)->output (log);
	  i++;
	}
    }
}

// Output a list of unnamed and unordered alists.
template <class T> void
output_vector (T const& items, const char* name, Log& log)
{
  if (log.check_member (name))
    {
      Log::Open open (log, name);
      for (typename T::const_iterator item = items.begin ();
	   item != items.end ();
	   item++)
	{
	  Log::Unnamed unnamed (log);
	  (*item)->output (log);
	}
    }
}

#endif // LOG_H
