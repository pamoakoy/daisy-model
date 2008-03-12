// vegetation.h

#ifndef VEGETATION_H
#define VEGETATION_H

#include "librarian.h"
#include <vector>

class Time;
class Bioclimate;
class Geometry;
class Soil;
class OrganicMatter;
class SoilHeat;
class SoilWater;
class SoilNH4;
class SoilNO3;
class PLF;
class Harvest;
class AM;

class Vegetation
{ 
  // Content.
public:
  const string name;
  static const char *const description;

  // Canopy queries.
public:
  virtual double LAI () const = 0; // Total LAI of all crops [0-]
  virtual double height () const = 0; // Max crop height in canopy [cm]
  virtual double cover () const = 0; // Fraction of soil covered by crops [0-1]
  virtual const PLF& LAIvsH () const = 0; // LAI below height [f: cm -> R]
  virtual const PLF& HvsLAI () const = 0; // Height with LAI below [f: R -> cm]
  virtual double ACExt () const = 0;	// Canopy extinction coefficient
  virtual double ACRef () const = 0;	// Canopy reflection coefficient 
  virtual double ARExt () const = 0;	// Radiation Extinction coefficient
  virtual double EpFactor () const = 0;	// Reference to pot. evapotransp
  virtual double albedo () const = 0;	// Another reflection factor
  virtual double interception_capacity () const = 0;// Canopy water cap. [mm]

  // Individual crop queries.
public:
  virtual double DS_by_name (const string& name) const = 0;// [-1:2]/DSremove
  virtual double DM_by_name (const string& name) const = 0;// Shoot DM [kg/ha]

  // Simulation
public:
  virtual void tick (const Time&, const Bioclimate&, const Soil&,
		     OrganicMatter&, const SoilHeat&, const SoilWater&,
		     SoilNH4&, SoilNO3&) = 0; // Allow plants to grow (hourly).
  virtual void tick (const Time&, const Bioclimate&, const Soil&,
		     const SoilHeat&, const SoilWater&) = 0;
  virtual double transpiration (// Actual trans. [mm/h]
				double potential_transpiration,	
				double canopy_evaporation,
				const Soil& soil, SoilWater& soil_water) = 0;
  virtual void force_production_stress  (double pstress);
  virtual void kill_all (const string&, const Time&, const Geometry&,
			 Bioclimate&, vector<AM*>& residuals) = 0;
  virtual void harvest (const string& column_name,
			const string& crop_name,
			const Time&, const Geometry&, 
			Bioclimate& bioclimate,
			double stub_length,
			double stem_harvest,
			double leaf_harvest, 
			double sorg_harvest,
			vector<const Harvest*>& harvest,
			vector<AM*>& residuals) = 0;
  virtual void sow (const AttributeList& al,
		    const Geometry&, OrganicMatter&) = 0;
  virtual void sow (const AttributeList& al,
		    const Geometry&) = 0;
  virtual void output (Log&) const;

  // Create and Destroy.
public:
  virtual void initialize (const Soil& soil, OrganicMatter&) = 0;
  static void load_syntax (Syntax&, AttributeList&);
  Vegetation (const AttributeList&);
  virtual ~Vegetation ();
};

static Librarian<Vegetation> Vegetation_init ("vegetation");

#endif // VEGETATION_H