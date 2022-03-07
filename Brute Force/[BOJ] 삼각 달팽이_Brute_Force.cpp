#include <string>
#include <vector>
#include <iostream>

using namespace std;

void print_vector(const vector<vector<int>>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < v[i].size(); j++)
            printf("%-3d ", v[i][j]);
        printf("\n");
    }
}

vector<vector<int>> make_triangle(int n)
{
    // +행 -> +열 -> -행
    int cnt = n,num = 1,row = 0,col = 0;
    
    vector<vector<int>> ret(n); // init
    for(int i = 0; i < n; i++)
        ret[i] = vector<int>(i+1);
    
    while(1)
    {
        for(int i = 0; i < cnt; i++)
            ret[row++][col] = num++;
        
        cnt--; row--; col++;
        if(cnt <= 0) break;
        
        for(int i = 0; i < cnt; i++)
            ret[row][col++] = num++;
        
        cnt--; row--; col -= 2;
        if(cnt <= 0) break;
        
        for(int i = 0; i < cnt; i++)
            ret[row--][col--] = num++;
        
        cnt--; row+=2; col++;
        if(cnt <= 0) break;
    }
    
    return ret;
}

vector<int> solution(int n)
{
    vector<int> answer;
    auto triangle = make_triangle(n);
    print_vector(triangle);
    
    for(int i = 0; i < triangle.size(); i++)
    {
        for(int j = 0; j < triangle[i].size(); j++)
            answer.push_back(triangle[i][j]);
    }
    
    return answer;
}

int main()
{
    auto v = solution(20);
    return 0;
}
