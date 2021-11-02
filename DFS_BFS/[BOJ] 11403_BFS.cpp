#include <queue>
#include <iostream>

using namespace std;

int N;
bool graph[128][128] = {0,};
bool result[128][128] = {0,};

void print()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << result[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            bool edge; cin >> edge;
            graph[i][j] = edge;
        }
    }
    
    for(int start = 0; start < N; start++)
    {
        queue<int> q;
        q.push(start);
        bool visit[128] = {0,};
        
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            
            for(int next = 0; next < N; next++)
            {
                if(graph[cur][next] && !visit[next])
                {
                    q.push(next);
                    visit[next] = true;
                    result[start][next] = 1;
                }
            }
        }
    }
    
    print();
    return 0;
}
