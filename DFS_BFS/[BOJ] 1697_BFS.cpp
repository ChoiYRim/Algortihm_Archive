#include <queue>
#include <iostream>

using namespace std;

struct Pos
{
    int x; // current position
    int t; // time
};

int N,K;
const int kLimit = 100000;
queue<Pos> q;
bool visit[kLimit+1] = {0,};
int (*func[3])(int);

inline bool range(int x) { return (0 <= x && x <= kLimit); }

inline int plus_one(int cur) { return (range(cur+1) ? cur+1 : cur); }

inline int minus_one(int cur) { return (range(cur-1) ? cur-1 : cur); }

inline int multi_one(int cur) { return (range(cur*2) ? cur*2 : cur); }

int main()
{
    cin >> N >> K;
    
    func[0] = plus_one; func[1] = minus_one; func[2] = multi_one;
    visit[N] = true;
    q.push({N,0});
    while(!q.empty())
    {
        Pos cur = q.front();
        q.pop();
        
        if(cur.x == K)
        {
            cout << cur.t << '\n';
            return 0;
        }
        
        for(int i = 0; i < 3; i++)
        {
            int next = func[i](cur.x);
            
            if(visit[next])
                continue;
            
            visit[next] = true;
            q.push({next,cur.t+1});
        }
    }
    
    return 0;
}
