// librarian.h
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


#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "library.h"
#include "block.h"
#include "alist.h"
#include "syntax.h"
#include "treelog.h"
#include "assertion.h"
#include <map>
#include <vector>

class Log;

template <class T>
class Librarian
{
  // Types.
private:
  typedef T& (*constructor) (const AttributeList&);
  typedef std::map<symbol, constructor> cmap_type;
  typedef T& (*builder) (Block&);
  typedef std::map<symbol, builder> bmap_type;

  // Content.
private:
  struct Content;
  friend struct Librarian::Content;
  static struct Content
  {
    Library lib;
    cmap_type constructors;
    bmap_type builders;
    int count;
    Content (const char *const name, derive_fun derive, 
	     const char *const description)
      : lib (name, derive, description),
	constructors (),
	builders (),
	count (0)
    { }
  } *content;

  // Functions.
public:
  static T* create (const AttributeList& al)
  {
    daisy_assert (al.check ("type"));
    const symbol name = al.identifier ("type");
    daisy_assert (library ().check (name));
    daisy_assert (library ().syntax (name).check (al, Treelog::null ()));
    daisy_assert (content->constructors.find (name) 
		  != content->constructors.end ());
    return &(content->constructors)[name] (al);
  }

  static T* build_free (Treelog& msg, const AttributeList& alist, 
			const std::string& scope_id)
  {
    daisy_assert (alist.check ("type"));
    const symbol type = alist.identifier ("type");
    daisy_assert (library ().check (type));
    const Syntax& syntax = library ().syntax (type);
    Block block (syntax, alist, msg, scope_id + ": " + type.name ());
    daisy_assert (syntax.check (alist, msg));
    daisy_assert (content->builders.find (type) != content->builders.end ());
    try
      {  
	T* result = &(content->builders)[type] (block); 
	daisy_assert (block.ok () && result);
	return result;
      }
    catch (const std::string& err)
      { block.error ("Build failed: " + err); }
    catch (const char *const err)
      { block.error ("Build failed: " + std::string (err)); }
    return NULL;
  }

  static T* build_alist (Block& parent, const AttributeList& alist, 
			 const std::string& scope_id)
  {
    daisy_assert (alist.check ("type"));
    const symbol type = alist.identifier ("type");
    daisy_assert (library ().check (type));
    const Syntax& syntax = library ().syntax (type);
    Block nested (parent, syntax, alist, scope_id + ": " + type.name ());
    daisy_assert (syntax.check (alist, nested.msg ()));
    daisy_assert (content->builders.find (type) != content->builders.end ());
    try
      {  return &(content->builders)[type] (nested); }
    catch (const std::string& err)
      { nested.error ("Build failed: " + err); }
    catch (const char *const err)
      { nested.error ("Build failed: " + std::string (err)); }
    return NULL;
  }

  static T* build_item (Block& parent, const std::string& key)
  { return build_alist (parent, parent.alist (key), key); }

  static std::vector<T*> build_vector (Block& al, const std::string& key)
  { 
    std::vector<T*> t;
    const std::vector<AttributeList*> f (al.alist_sequence (key));
    for (size_t i = 0; i < f.size (); i++)
      t.push_back (build_alist (al, *f[i], sequence_id (key, i)));

    return t;
  }

  static std::vector<const T*> build_vector_const (Block& al,
						   const std::string& key)
  { 
    std::vector<const T*> t;
    const std::vector<AttributeList*> f (al.alist_sequence (key));
    for (size_t i = 0; i < f.size (); i++)
      t.push_back (build_alist (al, *f[i], sequence_id (key, i)));

    return t;
  }

  static void add_base (AttributeList& al, const Syntax& syntax)
  { library ().add_base (al, syntax); }
  static void add_type (const symbol name, AttributeList& al,
			const Syntax& syntax,
			constructor cons)
  {
    library ().add (name, al, syntax);
    content->constructors.insert(std::make_pair (name, cons));
  }
  static void add_type (const symbol name, AttributeList& al,
			const Syntax& syntax,
			builder build)
  {
    library ().add (name, al, syntax);
    content->builders.insert(std::make_pair (name, build));
  }
  static void add_type (const char *const name, AttributeList& al,
			const Syntax& syntax,
			constructor cons)
  { add_type (symbol (name), al, syntax, cons); }
  static void add_type (const char *const name, AttributeList& al,
			const Syntax& syntax,
			builder build)
  { add_type (symbol (name), al, syntax, build); }
  static void derive_type (symbol name, const Syntax& syn, 
			   AttributeList& al, symbol super)
  {
    if (content->constructors.find (super) != content->constructors.end ())
      add_type (name, al, syn, (content->constructors)[super]);
    else
      add_type (name, al, syn, (content->builders)[super]);
  }
  static Library& library ()
  {
    daisy_assert (content);
    return content->lib;
  }

  // Create and Destroy.
public:
  Librarian (const char *const name)
  { 
    if (!content)
      content = new Content (name, &derive_type, T::description);
    content->count++;

  }
  ~Librarian ()
  { 
    daisy_assert (content);
    content->count--;
    if (content->count == 0)
      {
	delete content;
	content = 0;
      }
    else
      daisy_assert (content->count > 0);
  }
};

// This cutie will create a vector of objects from a vector of alists.
template <class T> 
std::vector<T*>
map_create (const std::vector<AttributeList*>& f)
{ 
  std::vector<T*> t;
  for (std::vector<AttributeList*>::const_iterator i = f.begin ();
       i != f.end ();
       i++)
    t.push_back (Librarian<T>::create (**i));
  return t;
}

template <class T> 
std::vector<const T*>
map_create_const (const std::vector<AttributeList*>& f)
{ 
  std::vector<const T*> t;
  for (std::vector<AttributeList*>::const_iterator i = f.begin ();
       i != f.end ();
       i++)
    t.push_back (Librarian<T>::create (**i));
  return t;
}

#endif // LIBRARIAN_H