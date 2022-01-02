#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using P = pair<int,int>;

int N,M,D,ans = 0;
bool shoot[16];
vector<pair<P,int>> target;

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

inline int getDistance(int ay,int ax,int ey,int ex) { return abs(ay-ey)+abs(ax-ex); }

void input()
{
    cin >> N >> M >> D;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            bool tmp; cin >> tmp;
            if(tmp)
                target.push_back({{y,x},0});
        }
    }
}

int getCloseTarget(P s)
{
    int ret = -1,minDist = 0x7fffffff;
    P cur = {-1,-1};
    
    for(int i = 0; i < (int)target.size(); i++)
    {
        P tPos = target[i].first;
        int dist = getDistance(s.first, s.second, tPos.first, tPos.second);
        
        if(dist <= D)
        {
            if(ret != -1)
            {
                if(minDist == dist)
                {
                    if(cur.second > tPos.second)
                    {
                        ret = i;
                        cur = tPos;
                    }
                }
                else if(minDist > dist)
                {
                    minDist = dist;
                    ret = i;
                    cur = tPos;
                }
            }
            else
            {
                ret = i;
                cur = tPos;
                minDist = dist;
            }
        }
    }
    
    return ret;
}

void dfs(int cnt,int index)
{
    if(cnt <= 0)
    {
        int num = 0;
        vector<P> pos;
        auto save = target;
        
        //cout << "shoot : ";
        for(int i = 0; i < M; i++)
        {
            if(shoot[i])
                pos.push_back({N,i});
            //cout << shoot[i] << ' ';
        }
        //cout << "\t";
        
        while(target.size() != 0)
        {
            for(int i = 0; i < (int)pos.size(); i++)
            {
                int idx = getCloseTarget(pos[i]);
                
                if(idx != -1)
                {
                    target[idx].second++;
                    if(target[idx].second == 1)
                        num++;
                }
            }
            
            for(int i = 0; i < (int)target.size(); i++)
            {
                if(target[i].second > 0)
                {
                    target.erase(target.begin()+i);
                    i--;
                    continue;
                }
                
                target[i].first.first++;
                if(target[i].first.first >= N)
                {
                    target.erase(target.begin()+i);
                    i--;
                }
            }
        }
        
        //cout << "num : " << num << '\n';
        ans = max(ans,num);
        target = save;
        return;
    }
    
    for(int i = index; i < M; i++)
    {
        if(!shoot[i])
        {
            shoot[i] = true;
            dfs(cnt-1,i);
            shoot[i] = false;
        }
    }
}

int main()
{
    input();
    
    dfs(3,0);
    
    cout << ans << '\n';
    return 0;
}
