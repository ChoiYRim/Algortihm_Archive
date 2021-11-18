#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N,M;
vector<int> num;
int result[8] = {0,};

void DFS(int depth)
{
    if(depth >= M)
    {
        for(int i = 0; i < M; i++)
            cout << result[i] << ' ';
        cout << '\n';
        return;
    }
    
    for(int i = 0; i < (int)num.size(); i++)
    {
        if(depth > 0)
        {
            if(result[depth-1] <= num[i])
            {
                result[depth] = num[i];
                DFS(depth+1);
            }
            continue;
        }
        
        result[depth] = num[i];
        DFS(depth+1);
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        num.push_back(tmp);
    }
    
    sort(num.begin(),num.end());
    
    DFS(0);
    return 0;
}
