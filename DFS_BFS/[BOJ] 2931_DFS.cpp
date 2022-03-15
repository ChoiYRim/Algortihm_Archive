#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX 26

// ↑ 0  ↓ 1  ← 2  → 3
int R, C, dir;
char arr[MAX][MAX];
pair<int, int> src;
const int dy[4] = { -1, 1, 0, 0 };
const int dx[4] = { 0, 0, -1, 1 };

void output(int y, int x)
{
    cout << y << " " << x << " ";
    bool dir_check[4] = { false, };
    
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        
        if (ny <= 0 || ny > R || nx <= 0 || nx > C) continue;
        
        if (arr[ny][nx] != '.')
        {
            if (i == 0 && (arr[ny][nx] == '|' || arr[ny][nx] == '+'
                || arr[ny][nx] == '1' || arr[ny][nx] == '4'))
                dir_check[i] = true;
            
            else if (i == 1 && (arr[ny][nx] == '|' || arr[ny][nx] == '+'
                || arr[ny][nx] == '2' || arr[ny][nx] == '3'))
                dir_check[i] = true;
            
            else if (i == 2 && (arr[ny][nx] == '-' || arr[ny][nx] == '+'
                || arr[ny][nx] == '1' || arr[ny][nx] == '2'))
                dir_check[i] = true;
            
            else if (i == 3 && (arr[ny][nx] == '-' || arr[ny][nx] == '+'
                || arr[ny][nx] == '3' || arr[ny][nx] == '4'))
                dir_check[i] = true;
        }
    }

    if (dir_check[0] && dir_check[1] && dir_check[2] && dir_check[3]) cout << "+";
    else if (dir_check[0] && dir_check[1]) cout << "|";
    else if (dir_check[2] && dir_check[3]) cout << "-";
    else if (dir_check[1] && dir_check[3]) cout << "1";
    else if (dir_check[0] && dir_check[3]) cout << "2";
    else if (dir_check[0] && dir_check[2]) cout << "3";
    else if (dir_check[1] && dir_check[2]) cout << "4";
    cout << endl;
    return;
}

void dfs(int y, int x, int d)
{
    if(arr[y][x] == '.')
    {
        output(y,x);
        return;
    }

    int ny = y + dy[d];
    int nx = x + dx[d];

    if (d == 0)
    {
        if (arr[ny][nx] == '|' || arr[ny][nx] == '+') d = 0;
        else if (arr[ny][nx] == '1') d = 3;
        else if (arr[ny][nx] == '4') d = 2;
    }

    else if (d == 1)
    {
        if (arr[ny][nx] == '|' || arr[ny][nx] == '+') d = 1;
        else if (arr[ny][nx] == '2') d = 3;
        else if (arr[ny][nx] == '3') d = 2;
    }

    else if (d == 2)
    {
        if (arr[ny][nx] == '-' || arr[ny][nx] == '+') d = 2;
        else if (arr[ny][nx] == '1') d = 1;
        else if (arr[ny][nx] == '2') d = 0;
    }

    else if (d == 3)
    {
        if (arr[ny][nx] == '-' || arr[ny][nx] == '+') d = 3;
        else if (arr[ny][nx] == '3') d = 0;
        else if (arr[ny][nx] == '4') d = 1;
    }
    dfs(ny, nx, d);
    return;
}

void get_direction()
{
    for (int i = 0; i < 4; i++)
    {
        int ny = src.first + dy[i];
        int nx = src.second + dx[i];

        if(ny <= 0 || ny > R || nx <= 0 || nx > C) continue;
        
        if (arr[ny][nx] != '.')
        {
            if (ny == src.first)
            {
                if (nx == src.second - 1)
                    dir = 2;
                else if (nx == src.second + 1)
                    dir = 3;
            }
            else if (nx == src.second)
            {
                if (ny == src.first - 1)
                    dir = 0;
                else if (ny == src.first + 1)
                    dir = 1;
            }
        }
    }
}

void input()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> R >> C;
    for(int i = 1; i <= R; i++)
    {
        for(int j = 1; j <= C; j++)
        {
            cin >> arr[i][j];
            if(arr[i][j] == 'M')
                src = {i,j};
        }
    }
}

int main()
{
    input();
    get_direction();
    dfs(src.first,src.second,dir);
    return 0;
}
