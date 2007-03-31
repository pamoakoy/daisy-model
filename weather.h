// weather.h
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


#ifndef WEATHER_H
#define WEATHER_H

#include "model.h"
#include "im.h"
#include "symbol.h"

class Time;
class Treelog;
class Block;

class Weather : public Model
{
  // Content.
public: 
  const symbol name;
  static const char *const component;
  
  // Location.
protected:
  /* const */ double latitude;
  /* const */ double longitude;
  /* const */ double elevation_;
  /* const */ double timezone;
public:
  enum surface_t { reference, field };
protected:
  /* const */ surface_t surface_;
  /* const */ double screen_height_;
public:
  surface_t surface () const 
  { return surface_; }
  double elevation () const; // [m]
  double screen_height () const; // [m]

  // Deposit.
protected:
  /* const */ IM DryDeposit;
  /* const */ IM WetDeposit;

  // Temperature.
protected:
  /* const */ double T_average;
  /* const */ double T_amplitude;
  /* const */ double max_Ta_yday;

  // State
private:
  double day_length_;
  double day_cycle_;
  double hourly_cloudiness_;
  double daily_cloudiness_;
  IM deposit_;

  // Simulation.
public:
  virtual void tick (const Time& time, Treelog&);
  void tick_after (const Time& time, Treelog&);
  virtual void output (Log&) const;

  // Communication with Bioclimate.
public:
  virtual double hourly_air_temperature () const = 0; // [dg C]
  virtual double daily_air_temperature () const = 0; // [dg C]
  virtual double daily_max_air_temperature () const = 0; // [dg C]
  virtual double daily_min_air_temperature () const = 0; // [dg C]
  virtual double hourly_global_radiation () const = 0; // [W/m2]
  virtual double daily_global_radiation () const = 0; // [W/m2]
  virtual double hourly_diffuse_radiation () const = 0; // [W/m2]
  virtual double reference_evapotranspiration () const = 0; // [mm/h]
  virtual double daily_precipitation () const = 0; // [mm/d]
  virtual double rain () const = 0;	// [mm/h]
  virtual double snow () const = 0;	// [mm/h]
  IM deposit () const; // [g [stuff] /cm�/h]
  double hourly_cloudiness () const // [0-1]
    { return hourly_cloudiness_; }
  double daily_cloudiness () const // [0-1]
    { return daily_cloudiness_; }
  virtual double vapor_pressure () const = 0; // [Pa]
  virtual double relative_humidity () const = 0; // []
  virtual double wind () const = 0;	// [m/s]

  // Initializing bioclimate.
public:
  virtual bool has_reference_evapotranspiration () const;
  virtual bool has_vapor_pressure () const;
  virtual bool has_wind () const;
  virtual bool has_min_max_temperature () const;
  virtual bool has_diffuse_radiation () const;
  virtual bool has_relative_humidity () const;

  // Light distribution.
public:
  double day_length () const	// [h]
    { return day_length_; }
  double day_cycle () const	// Sum over a day is 1.0.
    { return day_cycle_; }

public:
  double day_cycle (const Time&) const;	// Sum over a day is 1.0.
private:
  double day_length (const Time&) const;

  // Communication with SoilHeat.
public:
  double T_normal (const Time&, double delay = 0.0) const;

  // OrganicMatter initialization.
public:
  double average_temperature () const;

  // Astronomic utilities.
public:
  static double SolarDeclination (const Time& time); // [rad]
  static double RelativeSunEarthDistance (const Time& time);
  static double SunsetHourAngle (double Dec, double Lat); // [rad]
  double ExtraterrestrialRadiation (const Time& time) const; // [W/m2]
  double HourlyExtraterrestrialRadiation (const Time& time) const; // [W/m2]
  double sin_solar_elevation_angle (const Time& time) const; // []

  // Create and Destroy.
private:
  Weather (const Weather&);
public:
  virtual bool initialize (const Time& time, Treelog& err);
protected:
  Weather (Block&);
public:
  virtual bool check (const Time& from, const Time& to, Treelog& err) const;
  static void load_syntax (Syntax&, AttributeList&);
  ~Weather ();
};

#endif // WEATHER_H
