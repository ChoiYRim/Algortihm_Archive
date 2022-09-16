#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

unordered_map<int, int> m;

int main(int argc, char* argv[])
{
    int N, M;
    
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        
        m[tmp]++;
    }
    
    cin >> M;
    for(int i = 0; i < M; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        
        printf("%d ", m[tmp]);
    }
    cout << endl;
    return 0;
}
