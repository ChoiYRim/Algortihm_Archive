#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int N, M, K;
vector<int> judges;

void input()
{
    cin >> N >> M >> K;
    judges = vector<int>(K, 0);
    for(int i = 0; i < K; i++) cin >> judges[i];
}

string solve()
{
    string answer = "";

    int left = 0, right = N;

    while(left <= right)
    {
        int mid = (left + right) / 2; // 최솟값들 중에서 최대값을 mid라고 생각
        
        string cur = "1";
        int selected = 1, prev = 0;
        
        for(int i = 1; i < K; i++)
        {
            if(judges[i] - judges[prev] >= mid)
            {
                cur += "1";
                selected++;
                prev = i;

                if(selected == M) break;
            }
            else cur += "0";
        }

        while(cur.size() < K) cur += "0";

        if(selected == M)
        {
            left = mid + 1;
            answer = cur;
        }
        else
            right = mid - 1;
    }

    return answer;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
