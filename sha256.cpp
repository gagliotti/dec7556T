//
//  sha256.cpp
//  t22
//
//  Created by Martin on /29/519.
//  Copyright © 2019 Martin. All rights reserved.
//

#include "sha256.h"

std::string printSha256(const char *path) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::string hexHash("");

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) throw std::runtime_error("EVP_MD_CTX_new failed");

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1)
        throw std::runtime_error("EVP_DigestInit_ex failed");

    BIO* fileBio = BIO_new_file(path, "r");
    if (!fileBio) throw std::runtime_error("BIO_new_file failed");

    char buf[4096];
    int len = 0;
    while ((len = BIO_read(fileBio, buf, sizeof(buf))) > 0) {
        if (EVP_DigestUpdate(mdctx, buf, len) != 1)
            throw std::runtime_error("EVP_DigestUpdate failed");
    }

    unsigned int md_len = 0;
    if (EVP_DigestFinal_ex(mdctx, hash, &md_len) != 1)
        throw std::runtime_error("EVP_DigestFinal_ex failed");

    EVP_MD_CTX_free(mdctx);
    BIO_free(fileBio);

    char *hexOut = OPENSSL_buf2hexstr(hash, md_len);
    hexHash = std::string(hexOut);
    OPENSSL_free(hexOut);

    return hexHash;
}
