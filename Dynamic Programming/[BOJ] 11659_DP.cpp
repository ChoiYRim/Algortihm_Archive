#include <iostream>
#include <algorithm>

using namespace std;

int N,M;
int num[100001];

int main(int argc,char* argv[])
{
    int sum = 0;
    
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &num[i]);
        sum += num[i];
        num[i] = sum;
    }
    for(int i = 0; i < M; i++)
    {
        int a,b;
        scanf("%d %d", &a, &b);
        a--; b--;
        if(a >= 1)
            printf("%d\n", num[b]-num[a-1]);
        else
            printf("%d\n", num[b]);
    }
    
    return 0;
}
