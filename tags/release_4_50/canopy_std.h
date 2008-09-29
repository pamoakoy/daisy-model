// canopy_std.h -- Canopy development for standard crop model.
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


#include "canopy_simple.h"
#include <vector>

class CanopyStandard : public CanopySimple
{
  // Paramaters.
private:
  const double SpLAI;		// Specific leaf weight [ (m^2/m^2) / (g/m^2) ]
  const PLF& LeafAIMod;		// Specific leaf area index modifier
  const double SpSOrgAI;	// Specific storage organ area index
  const PLF& SOrgAIMod;		// Specific storage organ area index modifier
  const double SOrgPhotEff;	// Relative photosynt. effiency of stor. org.
  const double SpStemAI;	// Specific stem area index
  const PLF& StemAIMod;		// Specific stem area index modifier
  const double StemPhotEff;	// Relative photosynthetic effiency of stem.
  const PLF& HvsDS;		// Crop height as function of DS
  const PLF& HvsWStem;		// Relative Crop height as fun. of stem weight
  const std::vector<double>& LAIDist0; // Relative CAI distribution at DS=0
  const std::vector<double>& LAIDist1; // Relative CAI distribution at DS=1
  const double PARrel;		// Relative PAR below the canopy

  // Variables.
private:
  double Offset;		// Extra height after harvest [cm]
  double LeafAI;		// Leaf Area Index
  double StemAI;		// Stem Area Index
  double SOrgAI;		// Storage organ Area Index
  double LADm;			// Max Leaf Area Density [cm^2/cm^3]
  double ForcedCAI;		// CAI forced upon us from vegetation module.
public:
  double SimCAI;		// CAI simulated by default crop model.
  double CAImRat;		// (CAIm - CAI) / CAIm []

  // Functions.
public:
  double specific_LAI (double DS);
  double CropHeight (double WStem, double DS) const;
  double DS_at_height (double height) const;
public:
  void CropCAI (double WLeaf, double WSOrg, double WStem, double DS);
  double corresponding_WLeaf (const double DS) const;
  void CanopyStructure (double DS);

  // Simulation.
public:
  void cut (double WStem, double DS, double stub_length);
  void tick (double WLeaf, double WSOrg, double WStem, double DS, 
	     double CAI_force);
  void output (Log&) const;

  // Create and Destroy.
public:
  static void load_syntax (Syntax& syntax, AttributeList& alist);
  CanopyStandard (const AttributeList&);
  ~CanopyStandard ();
};
