// document.h --- Create documentation.
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


#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "librarian.h"

class Document
{
  // Content.
public:
  static const char *const description;

  // Typeset parts of it.
protected:
  virtual void print_submodel_entry (ostream&, const string&, int level,
				     const Syntax& syntax,
				     const AttributeList& alist) = 0;
  virtual void print_submodel_empty (ostream&, const string&, int level) = 0;
  virtual void print_submodel_header (ostream&, const string&, int level) = 0;
  virtual void print_submodel_trailer (ostream&, const string&, int level) = 0;
  virtual void print_log_header (ostream&, const string&, int level) = 0;
  virtual void print_log_trailer (ostream&, const string&, int level) = 0;
  virtual void print_sample_ordered (ostream&, const string&, bool seq) = 0;
  virtual void print_sample_entry (ostream&, const string& name, bool seq) = 0;
  virtual void print_sample_header (ostream& out, const string& name) = 0;
  virtual void print_sample_trailer (ostream& out, const string&) = 0;
  virtual void print_model_header (ostream&, const string& name) = 0;
  virtual void print_model_description (ostream&, const string&) = 0;
  virtual void print_model_trailer (ostream&, const string& name) = 0;
  virtual void print_fixed_header (ostream&, const string& name) = 0;
  virtual void print_fixed_trailer (ostream&, const string& name) = 0;
  virtual void print_component_header (ostream&, const string& name) = 0;
  virtual void print_component_description (ostream&, const string&) = 0;
  virtual void print_component_trailer (ostream&, const string& name) = 0;
  virtual void print_fixed_all_header (ostream&) = 0;
  virtual void print_fixed_all_trailer (ostream&) = 0;
  virtual void print_document_header (ostream&) = 0;
  virtual void print_document_trailer (ostream&) = 0;

  // Print parts of it.
protected:
  void print_submodel (ostream& out, const string& name, int level,
		       const Syntax& syntax,
		       const AttributeList& alist);
  void print_sample (ostream& out, const string& name,
		     const Syntax& syntax,
		     const AttributeList& alist);
private:
  void print_model (ostream& out, const string& name, 
		    const Syntax& syntax,
		    const AttributeList& alist);
  void print_fixed (ostream& out, const string& name, 
		    const Syntax& syntax,
		    const AttributeList& alist);
  void print_component (ostream& out, const Library& library);

  // Print it.
public:
  void print_document (ostream& out);

  // Print syntactical sugar.

  // Create and destroy.
public: 
  Document (const AttributeList&);
  virtual ~Document ();
};

static Librarian<Document> Document_init ("document");

#endif // DOCUMENT_H
