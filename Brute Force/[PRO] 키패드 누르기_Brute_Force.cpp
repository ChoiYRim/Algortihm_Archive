#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

pair<int,int> pos[10];

int dist(pair<int,int> src,pair<int,int> dst)
{
    int y1 = src.first,y2 = dst.first;
    int x1 = src.second,x2 = dst.second;
    
    int y = abs(y1-y2);
    int x = abs(x1-x2);
    
    return y+x;
}

string solution(vector<int> numbers,string hand)
{
    string answer = "";
    pair<int,int> left = {3,0},right = {3,2};
    bool hander = (hand == "right" ? 0 : 1);
    
    for(int i = 0; i < numbers.size(); i++)
    {
        int number = numbers[i];
        
        if(number == 1 || number == 4 || number == 7)
        {
            answer.push_back('L');
            left = {number/3,0};
        }
        else if(number == 3 || number == 6 || number == 9)
        {
            answer.push_back('R');
            right = {number/3-1,2};
        }
        else
        {
            pair<int,int> pos = {number/3,1};
            if(number == 0)
                pos = {3,1};
            
            int dist_left = dist(left,pos);
            int dist_right = dist(right,pos);
            
            if(dist_left == dist_right)
            {
                if(!hander)
                {
                    answer.push_back('R');
                    right = pos;
                }
                else
                {
                    answer.push_back('L');
                    left = pos;
                }
            }
            else if(dist_left < dist_right)
            {
                answer.push_back('L');
                left = pos;
            }
            else
            {
                answer.push_back('R');
                right = pos;
            }
        }
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    cout << solution({1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5}, "right") << endl;
    return 0;
}
