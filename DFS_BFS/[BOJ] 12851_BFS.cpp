#include <queue>
#include <climits>
#include <iostream>

using namespace std;

struct Pos
{
    int x; // current position
    int t; // time
};

int N,K;
const int kLimit = 100000;
pair<int,int> result;
int (*func[3])(int);
queue<Pos> q;
int visit[kLimit+1] = {0,}; // visited time

inline bool range(int x) { return (0 <= x && x <= kLimit); }

inline int plus_one(int x) { return (range(x+1) ? x+1 : x); }

inline int minus_one(int x) { return (range(x-1) ? x-1 : x); }

inline int multi_two(int x) { return (range(x*2) ? x*2 : x); }

int main()
{
    cin >> N >> K;
    q.push({N,0});
    result = {INT_MAX,0};
    func[0] = plus_one; func[1] = minus_one; func[2] = multi_two;
    
    while(!q.empty())
    {
        Pos cur = q.front();
        q.pop();
        
        if(visit[cur.x] > 0 && visit[cur.x] < cur.t)
            continue;
        if(cur.x == K)
        {
            if(cur.t < result.first)
                result = {cur.t,1};
            else if(cur.t == result.first)
                result.second++;
            continue;
        }
        
        visit[cur.x] = cur.t;
        for(int i = 0; i < 3; i++)
        {
            int nx = func[i](cur.x);
            int nt = cur.t+1;
            
            q.push({nx,nt});
        }
    }
    
    cout << result.first << '\n';
    cout << result.second << '\n';
    return 0;
}
