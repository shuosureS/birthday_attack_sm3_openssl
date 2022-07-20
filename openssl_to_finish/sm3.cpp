#include"openssl/evp.h"
#include"openssl/rsa.h"
#include<iostream>
//time=792875ms
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

int inttohex(int aa, unsigned char* buffer)
{
    static int  i = 0;
    i = 0;
    if (aa < 16)            
    {
        if (aa < 10)        
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'a';
        buffer[i + 1] = '\0'; 
    }
    else
    {
        inttohex(aa / 16, buffer);  
        i++;                
        aa %= 16;           
        if (aa < 10)        
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'a';
    }


    return i+1;
}

int main()
{
    unsigned char tinput[256] = "abcddef123456908213456a";
    int tlen = 23;
    unsigned char tagart[32];
    unsigned char input[256] = "";
    sm3_openssl(tinput, tlen, tagart);
    int ilen = 0;
    unsigned char output[32];
    int i=0;
    int start, end;
    start = clock();
    while (1) {
        ilen=inttohex(i, input);        
        sm3_openssl(input, ilen, output);
        
        if (output[0]==tagart[0] &&output[1]==tagart[1]&&output[2]==tagart[2] && output[3] == tagart[3])
        {
            end = clock();
            printf("¹¥»÷³É¹¦\n");
            printf("time=%dms\n", end - start);
            
            break;
        }
        i++;
    }
    
   

    
}
