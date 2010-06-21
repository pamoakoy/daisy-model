// iterative.h -- Generic iterative root finding algorithms.
// 
// Copyright 2007 Per Abrahamsen and KVL.
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

#ifndef ITERATIVE_H
#define ITERATIVE_H

#include <cmath>
#include <iostream>
#include <boost/noncopyable.hpp>
#include <vector>

class Treelog;

template<class T>
double
bisection (double min_x, double max_x, T& f, std::ostream *const dbg = NULL)
{
  // Initial range.
  double min_y = f (min_x);
  double max_y = f (max_x);

  // Iteration loop.
  double old_width = max_x - min_x;

  for (size_t iteration = 1; true; iteration++)
    {
      // New guess.
      const double x = (min_x + max_x) / 2.0;
      const double y = f (x);
      
      if (dbg)
	*dbg << iteration << ": [" << min_x << ";" << max_x << "] "
	     << "f (" << x << ") = " << y << "\n";

      // Does the new value have the same sign as the lower border?
      if (min_y * y > 0)
        {
          // Then we use it as the new lower border.
          min_x = x;
          min_y = y;
        }
      else
        {
          // Otherwise, we use it as upper border.
          max_x = x;
          max_y = y;
        }

      // Check it interval became more narrow.
      const double new_width = max_x - min_x;
      if (new_width >= old_width)
        // If not, this is our result.
        return x;
      old_width = new_width;
    }
}

template<class F, class D>
double // GCC 4.4 don't like D being a reference when called with a function.
Newton (double guess, F& f, D d, std::ostream *const dbg = NULL)
{
  // Value for initial guess.
  double value = f (guess);
  double abs_value = fabs (value);
  
  for (size_t iteration = 0; true; iteration++)
    {
      // Find new guess.
      const double slope = d (guess);
      const double new_guess = guess - value / slope;
      const double new_value = f (new_guess);
      const double new_abs_value = fabs (new_value);
      
      if (dbg)
	*dbg << iteration << ": f (" << guess  << ") = " << value << "; "
	     << "d (" << guess << ") = " << slope << "; "
	     << "next guess " << new_guess << "\n";

      // Was it an improvement?
      if (!(new_abs_value < abs_value))
	// If not, use last guess.
	return guess;

      // Use new guess for next iteration.
      guess = new_guess;
      value = new_value;
      abs_value = new_abs_value;
    }
}

// The Fixpoint class will find a fixpoint of an multivariable (or
// vector) function.  To use it, create a subclass that provides the
// following three functions: 'initial_guess' for the initial guess;
// 'f' for the function itself; and finaly 'max_distance' for the
// convergence criteria.
// 
// The class define the distance between two values as the Euclidian
// distance between two vectors created by dividing each parameter in
// each value by the corresponding max_distance component.  
//
// A fixpoint will be found if the function always point in the right
// direction (right hemisphere) in this vector space.

struct Fixpoint : boost::noncopyable
{
  // Our value type.
  typedef std::vector<double> Value;

  // Paramaters.
  const int max_iteration;

  // Our initial guess for a solution.
  virtual Value initial_guess () const = 0;

  // The function we want to find a fixpoint for.
  virtual Value f (const Value& x, Treelog& msg) = 0;
  
  // Distance
  double find_epsilon () const;
  virtual const Value& max_distance () const = 0;
  double diff (const Value& A, const Value& B) const;
  Value average (const Value& A, const Value& B) const;

  // Solve
  Value solve (Treelog&);

  Fixpoint (const int max_iter);
  virtual ~Fixpoint ();
};

#endif // ITERATIVE_H
