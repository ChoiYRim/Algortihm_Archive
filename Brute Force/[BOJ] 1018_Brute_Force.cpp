#include <iostream>
#include <vector>
#include <climits>

#define MAX(a,b) (a > b ? b : a)
#define RANGE(x,L) (0 <= x && x < L)

bool board[51][51] = {0,};
int ans = INT_MAX,N,M;

int check(bool isBlack,int y,int x)
{
    int cnt = 0;
    bool start = !isBlack;
    
    for(int i = y; i < y+8; i++)
    {
        start = !start;
        bool tmp = start;
        
        for(int j = x; j < x+8; j++)
        {
            if(board[i][j] != tmp)
                cnt++;
            tmp = !tmp;
        }
    }
    
    return cnt;
}

int main(int argc,char* argv[])
{
    std::cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            char ele; std::cin >> ele;
            if(ele == 'W')
                board[i][j] = 0;
            else
                board[i][j] = 1;
        }
    }
    
    for(int i = 0; i <= N-8; i++)
    {
        for(int j = 0; j <= M-8; j++)
        {
            ans = MAX(ans,check(false,i,j)); // white
            ans = MAX(ans,check(true,i,j)); // black
        }
    }
    
    std::cout << ans << '\n';
    return 0;
}
