#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include "Gamer.h"

using namespace std;

string difficultyCheck = "";

//Constructor for the class, also connected with the Person class constructor
Gamer::Gamer(const string &name, int regNo, int key):Person(name), GamerEncrypt{ key }
{
	this->name = name;
	this->regNo = regNo;
}


// method to return registration number
int Gamer::getRegNo() const
{
	return this->regNo;
}

// method to add the score to the map
// if a score for the module is already present it should be overwritten
void Gamer::addScore(float score,string difficulty)
{
	difficultyCheck = difficulty;
	this->scores.emplace ( std::pair<string,float>(difficulty, score) );
}

// method to retrieve the score
// should throw NoScoreException if gamer has no score yet
// it should display the score based on the levels of difficulty the gamer player
float Gamer::getHighestScore(string difficulty) const
{
	difficultyCheck = difficulty;
	float requiredScore = 0;
	multimap<string, float>::const_iterator it;

	try
	{
		for (it = this->scores.begin(); it != this->scores.end(); it++)
		{
	    	if(it->first == difficulty){
	    		if(requiredScore < it->second){
	    			requiredScore = it->second;
	    		}
	    	}
		}
	}
	catch (NoScoreException e)
	{
		cout << e.what() << endl;
	}

	return requiredScore;
}

//This function returns the gamers average score on certain difficulty level. It takes in a difficulty, cycles through all the scores
//that the player has and then if there are any scores for that difficulty then it puts them into the sum. Afterwards the sum is used
//to calculate the average by dividing how many scores in the difficulty were found.
float Gamer::getAverageScore(string difficulty) const
{
	difficultyCheck = difficulty;
	int scoreCount = 0;
	float scoreSum = 0;
	multimap<string, float>::const_iterator it;

	for (it = this->scores.begin(); it != this->scores.end(); it++)
	{
    	if(it->first == difficulty)
    	{
	   		scoreSum += it->second;
	   		scoreCount++;
	   	}
	}

	return scoreSum / scoreCount;
}

//This function is for finding the minimum score the player has for the given difficulty. It is basically like getHighestScore()
//but it cycles through the scores looking for minimum scores instead of maximum.
float Gamer::getMinimumScore(string difficulty) const
{
	difficultyCheck = difficulty;
	float requiredScore = 1000;
	multimap<string, float>::const_iterator it;

	for (it = this->scores.begin(); it != this->scores.end(); it++)
	{
		if(it->first == difficulty)
		{
			if(requiredScore > it->second)
	   		{
	   			requiredScore = it->second;
	   		}
		}
	}

	return requiredScore;
}

// friend function to output details of gamer to stream
// should output name, regno, and minimum, maximum and average score on a single line
// if the gamer has no scores "has no scores" should be output instead of the scores
ostream& operator<<(ostream &str, const Gamer &s){ 
	if(s.getHighestScore(difficultyCheck) == 0){
		str << "Name: " << s.getName() << ", Reg number:" << s.getRegNo() << "has no scores or they are not valid";
	}
	else
	{
		str << "Name: " << s.getName() << ", Reg number: " << s.getRegNo() << ", the highest score: " << s.getHighestScore(difficultyCheck) << 
		", the minimum score: " << s.getMinimumScore(difficultyCheck) << ", the average score: " << s.getAverageScore(difficultyCheck) << endl;
	}
	return str;
}