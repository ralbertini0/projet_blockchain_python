#include <pybind11/pybind11.h>
#include <iostream>
#include "../lib/hmac_sha512.h"

class PKDF2_HMAC512
{
    public:
        PKDF2_HMAC512(std::string &password, std::string &seed) : password(password), seed(seed) {}
        ~PKDF2_HMAC512() {}

        std::string get_hash() {
            std::string hash = seed;
            for (int i=0; i<2048;i++){
                hash = fake_hmac_sha512(password,hash);
            }
            return hash; };

    private:
        std::string password;
        std::string seed;
};
 
namespace py = pybind11;

char version[]="1.0";

char const* getVersion() {
	return version;
}

PYBIND11_MODULE(PKDF2_HMAC512,PKDF2_HMAC512_python)
{
  PKDF2_HMAC512_python.doc() = "PKDF2_HMAC512 1.0";
  PKDF2_HMAC512_python.def("getVersion", &getVersion, "a function returning the version");
  
    // bindings to PKDF2_HMAC512 class
    py::class_<PKDF2_HMAC512>(PKDF2_HMAC512_python, "PKDF2_HMAC512", py::dynamic_attr())
        .def(py::init<std::string &, std::string &>())
        .def("get_hash", &PKDF2_HMAC512::get_hash);
}