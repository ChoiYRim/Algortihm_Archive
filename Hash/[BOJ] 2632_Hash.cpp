#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int demand,N,M;
vector<int> A,B;
unordered_map<int,int> a,b;
int ta[1024]; // a의 0번째 인덱스부터 마지막 인덱스까지 피자의 연속된 크기
int tb[1024];

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int idxA = 0,idxB = 0;
    int aSize = 0,bSize = 0;
    
    cin >> demand;
    cin >> M >> N;
    for(int i = 0; i < M+N; i++)
    {
        int tmp; cin >> tmp;
        
        if(i < M)
        {
            if(!idxA)
                ta[idxA] = tmp;
            else
                ta[idxA] = ta[idxA-1]+tmp;
            idxA++;
            
            A.push_back(tmp);
            aSize += tmp;
        }
        else
        {
            if(!idxB)
                tb[idxB] = tmp;
            else
                tb[idxB] = tb[idxB-1]+tmp;
            idxB++;
            
            B.push_back(tmp);
            bSize += tmp;
        }
    }
    
    // 전체 선택
    a.insert({aSize,1});
    b.insert({bSize,1});
}

void Select(int limit,int total[1024],unordered_map<int,int>& m)
{
    unordered_map<int,int>::iterator it;
    
    for(int cnt = 1; cnt < limit; cnt++)
    {
        for(int i = 0; i < limit; i++) // 시작 인덱스
        {
            int amount = 0;
            int j = i+(cnt-1); // 끝 인덱스
            
            if(j >= limit)
            {
                amount += total[j%limit];
                j = limit-1;
            }
            if(i-1 >= 0)
                amount += (total[j]-total[i-1]);
            else
                amount += total[j];
            
            if(amount > demand)
                continue;
            
            if((it = m.find(amount)) != m.end())
            {
                it->second++;
                continue;
            }
            
            m.insert({amount,1});
        }
    }
}

int solve()
{
    int ret = 0;
    
    // 아무것도 고르지 않았을 경우
    a.insert({0,1});
    b.insert({0,1});
    
    // 1개 이상 골랐을 경우
    Select(M,ta,a);
    Select(N,tb,b);
    
    for(auto ait = a.begin(); ait != a.end(); ait++)
    {
        int pizzaA = ait->first;
        auto bit = b.find(demand-pizzaA);
        
        if(bit != b.end())
            ret += (ait->second*bit->second);
    }
    
    return ret;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
