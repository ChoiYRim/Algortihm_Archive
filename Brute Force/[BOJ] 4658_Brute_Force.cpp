#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<vector<int>>> v;

void input()
{
    char token = '*';
    
    while(token == '*')
    {
        vector<vector<int>> triangles;
        
        for(int i = 0; i < 6; i++)
        {
            vector<int> triangle(3);
            
            for(int j = 0; j < 3; j++) cin >> triangle[j];
            
            triangles.push_back(triangle);
        }
        
        v.push_back(triangles);
        cin >> token;
    }
}

void turn(vector<int>& triangle)
{
    int len = static_cast<int>(triangle.size());
    int prev = triangle[0];
    
    for(int i = 1; i < len; i++)
    {
        int tmp = triangle[i];
        
        triangle[i] = prev;
        prev = tmp;
    }
    triangle[0] = prev;
}

void dfs(int depth, vector<int>& prev, vector<vector<int>>& triangles, vector<bool>& selected, int& ans)
{
    if(depth == 5)
    {
        for(int i = 1; i < 6; i++)
        {
            if(selected[i]) continue;
            
            auto& src = triangles[0];
            auto& cur = triangles[i];
            
            if(prev[1] == cur[0] && src[0] == cur[1])
            {
                int sum = 0;
                for(int i = 0; i < 6; i++) sum += triangles[i][2];
                ans = max(ans, sum);
            }
            
            for(int j = 0; j < 2; j++)
            {
                turn(cur);
                
                if(prev[1] == cur[0] && src[0] == cur[1])
                {
                    int sum = 0;
                    for(int i = 0; i < 6; i++) sum += triangles[i][2];
                    ans = max(ans, sum);
                }
            }
        }
        
        //printf("answer : %d\n", ans);
        return;
    }
    
    for(int i = 1; i < 6; i++)
    {
        if(selected[i]) continue;
        
        auto& cur = triangles[i];
        
        if(prev[1] == cur[0])
        {
            selected[i] = true;
            dfs(depth+1, cur, triangles, selected, ans);
            selected[i] = false;
        }
        
        for(int j = 0; j < 2; j++)
        {
            turn(cur);
            
            if(prev[1] == cur[0])
            {
                selected[i] = true;
                dfs(depth+1, cur, triangles, selected, ans);
                selected[i] = false;
            }
        }
    }
}

void solve()
{
    for(auto& triangles : v)
    {
        // case 1 : 그대로
        int ans = 0;
        vector<bool> selected(6, false);
        
        selected[0] = true;
        dfs(1, triangles[0], triangles, selected, ans);
        
        // case 2 : turn 1
        selected = vector<bool>(6, false);
        selected[0] = true;
        turn(triangles[0]);
        dfs(1, triangles[0], triangles, selected, ans);
        
        // case 3 : turn 2
        selected = vector<bool>(6, false);
        selected[0] = true;
        turn(triangles[0]);
        dfs(1, triangles[0], triangles, selected, ans);
        
        if(ans == 0) cout << "none" << endl;
        else cout << ans << endl;
    }
}

int main(int argc, char* argv[])
{
    input();
    solve();
    return 0;
}
