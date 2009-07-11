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


#ifndef LOG_ALIST_H
#define LOG_ALIST_H

#include "log.h"
#include <deque>
#include <boost/shared_ptr.hpp>

class Library;
class Frame;

struct LogSubmodel : public Log
{
  // Filter functions.
  bool check_entry (symbol, const char* component) const;
  bool check_derived (symbol, symbol, const char* component) const;

  // Content.
  bool is_active;		// ... store the answer here.
  unsigned int nested;		// Nesting iff active.

  // Name of the entity we are logging.
  std::deque<symbol> entry_stack; 
  // Library of the object we are logging.
  std::deque<const Library*> library_stack; 
  // State and parameters of entity.
  std::deque<Frame*> frame_stack; 
  // Ditto for lists.
  std::deque<std::vector<const Frame*>/**/> frame_sequence_stack; 
  // Current element of Frame sequence.
  std::deque<int> unnamed_stack;

  // Stack Accessors.
  symbol entry () const;
  const Library& library () const;
  Frame& frame_entry () const;
  std::vector<const Frame*>& frame_sequence ();
  int unnamed ();

  // Stack Constructors.
  void push (symbol entry, 
	     const Library& library, const Frame& frame);
  void push (symbol entry, const Frame& frame);
  void push (symbol entry, const Frame& default_frame,
	     std::vector<boost::shared_ptr<const FrameModel>/**/> frame_sequence);
  void push (symbol entry, const Frame& default_frame,
	     std::vector<boost::shared_ptr<const FrameSubmodel>/**/> frame_sequence);
  void pop ();

  // Nesting.
  void open_ignore ();		// Ignored items.
  void close_ignore ();
  void open (symbol name); // Submodel singletons. 
  void close ();
  void open_unnamed ();		// Items in a Submodel sequence.
  void close_unnamed ();	
  void open_alist (symbol name, // Submodel singletons variant.
		   const Frame& frame);
  void close_alist ();

  void open_derived (symbol field, // Model singletons.
		     symbol type, const char* library); 
  void close_derived ();
  void open_object (symbol field, // Model singletons with alist.
		    symbol type, const Frame&, const char* library); 
  void close_object ();
  void open_entry (symbol type,   // Items in an Model sequence.
		   const Frame& frame, const char *const library);
  void close_entry ();
  void open_named_entry (symbol name,   // Named items in an Obj seq.
			 symbol type, 
			 const Frame& frame);
  void close_named_entry ();

  // Logging.
  void output_entry (symbol name, bool value);
  void output_entry (symbol name, double value);
  void output_entry (symbol name, int value);
  void output_entry (symbol name, symbol value);
  void output_entry (symbol name, const std::vector<double>& value);
  void output_entry (symbol name, const PLF& value);

  // Create and Destroy.
  bool check (const Border&, Treelog& err) const;
  LogSubmodel (const Block&);
  ~LogSubmodel ();
};

#endif // LOG_ALIST_H
