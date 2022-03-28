#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int G,P;
vector<int> planes,gates;

int find(int gate)
{
    if(gates[gate] == gate) return gate;
    return gates[gate] = find(gates[gate]);
}

void union_set(int u,int v)
{
    u = find(u);
    v = find(v);
    gates[u] = v;
}

void input()
{
    cin >> G;
    cin >> P;
    gates = vector<int>(G+1,0);
    for(int i = 0; i < P; i++)
    {
        int gate; cin >> gate;
        planes.push_back(gate);
    }
    for(int i = 1; i <= G; i++)
        gates[i] = i;
}

int solve()
{
    int cnt = 0;
    
    for(int i = 0; i < P; i++)
    {
        int gate = planes[i];
        
        if(find(gate) == 0) break;
        
        cnt++;
        union_set(find(gate),find(gate)-1);
    }
    
    return cnt;
}

int main(int argc,char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
