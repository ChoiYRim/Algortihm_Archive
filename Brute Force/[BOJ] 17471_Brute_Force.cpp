#include <queue>
#include <string>
#include <iostream>

using namespace std;

const int kMax = 0x7fffffff;
int N,ans = kMax,total = 0;
int population[128];
int area[16][16];
string visit;

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline int ABS(int a) { return (a > 0 ? a : -a); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        cin >> population[i];
        total += population[i];
    }
    for(int i = 1; i <= N; i++)
    {
        int adj; cin >> adj;
        for(int j = 0; j < adj; j++)
        {
            int a; cin >> a;
            area[i][a] = 1;
        }
    }
    visit = string(N+1,'0');
}

vector<int> getArea(char ch,int& sum)
{
    vector<int> area1;
    for(int i = 1; i <= N; i++)
    {
        if(visit[i] != ch)
        {
            sum += population[i];
            area1.push_back(i);
        }
    }
    return area1;
}

bool isConnected(vector<int> areaV)
{
    if(areaV.size() <= 0)
        return false;
    
    bool check[16] = {0,};
    int index[16] = {0,};
    queue<int> q;
    
    for(int i = 0; i < (int)areaV.size(); i++)
        index[areaV[i]] = 1;
    
    check[areaV[0]] = true;
    q.push(areaV[0]);
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        
        for(int i = 1; i <= N; i++)
        {
            if(area[cur][i] && !check[i] && index[i])
            {
                check[i] = true;
                q.push(i);
            }
        }
    }
    
    for(int i = 0; i < (int)areaV.size(); i++)
    {
        if(!check[areaV[i]])
            return false;
    }
    
    return true;
}

void dfs(int cnt,int index)
{
    if(cnt <= 0)
    {
        int sum1 = 0,sum2 = 0;
        vector<int> area1 = getArea('1',sum1);
        vector<int> area2 = getArea('0',sum2);
        
//        for(int i = 1; i <= N; i++)
//            cout << visit[i] << ' ';
//        cout << '\n';
        
        if(isConnected(area1) && isConnected(area2))
            ans = MIN(ans,ABS(sum1-sum2));
        return;
    }
    
    for(int i = index; i <= N; i++)
    {
        if(visit[i] != '1')
        {
            visit[i] = '1';
            dfs(cnt-1,i);
            visit[i] = '0';
        }
    }
}

int main(int argc,char* argv[])
{
    input();
    
    for(int i = 1; i <= N/2; i++)
    {
        dfs(i,1);
    }
    
    cout << (ans == kMax ? -1 : ans) << '\n';
    return 0;
}
