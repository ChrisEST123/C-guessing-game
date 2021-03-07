#include "encryption.h"
#include <string>
#include <iostream> 
#include <array>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";
std::array <char, 10> numList= {'0' , '1', '2', '3', '4', '5', '6', '7', '8', '9'};

/**
* encrypts a message. Uses the key number to move the letters in the message the acquired spaces relevant to the alphabet, in the end
encrypting the message.
*/
void Encryption::encrypt(string message)
{
	int decider = 0;
	string newMessage = "";
	string takenMessage = message;
	std::transform(takenMessage.begin(), takenMessage.end(), takenMessage.begin(), [](unsigned char c){ return std::tolower(c); });
	int tempKey = key;

	for(int i = 0; i < takenMessage.length(); i++)
	{
		char c = takenMessage[i];
		if(isspace(c))
		{
			decider++;
		}
		else
		{
			if(isdigit(c))
			{
				if(tempKey > numList.size())
				{
					tempKey = tempKey % numList.size();
				}
				for(int j = 0; j < numList.size(); j++)
				{
					if(c == numList[j])
					{
						if(j >= numList.size() - tempKey)
						{
							int newLocator = numList.size() - j;
							int actualLocation = tempKey - newLocator;
							c = numList[actualLocation];
							break;
						}
						else
						{
							c = numList[j+tempKey];
							break;
						}
					}
				}
			}
			else
			{
				if(tempKey > alphabet.length())
				{
					tempKey = tempKey % alphabet.length();
				}
				for(int j = 0; j < alphabet.length(); j++)
				{
					if(c == alphabet[j])
					{
						if(j >= alphabet.length() - key)
						{
							int newLocator = alphabet.length() - j;
							int actualLocation = tempKey - newLocator;
							c = alphabet[actualLocation];
							break;
						}
						else
						{
							c = alphabet[j+tempKey];
							break;
						}
					}
				}
			}
		}
		newMessage += c;
	}
	std::ofstream letsWrite;

	if(decider > 3)
	{
		letsWrite.open("gamers.txt", std::ofstream::app);

		letsWrite << newMessage << endl;

		letsWrite.close();
	}
	else
	{
		letsWrite.open("managers.txt", std::ofstream::app);

		letsWrite << newMessage << endl;

		letsWrite.close();
	}
}

/**
* decrypts a message. Uses the key to move the letters in the message so the message is decrypted in the end.
*/

string Encryption::decrypt(string message)
{
	int tempKey = key;
	string newMessage = "";
	for(int i = 0; i < message.length(); i++)
	{
		char c = message[i];
		if(isspace(c))
		{
			newMessage += c;
		}
		else
		{
			if(isdigit(c))
			{
				if(tempKey > numList.size())
				{
					tempKey = tempKey % numList.size();
				}
				for(int j = 0; j < numList.size(); j++)
				{
					if(c == numList[j])
					{
						if(j < tempKey)
						{
							int newLocator = tempKey - j;
							int actualLocation = numList.size() - newLocator;
							c = numList[actualLocation];
							break;
						}
						else
						{
							c = numList[j - tempKey];
							break;
						}
					}
				}
				newMessage += c;
			}
			else
			{
				if(tempKey > alphabet.length())
				{
					tempKey = tempKey % alphabet.length();
				}
				for(int j = 0; j < alphabet.length(); j++)
				{
					if(c == alphabet[j])
					{
						if(j < key)
						{
							int newLocator = tempKey - j;
							int actualLocation = alphabet.length() - newLocator;
							c = alphabet[actualLocation];
							break;
						}
						else
						{
							c = alphabet[j - tempKey];
							break;
						}
					}
				}
				newMessage += c;
			}
		}
	}
	return newMessage;
}

//This function is to determine the key in case the files were encrypted with a different key, chosen by the manager before 
//the programme termination, so the decrypt function knows what key to use upon decryption. Decided to do a forced check
//here since I could not come up with a better way to get the key.
int Encryption::checkKey(string message)
{
	int actualKey = 0;
	char checkUp = 'e';
	char encrypted = message[1];

	for(int i = 0; i < alphabet.length(); i++)
	{
		char c = alphabet[i];
		if(c == encrypted)
		{
			int counter = 0;
			int curPosition = i;
			bool loop = true;
			char tester = c;
			while(loop == true)
			{
				if(curPosition - counter < 0)
				{
					curPosition = alphabet.length();
					counter = 0;
				}
				tester = alphabet[curPosition - counter];
				if(tester == checkUp)
				{
					this->key = actualKey;
					loop = false;
				}
				else
				{
					actualKey++;
					counter++;
				}
			}
		}
	}
	return actualKey;
}

//This function is for changing the current key.
void Encryption::changeKey(int newKey)
{
	this->key = newKey;
}