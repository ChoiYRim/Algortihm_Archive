#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int A;
    int B;
    int C;
};

bool visit[1501][1501];

int main(int argc,char* argv[])
{
    int a,b,c; // a+b+c는 항상 일정
    queue<Node> q;
    bool exists = false;
    
    scanf("%d%d%d", &a, &b, &c);
    
    q.push({a,b,c});
    while(!q.empty())
    {
        int A = q.front().A;
        int B = q.front().B;
        int C = q.front().C;
        q.pop();
        
        if(A == B && B == C)
        {
            exists = true;
            break;
        }
        
        vector<int> cur = {A,B,C},next(3);
        sort(cur.begin(),cur.end());
        
        if(cur[0] != cur[1]) // 0,1
        {
            next[0] = cur[0]*2;
            next[1] = cur[1]-cur[0];
            next[2] = cur[2];
            if(!visit[next[0]][next[1]])
            {
                visit[next[0]][next[1]] = 1;
                q.push({next[0],next[1],next[2]});
            }
        }
        if(cur[0] != cur[2]) // 0,2
        {
            next[0] = cur[0]*2;
            next[1] = cur[1];
            next[2] = cur[2]-cur[0];
            if(!visit[next[0]][next[2]])
            {
                visit[next[0]][next[2]] = 1;
                q.push({next[0],next[1],next[2]});
            }
        }
        if(cur[1] != cur[2]) // 1,2
        {
            next[0] = cur[0];
            next[1] = cur[1]*2;
            next[2] = cur[2]-cur[1];
            if(!visit[next[1]][next[2]])
            {
                visit[next[1]][next[2]] = 1;
                q.push({next[0],next[1],next[2]});
            }
        }
    }
    
    cout << (exists ? 1 : 0) << endl;
    return 0;
}
