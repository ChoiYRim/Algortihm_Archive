#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N,K;
deque<int> d2;
int dy[2] = {0,1};
int dx[2] = {1,0};

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> K;
    for(int i = 0 ; i < N; i++)
    {
        int tmp; cin >> tmp;
        d2.push_back(tmp);
    }
}

// 높이가 2이상인 것들의 높이
inline int topLength(deque<deque<int>>& d3)
{
    return static_cast<int>(d3[0].size());
}

// 높이가 2이상인 것들을 제외한 너비
int bottomLength(deque<deque<int>>& d3)
{
    int width = 0;
    
    for(size_t i = 0; i < d3.size(); i++)
    {
        if(d3[i].size() > 1)
            continue;
        width++;
    }
    
    return width;
}

deque<deque<int>> splitTop(deque<deque<int>>& d3,int height)
{
    int cnt = 0;
    deque<deque<int>> ret;
    for(size_t i = 0; i < d3.size(); i++)
    {
        if(d3[i].size() >= height)
        {
            ret.push_back(d3[i]);
            cnt++;
        }
    }
    
    while(cnt > 0)
    {
        d3.pop_front();
        cnt--;
    }
    
    reverse(ret.begin(),ret.end());
    return ret;
}

void mergeDeque(deque<deque<int>>& d3,deque<deque<int>>& split)
{
    for(size_t i = 0; i < split.size(); i++)
    {
        for(size_t j = 0; j < split[i].size(); j++)
        {
            d3[j].push_back(split[i][j]);
        }
    }
}

deque<deque<int>> reflectDiff(deque<deque<int>>& d3)
{
    auto tmp_d3 = d3;
    
    for(int i = 0; i < d3.size(); i++)
    {
        for(int j = 0; j < d3[i].size(); j++)
        {
            int cur = d3[i][j];
            for(int k = 0; k < 2; k++)
            {
                int ny = i+dy[k];
                int nx = j+dx[k];
                
                if(ny < 0 || nx < 0)
                    continue;
                if(d3[ny].size() <= nx || d3.size() <= ny)
                    continue;
                
                int next = d3[ny][nx];
                int diff = abs(cur-next);
                
                if(diff / 5 < 1)
                    continue;
                
                if(cur < next)
                {
                    if(next-diff/5 >= 0)
                    {
                        tmp_d3[i][j] += diff/5;
                        tmp_d3[ny][nx] -= diff/5;
                    }
                }
                else if(cur > next)
                {
                    if(cur-diff/5 >= 0)
                    {
                        tmp_d3[i][j] -= diff/5;
                        tmp_d3[ny][nx] += diff/5;
                    }
                }
            }
        }
    }
    
    return tmp_d3;
}

void putHalf(deque<deque<int>>& d3)
{
    
    deque<deque<int>> half;
    for(int i = 0; i < d3.size(); i++)
    {
        int left = 0,right = static_cast<int>(d3[i].size()-1);
        
        deque<int> tmp;
        for(int j = 0; j <= (left+right)/2; j++)
        {
            tmp.push_back(d3[i].front());
            d3[i].pop_front();
        }
        reverse(tmp.begin(),tmp.end());
        half.push_back(tmp);
    }
    
    //reverse(half.begin(),half.end());
    for(auto& h : half)
        d3.push_front(h);
}

void arrange(int MAX,int MIN)
{
    // 가장 물고기가 적은 어항에 1마리 넣기 -> step 1
    for(auto& ele : d2)
        if(ele == MIN)
            ele++;
    
    // 가장 왼쪽의 어항을 그 어항의 오른쪽 위에 두기
    deque<deque<int>> d3;
    d3.push_back({d2[1],d2[0]});
    for(size_t i = 2; i < d2.size(); i++) d3.push_back({d2[i]});
    
    // 2개 이상 쌓여있는 어항을 띄워 시계 방향으로 90도 회전시키고 원래 어항 위에 둔다.
    int top = 0,bottom = 0;
    while((top = topLength(d3)) <= (bottom = bottomLength(d3)))
    {
        deque<deque<int>> split = splitTop(d3,top);
        mergeDeque(d3,split);
    }
    
    // 차이 반영
    d3 = reflectDiff(d3);
    d2.clear();
    for(int i = 0; i < d3.size(); i++)
        d2.insert(d2.end(),d3[i].begin(),d3[i].end());
    d3.clear();
    d3.push_back(d2);
    for(int i = 0; i < 2; i++)
    {
        putHalf(d3);
    }
    
    d2.clear();
    d3 = reflectDiff(d3);
    reverse(d3.begin(),d3.end());
    for(int i = 0; i < d3[0].size(); i++)
    {
        for(int j = 0; j < d3.size(); j++)
            d2.push_back(d3[j][i]);
    }
}

int solve()
{
    int clear = 0;
    int MAX = *max_element(d2.begin(),d2.end());
    int MIN = *min_element(d2.begin(),d2.end());
    
    while(MAX-MIN > K)
    {
        arrange(MAX,MIN);
        
        MAX = *max_element(d2.begin(),d2.end());
        MIN = *min_element(d2.begin(),d2.end());
        clear++;
    }
    
    return clear;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
