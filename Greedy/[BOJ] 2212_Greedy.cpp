#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, K;
vector<int> sensors;

void input()
{
    cin >> N >> K;
    sensors = vector<int>(N, 0);
    for(int i = 0; i < N; i++) cin >> sensors[i];
    
    sort(sensors.begin(), sensors.end());
}

int solve()
{
    if(N == K) return 0;
    
    int answer = 0;
    vector<int> dist(N-1, 0);
    
    for(int i = 0; i < N-1; i++) dist[i] = sensors[i+1]-sensors[i];
    sort(dist.begin(), dist.end());
    for(int i = 0; i < N-K; i++) answer += dist[i];
    
    return answer;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
