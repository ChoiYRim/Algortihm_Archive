#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((y >= 0 && y < 5) && (x >= 0 && x < 5));}

inline int get_distance(int y1,int x1,int y2,int x2) { return abs(y1-y2)+abs(x1-x2); }

bool is_possible(const vector<string>& place,const pair<int,int>& p1,const pair<int,int>& p2)
{
    vector<vector<bool>> visit(5,vector<bool>(5,0));
    queue<pair<pair<int,int>,int>> q;
    
    q.push({{p1.first,p1.second},0});
    visit[p1.first][p1.second] = 1;
    while(!q.empty())
    {
        int y = q.front().first.first;
        int x = q.front().first.second;
        int d = q.front().second;
        q.pop();
        
        if(y == p2.first && x == p2.second)
            return false;
        if(d > 2)
            continue;
        
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny,nx))
                continue;
            if(visit[ny][nx])
                continue;
            if(place[ny][nx] == 'X')
                continue;
            
            visit[ny][nx] = 1;
            q.push({{ny,nx},d+1});
        }
    }
    
    return true;
}

int check(const vector<string>& place,const vector<pair<int,int>>& persons)
{
    if(!persons.size())
        return 1;
    
    for(size_t i = 0; i < persons.size()-1; i++)
    {
        int py1 = persons[i].first;
        int px1 = persons[i].second;
        
        for(size_t j = i+1; j < persons.size(); j++)
        {
            int py2 = persons[j].first;
            int px2 = persons[j].second;
            
            int distance = get_distance(py1,px1,py2,px2);
            
            if(distance > 2)
                continue;
            else
            {
                if(is_possible(place,persons[i],persons[j]))
                    continue;
                
                return 0;
            }
        }
    }
    
    return 1;
}

vector<pair<int,int>> get_persons_positions(const vector<string>& place)
{
    vector<pair<int,int>> positions;
    
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 5; x++)
        {
            if(place[y][x] == 'P')
                positions.push_back({y,x});
        }
    }
    
    return positions;
}

vector<int> solve(const vector<vector<string>>& places)
{
    vector<int> ret;
    
    for(const auto& place : places)
    {
        auto persons = get_persons_positions(place);
        
        ret.push_back(check(place,persons));
    }
    
    return ret;
}

vector<int> solution(vector<vector<string>> places)
{
    vector<int> answer = solve(places);
    
    return answer;
}

int main()
{
    auto answer = solution({{"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"}, {"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"}, {"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"}, {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"}, {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}});
    
    for(const auto& a : answer)
        cout << a << endl;
    return 0;
}
