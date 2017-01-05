#include "TeraCrypt.hpp"

using namespace Crypt;

Session::Session(byte *CKey1, byte *CKey2, byte *SKey1, byte *SKey2)
{
	byte TmpKey1[128], TmpKey2[128];
	Encryptor = new Cryptor();
	Decryptor = new Cryptor();
	memcpy(ClientKey1, CKey1, 128);
	memcpy(ClientKey2, CKey2, 128);
	memcpy(ServerKey1, SKey1, 128);
	memcpy(ServerKey2, SKey2, 128);

	ShiftKey(TmpKey1, ServerKey1, 67, true);
	XorKey(TmpKey2, TmpKey1, 128, ClientKey1, 128);

	ShiftKey(TmpKey1, ClientKey2, 29, false);
	XorKey(DecryptKey, TmpKey1, 128, TmpKey2, 128);

	Decryptor->GenerateKey(DecryptKey);

	
	ShiftKey(EncryptKey, ServerKey2, 41, true);
	Decryptor->ApplyCryptor(EncryptKey, 128);

	Encryptor->GenerateKey(EncryptKey);
}

Session::~Session()
{
	delete Encryptor;
	delete Decryptor;
}

void Session::Encrypt(byte *data, int length)
{
	Encryptor->ApplyCryptor(data, length);
}

void Session::Decrypt(byte *data, int length)
{
	Decryptor->ApplyCryptor(data, length);
}

void Session::XorKey(byte *result, byte *key1, int Length1, byte *key2, int Length2)
{
	int Length = Length1 < Length2 ? Length1 : Length2;
	for (int i = 0; i < Length; i++)
		result[i] = (byte)(key1[i] ^ key2[i]);
}

void Session::ShiftKey(byte *result, byte *src, int n, bool direction)
{
	int Length = 128;
	for (int i = 0; i < Length; i++)
		if (direction)
			result[(i + n) % Length] = src[i];
		else
			result[i] = src[(i + n) % Length];
}
