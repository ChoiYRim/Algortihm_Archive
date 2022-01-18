#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N,K;
vector<int> flug;
vector<int> devices;
const int kInf = 0x7fffffff;

int main()
{
    int pull = 0;
    
    cin >> N >> K;
    for(int i = 0; i < K; i++)
    {
        int device; cin >> device;
        devices.push_back(device);
    }
    
    flug = vector<int>(N,0);
    for(size_t cur = 0; cur < K; cur++)
    {
        int curDevice = devices[cur];
        
        auto it = std::find(flug.begin(),flug.end(),curDevice);
        if(it != flug.end()) // 이미 꽂혀 있음
            continue;
        
        it = std::find(flug.begin(),flug.end(),0);
        if(it != flug.end()) // 아직 안꽂은 칸이 존재
        {
            *it = curDevice;
            continue;
        }
        
        vector<int> dists(N,kInf);
        for(size_t i = 0; i < N; i++)
        {
            int flugDevice = flug[i];
            for(size_t j = cur+1; j < K; j++)
            {
                if(flugDevice == devices[j])
                {
                    dists[i] = static_cast<int>(j-cur);
                    break;
                }
            }
        }
        
        size_t pullout = 0;
        int dist = dists[0];
        for(size_t i = 1; i < N; i++)
        {
            if(dist < dists[i])
            {
                pullout = i;
                dist = dists[i];
            }
        }
        
        flug[pullout] = curDevice;
        pull++;
    }
    
    cout << pull << std::endl;
    return 0;
}
