#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

int N,ans = 0;
vector<int> num = {2, 6, 10, 11, 15, 20, 51, 55, 60, 100};
bool visit[1024] = {0,};

int convert(int num)
{
    switch(num)
    {
        case 1:
            return 1;
        case 2:
            return 5;
        case 3:
            return 10;
        case 4:
            return 50;
    }
    
    return 0;
}

int main(int argc,char* argv[])
{
    cin >> N;

    if(N == 1)
    {
        cout << 4 << '\n';
        return 0;
    }
    else if(N == 2)
    {
        cout << 10 << '\n';
        return 0;
    }
    for(int i = 3; i <= N; i++)
    {
        memset((bool *)visit,0,sizeof(visit));
        vector<int> v;
        
        for(int j = 0; j < num.size(); j++)
        {
            for(int k = 1; k <= 4; k++)
            {
                int tmp = num[j];
                
                tmp += convert(k);
                if(visit[tmp])
                    continue;
                
                visit[tmp] = true;
                v.push_back(tmp);
            }
        }
        num = v;
    }
    
    cout << num.size() << '\n';
    return 0;
}
