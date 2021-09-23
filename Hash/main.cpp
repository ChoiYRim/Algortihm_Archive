#include <iostream>
#include <unordered_map> // no duplicated element
#include <string>
#include <vector>

class UrlMapingBySTL
{
private:
    std::unordered_map<std::string, std::string> urls;
    
public:
    
    inline void Insert(std::string origin,std::string abbreviation)
    {
        urls.insert({abbreviation,origin});
    }
    
    std::string Find(std::string abbreviation)
    {
        std::string origin = "";
        std::unordered_map<std::string,std::string>::iterator it;
        
        if((it = urls.find(abbreviation)) != urls.end())
            origin = it->second;
        return origin;
    }
};

class SimpleCuckooHash
{
private:
    std::vector<int> data1;
    std::vector<int> data2;
    int size;
    
    void InsertImplement(int key,int cnt,int table) // key , cycling count , table number
    {
        if(cnt >= size)
        {
            std::cout << "Cycling occurs, need a new hash function" << '\n';
            return;
        }
        
        if(table == 1)
        {
            int hash = hash1(key);
            if(data1[hash] == -1)
            {
                std::cout << "Insert " << key << " in " << table << "'th table" << '\n';
                data1[hash] = key;
            }
            else
            {
                int old = data1[hash];
                data1[hash] = key;
                std::cout << "Insert " << key << " in " << table << "'th table" << '\n';
                InsertImplement(old,cnt+1,2);
            }
        }
        else
        {
            int hash = hash2(key);
            if(data2[hash] == -1)
            {
                std::cout << "Insert " << key << " in " << table << "'th table" << '\n';
                data2[hash] = key;
            }
            else
            {
                int old = data2[hash];
                data2[hash] = key;
                std::cout << "Insert " << key << " in " << table << "'th table" << '\n';
                InsertImplement(old,cnt+1,1);
            }
        }
    }
    
public:
    inline int hash1(int key) const { return key % size; } // can't convert member value
    
    inline int hash2(int key) const { return (key/size)%size; }
    
    SimpleCuckooHash(int n) : size(n)
    {
        data1 = std::vector<int>(size,-1);
        data2 = std::vector<int>(size,-1);
    }
    
    std::vector<int>::iterator LookUp(int key)
    {
        auto hashValue1 = hash1(key);
        if(data1[hashValue1] == key)
        {
            std::cout << "On the first table, we found " << key << '\n';
            return data1.begin()+hashValue1;
        }
        
        auto hashValue2 = hash2(key);
        if(data2[hashValue2] == key)
        {
            std::cout << "On the second table, we found " << key << '\n';
            return data2.begin()+hashValue2;
        }
        
        return data2.end();
    }
    
    void Erase(int key)
    {
        auto position = LookUp(key);
        if(position != data2.end())
        {
            *position = -1;
            std::cout << "We found " << key << " and erase it" << '\n';
        }
        
        std::cout << "We can't find " << key << '\n';
        return;
    }
    
    void Insert(int key)
    {
        InsertImplement(key,0,1);
    }
    
    void Print()
    {
        std::cout << "Index: ";
        for(int i = 0; i < size; i++)
            std::cout << i << '\t';
        std::cout << '\n';
        
        std::cout << "Data1: ";
        for(auto i : data1)
            std::cout << i << '\t';
        std::cout << '\n';
        
        std::cout << "Data2: ";
        for(auto i : data2)
            std::cout << i << '\t';
        std::cout << '\n';
    }
};


int main(int argc,char* argv[])
{
    UrlMapingBySTL urlMaping;
    
    urlMaping.Insert("https://www.naver.com","naver.com");
    urlMaping.Insert("https://www.google.com","google.com");
    urlMaping.Insert("https://www.daum.net","daum.net");
    
    std::cout << urlMaping.Find("naver.com") << '\n';
    std::cout << urlMaping.Find("google.com") << '\n';
    std::cout << urlMaping.Find("daum.net") << '\n';
    return 0;
}
