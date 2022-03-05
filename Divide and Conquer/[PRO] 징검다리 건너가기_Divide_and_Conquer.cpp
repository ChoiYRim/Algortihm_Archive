#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// mid(사람의 수)를 뺐을 때 디딤돌이 k개 연속해서 있는가?
bool binary_search(const vector<int>& v,int mid,int k)
{
    int cnt = 0;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i]-mid <= 0)
            cnt++;
        else
            cnt = 0;
        
        if(cnt >= k)
            return true;
    }
    
    return false;
}

int solution(vector<int> stones, int k)
{
    int left = 1;
    int right = *max_element(stones.begin(),stones.end());
    
    while(left <= right)
    {
        int mid = (left+right)/2;
        if(binary_search(stones,mid,k))
            right = mid-1;
        else
            left = mid+1;
    }
    
    return left;
}

int main(int argc,char* argv[])
{
    cout << solution({2,4,5,3,2,1,4,2,5,1},3) << endl;
    return 0;
}
