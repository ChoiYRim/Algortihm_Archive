#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
 
using namespace std;

const int kMaxWordLen = 10001;
 
struct Trie
{
    Trie *child[26];
    int children_num;
    bool last;
    
    Trie();
 
    void insert(const char *str);
    
    int find(const char *str);
    
    virtual ~Trie()
    {
        for(int i = 0; i < 26; i++)
            if(child[i] != nullptr)
                delete child[i];
    }
};
 
Trie* trie[kMaxWordLen],* reversed_trie[kMaxWordLen];

Trie::Trie()
{
    children_num = 0;
    last = false;
        
    for(int i = 0; i < 26; i++)
        child[i] = nullptr;
}
 
void Trie::insert(const char *str)
{
    children_num++;
    if(*str == '\0')
    {
        last = true;
        return;
    }
 
    int cur = *str - 'a';
    
    if(child[cur] == nullptr)
        child[cur] = new Trie();
    child[cur]->insert(str+1);
}
 
int Trie::find(const char *str)
{
    if(*str == '?')
        return children_num;
 
    int cur = *str - 'a';
    
    if(child[cur] == nullptr)
        return 0;
    return child[cur]->find(str+1);
}
 
vector<int> solution(vector<string> words, vector<string> queries)
{
    vector<int> answer;
    
    for(auto i = 0; i < words.size(); i++)
    {
        string word = words[i];
        auto len = word.length();
        
        if(trie[len] == nullptr)
            trie[len] = new Trie();
        trie[len]->insert(word.c_str());
 
        reverse(word.begin(),word.end());
        
        if(reversed_trie[len] == nullptr)
            reversed_trie[len] = new Trie();
        reversed_trie[len]->insert(word.c_str());
    }
 
    map<string,int> m;
    for(auto i = 0; i < queries.size(); i++)
    {
        string query = queries[i];
        int len = static_cast<int>(query.length());
        
        if(m.count(query) != 0)
        {
            answer.push_back(answer[m[query]]);
            continue;
        }
        
        m[query] = i;
        if(query.back() == '?')
        {
            if(trie[len] == NULL)
                answer.push_back(0);
            else
                answer.push_back(trie[len]->find(query.c_str()));
        }
        else
        {
            reverse(query.begin(),query.end());
            
            if(reversed_trie[len] == NULL)
                answer.push_back(0);
            else
                answer.push_back(reversed_trie[len]->find(query.c_str()));
        }
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    auto v = solution({"frodo", "front", "frost", "frozen", "frame", "kakao"}, {"fro??", "????o", "fr???", "fro???", "pro?"});
    
    for(const auto& ele : v)
        cout << ele << endl;
    return 0;
}
