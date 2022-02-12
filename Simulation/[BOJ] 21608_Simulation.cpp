#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int N;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
vector<vector<int>> Map;
bool priority[512][512];
queue<int> students;

inline bool range(int y,int x) { return ((y >= 1 && y <= N) && (x >= 1 && x <= N)); }

bool comp(const pair<pair<int,int>,int>& p1,const pair<pair<int,int>,int>& p2)
{
    if(p1.second == p2.second)
    {
        const pair<int,int>& pos1 = p1.first;
        const pair<int,int>& pos2 = p2.first;
        
        if(pos1.first == pos2.first)
            return pos1.second < pos2.second;
        return pos1.first < pos2.first;
    }
    
    return p1.second > p2.second;
}

void print_map()
{
    for(int y = 1; y <= N; y++)
    {
        for(int x = 1; x <= N; x++)
        {
            cout << Map[y][x] << ' ';
        }
        cout << endl;
    }
}

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N;
    Map = vector<vector<int>>(N+2,vector<int>(N+2,0));
    for(int i = 0; i < N*N; i++)
    {
        int student; cin >> student;
        students.push(student);
        for(int j = 0; j < 4; j++)
        {
            int tmp; cin >> tmp;
            priority[student][tmp] = true;
        }
    }
}

auto get(int student)
{
    vector<vector<pair<pair<int,int>,int>>> position; // 주변에 좋아하는 학생의 수가 0~4인 위치
    position = vector<vector<pair<pair<int,int>,int>>>(5,vector<pair<pair<int,int>,int>>());
    
    for(int y = 1; y <= N; y++)
    {
        for(int x = 1; x <= N; x++)
        {
            if(Map[y][x]) continue;
            
            int cnt = 0,empty_cnt = 0;
            for(int i = 0; i < 4; i++)
            {
                int ny = y+dy[i];
                int nx = x+dx[i];
                int adj;
                
                if(!range(ny,nx))
                    continue;
                
                adj = Map[ny][nx];
                if(!adj)
                {
                    empty_cnt++;
                    continue;
                }
                if(priority[student][adj])
                    cnt++;
            }
            position[cnt].push_back({{y,x},empty_cnt});
        }
    }
    
    return position;
}

void find_position(int student)
{
    // 1. 비어있는 칸 중에서 좋아하는 학생이 주변에 제일 많은 칸으로 지정
    int y,x,idx = 0;
    auto pos = get(student);
    
    for(int i = 4; i >= 0; i--)
    {
        if(pos[i].size() > 0)
        {
            idx = i;
            break;
        }
    }
    
    if(pos[idx].size() < 1)
        return;
    
    // 2. 1을 만족하는 것이 여러개라면 주변에 비어있는 칸이 제일 많은 칸으로 지정
    // 3. 2를 만족하는 것이 여러개라면 행과 열이 작은 순서대로
    sort(pos[idx].begin(),pos[idx].end(),comp);
    y = pos[idx][0].first.first;
    x = pos[idx][0].first.second;
    
    Map[y][x] = student;
    return;
}

int calculate()
{
    int sum = 0;
    int convert[5] = {0,1,10,100,1000};
    
    for(int y = 1; y <= N; y++)
    {
        for(int x = 1; x <= N; x++)
        {
            int cnt = 0,cur = Map[y][x];
            
            for(int i = 0; i < 4; i++)
            {
                int ny = y+dy[i];
                int nx = x+dx[i];
                int adj;
                
                if(!range(ny,nx))
                    continue;
                
                adj = Map[ny][nx];
                if(priority[cur][adj])
                    cnt++;
            }
            
            sum += convert[cnt];
        }
    }
    
    return sum;
}

int solve()
{
    while(!students.empty())
    {
        int student = students.front();
        students.pop();
        
        find_position(student);
    }
    
    return calculate();
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    
    //print_map();
    return 0;
}
