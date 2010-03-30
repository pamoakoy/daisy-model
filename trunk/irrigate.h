// irrigate.h --- Manage irrigation events.
// 
// Copyright 2010 KU.
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


#ifndef IRRIGATE_H
#define IRRIGATE_H

#include "timestep.h"
#include "memutils.h"
#include "symbol.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

class Solute;
class Volume;
class BlockSubmodel;

class Irrigation : private boost::noncopyable
{
  // Content.
  enum target_t { overhead, surface, subsoil };
  struct Event : private boost::noncopyable
  {
    // Content.
    Timestep time_left;
    const double flux;
    const boost::shared_ptr<Solute> solute;
    const target_t target;
    static target_t symbol2target (symbol s);
    const boost::shared_ptr<Volume> volume;
    
    // Create and Destroy.
    static void load_syntax (Frame&);
    explicit Event (const BlockSubmodel&);
  };
  auto_vector<Event*> events;

  // Create and Destroy.
  static void load_syntax (Frame&);
public:
  Irrigation (const BlockSubmodel&);
};

#endif // IRRIGATE_H
