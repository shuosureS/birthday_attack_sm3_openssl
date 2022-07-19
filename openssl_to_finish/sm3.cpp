#include"openssl/evp.h"
#include"openssl/rsa.h"
#include<iostream>
using namespace std;
int sm3_openssl(const void* message, size_t len, unsigned char* hash)
{
    EVP_MD_CTX* md_ctx;
    const EVP_MD* md;

    md = EVP_sm3();
    md_ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(md_ctx, md, NULL);
    EVP_DigestUpdate(md_ctx, message, len);
    EVP_DigestFinal_ex(md_ctx, hash, NULL);
    EVP_MD_CTX_free(md_ctx);
    return 0;
}

int main()
{
    unsigned char input2[256] = "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
    int ilen2 = 64;
    unsigned char output2[32];
    int i2;
    // ctx;

    int start, end;
    start = clock();
    for (int i = 0; i < 10000000; i++) {
        sm3_openssl(input2, ilen2, output2);
    }
    end = clock();
    printf("time=%dms\n", end - start);

    system("pause");
}
