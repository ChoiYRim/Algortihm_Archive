#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

int N,M,K;
std::vector<long long> input;

template <typename T>
class SegTree
{
private:
    std::vector<T> v;
    std::vector<T> nodes;
    
    T init(int cur,int left,int right)
    {
        if(left == right)
            return nodes[cur] = v[left];
        
        int mid = (left+right)/2;
        T l = this->init(cur*2,left,mid);
        T r = this->init(cur*2+1,mid+1,right);
        
        return nodes[cur] = l + r;
    }
    
public:
    SegTree(int n,std::vector<T>& i)
    {
        int height = ceil(log2(n));
        int numbers = (1 << (height+1))+1;
        nodes = std::vector<T>(numbers,0);
        
        this->v = i;
        this->init(1,0,(int)v.size()-1);
    }
    
    void update(int cur,int left,int right,int idx,T diff)
    {
        if(idx < left || idx > right)
            return;
        
        this->nodes[cur] += diff;
        
        if(left == right)
        {
            this->v[idx] += diff;
            input[idx] += diff;
            return;
        }
        
        int mid = (left+right)/2;
        this->update(cur*2,left,mid,idx,diff);
        this->update(cur*2+1,mid+1,right,idx,diff);
    }
    
    T getSum(int cur,int start,int end,int left,int right) // [left,right] 현재 구간 , [start,end] 찾고자 하는 범위
    {
        if(start > right || end < left)
            return 0;
        if(start <= left && end >= right)
            return nodes[cur];
        
        int mid = (left+right)/2;
        
        T leftResult = this->getSum(cur*2,start,end,left,mid);
        T rightResult = this->getSum(cur*2+1,start,end,mid+1,right);
        
        return leftResult+rightResult;
    }
};

int main(int argc,char* argv[])
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    
    SegTree<long long>* root;
    
    std::cin >> N >> M >> K;
    for(int i = 0; i < N; i++)
    {
        long long num; std::cin >> num;
        input.push_back(num);
    }
    
    root = new SegTree<long long>(N,input);
        
    for(int i = 0; i < M+K; i++)
    {
        int a,b;
        long long c; std::cin >> a >> b >> c;

        if(a == 1) // b번째 수를 c로 변경
        {
            long long diff = c-input[b-1];
            root->update(1,0,N-1,b-1,diff);
        }
        else // 2 : [b,c] 출력
        {
            std::cout << root->getSum(1,b-1,(int)c-1,0,N-1) << '\n';
        }
    }
    
    return 0;
}
