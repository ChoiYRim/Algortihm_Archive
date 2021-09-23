// compile : g++ -o [execute file name] main.cpp -lssl -lcrypto
// before get started, must install openssl

#include <iostream>
#include <vector>
#include <string>
#include <openssl/md5.h>

class BloomFilter
{
private:
    int nHashes;
    std::vector<bool> bits;
    static constexpr int hashSize = 128/8; // 16 bytes
    unsigned char hashValue[hashSize];
    
public:
    BloomFilter(int size,int hashes) : bits(size) , nHashes(hashes)
    {
        if(nHashes > hashSize)
            throw("too many hash functions\n");
        if(size > 255)
            throw("the size of bloom filter can't be over 255\n");
    }
    
    void Hash(const std::string& email)
    {
        MD5(reinterpret_cast<const unsigned char*>(email.data()),email.length(),hashValue);
    }
    
    void Add(const std::string& email)
    {
        Hash(email);
        for(auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
            bits[*it % bits.size()] = true;
        std::cout << "Add to Bloom Filter : " << email << '\n';
    }
    
    bool LookUp(const std::string& email)
    {
        Hash(email);
        for(auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
        {
            if(!bits[*it % bits.size()])
            {
                std::cout << email << " : you can use this name" << '\n';
                return false;
            }
        }
        
        std::cout << email << " : already exists" << '\n';
        return true;
    }
    
};

int main(int argc,char* argv[])
{
    BloomFilter bloom(128,5);
    
    bloom.Add("abc@naver.com");
    bloom.Add("xyz@naver.com");
    
    bloom.LookUp("abc");
    bloom.LookUp("xyz@naver.com");
    bloom.LookUp("xyz");
    
    bloom.Add("abcd@naver.com");
    bloom.Add("ab@naver.com");
    
    bloom.LookUp("abcd");
    bloom.LookUp("ab@naver.com");
    return 0;
}
