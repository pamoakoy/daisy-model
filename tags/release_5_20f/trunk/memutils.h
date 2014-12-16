// memutils.h -- Utilities for memory management.
// 
// Copyright 2005 Per Abrahamsen and KVL.
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

#ifndef MEMUTILS_H
#define MEMUTILS_H

#include <vector>
#include <map>

template <class ForwardIterator> // From Mumit's STL newbie guide.
void sequence_delete (ForwardIterator first, ForwardIterator last) {
  while (first != last)
    delete *first++;
}

template <class ForwardIterator>
void map_delete (ForwardIterator first, ForwardIterator last) 
{
  while (first != last)
    {
      delete (*first).second;
      (*first).second = 0;
      first++;
    }
}

template <class T>
struct auto_vector : public std::vector<T>
{
  auto_vector (const std::vector<T>& t)
    : std::vector<T> (t)
  { }
  auto_vector ()
    : std::vector<T> ()
  { }
  ~auto_vector ()
  { sequence_delete (this->begin (), this->end ()); }
};

template <class S, class T>
struct auto_map : public std::map<S, T>
{
  auto_map (const std::map<S, T>& m)
    : std::map<S, T> (m)
  { }
  auto_map ()
    : std::map<S, T> ()
  { }
  ~auto_map ()
  { map_delete (this->begin (), this->end ()); }
};

#endif // MEMUTILS_H
