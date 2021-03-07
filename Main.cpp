#include "Gamer.h"
#include "Manager.h"
#include "encryption.h"
#include <string>
#include <iostream> 
#include <cstdlib>
#include <list>
#include <fstream>
#include <algorithm> 
#include <sstream>

//My Student ID is 1906001

using namespace std;

//Class for the game itself. The variables are for initialising the beginning rules for the game. All of the "change" functions are for
//in case the manager decides to change the rules. If a certain rule is changed then the function is called for the variable change.
//After that there is the function that actually creates the game.
class GuessingGame
{
public:
	float finalScore = 0;
	int guessingNumber = 0;
	int playerNum = 0;
	int easyStart = 0;
	int easyEnd = 10;
	int medStart = 0;
	int medEnd = 100; 
	int hardStart = 0;
	int hardEnd = 1000;

	int changeEasyStart(int newEasyStart)
	{
		return easyStart = newEasyStart;
	}

	int changeEasyEnd(int newEasyEnd)
	{
		return easyEnd = newEasyEnd;
	}

	int changeMedStart(int newMedStart)
	{
		return medStart = newMedStart;
	}

	int changeMedEnd(int newMedEnd)
	{
		return medEnd = newMedEnd;
	}

	int changeHardStart(int newHardStart)
	{
		return hardStart = newHardStart;
	}

	int changeHardEnd(int newHardEnd)
	{
		return hardEnd = newHardEnd;
	}

	//This function creates the game. It takes in the difficulty and from that can say what the game boundaries will be. Once the
	// boundaries have been received then a random number is generated and from there the player will start guessing which number
	//the program though of. At the same time per every guess, as requested in the brief, the points rise by 1 and once the
	//player reaches the end, then the score will be returned from the function, as the players end score. I decided not to give
	//a point if the player writes anything that is not a number.
	float gameStarter(int difficulty)
	{
		bool gameRunning = true;
		int starterNumber = 0;
		int endNumber = 0;
		if(difficulty == 1)
		{
			starterNumber = easyStart;
			endNumber = easyEnd;
		}
		if(difficulty == 2)
		{
			starterNumber = medStart;
			endNumber = medEnd;
		}
		if(difficulty == 3)
		{
			starterNumber = hardStart;
			endNumber = hardEnd;
		}
		finalScore = 0;

		guessingNumber = rand() % (endNumber - starterNumber) + starterNumber;
		while(gameRunning == true)
		{
			cout << "Write a number between " << starterNumber << " and " << endNumber << endl;

			cin >> playerNum;

			if(cin.fail())
			{
				cout<<"You did not input a valid number!" << endl;
				cin.clear(); 
		     	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			else
			{
				if(playerNum > endNumber || playerNum < starterNumber)
				{
					finalScore++;
					cout<<"Your number is out of bounds!" << endl;
					continue;
				}
				else
				{
					if(guessingNumber > playerNum)
					{
						cout << "Your guess is too low!" << endl;
						finalScore++;
						continue;
					}
					if(guessingNumber < playerNum)
					{
						cout << "Your guess is too high" << endl;
						finalScore++;
						continue;
					}
					if(guessingNumber == playerNum)
					{
						finalScore++;
						cout << "Your guess was correct! Your final score is " << finalScore << endl;
						gameRunning = false;
					}
				}
			}
		}
	
		return finalScore;
	}

};

//Here I write out all the different functions that are used in this file. Their bodies and explanation can be found later in the file.
void theGame(std::list<Manager>& managerlist, std::list<Gamer>& gamerlist, Gamer& gamer, GuessingGame& game, int& currentKey);

void yourStatistics(std::list<Gamer>& gamerlist, float newScore, string difficulty);

void topScores(std::vector<float> scores, string regNo, float score);

void theGameChanger(std::list<Manager>& managelist, std::list<Gamer>& gamerlist, Manager& manage, GuessingGame& game, int& currentKey);

bool isFloat( string myString );

//This is the function that kicks off the program. It first tries to open the gamer and manager .txt files and then it puts all the
//values per line into one gamer or manager object, which is then put into a list of the given object type. That is what the first
// 2 bigger loops are for.
main(){
	std::list<Gamer> gamerlist;
	std::list<Manager> managerlist;
	string nextline = "";
	string addstring = "";
	ifstream gamerfile;
	ifstream managerfile;
    string nextword;
    bool realGamerLoop = true;
    bool realManagerLoop = true;
    bool gamerFileEncrypted = false;
    bool managerFileEncrypted = false;

	gamerfile.open("gamers.txt");//open file
    if (!gamerfile)
    {   cout << "Failed to open gamers.txt" << endl;
        exit(1);
    }

    //Adding some checks for the encryption here, so the programme knows the current key and if the file is encrypted.
    Gamer tempGamer("David", 1, 3);
    string checkUp = "";
    getline (gamerfile, checkUp);
    string checkString = "";
    int currentKey = 0;
    int checkCounter = 0;
    for(int i = 0; i < checkUp.length(); i++)
    {
    	char c = checkUp[i];
    	if(isspace(c))
    	{
    		if(checkCounter == 0)
    		{
    			if(tempGamer.isEncrypted(checkString) == true)
			    {
			    	gamerFileEncrypted = true;
			    }
			    checkCounter++;
			    checkString = "";
			    continue;
    		}
    		if(checkCounter == 1)
    		{
    			currentKey = tempGamer.checkKey(checkString);
    		}
    	}
    	checkString += c;
    }

    gamerfile.close();

    if(currentKey == 0)
    {
    	currentKey = 3;
    }

    tempGamer.changeKey(currentKey);

    gamerfile.open("gamers.txt");//open file
    if (!gamerfile)
    {   cout << "Failed to open gamers.txt" << endl;
        exit(1);
    }
	
    while(realGamerLoop == true)
    {
    	if(getline (gamerfile, nextline))
	    {
        	float score1 = 0;
        	float score2 = 0;
			int counter = 0;
		   	string name = "";
		   	string regNoString = "";
		   	string addScoreString1 = "";
		   	string addScoreString2 = "";
		   	string addScoreString3 = "";
		   	string addstring = "";
		   	bool gamerValid = false;
		   	int regNo = 0;
		   	std::string::size_type sz;

		   	if(gamerFileEncrypted == true)
		   	{
		   		nextline = tempGamer.decrypt(nextline);
		   	}
		   	for(int i = 0; i<=nextline.length(); i++)
			 {
			   	char c = nextline[i];
			   	if(isspace(c))
			   	{
			   		if(counter == 0)
			   		{
			   			std::string::size_type sz;
			   			regNo = std::stoi(regNoString, &sz);
			   			counter++;
			   			continue;
			   		}
			   		if(gamerValid == true)
			   		{
			   			if(counter == 1)
			   			{
			   				if(isFloat(addstring) == false)
				   			{
				   				name = addstring;
				   				counter++;
				   				continue;
				   			}
			   			}
			   			if(counter == 2)
				   		{
				   			score1 = std::stof(addScoreString1, &sz);
				   			counter++;
				   			continue;
				   		}
				   		if(counter == 3)
				   		{
				   			score2 = std::stof(addScoreString2, &sz);
				   			counter++;
				   			continue;
				   		}
			   		}
			   		if(counter == 1)
			   		{
			   			gamerValid = true;
			   		}
			   }
			   if(counter == 0)
			   {
			   		regNoString += c;
			   }
			   if(counter == 1)
			   {
			   		addstring += c;
			   }
			   if(counter == 2)
			   {
			   		addScoreString1 += c;
			   }
			   if(counter == 3)
			   {
			   		addScoreString2 += c;
			   }
			   if(counter == 4)
			   {
			   		addScoreString3 += c;
			   }
			}
			Gamer g(name, regNo, currentKey);
			g.addScore(score1, "easy");
			if(counter < 4)
			{
				float score = std::stof(addScoreString2, &sz);
				g.addScore(score, "medium");
			}
			if(counter == 4)
			{
				g.addScore(score2, "medium");
				float score = std::stof(addScoreString3, &sz);
				g.addScore(score, "hard");
			}
			gamerlist.push_back(g);
	    }
	    else
		{
			realGamerLoop = false;
		}
    }

    gamerfile.close();

    managerfile.open("managers.txt");//open file
    if (!managerfile)
    {   cout << "Failed to open managers.txt" << endl;
        exit(1);
    }

    //Here I am checking if the manager file is encrypted.
    Manager tempManager("David", 1, currentKey);
    checkUp = "";
    getline (managerfile, checkUp);
    checkString = "";
    checkCounter = 0;
    for(int i = 0; i < checkUp.length(); i++)
    {
    	char c = checkUp[i];
    	if(isspace(c))
    	{
    		if(checkCounter == 0)
    		{
    			if(tempManager.isEncrypted(checkString) == true)
			    {
			    	managerFileEncrypted = true;
			    }
			    checkCounter++;
			    checkString = "";
			    break;
    		}
    	}
    	checkString += c;
    }

    managerfile.close();

    tempManager.changeKey(currentKey);

    managerfile.open("managers.txt");//open file
    if (!managerfile)
    {   cout << "Failed to open managers.txt" << endl;
        exit(1);
    }

    while(realManagerLoop == true)
    {
    	if(getline (managerfile, nextline))
	    {
	    	int counter = 0;
	    	string name = "";
		   	string regNoString = "";
		   	string addstring = "";
	    	int regNo = 0;
	    	if(managerFileEncrypted == true)
		   	{
		   		nextline = tempManager.decrypt(nextline);
		   	}
	    	for(int i = 0; i<=nextline.length(); i++)
			 {
			   char c = nextline[i];
			   if(isspace(c))
			   {
			   		if(counter == 0)
			   		{
			   			std::string::size_type sz;
			   			regNo = std::stoi(regNoString, &sz);
			   			counter++;
			   			continue;
			   		}
			   		if(counter == 1)
			   		{
			   			name = addstring;
			   			counter++;
			   		}
			   	}
			   	if(counter == 0)
				  {
			  		regNoString += c;
				  }
				  if(counter == 1)
				  {
				  	addstring += c;
				  }
				  if(counter == 2)
				  {
				  	addstring += c;
				  }
			 }
			 name = addstring.substr(0, addstring.size()-1);
			Manager m(name, regNo, currentKey);
			managerlist.push_back(m);  
		}
		else
		{
			realManagerLoop = false;
		}
    }

    managerfile.close();

    //Added a new if statement here as well, in case the file is not encrypted upon programme boot up. The next 2 loops encrypt
    //all the lines in the files if required.
    if(gamerFileEncrypted == false)
    {
    	std::ofstream letsWrite;

		letsWrite.open("gamers.txt", std::ofstream::out | std::ofstream::trunc);

		letsWrite.close();

		letsWrite.open("managers.txt", std::ofstream::out | std::ofstream::trunc);

		letsWrite.close();

		std::list<Gamer>::iterator it;
		for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
		{
			it->changeKey(currentKey);
			string timeToEncrypt = "";
		   	int easyNum = 0;
		   	int medNum = 0;
	    	int hardNum = 0;
			string name = it->getName();
		  	int regNo = it->getRegNo();
		   	easyNum = it->getHighestScore("easy");
		   	medNum = it->getHighestScore("medium");
		   	hardNum = it->getHighestScore("hard");
		   	timeToEncrypt = std::to_string(regNo) + " " + name + " " + std::to_string(easyNum) + " " + std::to_string(medNum) + " " + std::to_string(hardNum);
		   	it->encrypt(timeToEncrypt);
		}	
				
		std::list<Manager>::iterator itSecond;
		for(itSecond = managerlist.begin(); itSecond != managerlist.end(); ++itSecond)
		{
			itSecond->changeKey(currentKey);
			string timeToEncrypt = "";
			string newReg = "";
			string name = itSecond->getName();
			int regNo = itSecond->getRegNo();
			if(regNo < 10)
			{
			   	newReg = "000" + std::to_string(regNo);
			}
			if(regNo > 9 && regNo < 100)
			{
				newReg = "00" + std::to_string(regNo);
			}
		  	timeToEncrypt = newReg + " " + name;
		  	itSecond->encrypt(timeToEncrypt);
		}
    }

    //From here I ask for a name from the user. The name is going to be the gateway to either getting the gamer or manager menu.
    //Both loops take the inserted name in and check if either list has any user with those credentials. If one is found then
    //depending on whether it was a gamer or manager recognized then it will give their menu(function). However if a completely 
    //new name is inserted then that will automatically create a new gamer. Before starting the loops I also initialize the 
    //GuessingGame class since both the gamer and manager function need a GuessingGame parameter in my system.
	#define BUF_SIZE 100

    char buf[BUF_SIZE];

    cout << "Please enter your name: ";

    cin.getline(buf, BUF_SIZE);

    GuessingGame game;

    std::list<Gamer>::iterator it;
    int gamerCounter = 0;
    for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
    {
    	string name = it->getName();
    	if(name == buf){
    		Gamer actualGamer = *it;
    		gamerCounter++;
    		theGame(managerlist, gamerlist, actualGamer, game, currentKey);
    		break;
    	}
    }

    std::list<Manager>::iterator its;
    for(its = managerlist.begin(); its != managerlist.end(); ++its)
    {
    	string name = its->getName();
    	if(name == buf){
    		int reqNo = its->getRegNo();
    		Manager actualManager(name, reqNo, currentKey);
    		gamerCounter++;
    		theGameChanger(managerlist, gamerlist, actualManager, game, currentKey);
    		break;
    	}
    }

    if(gamerCounter == 0)
    {
    	int req = rand() % 99999 + 10000;
    	for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
	    {
	    	int reqnum = it->getRegNo();
	    	if(reqnum == req){
	    		int req = rand() % 99999 + 10000;
	    	}
	    }
	    Gamer actualGamer(buf, req, currentKey);
	    gamerlist.push_back(actualGamer);
	    cout << "New player created!" << endl;
	    actualGamer.changeKey(currentKey);
	    theGame(managerlist, gamerlist, actualGamer, game, currentKey);
	}
}

//This function is for the gamers specifically. It gives a menu for the gamer with options. Once an option is chosen then a
//user input check is done. During this whole process it will keep looping the menu unless the player were to choose exiting 
//the game.
void theGame(std::list<Manager>& managerlist, std::list<Gamer>& gamerlist, Gamer& gamer, GuessingGame& game, int& currentKey)
{
	bool gameActive = true;
	bool choiceActive = true;
	float newScore = 0;
	string diffCheck = "easy";


	while(gameActive == true)
	{
		
		cout<< "Write the number of the option you want to pick" << endl;
		cout<< "1)	Play game" << endl;
		cout<< "2)	Your statistics" << endl;
		cout<< "3)	Display top 10" << endl;
		cout<< "4)	Exit game" << endl;

		int choice;
		cin >> choice;
		//https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
		if(cin.fail())
		{
			cout<<"User did not input a number!" << endl;
		    cin.clear(); 
		     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		     continue;
		}
		if(choice <= 0 || choice > 4)
		{
			cout<<"User did not input a number from the given list!" << endl;
			continue;
		}

		//This choice is for starting up the game. It gives the player a new choice, between levels. Depending on which one is
		//chosen the programme will  start the game with the given difficulty. This function also changes the diffCheck variable,
		//which comes into play in the your statistics section of the game. It then adds the score into the gamer objects multimap.
		//It also has a small loop for checking the input of the player.
		if(choice == 1)
		{
			int difficulty = 0;

			while(choiceActive == true)
			{
				cout<<"Choose your difficulty, and write the number:" << endl;
				cout << "1) Easy -> smallest pool of numbers to guess from" << endl;
				cout << "2) Medium -> a bit bigger pool of numbers to guess from" << endl;
				cout << "3) Hard -> the biggest pool of numbers to choose from" << endl;

				cin >> difficulty;
				if(cin.fail())
				{
					cout<<"User did not input a number!" << endl;
					cin.clear(); 
		    		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if(difficulty <= 0 || difficulty > 3)
				{
					cout<<"User did not input a number from the given list!" << endl;
					continue;
				}
				else
				{
					choiceActive = false;
				}

			}
			newScore = game.gameStarter(difficulty);
			if(difficulty == 1)
			{
				diffCheck = "easy";
			}
			if(difficulty == 2)
			{
				diffCheck = "medium";
			}
			if(difficulty == 3)
			{
				diffCheck = "hard";
			}
			gamer.addScore(newScore, diffCheck);
			choiceActive = true;
			continue;
		}

		//This choice is for seeing how the player compares to all the other gamers in the "database". I decided to implement
		//a check here as well, for if a player has a score or not. This was implemented since the assignment brief needed the
		//insertion of a single score as the parameter, so I decided to choose the score to be the last score the player got
		//from the current session.
		if(choice == 2)
		{
			if(newScore > 0)
			{
				yourStatistics(gamerlist, newScore, diffCheck);
				continue;
			}
			else
			{
				cout << "Play a game to have a score to compare to!" << endl;
				continue;
			}
		}

		//This choice is for gettting the top 10 highest scores, as requested in the brief, within all the gamers currently 
		//in the gamerlist. It loops through the gamerlist and puts all the scores in separate vectors depending on which
		//difficulty the score belongs to. The vector is then sorted, resized(in case there are more than 10 players) and then
		//for the topScores function also find out the current players score on each difficulty, and their registration number.
		//Reasoning for these parameters is explained at the function itself. The funciton outputs the top scores.
		//Sidenote: Since in the brief the game is supposed to give you points per guess, then I think it would make more sense
		//to make the top 10 list be about minimum scores not highest, since the less points you get, the faster you got to the
		//right guess. Just in case I am keeping the scoring as it is asked in the brief.
		if(choice == 3)
		{
			std::vector<float> scoreVectorEasy;
			std::vector<float> scoreVectorMedium;
			std::vector<float> scoreVectorHard;
			std::list<Gamer>::iterator it;
			for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
			{
				scoreVectorEasy.push_back(it->getHighestScore("easy"));
				scoreVectorMedium.push_back(it->getHighestScore("medium"));
				scoreVectorHard.push_back(it->getHighestScore("hard"));
			}
			std::sort (scoreVectorEasy.rbegin(), scoreVectorEasy.rend());
			std::sort (scoreVectorMedium.rbegin(), scoreVectorMedium.rend());
			std::sort (scoreVectorHard.rbegin(), scoreVectorHard.rend());

			scoreVectorEasy.resize(10);
			scoreVectorMedium.resize(10);
			scoreVectorHard.resize(10);

			int scoreEasy = gamer.getHighestScore("easy");
			int scoreMedium = gamer.getHighestScore("medium");
			int scoreHard = gamer.getHighestScore("hard");
			std::string regNo = std::to_string(gamer.getRegNo());

			cout<< "Easy difficulty top 10" << endl;
			topScores(scoreVectorEasy, regNo, scoreEasy);

			cout<< "Medium difficulty top 10" << endl;
			topScores(scoreVectorMedium, regNo, scoreMedium);

			cout<< "Hard difficulty top 10" << endl;
			topScores(scoreVectorHard, regNo, scoreHard);
		}

		//From any choice taken here, the gamer main loop ends. This choice gives the player new options, but before that adds the 
		//current player to the gamerlist with all of their scores. If the gamer already exists in the list then that gamer is 
		//replaced with its current iteration. Afterwards the gamer.txt file is overwritten with all of the information that was in 
		//it initially, with the changes or additions that the current gamer brings.
		if(choice == 4)
		{
			int gamingCount = 0;
			std::list<Gamer>::iterator i;
			for (i = gamerlist.begin(); i != gamerlist.end(); ++i)
			{
				if(i->getName() == gamer.getName())
				{
					i = gamerlist.erase(i);
    				gamerlist.insert(i,gamer);
    				gamingCount++;
    				break;
				}
			}
			if(gamingCount == 0)
			{
				gamerlist.push_back(gamer);
			}
			string easy = "easy";
			string medium = "medium";
			string hard = "hard";

			//Different from previous code, here I truncate the current gamer file so all the gamer names can be written into the file
			//with the use of the right key.
			std::ofstream letsWrite;

			letsWrite.open("gamers.txt", std::ofstream::out | std::ofstream::trunc);

			letsWrite.close();

			std::list<Gamer>::iterator it;
			for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
		    {
		    	it->changeKey(currentKey);
				string timeToEncrypt = "";
		    	int easyNum = 0;
		    	int medNum = 0;
		    	int hardNum = 0;
		  		string name = it->getName();
			   	int regNo = it->getRegNo();
			   	easyNum = it->getHighestScore(easy);
			   	medNum = it->getHighestScore(medium);
			   	hardNum = it->getHighestScore(hard);
			   	//Here the code differs again, instead of putting the info straight into the file, I instead put it into the encrypt
			   	//which puts it into the file with the right encryption by itself.
			   	timeToEncrypt = regNo + " " + name + " " + std::to_string(easyNum) + " " + std::to_string(medNum) + " " + std::to_string(hardNum);
			   	it->encrypt(timeToEncrypt);
			}

			//From here the player gets a new choice. If they choose a new gamer, then they get to write a name again. As in the main
			//function, if the name is found then that gamer from the gamerlist is going to be the next gamer used in the function.
			//If the name is not found then a new gamer is made from that name, and also the game function is started. The second choice
			//starts a loop. The player is asked to insert a manager name, if the name does not exist, then it keeps looping until an
			//existing name is inserted. Once the name is inserted than a manager menu function is run. On the third choice the whole
			//programme is closed for good.
			bool chosen = false;
			int choices = 0;
			while(chosen == false)
			{
				cout << "Are you sure you want to exit? You could instead go as another gamer or a manager, choose the number of the choice you want" << endl;
				cout << "1) Choose new Gamer" << endl;
				cout << "2) Switch to manager" << endl;
				cout << "3) Exit the game" << endl;

				cin >> choices;
				if(cin.fail())
				{
					cout<<"User did not input a number!" << endl;
					cin.clear(); 
		     		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if(choices <= 0 || choices > 3)
				{
					cout<<"User did not input a number from the given list!" << endl;
					continue;
				}
				else
				{
					chosen = true;
					if(choices == 1)
					{	
						cin.ignore();
						int gamerCounter = 0;
						#define BUF_SIZE 100

					    char buf[BUF_SIZE];

					    cout << "Please enter a name: " << endl;;

					    cin.getline(buf, BUF_SIZE);

						std::list<Gamer>::iterator it;
					    for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
					    {
					    	string name = it->getName();
					    	if(name == buf)
					    	{
					    		Gamer actualGamer = *it;
					    		theGame(managerlist, gamerlist, actualGamer, game, currentKey);
						    	gamerCounter++;
						    	continue;
						   	}
						}

						if(gamerCounter == 0)
					    {
					    	int req = rand() % 99999 + 10000;
					    	for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
						    {
						    	int reqnum = it->getRegNo();
						    	if(reqnum == req){
						    		int req = rand() % 99999 + 10000;
						    	}
						    }
						    Gamer actualGamer(buf, req, currentKey);
						    cout << "New player created!" << endl;
						    theGame(managerlist, gamerlist, actualGamer, game, currentKey);
						}
						gameActive = false;
					}
					if(choices == 2)
					{
						cin.ignore();
						bool managerLoop = true;
						int managerCounter = 0;
						while(managerLoop == true)
						{
							int counter = 0;
							#define BUF_SIZE 100

						    char buf[BUF_SIZE];

						    cout << "Please enter a manager name: " << endl;

						    cin.getline(buf, BUF_SIZE);

						    std::list<Manager>::iterator it;
						    for(it = managerlist.begin(); it != managerlist.end(); ++it)
						    {
						    	string name = it->getName();
						    	if(name == buf){
						    		Manager & actualManager = *it;
						    		managerCounter++;
						    		
						    		theGameChanger(managerlist, gamerlist, actualManager, game, currentKey);
						    		managerLoop = false;
						    		gameActive = false;
						    	}
						    }
						    if(managerCounter == 0)
						    {
						    	cout << "Not a valid manager name" << endl;
						    	continue;
						    }
						}
					}
					if(choices == 3)
					{
						cout << "Thanks for playing!" << endl;
						gameActive = false;
					}
				}
			}
		}
		
	}
}

//Since the assignment brief asked me to take in as parameters a gamer object collection and only a score as well, then I decided to
//make this function compare the players last score to the other gamers scores in the same difficulty. Since this function takes in 
//only 1 score to compare with then it has to belong to only 1 difficulty. To make comparisons between the current score and the other 
//gamers then the  getHighestScore function needs to know what the last difficulty played was, so because of that I decided to bend the 
//requirements a bit and also include the current difficulty as parameter, so the function could actually compare the scores.
//This function finds all the players whose score is higher than the current players score, sorts the vector with the found scores
//and then loops through the vector and gamerlist to output all the gamers in the right order with the correct output from gamer.cpp.
void yourStatistics(std::list<Gamer>& gamerlist, float newScore, string difficulty)
{
	float score = newScore;
	int counter = 0;
	std::list<Gamer> gaminglist;
	std::vector<float> scoreVector;

	cout << "The players who have a higher score or an equal score to you for the last difficulty played are: " << endl;

	std::list<Gamer>::iterator it;

	for (it = gamerlist.begin(); it != gamerlist.end(); ++it){
		if(it->getHighestScore(difficulty) >= score)
		{
			gaminglist.push_back(*it);
			scoreVector.push_back(it->getHighestScore(difficulty));
			counter++;
		}
	}

	std::sort (scoreVector.rbegin(), scoreVector.rend());

	if(counter == 0)
	{
		cout << "No such scores found!" << endl;
	}
	if(counter == 1)
	{
		std::list<Gamer>::iterator it;
		for (it = gaminglist.begin(); it != gaminglist.end(); ++it){
			cout << *it << endl;
		}
	}
	if(counter > 1)
	{
		std::list<Gamer>::iterator it;
		std::vector<float>::iterator its;
		float temp = 0;
		for(its = scoreVector.begin(); its != scoreVector.end(); ++its)
		{
			if(temp == *its)
			{
				continue;
			}
			for (it = gaminglist.begin(); it != gaminglist.end(); ++it)
			{
				if(*its == it->getHighestScore(difficulty))
				{
					cout << *it << endl;
				}
			}
			temp = *its;
		}
	}
}

//Since the brief asked for this function to take in a vector of all the players scores, a single string of registration number, and a
//single float score, then I decided that this function will output all the scores in the top 10 list, given with the vector, but once
// the score reaches a score given in as parameter(the current players score) then the function will also add to the score that it is
//exactly the same as the score they have(so they know their standing in the top 10) and then it also print out in the brackets the
//current players registration number.
void topScores(std::vector<float> scores, string regNo, float score)
{
	int count = 1;
	std::vector<float>::iterator it;
	for(it = scores.begin(); it != scores.end(); ++it)
	{
		cout << count << ". ";
		if(*it == score)
		{
			cout << *it << " <-- The Equivalent To Your Score! (" << regNo << ")" << endl; 
		}
		else 
		{
			cout << *it << endl;
		}
		count++;
	}
}

//This function is for the managers. At first the manager is given a choice between 4 options. Manager input is checked.
void theGameChanger(std::list<Manager>& managerlist, std::list<Gamer>& gamerlist, Manager& manager, GuessingGame& game, int& currentKey)
{
	bool gameActive = true;
	bool newGameMade = false;
	GuessingGame newGame;
	int thisKey = currentKey;

	while(gameActive == true)
	{
		cout<< "Write the number of the option you want to pick" << endl;
		cout<< "1)	Reset game" << endl;
		cout<< "2)	Change game levels" << endl;
		cout<< "3)	Change Security Key" << endl;
		cout<< "4)	Add another manager" << endl;
		cout<< "5)	Exit game" << endl;

		int choice;
		cin >> choice;
		if(cin.fail())
		{
			cout<<"User did not input a number!" << endl;
			cin.clear(); 
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if(choice <= 0 || choice > 5)
		{
			cout<<"User did not input a number from the given list!" << endl;
			continue;
		}

		//As the title says, this choice just resets the game with the beginning values. I only have a boolean here so then later
		//the function knows whether to use the game object taken into the manager function or create a new one overall.
		if(choice == 1)
		{
			newGameMade = true;
			cout << "Game has been reset!" << endl;
		}

		//This choice gives the manager an option on which difficulty he wants to change. The choice is checked and then the manager is 
		//asked to insert a new starting boundary for the guessing game on that level. If the input is correct then it asks for the
		//end boundary number, now if the number is less than the starter then it asks for a new number. Once the numbers have been
		//inserted and difficulty has been received then the function changes the values of the current game object, depending on the
		//difficulty chosen.
		if(choice == 2)
		{
			bool levelChanger = true;
			bool levelChanged = false;
			int starterNumber = 0;
			int endNumber = 0;

			while(levelChanger == true)
			{
				cout << "Which level do you want to change? Write the corresponding number" << endl;
				cout << "1) easy" << endl;
				cout << "2) medium" << endl;
				cout << "3) hard" << endl;

				int difficulty;
				cin >> difficulty;
				if(cin.fail())
				{
					cout<<"User did not input a valid number!" << endl;
					cin.clear(); 
		     		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if(choice < 1 || choice > 3)
				{
					cout<<"User did not input a number from the given list!" << endl;
					continue;
				}
		
				bool validStarter = false;
				bool validEnd = false;
				while(validStarter == false)
				{
					cout << "Please write the new starting number!" << endl;

					cin >> starterNumber;
					if(cin.fail())
					{
						cout<<"User did not input a valid number!" << endl;
						cin.clear(); 
		     			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					else
					{
						validStarter = true;
					}
				}

				while(validEnd == false)
				{
					cout << "Please write the new end number!" << endl;

					cin >> endNumber;
					if(cin.fail())
					{
						cout<<"User did not input a valid number!" << endl;
						cin.clear(); 
		     			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					else
					{
						if(endNumber <= starterNumber)
						{
							cout << "Too small number for the game in comparison to starting number!" << endl;
							continue;
						}
						else
						{
							validEnd = true;
						}
					}
				}

				if(difficulty == 1)
				{
					game.changeEasyStart(starterNumber);
					game.changeEasyEnd(endNumber);
					levelChanger = false;
				}

				if(difficulty == 2)
				{
					game.changeMedStart(starterNumber);
					game.changeMedEnd(endNumber);
					levelChanger = false;
				}

				if(difficulty == 3)
				{
					game.changeHardStart(starterNumber);
					game.changeHardEnd(endNumber);
					levelChanger = false;
				}
			}
			cout << "The level has been changed!" << endl;
		}

		//This choice is new in the exercise. What it does is that it asks the user for a new key, and check that user does enter
		//an int. Afterwards it reinitialises the Encryption class object with the new chosen key and then deletes everything from
		//both .txt files. After that is done it will loop through the whole gamerlist and managerlist, getting all the neccessary
		//values and then putting them into a string, which goes in to the Encryption classes encrypt function. The encrypt function
		//writes the string as lines into the file with the correct key.
		if(choice == 3)
		{
			bool keyChanger = true;
			int newKey;

			while(keyChanger == true)
			{
				cout << "Please insert a new number to be chosen as the key!" << endl;

				cin >> newKey;
				if(cin.fail())
				{
					cout<<"User did not input a valid number!" << endl;
					cin.clear(); 
		     		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		     		newKey = 0;
					continue;
				}
				else
				{
					keyChanger = false;
				}
			}
			manager.changeKey(newKey);

			std::ofstream letsWrite;

			letsWrite.open("gamers.txt", std::ofstream::out | std::ofstream::trunc);

			letsWrite.close();

			letsWrite.open("managers.txt", std::ofstream::out | std::ofstream::trunc);

			letsWrite.close();

			std::list<Gamer>::iterator it;
			for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
		    {
		    	it->changeKey(newKey);
				string timeToEncrypt = "";
		    	int easyNum = 0;
		    	int medNum = 0;
		    	int hardNum = 0;
		  		string name = it->getName();
			   	int regNo = it->getRegNo();
			   	easyNum = it->getHighestScore("easy");
			   	medNum = it->getHighestScore("medium");
			   	hardNum = it->getHighestScore("hard");
			   	timeToEncrypt = std::to_string(regNo) + " " + name + " " + std::to_string(easyNum) + " " + std::to_string(medNum) + " " + std::to_string(hardNum);
			   	it->encrypt(timeToEncrypt);
			}	
			
			std::list<Manager>::iterator itSecond;
			for(itSecond = managerlist.begin(); itSecond != managerlist.end(); ++itSecond)
			{
				itSecond->changeKey(newKey);
				string timeToEncrypt = "";
				string newReg = "";
				string name = itSecond->getName();
			   	int regNo = itSecond->getRegNo();
			   	if(regNo < 10)
				{
				   	newReg = "000" + std::to_string(regNo);
				}
				if(regNo > 9 && regNo < 100)
				{
					newReg = "00" + std::to_string(regNo);
				}
			   	timeToEncrypt = newReg + " " + name;
			   	itSecond->encrypt(timeToEncrypt);
			   	thisKey = newKey;
			}
		}

		//This choice lets the manager add a new manager to the system. It asks for a name and then check if the name already exists
		//in the managerlist. If not then it makes the registration number the next from the last manager and puts the new manager into
		//the managerlist. Also writes the new manager immediately into the .txt file.
		if(choice == 4)
		{
			cin.ignore();
			bool truename = false;
			while(truename == false)
			{
				int manageCount = 0;
				#define BUF_SIZE 100

				char buf[BUF_SIZE];

			    cout << "Please enter a new manager name: " << endl;;

			    cin.getline(buf, BUF_SIZE);

			    std::list<Manager>::iterator it;
			    for(it = managerlist.begin(); it != managerlist.end(); ++it)
			    {
			    	string name = it->getName();
			    	if(name == buf)
			    	{
			    		cout << "This name is already taken, please choose another one" << endl;
			   			manageCount++;
					}
				}
				if(manageCount == 0)
				{
					int newCounter = 0;
					int req = 0;
					std::list<Manager>::iterator iter;
			    	for (iter = managerlist.begin(); iter != managerlist.end(); ++iter)
				    {
				    	newCounter++;
				    }
				    req = newCounter + 1;
				    Manager actualManager(buf, req, thisKey);
				    managerlist.push_back(actualManager);

				    //Changed the code from here, no longer is there a need for a writer since encrypt writes by itself. So the
				    //lines that were supposed to go into the file get put into a string and then encrypted first.
				    string managerAddition = "";

					if(newCounter < 10)
				    {
				    	managerAddition = "000" + std::to_string(req) + " " + buf;
				    }
				    if(newCounter > 9 && newCounter < 100)
				    {
				    	managerAddition = "00" + std::to_string(req) + " " + buf;
				    }

				    actualManager.changeKey(thisKey);
					actualManager.encrypt(managerAddition);
				    cout << "New manager created!" << endl;
				    truename = true;
				}
			}
		}

		//Here the manager gets a choice of either using another manager, switching to a new gamer or exiting the game for good. Note
		//that if the manager or the game rafterwards were to exit the game, then all changes to the levels will be lost and reset.
		//If a new manager is chosen then like in the gamer function, it goes through the loop until an actual manager name is written.
		//If a new gamer is chosen, then if the name written by user exists in the the list then that becomes the gamer, if not then a
		//new gamer is made. If exiting the game is chosen, then the programme is closed.
		if(choice == 5)
		{
			bool chosen = false;
			int choices = 0;
			while(chosen == false)
			{
				cout << "Are you sure you want to exit? You could instead go as another manager or a gamer, if you exit the game then all level changes will be lost" << endl;
				cout << "Write the number of your choice" << endl;
				cout << "1) Choose new Manager" << endl;
				cout << "2) Switch to gamer" << endl;
				cout << "3) Exit the game" << endl;

				cin >> choices;
				if(cin.fail())
				{
					cout<<"User did not input a number!" << endl;
					cin.clear(); 
		     		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if(choices < 0 || choices > 3)
				{
					cout<<"User did not input a number from the given list!" << endl;
					continue;
				}
				else
				{
					chosen = true;
					if(choices == 1)
					{	
						bool managerLoop = true;
						while(managerLoop == true)
						{
							int counter = 0;
							#define BUF_SIZE 100

						    char buf[BUF_SIZE];

						    cout << "Please enter a manager name: " << endl;

						    cin.getline(buf, BUF_SIZE);

						    std::list<Manager>::iterator it;
						    for(it = managerlist.begin(); it != managerlist.end(); ++it)
						    {
						    	string name = it->getName();
						    	if(name == buf){
						    		Manager& actualManager = *it;
						    		counter++;
						    		
						    		if(newGameMade == true)
						    		{
						    			theGameChanger(managerlist, gamerlist, actualManager, newGame, thisKey);
						    		}
						    		else
						    		{
						    			theGameChanger(managerlist, gamerlist, actualManager, game, thisKey);
						    		}
						    		managerLoop = false;
						    		gameActive = false;
						    	}

						    }
						    if(counter == 0)
						    {
						    	cout << "Not a valid manager name" << endl;
						    	continue;
						    }
						}
					}
					if(choices == 2)
					{	
						cin.ignore();
						int gamerCounter = 0;
						#define BUF_SIZE 100

					    char buf[BUF_SIZE];

					    cout << "Please enter a name: " << endl;;

					    cin.getline(buf, BUF_SIZE);

						std::list<Gamer>::iterator it;
					    for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
					    {
					    	string name = it->getName();
					    	if(name == buf)
					    	{
					    		Gamer actualGamer = *it;
						    	gamerCounter++;
						    	if(newGameMade == true)
								{
									theGame(managerlist, gamerlist, actualGamer, newGame, thisKey);
								}
								else
								{
									theGame(managerlist, gamerlist, actualGamer, game, thisKey);
								}
						    	break;
						   	}
						}

						if(gamerCounter == 0)
					    {
					    	int req = rand() % 99999 + 10000;
					    	for (it = gamerlist.begin(); it != gamerlist.end(); ++it)
						    {
						    	int reqnum = it->getRegNo();
						    	if(reqnum == req){
						    		int req = rand() % 99999 + 10000;
						    	}
						    }
						    Gamer actualGamer(buf, req, thisKey);
						    gamerlist.push_back(actualGamer);
						    cout << "New player created!" << endl;
						    if(newGameMade == true)
							{
								theGame(managerlist, gamerlist, actualGamer, newGame, thisKey);
							}
							else
							{
								theGame(managerlist, gamerlist, actualGamer, game, thisKey);
							}
						}
						gameActive = false;
					}
					if(choices == 3)
					{
						cout << "Thanks for playing!" << endl;
						gameActive = false;
					}
				}
			}
		}
	}
}

//This code was taken from here, just for the main function check up: https://stackoverflow.com/questions/447206/c-isfloat-function
//It checks if the string is a float or not.
bool isFloat( string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail(); 
}
