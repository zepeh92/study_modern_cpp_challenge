/*
94. FILE SIGNING
Write a program that is able to sign files and verify that a signed file has not ben tampered with, using RSA cryptography
When signing a file, the signature should be written to a separate file and used later for the verification process.
The program shoud provide at least two functions: one that signs a file(tasing as arguments the path to the file, the path to the RSA private key, and the path to the file where the signature will be written) and one that verifies a file (talking as arguments the path to the file, the path to the RSA public key, and the path to the signature file).
*/

#include <iostream>
#include <string>
#include <filesystem>
#include <openssl/rsa.h>

struct FileSign
{
  std::string publicKey;
};

class FileSignatory
{
public:

  FileSign sign(const std::filesystem::path& filePath)
  {
    FileSign fileSign;

    return fileSign;
  }

  bool is_valid_sign(const std::filesystem::path& filePath, const FileSign& fileSign) const
  {
    return false;
  }
};

int main()
{
  FileSignatory fileSignatory;
  FileSign sign = fileSignatory.sign("./testfile.txt");

  return 0;
}