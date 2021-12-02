#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int N,ans = 0;
int height[64] = {0,};
int temp[64] = {0,};

int main()
{
    int rab,cat;
    
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        if(tmp >= N)
        {
            cout << 0 << '\n';
            return 0;
        }
        height[tmp]++;
    }
    
    // 각 집합의 크기
    for(rab = 0; rab <= (N/2); rab++)
    {
        memcpy(temp, height, sizeof(height));
        
        int cnt = 1;
        bool flag = true;
        vector<int> v;
        
        cat = N-rab;
        for(int rh = rab-1; rh >= 0; rh--)
        {
            if(!temp[rh])
            {
                flag = false;
                break;
            }
            temp[rh]--;
        }
        
        if(!flag)
            continue;
        
        for(int ch = cat-1; ch >= 0; ch--)
        {
            if(!temp[ch])
            {
                flag = false;
                break;
            }
            temp[ch]--;
            if(temp[ch])
            {
                flag = false;
                break;
            }
            v.push_back(ch);
        }
        
        if(!flag)
            continue;
        
        for(int i = 0; i < (int)v.size(); i++)
            cnt *= (height[v[i]]);
        
        if(rab != cat)
            ans += (cnt*2);
        else
            ans += cnt;
    }
    
    cout << ans << '\n';
    return 0;
}
