#ifndef _HMAC_SHA512_H_
#define _HMAC_SHA512_H_

#include <stddef.h>
#include <string>

std::string  
hmac_sha512(
    // [in]: The key and its length.
    //      Should be at least 32 bytes long for optimal security.
    const std::string key,
    const std::string data);

std::string  
fake_hmac_sha512(
    // [in]: The key and its length.
    //      Should be at least 32 bytes long for optimal security.
    const std::string key,
    const std::string data);

#endif  // _HMAC_SHA512_H_