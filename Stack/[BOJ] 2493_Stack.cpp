#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
stack<pair<int ,int>> st;
vector<int> answer, Data;

void solve()
{
    scanf("%d", &N);
    Data = vector<int>(N, 0);
    answer = vector<int>(N, 0);
    for(int i = 0; i < N; i++)
    {
        int result = 0;
        scanf("%d", &Data[i]);
        
        while(!st.empty())
        {
            auto top = st.top();
            
            if(top.first >= Data[i])
            {
                result = top.second;
                break;
            }
            
            st.pop();
        }
        
        answer[i] = result;
        st.push({Data[i], i+1});
    }
}

void output()
{
    for(int i = 0; i < N; i++)
        printf("%d ", answer[i]);
    printf("\n");
}

int main(int argc, char* argv[])
{
    solve();
    output();
    return 0;
}
