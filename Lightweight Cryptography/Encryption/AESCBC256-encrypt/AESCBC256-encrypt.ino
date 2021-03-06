#include <AES.h>
#include <CBC.h>

struct EncryptionTest
{
  const char *name;
  byte key[32];
  byte iv[16];
  byte plaintext[96];
};

static EncryptionTest const AES256CBCTest = {
  "AES-256-CBC-encrypt",
  {0x37, 0x4C, 0x33, 0x53, 0x77, 0x53, 0x71, 0x61,
  0x34, 0x4D, 0x6E, 0x4D, 0x69, 0x50, 0x5A, 0x44,
  0x53, 0x55, 0x46, 0x78, 0x52, 0x79, 0x56, 0x65,
  0x74, 0x6B, 0x41, 0x63, 0x53, 0x47, 0x75, 0x4E},
  {0x50, 0x55, 0x71, 0x78, 0x33, 0x31, 0x7A, 0x36,
   0x53, 0x35, 0x61, 0x65, 0x59, 0x4B, 0x6B, 0x4E},
  {0x4C, 0x6F, 0x72, 0x65, 0x6D, 0x20, 0x69, 0x70,
  0x73, 0x75, 0x6D, 0x20, 0x64, 0x6F, 0x6C, 0x6F,
  0x72, 0x20, 0x73, 0x69, 0x74, 0x20, 0x61, 0x6D,
  0x65, 0x74, 0x2C, 0x20, 0x63, 0x6F, 0x6E, 0x73,
  0x65, 0x63, 0x74, 0x65, 0x74, 0x75, 0x72, 0x20,
  0x61, 0x64, 0x69, 0x70, 0x69, 0x73, 0x63, 0x69,
  0x6E, 0x67, 0x20, 0x65, 0x6C, 0x69, 0x74, 0x20,
  0x6D, 0x6F, 0x72, 0x62, 0x69, 0x20, 0x76, 0x65,
  0x6E, 0x65, 0x6E, 0x61, 0x74, 0x69, 0x73, 0x20,
  0x65, 0x72, 0x61, 0x74, 0x20, 0x6A, 0x75, 0x73,
  0x74, 0x6F, 0x20, 0x70, 0x75, 0x6C, 0x76, 0x69,
  0x6E, 0x61, 0x72, 0x20, 0x73, 0x65, 0x64, 0x2E}
};

CBC<AES256> cipher;

void performEncryption(const struct EncryptionTest *encryption, Cipher *cipher) {
  unsigned long start;
  unsigned long elapsed;
  byte output[96] = {0};

  for (short i=0; i < 96; i++) {
    Serial.print((char)encryption->plaintext[i]);
  }
  Serial.println();
  start = millis();
  cipher->setKey(encryption->key, cipher->keySize());
  cipher->setIV(encryption->iv, cipher->ivSize());
  cipher->encrypt((uint8_t*) output, (uint8_t*)encryption->plaintext, sizeof(encryption->plaintext));
  elapsed = millis() - start;
  printHex(output, 96);
  Serial.println(); Serial.print(elapsed); Serial.print(" milliseconds \n");
}

void printHex(const uint8_t *input, size_t len) {
 for (short i=0; i < len; i++) {
    if (i % 8 == 0) {
      Serial.println();
    }
    Serial.print("0x");
    if (input[i] < 16) {
      Serial.print('0'); 
    }
    Serial.print(input[i], HEX);
    if (i+1 != len) {
      Serial.print(", ");
    }
 }
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print(AES256CBCTest.name);
  Serial.println();
  performEncryption(&AES256CBCTest, &cipher);
}

void loop() {
}
