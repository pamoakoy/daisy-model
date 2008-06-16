// surface.h

#include "uzmodel.h"

struct IM;
struct AttributeList;
struct Log;
struct SoilWater;
struct Soil;
struct Chemicals;
struct SoilChemicals;

class Surface : public UZtop
{
  struct Implementation;
  Implementation& impl;

public:

  // Communication with soil.
  bool flux_top () const;	// From UZtop.
  double q () const;
  void flux_top_on () const;
  void flux_top_off () const;
  bool accept_top (double);
  bool soil_top () const;
  double ponding () const;
  double temperature () const;
  int last_node () const;

  const IM& matter_flux ();
  const Chemicals&  chemicals_down () const;

  void mixture (const IM& soil_im /* g/cm^2/mm */,
		const SoilChemicals& soil_chemicals);
  void update_water (const Soil&, const vector<double>& S_,
		     vector<double>& h_, vector<double>& Theta_,
		     vector<double>& q, const vector<double>& q_p);

  // Manager.
  void fertilize (const IM&);
  void spray (const Chemicals& chemicals_in);
  void set_detention_capacity (double);
  void ridge (const Soil& soil, const SoilWater& soil_water,
	      const AttributeList&);
  void unridge ();

  // Simulation.
  void output (Log&) const;
  void tick (double PotSoilEvaporation, double Water, double temp,
	     const Soil&, const SoilWater&);

  // Communication with bioclimate.
  double EpFactor () const;
  double EpInterchange () const;
  double albedo (const Soil& soil, const SoilWater& soil_water) const;
  double exfiltration () const; // [mm/h]
  double evap_soil_surface () const; // [mm/h]
  double evap_pond () const; // [mm/h]

  // Communication with external model.
  void put_ponding (double pond);	// [mm]
  void put_no3 (double no3); // [g/cm^2]
  double get_no3 () const; // [g/cm^2]
  void put_chemical (const string&, double); // [g/cm^2]
  double get_chemical (const string&) const; // [g/cm^2]

  // Create.
  static void load_syntax (Syntax&, AttributeList&);
  Surface (const AttributeList& par);
  ~Surface ();
};
