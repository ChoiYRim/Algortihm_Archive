#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<bool> COL;
vector<pair<int,int>> queens;

bool check(int row,int col)
{
    for(auto& queen : queens)
    {
        if(abs(row-queen.first) == abs(col-queen.second))
            return false;
    }
    
    return true;
}

int dfs(int row,int n)
{
    if(row >= n)
        return 1;
    
    int ret = 0;
    for(int col = 0; col < n; col++)
    {
        if(check(row,col) && !COL[col])
        {
            COL[col] = true;
            queens.push_back({row,col});
            ret += dfs(row+1,n);
            queens.pop_back();
            COL[col] = false;
        }
    }
    
    return ret;
}

int solution(int n)
{
    int answer = 0;
    
    COL = vector<bool>(n,false);
    for(int col = 0; col < n; col++)
    {
        COL[col] = true;
        queens.push_back({0,col});
        answer += dfs(1,n);
        queens.pop_back();
        COL[col] = false;
    }
    
    return answer;
}

int main()
{
    int n;
    
    std::cin >> n;
    std::cout << solution(n) << endl;
    return 0;
}
