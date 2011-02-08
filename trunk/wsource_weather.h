// wsource_weather.h
// 
// Copyright 2011 KU.
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


#ifndef WSOURCE_WEATHER_H
#define WSOURCE_WEATHER_H

#include "wsource.h"
#include "weatherdata.h"
#include <boost/scoped_ptr.hpp>

class IM;

class WSourceWeather : public WSource
{
  class Implementation;
  const boost::scoped_ptr<Implementation> impl;

  // Location.
public:
  double latitude () const;
  double longitude () const; 
  double elevation () const; // [m]
  double timezone () const;
  double screen_height () const; // [m]
  Weatherdata::surface_t surface () const;

  // Simulation.
protected:
  void output_common (Log& log) const;
public:
  double suggest_dt () const;   // [h]
  void weather_tick (const Time& time, Treelog&);
  void output (Log&) const;

  // Communication with Bioclimate.
public:
  double air_temperature () const; // [dg C]
  double daily_air_temperature () const; // [dg C]
  double daily_max_air_temperature () const; // [dg C]
  double daily_min_air_temperature () const; // [dg C]
  double global_radiation () const; // [W/m2]
  double daily_global_radiation () const; // [W/m2]
  double diffuse_radiation () const; // [W/m2]
  double reference_evapotranspiration () const; // [mm/h]
  double daily_precipitation () const; // [mm/d]
  double rain () const;	// [mm/h]
  double snow () const;	// [mm/h]
  const IM& deposit () const; // [g [stuff] /cm�/h]
  double cloudiness () const; // [0-1]
  double vapor_pressure () const; // [Pa]
  double wind () const;	// [m/s]
  double CO2 () const; //[Pa]
  double O2 () const; //[Pa]
  double air_pressure () const; //[Pa]

  // Initializing bioclimate.
public:
  bool has_reference_evapotranspiration () const;
  bool has_vapor_pressure () const;
  bool has_wind () const;
  bool has_min_max_temperature () const;
  bool has_diffuse_radiation () const;
  double timestep () const; // [d]

  // Light distribution.
public:
  double day_length () const; // [h]

  // Communication with SoilHeat.
public:
  double T_normal (const Time&, double delay = 0.0) const;

  // OrganicMatter initialization.
public:
  double average_temperature () const;

  // Astronomic utilities.
public:
  double extraterrestrial_radiation (const Time&) const; // [W/m2]
  double sin_solar_elevation_angle (const Time&) const; // []
protected:
  double relative_extraterestial_radiation (const Time&) const; // []
  double day_length (const Time&) const; // [h]

  // Create and Destroy.
public:
  static void load_common (Frame& frame);
  bool weather_initialize (const Time& time, Treelog& msg);
protected:
  WSourceWeather (const BlockModel&);
public:
  bool weather_check (const Time& from, const Time& to, Treelog&) const;
  ~WSourceWeather ();
};

#endif // WSOURCE_WEATHER_H
