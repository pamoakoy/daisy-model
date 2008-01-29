// condition.h -- Logic expressions

#ifndef CONDITION_H
#define CONDITION_H

#include "librarian.h"

class Daisy;

class Condition
{  
  // Content.
public:
  static const char *const description;

  // Simulation.
public:
  virtual bool match (const Daisy&) const = 0;

  // Create & Destroy.
protected:
  Condition ();
public:
  virtual ~Condition ();
};

static Librarian<Condition> Condition_init ("condition");

#endif CONDITION_H