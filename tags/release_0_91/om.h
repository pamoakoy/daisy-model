// om.h

#ifndef OM_H
#define OM_H

#include "common.h"
#include <vector>

class AttributeList;
class Syntax;
class Log;
class Geometry;

class OM
{ 
  // Parameters
public:
  static const double Unspecified;// No initial fraction specified.
  const double initial_fraction; // Relative fraction for this om.
  const double initial_C_per_N;	// Initial value for C/N.

  // Content.
public:
  double top_C;			// Carbon on the ground.
  double top_N;			// Nitrogen on the ground;
  vector<double> C;		// Carbon in each node.
  vector<double> C_per_N;	// Ratio of carbon per nitrogen.
  const double turnover_rate;	// How fast this is it turned over?
  const vector <double> efficiency;	// How digestible is this?
  const double maintenance;	// How fast does it eat itself?
  const vector<double> fractions;	// How much is turned into SMB and SOM?
private:
  vector<double> get_N () const;
  void set_N (vector<double>&);

  // Simulation.
public:
  void output (Log&) const;
  void mix (const Geometry&, double from, double to, double penetration = 1.0);
  void distribute (const Geometry&, const vector<double>& density);
  void swap (const Geometry&, double from, double middle, double to);
  double total_C (const Geometry& geometry) const;
  double total_N (const Geometry& geometry) const;
  void pour (vector<double>& cc, vector<double>& nn);
  void add (double C, double N);// Add dead leafs.
  void add (const Geometry&,	// Add dead roots.
	    double C, /* Fixed C/N */
	    const vector<double>& density);
  void add (const Geometry&,	// Add dead roots.
	    double C, double N, 
	    const vector<double>& density);


public:
  void tick (unsigned int size, const double* turnover_factor, 
	     const double* N_soil, double* N_used,
	     double* CO2, const vector<OM*>& smb, const vector<OM*>&som);
  void tick (unsigned int size, const double* turnover_factor,
	     const double* N_soil, double* N_used,
	     double* CO2, const vector<OM*>& smb, 
	     double* som_C, double* som_N);
private:
  void tock (unsigned int size, const double* rate,
	     double factor, double efficiency, 
	     const double* N_soil, double* N_used,
	     double* CO2, OM& om);
  // Create & Destroy.
public:
  static void load_syntax (Syntax&, AttributeList&);
  OM (const AttributeList& al);
};

#endif OM_H