//
//  sha256.hpp
//  t22
//
//  Created by Martin on /29/519.
//  Copyright © 2019 Martin. All rights reserved.
//

#ifndef sha256_hpp
#define sha256_hpp

#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/sha.h>
#include <string>
#include <iostream>

std::string printSha256(const char *path);


#endif /* sha256_hpp */
