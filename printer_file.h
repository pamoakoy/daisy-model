// printer_file.h -- Print alist in ParserFile format.
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


#ifndef PRINTER_FILE_H
#define PRINTER_FILE_H

#include "printer.h"
#include "symbol.h"
#include <iosfwd>
#include <memory>

class PrinterFile : public Printer
{
  // Content.
private:
  struct Implementation;
  std::auto_ptr<Implementation> impl;

  // Interface.
public:
  // Print comment.
  void print_comment (const std::string& comment);
  // Print content of alist.
  void print_alist (const AttributeList& alist, const Syntax& syntax,
		    const AttributeList& super_alist, 
                    const Syntax& super_syntax);
  // Print entry in alist.
  void print_entry (const AttributeList&, const Syntax&,
		    const std::string& key);
  // Print specific parameterization.
  void print_parameterization (symbol library_name, symbol name, 
                               bool print_description = true);
  // Print all elements in all libraries associated with 'filename'.
  void print_library_file (const std::string& filename);
  // Print a parser input.
  void print_input (const AttributeList& alist);

  // True iff no errors have occured.
  bool good ();

  // Utitlites.
  static void print_string (std::ostream& out, const std::string& value);

 // Create and Destroy.
public:
  PrinterFile (Block& al);
  PrinterFile (const Metalib&, const std::string& filename);
  PrinterFile (const Metalib&, std::ostream& out);
  ~PrinterFile ();
};

#endif // PRINTER_FILE_H
