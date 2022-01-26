#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int N;

int main()
{
    priority_queue<int> maxh;
    priority_queue<int,vector<int>,greater<int>> minh;
    
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        
        if(maxh.empty())
            maxh.push(tmp);
        else if(maxh.size() != minh.size())
            minh.push(tmp);
        else
            maxh.push(tmp);
        
        if(!maxh.empty() && !minh.empty() && !(maxh.top() <= minh.top()))
        {
            int MAX = maxh.top();
            int MIN = minh.top();
            
            maxh.pop();
            minh.pop();
            
            maxh.push(MIN);
            minh.push(MAX);
        }
        
        printf("%d\n", maxh.top());
    }
    
    return 0;
}
