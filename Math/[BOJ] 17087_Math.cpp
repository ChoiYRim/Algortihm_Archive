// Reference : https://intaehwang.tistory.com/52

#include <cstdio>
 
using namespace std;
 
int cal(int x, int y)
{
    if (y == 0)
        return x;
    else
        return cal(y, x%y);
}
 
int main()
{
    int d[100001];
    int n, s;
    scanf("%d %d", &n, &s);
    
    for (int i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        tmp -= s;
        
        if (tmp < 0)
            tmp = -tmp;
        d[i] = tmp;
    }
    
    int ans = d[0];
    for (int i = 1; i < n; i++)
        ans = cal(ans, d[i]);
    printf("%d", ans);
}
