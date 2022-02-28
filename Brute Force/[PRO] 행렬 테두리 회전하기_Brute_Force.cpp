#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int N,M;
vector<vector<int>> arr;

void print_arr()
{
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            printf("%3d ", arr[y][x]);
        }
        printf("\n");
    }
}

void make_arr()
{
    int num = 1;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            arr[y][x] = num;
            num++;
        }
    }
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries)
{
    vector<int> answer;
    
    N = rows;
    M = columns;
    arr = vector<vector<int>>(N+1,vector<int>(M+1,0));
    
    make_arr();
    
    //print_arr();
    
    for(const auto& query : queries)
    {
        int x1 = query[0]-1,y1 = query[1]-1;
        int x2 = query[2]-1,y2 = query[3]-1;
        
        int save = arr[x1][y1];
        int result = min(arr[x1+1][y1],arr[x1][y1]);
        
        arr[x1][y1] = arr[x1+1][y1];
        for(int y = y1+1; y <= y2; y++)
        {
            int tmp = arr[x1][y];
            arr[x1][y] = save;
            save = tmp;
            result = min(result,save);
        }
        for(int x = x1+1; x <= x2; x++)
        {
            int tmp = arr[x][y2];
            arr[x][y2] = save;
            save = tmp;
            result = min(result,save);
        }
        for(int y = y2-1; y >= y1; y--)
        {
            int tmp = arr[x2][y];
            arr[x2][y] = save;
            save = tmp;
            result = min(result,save);
        }
        for(int x = x2-1; x > x1; x--)
        {
            int tmp = arr[x][y1];
            arr[x][y1] = save;
            save = tmp;
            result = min(result,save);
        }
        
        answer.push_back(result);
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    auto v = solution(100, 97, {{1,1,100,97}});
    return 0;
}
