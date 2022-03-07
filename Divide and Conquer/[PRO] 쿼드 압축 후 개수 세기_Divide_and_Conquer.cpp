#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> v;

void split(int y1, int x1, int y2, int x2, vector<int>& answer)
{
    printf("[%-2d,%-2d] ~ [%-2d,%-2d]\n", y1, x1, y2, x2);
    
    if(y1 == y2 && x1 == x2)
    {
        int ele = v[y1][x1];
        answer[ele]++;
        return;
    }
    
    bool finish = true;
    int ele = v[y1][x1];
    for(int y = y1; y <= y2 && finish; y++)
    {
        for(int x = x1; x <= x2; x++)
        {
            if(v[y][x] != ele)
            {
                finish = false;
                break;
            }
        }
    }
    
    if(!finish)
    {
        split(y1, x1, (y1+y2)/2, (x1+x2)/2, answer); // [0,0] [1,1]
        split(y1, (x1+x2)/2+1, (y1+y2)/2, x2, answer); // [0,2] [1,3]
        split((y1+y2)/2+1, x1, y2, (x1+x2)/2, answer); // [2,0] [3,1]
        split((y1+y2)/2+1, (x1+x2)/2+1, y2, x2, answer); // [2,2] [3,3]
        return;
    }
    
    answer[ele]++;
    return;
}

vector<int> solution(vector<vector<int>> arr)
{
    vector<int> answer(2,0);
    int len = static_cast<int>(arr.size());
    
    v = arr;
    split(0, 0, len-1, len-1, answer); // [0,0] [3,3]
    return answer;
}

int main()
{
    auto v = solution({{1,1,0,0},{1,0,0,0},{1,0,0,1},{1,1,1,1}});
    
    return 0;
}
