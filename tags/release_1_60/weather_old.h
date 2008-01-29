// weather_old.h --- Common code for old weather models.

#ifndef WEATHER_OLD_H
#define WEATHER_OLD_H

#include "weather.h"

class WeatherOld : public Weather
{
  // Content.
private:
  struct Implementation;
  Implementation& impl;
  
  // Simulation.
public:
  void tick (const Time& time);
  void output (Log&) const;
protected:
  void distribute (double precipitation);

  // Communication with Bioclimate.
public:
  double hourly_air_temperature () const; // [dg C]
  double hourly_global_radiation () const; // [W/m2]
  double daily_global_radiation () const; // [W/m2]
  double reference_evapotranspiration () const; // [mm/h]
  double rain () const;	// [mm/h]
  double snow () const;	// [mm/h]
  double vapor_pressure () const; // [Pa]
  double wind () const;	// [m/s]

  // Communication with external model.
  void put_precipitation (double prec);// [mm/d]
  void put_air_temperature (double T); // [�C]
  void put_reference_evapotranspiration (double ref); // [mm/d]
  void put_global_radiation (double radiation); // [W/m�]

  // Create and Destroy.
protected:
  WeatherOld (const AttributeList&);
public:
  static void load_syntax (Syntax&, AttributeList&);
  ~WeatherOld ();
};

#endif WEATHER_OLD_H