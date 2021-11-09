#include <queue>
#include <vector>
#include <iostream>

using namespace std;

const int kLimit = 100000;

struct Pos
{
    int x; // current position
    int t; // time
};

int N,K;
queue<Pos> q;
int (*func[3])(int);
int previous[kLimit+1] = {0,};
bool visit[kLimit+1] = {0,};

//inline int MIN(int a,int b) { return (a > b ? b : a); }

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
            int pos = cur.x;
            vector<int> path;
            
            cout << cur.t << '\n';
            while(pos != N)
            {
                path.push_back(pos);
                pos = previous[pos];
            }
            path.push_back(N);
            
            for(int i = (int)path.size()-1; i >= 0; i--)
                cout << path[i] << ' ';
            cout << '\n';
            break;
        }
        
        for(int i = 0; i < 3; i++)
        {
            int nx = func[i](cur.x);
            
            if(!visit[nx])
            {
                visit[nx] = true;
                previous[nx] = cur.x;
                q.push({nx,cur.t+1});
            }
        }
    }
    
    return 0;
}
