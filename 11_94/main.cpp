/*
94. FILE SIGNING
Write a program that is able to sign files and verify that a signed file has not ben tampered with, using RSA cryptography
When signing a file, the signature should be written to a separate file and used later for the verification process.
The program shoud provide at least two functions: one that signs a file(tasing as arguments the path to the file, the path to the RSA private key, and the path to the file where the signature will be written) and one that verifies a file (talking as arguments the path to the file, the path to the RSA public key, and the path to the signature file).
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <filesystem>
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/sha.h>

using namespace std;

class Rsa256
{
public:

  Rsa256()
  {
  }

  Rsa256(Rsa256&& rhs) noexcept
  {
    keypair = rhs.keypair;
    hasPrivateKey = rhs.hasPrivateKey;
    hasPublicKey = rhs.hasPublicKey;
    padding = rhs.padding;

    rhs.keypair = nullptr;
    rhs.hasPrivateKey = false;
    rhs.hasPublicKey = false;
  }

  Rsa256(const Rsa256& rhs) = delete;

  ~Rsa256()
  {
    if (keypair)
    {
      RSA_free(keypair);
    }
  }

  void SetPadding(int padding)
  {
    this->padding = padding;
  }

  string GetPrivateKey()
  {
    BIO* pri = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(pri, keypair, nullptr, nullptr, 0, nullptr, nullptr);
    int pri_len = BIO_pending(pri);
    char* pri_key = (char*)malloc(pri_len + 1);
    BIO_read(pri, pri_key, pri_len);
    pri_key[pri_len] = '\0';
    string ret = pri_key;
    free(pri_key);
    BIO_free_all(pri);
    return ret;
  }

  string GetPublicKey()
  {
    BIO* pub = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(pub, keypair);
    int pub_len = BIO_pending(pub);
    char* pub_key = (char*)malloc(pub_len + 1);
    BIO_read(pub, pub_key, pub_len);
    pub_key[pub_len] = '\0';
    string ret = pub_key;
    free(pub_key);
    BIO_free_all(pub);
    return ret;
  }

  int PublicEncrypt(const void* plain, int plainLength, void* outCipher)
  {
    return RSA_public_encrypt(plainLength, (unsigned char*)plain, (unsigned char*)outCipher, keypair, padding);
  }

  int PublicDecrypt(const void* plain, int plainLength, void* outCipher)
  {
    return RSA_public_encrypt(plainLength, (unsigned char*)plain, (unsigned char*)outCipher, keypair, padding);
  }

  int PrivateDecrypt(const void* cipher, int cipherLength, void* outPlain)
  {
    int len =
      RSA_private_decrypt(
        cipherLength,
        (unsigned char*)cipher,
        (unsigned char*)outPlain,
        keypair,
        padding);
    return len;
  }

  // private key encryption supports only these paddings. RSA_PKCS1_PADDING and RSA_NO_PADDING.
  int PrivateEncrypt(const void* plain, int plainLength, void* outCipher) 
  {
    return PrivateEncrypt(plain, plainLength, outCipher, this->padding);
  }

  // private key encryption supports only these paddings. RSA_PKCS1_PADDING and RSA_NO_PADDING.
  int PrivateEncrypt(const void* plain, int plainLength, void* outCipher, int padding)
  {
    int len =
      RSA_private_encrypt(
        plainLength,
        (unsigned char*)plain,
        (unsigned char*)outCipher,
        keypair,
        padding);
    return len;
  }

  static Rsa256 Generate(int keyLengthInBits, int e = RSA_F4)
  {
    Rsa256 rsa256{};
    RSA* rsa = RSA_new();
    BIGNUM* bne = BN_new();
    BN_set_word(bne, e);
    int res = RSA_generate_key_ex(rsa, keyLengthInBits, bne, nullptr); // RSA_generate_key_ex() returns 1 on success or 0 on error.
    BN_free(bne);
    rsa256.keypair = rsa;
    rsa256.hasPrivateKey = true;
    rsa256.hasPublicKey = true;
    return rsa256;
  }

  static Rsa256 Create(const void* key, bool isPublicKey)
  {
    bool hasPrivateKey = false;
    bool hasPublicKey = false;

    BIO* keybio = BIO_new_mem_buf(key, -1);
    RSA* rsa = nullptr;
    if (isPublicKey)
    {
      rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, nullptr, nullptr);
      hasPublicKey = true;
    }
    else
    {
      rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, nullptr, nullptr);
      hasPrivateKey = true;
    }
    BIO_free_all(keybio);

    Rsa256 rsa256{};
    rsa256.keypair = rsa;
    rsa256.hasPrivateKey = hasPrivateKey;
    rsa256.hasPublicKey = hasPublicKey;
    
    return rsa256;
  }

private:

  int padding = RSA_PKCS1_PADDING; // PKCS #1 v1.5 padding.This currently is the most widely used mode.
  bool hasPublicKey = false;
  bool hasPrivateKey = false;
  RSA* keypair = nullptr;
};

struct FileSign
{
  vector<unsigned char> sign;
  vector<unsigned char> pubKey;
  vector<unsigned char> priKey;
};

class FileSignatory
{
public:

  FileSign Sign(const filesystem::path& filePath)
  {
    Rsa256 rsa = Rsa256::Generate(8 * 256);

    vector<unsigned char> fileHash;
    auto abs = filesystem::absolute(filePath);
    const wchar_t* cabs = abs.c_str();
    ifstream ifs;
    ifs.open(cabs, ios::binary);
    if (ifs.is_open())
    {
      fileHash = MakeHash(ifs);
      ifs.close();
    }
    
    FileSign ret;

    vector<unsigned char> fileSign;
    fileSign.resize(256);
    const int fileSignSize = rsa.PrivateEncrypt(fileHash.data(), fileHash.size(), fileSign.data());
    fileSign.resize(fileSignSize);

    ret.sign = std::move(fileSign);
    
    return ret;
  }

  bool IsValidSign(const vector<unsigned char>& pubKey, const vector<unsigned char>& sign)
  {
    return true;
  }

  std::vector<unsigned char> MakeHash(std::istream& is)
  {
    std::vector<unsigned char> fileHash;
    fileHash.resize(SHA256_DIGEST_LENGTH);

    SHA256_CTX shactx;
    SHA256_Init(&shactx);
    char readBuffer[1024]{ 0, };
    while (is.good())
    {
      is.read(readBuffer, sizeof(readBuffer));
      int gcnt = is.gcount();
      SHA256_Update(&shactx, readBuffer, gcnt);
    }
    SHA256_Final(fileHash.data(), &shactx);

    return fileHash;
  }

private:
};

int main()
{
  FileSignatory fileSignatory;
  FileSign sign = fileSignatory.Sign("testfile.txt");

  return 0;
}