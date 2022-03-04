#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

struct Trie
{
    char c;
    vector<Trie*> children;
    
    Trie(char c) : c(c)
    {
        children = vector<Trie*>(10,nullptr);
    }
    
    void insert(const char* str);
    
    bool is_included(const char* str);
        
    virtual ~Trie()
    {
        for(int i = 0; i < children.size(); i++)
        {
            if(children[i] != nullptr)
                delete children[i];
        }
    }
};

void Trie::insert(const char* str)
{
    if(*str == '\0')
        return;
    
    int idx = *str-'0';
    
    if(children[idx] != nullptr)
        children[idx]->insert(++str);
    else
    {
        children[idx] = new Trie(*str);
        children[idx]->insert(++str);
    }
}

bool Trie::is_included(const char *str)
{
    if(*str == '\0')
    {
        for(int i = 0; i < 10; i++)
        {
            if(children[i] != nullptr)
                return true;
        }
        
        return false;
    }
    
    int idx = *str-'0';
    
    if(children[idx] != nullptr)
        return children[idx]->is_included(++str);
    return false;
}

int T,N;
Trie* root;

int main(int argc,char* argv[])
{
    cin >> T;
    while(T--)
    {
        vector<string> v;
        
        cin >> N;
        for(int i = 0; i < N; i++)
        {
            string tmp; cin >> tmp;
            v.push_back(tmp);
        }
        
        root = new Trie('/');
        
        for(int i = 0; i < v.size(); i++)
        {
            const char* tmp = v[i].c_str();
            root->insert(tmp);
        }
        
        // 어떤 전화번호가 다른 전화번호에 종속되어 있는가? -> Yes : No 출력 , No : Yes 출력
        bool check = false;
        for(int i = 0; i < v.size(); i++)
        {
            const char* phone = v[i].c_str();
            if(root->is_included(phone))
            {
                check = true;
                break;
            }
        }
        
        cout << (check == true ? "NO" : "YES") << endl;
        
        delete root;
        root = nullptr;
    }
    
    return 0;
}
