// traverse_depend.h -- Check dependencies in Daisy datastructures.

#ifndef TRAVERSE_DEPEND_H
#define TRAVERSE_DEPEND_H

#include <string>
#include <set>
#include <map>
using namespace std;

struct Treelog;
struct Syntax;
struct AttributeList;

typedef map<string, set<string>/**/> dep_map;

bool
has_dependencies (const string& component, const string& parameterization);

bool
has_dependencies (const string& component, const string& parameterization, 
		    const Syntax& syntax, AttributeList& alist,
		    const string& name);
bool
check_dependencies (const string& component, const string& parameterization, 
		    Treelog& treelog);

bool
check_dependencies (const string& component, const string& parameterization, 
		    const Syntax& syntax, AttributeList& alist,
		    const string& name, Treelog& treelog);
bool
find_dependencies (const string& component, const string& parameterization, 
		   dep_map& dependencies);


#endif TRAVERSE_DEPEND_H
