#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <string>
#include <vector>
#include <stdexcept>
#include "Person.h"
#include "ManagerEncrypt.h"

using namespace std;

class Manager: public Person, public ManagerEncrypt
{   public:
        // constructor should initialise name and registration number using arguments
        Manager(const string &name, int regNo, int key);

	   // method to return registration number
	   int getRegNo() const;

	   //overridden function from encryption.h, checks if the manager file is encrypted.
	   bool isEncrypted(string enc_message) override
	   {
	   		string versus = "0001";
	   		bool verdict = false;
	   		if(enc_message == versus)
	   		{
	   			verdict = false;
	   		}
	   		else
	   		{
	   			verdict = true;
	   		}
	   		return verdict;
	   }

    private:
	   int regNo;
	   string name;
};

#endif
