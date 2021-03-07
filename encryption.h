/**
 * Encryption abstract class, for CE221 Assignment 2 (Exercise 2)
 */

#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

using namespace std;
#include <string>
#include <list>

class Encryption
{
        public:

                /**
                 * Constructor. Stores the key for encryption
                 */
                Encryption(int key)
                {
                }

                //pure virtual function for filter
                virtual bool isEncrypted(string enc_message)=0;

                /**
                 * encrypts a message
                 */
                void encrypt(string message);

                /**
                 * decrypts a message
                 */

                string decrypt(string message);

                //This function is to determine the key in case the files were encrypted with a different key, chosen by the manager before 
                //the programme termination, so the decrypt function knows what key to use upon decryption.
                int checkKey(string message);

                //This function is for changing the current key.
                void changeKey(int newKey);

        private:
                int key; //key for the encryption of a message
    
 };

 #endif
