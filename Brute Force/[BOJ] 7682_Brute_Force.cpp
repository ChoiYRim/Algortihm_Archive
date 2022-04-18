#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int dy[8][3] = {{0,0,0}, {0,-1,-2}, {0,-1,-2}, {0,-1,-2}, {0,0,0}, {0,1,2}, {0,1,2}, {0,1,2}};
const int dx[8][3] = {{0,-1,-2}, {0,-1,-2}, {0,0,0}, {0,1,2}, {0,1,2}, {0,1,2}, {0,0,0}, {0,-1,-2}};

inline bool range(int y, int x) { return ((y >= 0 && y < 3) && (x >= 0 && x < 3)); }

void get_count(const vector<string>& map, int& x_cnt, int& o_cnt)
{
    x_cnt = o_cnt = 0;
    
    for(const auto& line : map)
    {
        for(const auto& ele : line)
        {
            if(ele == 'X') x_cnt++;
            if(ele == 'O') o_cnt++;
        }
    }
}

int check(const vector<string>& map, char winner)
{
    int win = 0;
    vector<vector<bool>> visit(3, vector<bool>(3, 0));
    
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            if(map[y][x] != winner || visit[y][x]) continue;
            
            for(int i = 0; i < 8; i++)
            {
                int y2 = y+dy[i][1], y3 = y+dy[i][2];
                int x2 = x+dx[i][1], x3 = x+dx[i][2];
                
                if(!range(y2, x2) || !range(y3, x3)) continue;
                if(map[y2][x2] != winner || map[y3][x3] != winner) continue;
                if(visit[y2][x2] || visit[y3][x3]) continue;
                
                for(int j = 0; j < 8; j++) // mid
                {
                    int y4 = y2+dy[j][1], y5 = y2+dy[j][2];
                    int x4 = x2+dx[j][1], x5 = x2+dx[j][2];
                    
                    if(!range(y4, x4) || !range(y5, x5)) continue;
                    if(map[y4][x4] != winner || map[y5][x5] != winner) continue;
                    if(visit[y4][x4] || visit[y5][x5]) continue;
                    
                    visit[y2][x2] = true;
                    visit[y4][x4] = true;
                    visit[y5][x5] = true;
                    win++;
                }
                
                for(int j = 0; j < 8; j++) // rear
                {
                    if((j+4)%8 != i) continue; // 반대 방향은 체크 안함
                    
                    int y4 = y3+dy[j][1], y5 = y3+dy[j][2];
                    int x4 = x3+dx[j][1], x5 = x3+dx[j][2];
                    
                    if(!range(y4, x4) || !range(y5, x5)) continue;
                    if(map[y4][x4] != winner || map[y5][x5] != winner) continue;
                    if(visit[y4][x4] || visit[y5][x5]) continue;
                    
                    visit[y3][x3] = true;
                    visit[y4][x4] = true;
                    visit[y5][x5] = true;
                    win++;
                }
                
                visit[y][x] = true;
                //visit[y2][x2] = true;
                visit[y3][x3] = true;
                win++;
            }
        }
    }
    
    return win;
}

string output(const vector<string>& map)
{
    int x_cnt, o_cnt, diff;
    int x_win, o_win;
    
    get_count(map, x_cnt, o_cnt);
    
    diff = x_cnt-o_cnt;
    
    if(diff < 0 || diff > 1) return "invalid";
    
    x_win = check(map, 'X');
    o_win = check(map, 'O');
    
    if(x_win > 0 && o_win > 0) return "invalid";
    
    if(diff != 0)
    {
        if(x_win < o_win || o_win > 0) return "invalid";
        if(x_win == o_win && x_cnt+o_cnt < 9) return "invalid";
        return "valid";
    }
    
    if(x_win > o_win || x_win > 0 || o_win < 1) return "invalid";
    return "valid";
}

void solve()
{
    while(true)
    {
        vector<string> map;
        string input = ""; cin >> input;
        
        if(input == "end") break;
        
        for(int i = 0; i < 9; i += 3) map.push_back(input.substr(i,3));
        
        cout << output(map) << endl;
    }
}

int main(int argc, char* argv[])
{
    solve();
    return 0;
}
