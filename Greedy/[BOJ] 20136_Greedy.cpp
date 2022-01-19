#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N,K;
vector<int> devices;
vector<int> flugs;

void input()
{
    cin >> N >> K;
    for(int i = 0; i < K; i++)
    {
        int device; cin >> device;
        devices.push_back(device);
    }
    flugs = vector<int>(N,0);
}

int main()
{
    int pull = 0;
    
    input();
    for(auto idx = 0; idx < devices.size(); idx++)
    {
        int device = devices[idx];
        auto it = std::find(flugs.begin(),flugs.end(),device); // 현재 꼽혀 있는가?
        
        if(it != flugs.end()) // yes
            continue;
        
        // no
        it = std::find(flugs.begin(),flugs.end(),0); // 아직 안꼽힌 자리가 있는가?
        if(it != flugs.end()) // yes
        {
            *it = device; // insert
            continue;
        }
        
        // no
        vector<int> dists(N,0x7fffffff); // 디바이스 사이의 거리
        for(auto i = 0; i < flugs.size(); i++)
        {
            auto next = std::find(devices.begin()+idx+1, devices.end(),flugs[i]);
            if(*next != flugs[i])
                continue;
            
            auto nextIdx = next-devices.begin();
            dists[i] = static_cast<int>(nextIdx-idx);
        }
        
        int target = 0,dist = dists[target];
        for(auto i = 1; i < dists.size(); i++)
        {
            if(dist < dists[i])
            {
                target = i;
                dist = dists[i];
            }
        }
        
        flugs[target] = device;
        pull++;
    }
    
    cout << pull << endl;
    return 0;
}
