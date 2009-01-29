// timestep.h -- Time difference.
// 
// Copyright 2006 Per Abrahamsen and KVL.
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

#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "time.h"
#include "vcheck.h"
#include <string>
#include <memory>

class Frame;
class AttributeList;
class Syntax;
class Block;

class Timestep
{
  // Content.
private:
  struct Implementation;
  const std::auto_ptr<Implementation> impl;

  // Prebuild values.
public:
  static const Timestep& year ();
  static const Timestep& day ();
  static const Timestep& hour ();
  static const Timestep& minute ();
  static const Timestep& second ();

  // Extract elements.
public:
  int years () const;
  int days () const;
  int hours () const;
  int minutes () const;
  int seconds () const;

  // Extract totals.
public:
  double total_hours () const;
    
  // Create.
public:
  struct GenCheck : public VCheck
  {
  private:
    virtual void check_dt (double dt) const throw (std::string) = 0;
    void check (Metalib&, const Frame& frame, const symbol key)
      const throw (std::string);
  };
  static const VCheck& positive ();
  static const VCheck& non_zero ();
  static void load_syntax (Frame&);
  static void load_frame (Frame&);
  static const Timestep& null ();
  explicit Timestep (Block&);
  Timestep (int years, int days, int hours, int minutes, int seconds);
  ~Timestep ();
  Timestep (const Timestep&);
private:                    
  explicit Timestep ();
  explicit Timestep (const AttributeList&);
  const Timestep& operator= (const Timestep&);
};

// Time operations.
void operator+= (Time&, const Timestep&);

Time operator+ (const Time&, const Timestep&);
Time operator- (const Time&, const Timestep&);

Timestep operator- (const Timestep& step);
Timestep operator- (const Time&, const Time&);
Timestep operator+ (const Timestep&, const Timestep&);
bool operator== (const Timestep&, const Timestep&);

#endif // TIMESTEP_H
