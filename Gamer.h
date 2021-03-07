#ifndef _GAMER_H_
#define _GAMER_H_

#include <string>
#include <map>
#include <stdexcept>
#include "Person.h"
#include "GamerEncrypt.h"

using namespace std;

//This class is for handling an exception of a score being missing
class NoScoreException: public exception
{
	public:
    const char* what() {
        return "The player has no score yet.";
    }
};

class Gamer: public Person, public GamerEncrypt
{   public:
        // constructor should initialise name and registration number using arguments
        // and initialise score map to be empty
        Gamer(const string &name, int regNo, int key);

	   // method to return registration number
	   int getRegNo() const;

	   // method to add the score to the map
	   void addScore(float score,string difficulty);

	   // method to retrieve the score
	   // should throw NoScoreException if gamer has no score yet
	   // it should display the score based on the levels of difficulty the gamer player
	   float getHighestScore(string difficulty) const;

	   //This method returns the average score of a gamer for the given difficulty
	   float getAverageScore(string difficulty) const;

	   //This method returns the smallest score the player has for the given difficulty.
	   float getMinimumScore(string difficulty) const;

	   //overriden function from encryption.h, checks if the gamer file is encrypted or not.
	   bool isEncrypted(string enc_message) override
	   {
	   		string versus = "10101";
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
	   multimap<string,float> scores;  // scores multimap, with each in range 0.0 to 100.0, and an
	   									//associated level of difficulty 

    // friend function to output details of gamer to stream
    // should output name, regno, and minimum, maximum and average score on a single line
    // if the gamer has no scores "has no scores" should be output instead of the scores
    friend ostream& operator<<(ostream &str, const Gamer &s);
};

#endif
