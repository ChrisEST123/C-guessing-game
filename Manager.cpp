#include <string>
#include <vector>
#include <stdexcept>
#include "Manager.h"

using namespace std;

// constructor should initialise name and registration number using arguments. Also uses Person's constructor.
Manager::Manager(const string &name, int regNo, int key):Person(name), ManagerEncrypt{ key }
{
	this->name = name;
	this->regNo = regNo;
}

// method to return registration number
 int Manager::getRegNo() const
 {
 	return this->regNo;
 }