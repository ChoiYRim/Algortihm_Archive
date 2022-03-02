#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves)
{
    int answer = 0;
    stack<int> st;
    int r = (int)board.size();
    
    for(int i = 0; i < moves.size(); i++)
    {
        int col = moves[i]-1;
        int unit = 0;
        bool is_exist = false;
        
        for(int row = 0; row < r; row++)
        {
            if(board[row][col])
            {
                unit = board[row][col];
                board[row][col] = 0;
                is_exist = true;
                break;
            }
        }
        if(is_exist)
        {
            if(st.empty())
            {
                st.push(unit);
                continue;
            }
            if(st.top() != unit)
            {
                st.push(unit);
                continue;
            }
            
            st.pop();
            answer += 2;
        }
    }
    
    return answer;
}
int main()
{
    cout << solution({{0,0,0,0,0},{0,0,1,0,3},{0,2,5,0,1},{4,2,4,4,2},{3,5,1,3,1}},{1,5,3,5,1,2,1,4}) << endl;
    return 0;
}
