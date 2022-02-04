#include <queue>
#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;

int N,W,L;
queue<int> trucks;
deque<pair<int,int>> bridge; // [time,weight]

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> W >> L;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        trucks.push(tmp);
    }
}

int solve()
{
    int hours = 1;
    int bridge_weight = trucks.front();
    
    bridge.push_front({0,bridge_weight});
    trucks.pop();
    while(!bridge.empty())
    {
        if(hours-bridge.back().first >= W)
        {
            bridge_weight -= bridge.back().second;
            bridge.pop_back();
        }
        
        int truck_weight = 0;
        
        if(!trucks.empty())
            truck_weight = trucks.front();
        
        if(truck_weight && bridge_weight+truck_weight <= L)
        {
            bridge_weight += truck_weight;
            bridge.push_front({hours,truck_weight});
            trucks.pop();
        }
        
        hours++;
    }
    
    return hours;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
