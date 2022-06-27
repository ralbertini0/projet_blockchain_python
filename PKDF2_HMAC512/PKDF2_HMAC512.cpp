#include <pybind11/pybind11.h>
#include <iostream>
#include <string>

#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>


#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
using namespace CryptoPP;
using namespace std;
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 



char version[]="1.0";

char const* getVersion() {
	return version;
}

class PKDF2_HMAC512
{
    public:
        PKDF2_HMAC512(string &password, string &random_word, int num_itr) : password(password), random_word(random_word),  num_itr(num_itr) {}
        ~PKDF2_HMAC512() {}

        string get_hash() { return password+"43BD48ADE3219A1931115A1DABBE1A7F"; };

    private:
        string password;
        string random_word;
        int num_itr;


    string PKDF2_HMAC512(string &password, string &random_word, int num_itr, uint outputBytes)
    {
    SecByteBlock result(outputBytes);
        string hexResult;

        PKCS5_PBKDF2_HMAC<SHA512> pbkdf;

        pbkdf.DeriveKey(result, result.size(),0x00,(byte *) &password.data(), &password.size(),(byte *) &random_word.data(), &random_word.size(),num_itr);

        ArraySource resultEncoder(result,result.size(), true, new HexEncoder(new StringSink(hexResult)));

    return hexResult;

}



};
 
namespace py = pybind11;


PYBIND11_MODULE(PKDF2_HMAC512,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
    // bindings to PKDF2_HMAC512 class
    py::class_<PKDF2_HMAC512>(greetings, "PKDF2_HMAC512", py::dynamic_attr())
        .def(py::init<std::string &, string &,int>())
        .def("get_hash", &PKDF2_HMAC512::get_hash);
}