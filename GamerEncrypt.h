#ifndef _GAMERENCRYPT_H_
#define _GAMERENCRYPT_H_

#include "encryption.h"

//This is the linker class in between encryption.h and gamer.h. This is required to avoid the multiple section warning.
//This function carries over the isEncrypted function from encryption.h to gamer.h

using namespace std;

class GamerEncrypt: public Encryption
{
public:
	bool isEncrypted(string enc_message) override =0;

	GamerEncrypt(int key)
        : Encryption{ key }
        {
        }
};

#endif