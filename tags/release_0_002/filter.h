// filter.h

#ifndef FILTER_H
#define FILTER_H

#include "librarian.h"

class Geometry;

class Filter
{
  // Use.
public:
  virtual bool check (string, bool log_only = false) const = 0;
  virtual Filter& lookup (string) const = 0;
  virtual const vector<double> select (const Geometry&,
				       const vector<double>&);
  virtual void accumulate (const Geometry&,
			   const vector<double>&);
  virtual bool accumulating () const;
  // Create and Destroy.
public:
  virtual bool check (const Library&, int size) const;
  virtual bool check (const Syntax&, int size) const;
  virtual bool check (Syntax::type, int size) const;
  virtual ~Filter ();
protected:
  Filter ();
};

static Librarian<Filter> Filter_init ("filter");

#endif FILTER_H