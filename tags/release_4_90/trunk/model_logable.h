// model_logable.h -- Base class for logable models in Daisy.
// 
// Copyright 2007, 2009 Per Abrahamsen and KVL.
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


#ifndef MODEL_LOGABLE_H
#define MODEL_LOGABLE_H

#include "model.h"
#include "symbol.h"

class Log;

// 'ModelLogable' is the base class for all logable models.
class ModelLogable : public Model
{
  // Content.
public:
  const symbol name;            // Remember name for logs.
  virtual symbol library_id () const = 0;

  // Use.
public:
  virtual void output (Log& log) const = 0;

  // Create and Destroy.
protected:
  ModelLogable (symbol);
};

#endif // MODEL_LOGABLE_H
