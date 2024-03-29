// hydraulic_B_C.C -- Campbell retention curve model with Burdine theory.
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

#define BUILD_DLL
#include "hydraulic.h"
#include "block_model.h"
#include "check.h"
#include "mathlib.h"
#include "librarian.h"
#include "frame.h"

class HydraulicB_C : public Hydraulic
{
  // Content.
  const double h_b;
  const double b;
  const double l;

  // Use.
public:
  double Theta (double h) const;
  double K (double h) const;
  double Cw2 (double h) const;
  double h (double Theta) const;
  double M (double h) const;
private:
  double Sr (double h) const;
  
  // Create and Destroy.
public:
  HydraulicB_C (const BlockModel&);
  ~HydraulicB_C ();
};

double 
HydraulicB_C::Theta (const double h) const
{
  return Sr (h) * Theta_sat;
}

double 
HydraulicB_C::K (const double h) const
{
  return K_sat * pow (Sr (h), 2 * b + 1 + l);
}

double 
HydraulicB_C::Cw2 (const double h) const
{
  if (h < h_b)
    return -(Theta_sat*(pow(h_b / h, 1 / b - 1)*h_b) / (pow(h, 2)*b));
  else
    return 0.0;
}

double 
HydraulicB_C::h (const double Theta) const
{
  if (Theta < Theta_sat)
    return h_b / pow(Theta / Theta_sat, b);
  else
    return h_b;
}

double 
HydraulicB_C::M (double h) const
{
  if (h <= h_b)
    return K_sat * (-h_b / (1.0 + (1.0 + l) / b)) * pow (h_b / h, 1.0 + (1.0 + l) / b);
  else
    return M (h_b) + K_sat * (h - h_b);
}

double 
HydraulicB_C::Sr (double h) const
{
  if (h < h_b)
    return pow (h_b / h, 1.0 / b);
  else
    return 1;
}

HydraulicB_C::HydraulicB_C (const BlockModel& al)
  : Hydraulic (al),
    h_b (al.number ("h_b")),
    b (al.number ("b")),
    l (al.number ("l"))
{ }

HydraulicB_C::~HydraulicB_C ()
{ }

// Add the HydraulicB_C syntax to the syntax table.

static struct HydraulicB_CSyntax : public DeclareModel
{
  Model* make (const BlockModel& al) const
    {
      return new HydraulicB_C (al);
    }

  HydraulicB_CSyntax ()
    : DeclareModel (Hydraulic::component, "B_C", 
		 "Campbell retention curve model with Burdine theory.")
  { }
  void load_frame (Frame& frame) const
    { 
      frame.set_strings ("cite", "campbell1974simple", "burdine1953");
      Hydraulic::load_Theta_sat (frame);
      Hydraulic::load_K_sat (frame);
      frame.declare ("h_b", "cm", Check::negative (), Attribute::Const,
		  "Bubbling pressure.");
      frame.declare ("b", Attribute::None (), Check::positive (), Attribute::Const,
		  "Campbell parameter.");
    frame.declare ("l", Attribute::None (), Check::none (), Attribute::Const,
                   "Burdine form parameter.");
    frame.set ("l", 2.0);

    }
} hydraulicB_C_syntax;

