// uzmodel.h

#ifndef UZMODEL_H
#define UZMODEL_H

#include "librarian.h"

class Soil;
class Library;
class Syntax;
class AttributeList;
class Log;

class UZtop
{
public:
  virtual bool flux_top () const = 0;
  virtual double q () const = 0;
  double h () const
  { return -q () * dt; }
  virtual void flux_top_on () const = 0;
  virtual void flux_top_off () const = 0;
  virtual bool accept_top (double) = 0;
  virtual bool soil_top () const;
  virtual ~UZtop ();
};

class UZbottom
{
public:
  virtual bool flux_bottom () const = 0;
  virtual bool accept_bottom (double) = 0;
  virtual bool is_lysimeter () const;
  virtual ~UZbottom ();
};

class UZmodel : public UZtop, public UZbottom
{
  // Content.
public: 
  const string name;
  static const char *const description;

  // UZtop.
public:
  bool flux_top () const = 0;
  double q () const = 0;
  void flux_top_on () const = 0;
  void flux_top_off () const = 0;
  bool accept_top (double) = 0;

  // UZbottom.
public:
  bool flux_bottom () const = 0;
  bool accept_bottom (double) = 0;
  
  // Simulate.
public:
  virtual bool tick (const Soil& soil,
		     unsigned int first, const UZtop& top, 
		     unsigned int last, const UZbottom& bottom, 
		     const vector<double>& S,
		     const vector<double>& h_old,
		     const vector<double>& Theta_old,
		     const vector<double>& h_ice,
		     vector<double>& h,
		     vector<double>& Theta,
		     vector<double>& q) = 0;
  virtual void output (Log&) const = 0;

  // Create and Destroy.
public:
  virtual void has_macropores (bool); // Tell UZ that there is macropores.
protected:
  UZmodel (string name);
public:
  virtual ~UZmodel ();
};

static Librarian<UZmodel> UZmodel_init ("uzmodel");

#endif UZMODEL_H
