#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int N,M;
vector<int> v;
vector<pair<int,int>> requests;

int height,nodes;
vector<int> min_segTree,max_segTree;

void input()
{
    scanf("%d %d", &N, &M);
    
    v = vector<int>(N);
    for(int i = 0; i < N; i++)
        cin >> v[i];
    
    requests = vector<pair<int,int>>(M);
    for(int i = 0; i < M; i++)
        cin >> requests[i].first >> requests[i].second;
}

int insert(int idx,int left,int right,bool flag)
{
    if(left == right)
    {
        if(!flag)
            return min_segTree[idx] = v[left];
        return max_segTree[idx] = v[left];
    }
    if(left > right)
    {
        if(!flag)
            return 0x7fffffff;
        return 0;
    }
        
    int mid = (left+right)/2;
    int left_result = insert(idx*2,left,mid,flag);
    int right_result = insert(idx*2+1,mid+1,right,flag);
    
    if(!flag)
        return min_segTree[idx] = min(left_result,right_result);
    return max_segTree[idx] = max(left_result,right_result);
}

// [left,right] 현재 탐색 중인 범위 , [start,end] 찾아야할 범위
int find_value(int idx,int left,int right,int start,int end,bool flag)
{
    if(left > end || right < start) // 범위 이탈
    {
        if(!flag)
            return 0x7fffffff;
        return 0;
    }
    if(start <= left && end >= right)
    {
        if(!flag)
            return min_segTree[idx];
        return max_segTree[idx];
    }
    
    int mid = (left+right)/2;
    int left_result = find_value(idx*2, left, mid, start, end, flag);
    int right_result = find_value(idx*2+1, mid+1, right, start, end, flag);
    
    if(!flag)
        return min(left_result,right_result);
    return max(left_result,right_result);
}

void make_segment_tree()
{
    int len = static_cast<int>(v.size());
    
    height = ceil(log2(len));
    nodes = (1 << (height+1))+1;
    min_segTree = vector<int>(nodes,0);
    max_segTree = vector<int>(nodes,0);
    
    insert(1,0,len-1,0);
    insert(1,0,len-1,1);
}

void solve()
{
    int len = static_cast<int>(v.size());
    
    for(const auto& request : requests)
    {
        int from = request.first-1;
        int to = request.second-1;
        int min_result = find_value(1,0,len-1,from,to,0);
        int max_result = find_value(1,0,len-1,from,to,1);
        
        printf("%d %d\n", min_result, max_result);
    }
}

int main(int argc,char* argv[])
{
    input();
    make_segment_tree();
    solve();
    return 0;
}
