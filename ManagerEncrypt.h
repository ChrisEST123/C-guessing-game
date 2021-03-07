#ifndef _MANAGERENCRYPT_H_
#define _MANAGERENCRYPT_H_

#include "encryption.h"

using namespace std;

//This is the linker class in between encryption.h and manager.h. This is required to avoid the multiple section warning.
//This function carries over the isEncrypted function from encryption.h to manager.h

class ManagerEncrypt: public Encryption
{
public:
	bool isEncrypted(string enc_message) override =0;

	ManagerEncrypt(int key)
        : Encryption{ key }
        {
        }
};

#endif