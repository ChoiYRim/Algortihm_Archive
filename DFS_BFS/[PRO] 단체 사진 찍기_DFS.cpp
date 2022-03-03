#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Dist
{
    char c;
    char r;
    int dist;
};

string str = "ACFJMNRT";
vector<bool> visit(8,0);
map<char,vector<Dist>> m;

void print_map()
{
    for(auto it = m.begin(); it != m.end(); it++)
    {
        printf("[%c] : ", it->first);
        for(int i = 0; i < it->second.size(); i++)
        {
            printf("{%c %c %d} ", it->second[i].c, it->second[i].r, it->second[i].dist);
        }
        printf("\n");
    }
}

void split(const vector<string>& data)
{
    m.clear();
    
    for(int i = 0; i < data.size(); i++)
    {
        string s = data[i];
        m[s[0]].push_back({s[2],s[3],s[4]-'0'});
    }
}

void dfs(int depth,string cur,int& answer)
{
    if(depth == str.length())
    {
        for(int i = 0; i < cur.length(); i++)
        {
            char from = cur[i];
            for(int j = 0; j < cur.length(); j++)
            {
                if(i == j)
                    continue;
                
                char to = cur[j];
                for(auto it = m[from].begin(); it != m[from].end(); it++)
                {
                    if(it->c != to)
                        continue;
                    
                    int diff = abs(i-j)-1;
                    int dist = it->dist;
                    char r   = it->r;
                    
                    if(r == '=')
                    {
                        if(diff != dist)
                            return;
                    }
                    else if(r == '<')
                    {
                        if(diff >= dist)
                            return;
                    }
                    else if(r == '>')
                    {
                        if(diff <= dist)
                            return;
                    }
                }
            }
        }
        
        answer++;
        return;
    }
    
    for(int i = 0; i < str.length(); i++)
    {
        if(visit[i])
            continue;
        
        visit[i] = true;
        cur.push_back(str[i]);
        dfs(depth+1,cur,answer);
        cur.pop_back();
        visit[i] = false;
    }
}

int solution(int n, vector<string> data)
{
    int answer = 0;
    
    split(data);
    
    //print_map();
    
    dfs(0,"",answer);
    
    return answer;
}

int main()
{
    cout << solution(2, {"M~C<2", "C~M>1"}) << endl;
    return 0;
}
