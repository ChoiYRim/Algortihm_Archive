#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
vector<int> cards;

void input()
{
    cin >> N;
    cards = vector<int>(N);
    for(int i = 0; i < N; i++) scanf("%d", &cards[i]);
    cin >> M;
    sort(cards.begin(), cards.end());
}

bool bs(int num)
{
    int left = 0, right = N-1;
    
    while(left <= right)
    {
        int mid = (left+right)/2;
        
        if(cards[mid] < num)
            left = mid+1;
        else if(cards[mid] > num)
            right = mid-1;
        else return true;
    }
    
    return false;
}

void solve()
{
    for(int i = 0; i < M; i++)
    {
        int num;
        scanf("%d", &num);
        printf("%d ", bs(num));
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    input();
    solve();
    return 0;
}
