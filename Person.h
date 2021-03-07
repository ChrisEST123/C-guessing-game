#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

using namespace std;

//This class is for all the users in the game, the class Person has functions that both of the classes need, in terms of the name
class Person
{   public:
	//The constructor for the class
        Person(const string &name);

        //Function to get access to the persons name
	   string getName() const;

	   //function to change a persons name if needed
	   void changeName(const string &newName);
    protected:
	   string name;
};

#endif
