#include <string>
#include <iostream>

using namespace std;

string A,B,result = "0";
bool visit[16] = {0,};

void DFS(string cur)
{
    if(cur.length() >= A.length())
    {
        if(result.length() > 0 && stoi(cur) < stoi(B) && stoi(cur) > stoi(result))
            result = cur;
        return;
    }
        
    for(int i = 0; i < (int)A.length(); i++)
    {
        int curA = A[i]-'0';
        
        if(!visit[i])
        {
            if(cur.length() <= 0 && !curA)
                continue;
            visit[i] = true;
            cur.push_back(curA+'0');
            DFS(cur);
            cur.pop_back();
            visit[i] = false;
        }
    }
}

int main(int argc,char* argv[])
{
    cin >> A >> B;
    
    DFS("");
    
    if(result == "0")
        cout << -1 << '\n';
    else
        cout << result << '\n';
    return 0;
}
