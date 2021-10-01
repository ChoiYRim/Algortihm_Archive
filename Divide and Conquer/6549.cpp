#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#define INF 0x7fffffff

using namespace std;

int n,tHeight,tNodes;
long long answer;
vector<long long> result,height,stree;

void solution(int left,int right);

int init(int cur,int left,int right);

long long find(int cur,int start,int end,int left,int right);

int main(int argc,char* argv[])
{
    while(cin >> n && n)
    {
        for(int i = 0; i < n; i++)
        {
            int tmp; cin >> tmp;
            height.push_back(tmp);
        }
        
        tHeight = ceil(log2(n));
        tNodes = (1 << (tHeight+1));
        stree = vector<long long>(tNodes);
        answer = 0;
        
        init(1,0,n-1);
        solution(0,n-1);
        result.push_back(answer);
        height.clear();
    }
    
    for(int i = 0; i < (int)result.size(); i++)
        cout << result[i] << '\n';
    
    return 0;
}

int init(int cur,int left,int right)
{
    if(left == right)
        return stree[cur] = left;
    
    int mid = (left+right)/2;
    
    int left_result = init(cur*2,left,mid);
    int right_result = init(cur*2+1,mid+1,right);
    
    return stree[cur] = (height[left_result] < height[right_result] ? left_result : right_result);
}

void solution(int left,int right)
{
    if(left > right)
        return;
    
    long long index = find(1,0,n-1,left,right);
    
    answer = max(answer,height[index]*(right-left+1));
    
    solution(left,(int)index-1);
    solution((int)index+1,right);
}

long long find(int cur,int start,int end,int left,int right) // find the minimum index
{
    if(end < left || start > right) // 일부만 걸치거나 범위 이탈
        return INF;
    if(start >= left && end <= right)
        return stree[cur];
    
    int mid = (start+end)/2;
    
    long long left_result = find(cur*2,start,mid,left,right);
    long long right_result = find(cur*2+1,mid+1,end,left,right);
    
    // 일부 구간만 겹치는 경우 or 범위 이탈한 경우
    if(left_result == INF) // cur의 왼쪽 자식이 일부만 걸치거나 범위 이탈
        return right_result;
    else if(right_result == INF) // cur의 오른쪽 자식이 일부만 걸치거나 범위 이탈
        return left_result;
    
    return height[left_result] < height[right_result] ? left_result : right_result;
}
