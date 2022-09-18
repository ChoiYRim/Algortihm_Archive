#include <deque>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int N;
deque<int> a, p;
unordered_map<int, pair<int, int>> answer, player;

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        a.push_back(tmp);
    }
    for(int i = 0; i < N; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        p.push_back(tmp);
    }
    
    for(int i = 0; i < N; i++)
    {
        if(i == 0)
        {
            if(N < 2)
            {
                answer.insert({a[i], {a[N-1], a[0]}});
                player.insert({p[i], {p[N-1], p[0]}});
            }
            else
            {
                answer.insert({a[i], {a[N-1], a[1]}});
                player.insert({p[i], {p[N-1], p[1]}});
            }
        }
        else if(i == N-1)
        {
            answer.insert({a[i], {a[N-2], a[0]}});
            player.insert({p[i], {p[N-2], p[0]}});
        }
        else
        {
            answer.insert({a[i], {a[i-1], a[i+1]}});
            player.insert({p[i], {p[i-1], p[i+1]}});
        }
    }
}

string solve()
{
    bool reverse = false;
    
    if(player.find(a[0]) == player.end()) return "bad puzzle";
    
    auto aorder = answer[a[0]];
    auto porder = player[a[0]];
    
    if(aorder.first != porder.first || aorder.second != porder.second)
    {
        if(aorder.first != porder.second || aorder.second != porder.first)
            return "bad puzzle";
        reverse = true;
    }
    
    for(int i = 1; i < N; i++)
    {
        int cur = a[i];
        
        if(player.find(cur) == player.end()) return "bad puzzle";
        
        aorder = answer[cur];
        porder = player[cur];
        
        if(!reverse)
        {
            if(aorder.first != porder.first || aorder.second != porder.second)
                return "bad puzzle";
        }
        else
        {
            if(aorder.first != porder.second || aorder.second != porder.first)
                return "bad puzzle";
        }
    }
    return "good puzzle";
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
