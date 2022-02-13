#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

const int EMPTY = 6;
const int BLACK = -1;

struct Node
{
    int y;
    int x;
};

struct Group
{
    vector<Node> nodes; // 미리 정렬돼 있어야 함
    int r; // rainbow numbers
};

int N,M;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
vector<vector<int>> board;

bool comp_node(const Node& n1,const Node& n2)
{
    if(board[n1.y][n1.x] == board[n2.y][n2.x])
    {
        if(n1.y == n2.y)
            return n1.x < n2.x;
        return n1.y < n2.y;
    }
    
    return board[n1.y][n1.x] > board[n2.y][n2.x];
}

bool comp_group(const Group& g1,const Group& g2)
{
    if(g1.nodes.size() == g2.nodes.size())
    {
        if(g1.r == g2.r)
        {
            if(g1.nodes[0].y == g2.nodes[0].y)
                return g1.nodes[0].x > g2.nodes[0].x;
            
            return g1.nodes[0].y > g2.nodes[0].y;
        }
        
        return g1.r > g2.r;
    }
    
    return g1.nodes.size() > g2.nodes.size();
}

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < N)); }

void print_board()
{
    cout << "MAP" << endl;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            printf("%2d ", board[y][x]);
        }
        cout << endl;
    }
}

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    board = vector<vector<int>>(N+1,vector<int>(N+1,0));
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            cin >> board[y][x];
        }
    }
}

auto get_blocks()
{
    vector<vector<bool>> visit(N+1,vector<bool>(N+1,0));
    vector<Group> groups;
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            if(board[y][x] <= 0 || board[y][x] > 5)
                continue;
            if(visit[y][x])
                continue;
            
            queue<Node> q;
            vector<Node> v,r;
            int rainbow = 0,color = board[y][x];
            
            visit[y][x] = 1;
            q.push({y,x});
            while(!q.empty())
            {
                int cy = q.front().y;
                int cx = q.front().x;
                v.push_back({cy,cx});
                q.pop();
                
                for(int i = 0; i < 4; i++)
                {
                    int ny = cy+dy[i];
                    int nx = cx+dx[i];
                    
                    if(!range(ny,nx))
                        continue;
                    if(visit[ny][nx])
                        continue;
                    if(board[ny][nx] == EMPTY)
                        continue;
                    if(board[ny][nx] == BLACK)
                        continue;
                    if(board[ny][nx] != 0 && board[ny][nx] != color)
                        continue;
                    
                    visit[ny][nx] = 1;

                    if(board[ny][nx] == 0)
                    {
                        rainbow++;
                        r.push_back({ny,nx});
                        q.push({ny,nx});
                        continue;
                    }
                    
                    q.push({ny,nx});
                }
            }
            if(v.size() < 2 || v.size()-rainbow < 1)
                continue;
            
            sort(v.begin(),v.end(),comp_node);
            groups.push_back({v,rainbow});
            for(auto& a : r)
                visit[a.y][a.x] = 0;
        }
    }
    
    sort(groups.begin(),groups.end(),comp_group);
    return groups;
}

int get_score(const Group& g)
{
    for(const auto& pos : g.nodes)
    {
        int y = pos.y;
        int x = pos.x;
        
        board[y][x] = EMPTY;
    }
    
    return static_cast<int>(g.nodes.size()*g.nodes.size());
}

void fall()
{
    for(int x = 0; x < N; x++)
    {
        int y = N-1;
        int pos = y;
        
        while(y >= 0)
        {
            if(board[y][x] == BLACK)
            {
                pos = y-1;
            }
            else if(board[y][x] != EMPTY)
            {
                if(pos != y)
                {
                    board[pos][x] = board[y][x];
                    board[y][x] = EMPTY;
                }
                pos--;
            }
            
            y--;
        }
    }
}

void turn()
{
    vector<vector<int>> newBoard(N+1,vector<int>(N+1,0));
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            newBoard[N-1-x][y] = board[y][x];
        }
    }
    
    board = newBoard;
}

int solve()
{
    int result = 0;
    vector<Group> groups;
    
    while((groups = get_blocks()).size() > 0)
    {
        Group largest = groups[0];
        
        result += get_score(largest);
        
        fall();
                
        turn();
                
        fall();
        
        //print_board();
    }
    
    return result;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
