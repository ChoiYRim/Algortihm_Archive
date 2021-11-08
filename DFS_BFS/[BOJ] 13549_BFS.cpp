#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Pos
{
    int x; // current position
    int t; // time
};

struct compare
{
    bool operator()(const Pos& p1,const Pos& p2) { return (p1.t > p2.t); }
};

int N,K;
priority_queue<Pos,vector<Pos>,compare> q;
const int kLimit = 100000;
bool visit[kLimit+1] = {0,};
int (*func[3])(int);

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline bool range(int x) { return (0 <= x && x <= kLimit); }

inline int plus_one(int cur) { return (range(cur+1) ? cur+1 : cur); }

inline int minus_one(int cur) { return (range(cur-1) ? cur-1 : cur); }

inline int multi_one(int cur) { return (range(cur*2) ? cur*2 : cur); }

int main()
{
    cin >> N >> K;
    func[0] = plus_one; func[1] = minus_one; func[2] = multi_one;
    
    q.push({N,0});
    while(!q.empty())
    {
        Pos cur = q.top();
        q.pop();
        
        if(visit[cur.x])
            continue;
        if(cur.x == K)
        {
            cout << cur.t << '\n';
            return 0;
        }
        
        visit[cur.x] = true;
        for(int i = 0; i < 3; i++)
        {
            int nx = func[i](cur.x);
            
            if(i < 2)
                q.push({nx,cur.t+1});
            else
                q.push({nx,cur.t});
        }
    }
    
    return 0;
}
