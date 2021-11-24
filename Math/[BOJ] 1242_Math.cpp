#include <iostream>

using namespace std;

int N,M,K;

int game(int total,int target)
{
    int out_turn = (K % total != 0 ? K % total : total);
    
    if(out_turn == target || total == 1) // 재귀 탈출문
        return 1;
    
    if(target >= out_turn)
        target = target - out_turn;
    else
        target = (total - out_turn) + target;
    
    return game(total-1,target)+1;
}

int main()
{
    cin >> N >> K >> M;
    cout << game(N,M) << '\n';
    return 0;
}
