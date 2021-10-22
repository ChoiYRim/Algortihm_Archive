#include <cmath>
#include <iostream>

#define INF 1000000
#define MAX 987654321

using namespace std;

int N,M,cur = 100;
bool button[16] = {0,};

int len(int num)
{
    if(!num)
    {
        if(button[0])
            return 0;
        return 1;
    }
    
    int ret = 0;
    while(num)
    {
        if(button[num%10])
            return 0;
        num /= 10;
        ret++;
    }
    
    return ret;
}

int main(void)
{
    int result;
    
    cin >> N;
    cin >> M;
    for(int i = 0; i < M; i++)
    {
        char btn; cin >> btn;
        
        if(btn >= '0' && btn <= '9')
            button[btn-'0'] = true;
    }
    
    result = abs(N-100);
    for(int i = 0; i <= INF; i++)
    {
        int num = i;
        int length = len(num);
        
        if(length > 0)
        {
            int click = abs(num-N);
            if(result > click+length)
                result  = click+length;
        }
    }
    
    cout << result << '\n';
    return 0;
}
