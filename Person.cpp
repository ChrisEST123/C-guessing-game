#include <string>
#include "Person.h"

using namespace std;

//Initializes the class with a name
Person::Person(const string &name)
{   this->name = name;
}

//The constructor for the class
string Person::getName() const
{   return name;
}

//function to change a persons name if needed
void Person::changeName(const string &newName)
{   name = newName;
}
