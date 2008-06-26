// pedo.h --- Pedotransfer functions based on soil attributes.
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


#ifndef PEDOTRANSFER_H
#define PEDOTRANSFER_H

#include "model.h"
#include "symbol.h"
#include <vector>

class Soil;
class Treelog;
class Block;

class Pedotransfer : public Model
{
  // Content.
public:
  static const char *const component;
  const symbol name;

  // Simulation.
public:
  void set (const Soil&, std::vector<double>&, const std::string& dim ) const;
  virtual double value (const Soil&, int i) const = 0; 
  virtual const std::string& dimension () const = 0;

  // Utilities.
public:
  static bool known (const std::string& dim);
  static void debug_message (const std::string& name, 
                             const std::vector<double>& value,  
                             const std::string& dim, 
                             Treelog& msg);

  // Create and Destroy.
public:
  bool check (const Soil&, const std::string& dim,
              Treelog& err) const;
  virtual bool check_nested (const Soil&, Treelog& err) const = 0;
  Pedotransfer (Block&);
  ~Pedotransfer ();
};

#endif // PEDOTRANSFER_H