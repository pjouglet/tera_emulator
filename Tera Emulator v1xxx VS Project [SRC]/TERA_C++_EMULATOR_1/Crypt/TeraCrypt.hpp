#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <mutex>

#include "data_type.hpp"

namespace Crypt
{
    class Sha_l
    {
        protected:
	  ulong LengthLow;
	  ulong LengthHigh;
	  byte MessageBlock[64];
	  int MessageBlockIndex;
	  int Computed;
	  int Corrupted;
	  ulong CircularShift(int bits, ulong word);
	  int Result();
	  void Input(byte *messageArray, int size);
	  void ProcessMessageBlock();
	  void PadMessage();

	public:
	  uint MessageDigest[5];
	  Sha_l(byte *src, int size);
    };
    class CryptorKey
    {
	public:
	  int Size;
	  int Pos1;
	  int Pos2;
	  int MaxPos;
	  int Key;
	  byte Buffer[58*4];
	  ulong Sum;
	  void set(int size, int maxPos);
    };
    class Cryptor
    {
	protected:
	  int ChangeLen;
	  int ChangeData;
	  CryptorKey Key[3];

	public:
	  Cryptor();
	  void FillKey(byte *src, byte *buf);
	  void GenerateKey(byte *src);
	  void ApplyCryptor(byte *buf, int size);
    };
    class Session
    {
        protected:
	  Cryptor *Encryptor;
	  Cryptor *Decryptor;
	  std::mutex _lockMutex;
	  void Lock();
	  void Unlock();

        public:
	  byte EncryptKey[128];
	  byte DecryptKey[128];
	  byte ClientKey1[128];
	  byte ClientKey2[128];
	  byte ServerKey1[128];
	  byte ServerKey2[128];
	  Session(byte *CKey1, byte *CKey2, byte *SKey1, byte *SKey2);
	  ~Session();
	  void Encrypt(byte *data, int length);
	  void Decrypt(byte *data, int length);
	  void XorKey(byte *result, byte *key1, int Length1, byte *key2, int Length2);
	  void ShiftKey(byte *result, byte *src, int n, bool direction = true);
    };
}
