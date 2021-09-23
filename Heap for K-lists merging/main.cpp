#include <vector>
#include <iostream>
#include <algorithm>

struct node
{
    int data;
    int listPosition;
    int dataPosition;
};

std::vector<int> merge(const std::vector<std::vector<int>>& input)
{
    std::vector<int> result;
    std::vector<node> heap;
    
    // define the lambda function for min heap - such as greater<T>
    auto comparator = [](const node& left,const node& right)
    {
        if(left.data == right.data)
            return left.listPosition > right.listPosition;
        return left.data > right.data;
    };
    
    for(int i = 0; i < input.size(); i++)
    {
        heap.push_back({input[i][0],i,0});
        std::push_heap(heap.begin(),heap.end(),comparator); // 각 input의 첫 번째 값을 넣을 때마다 heap으로 정렬해줌
        // 각 리스트 별 첫째 값이 가장 작은 순으로 정렬됨
    }
    
    while(!heap.empty())
    {
        std::pop_heap(heap.begin(),heap.end(),comparator); // 부모노드가 맨 마지막 노드와 교환됨
        auto mini = heap.back(); // 최소값 추출
        
        heap.pop_back();
        result.push_back(mini.data);
        int nextIdx = mini.dataPosition+1;
        if(nextIdx < input[mini.listPosition].size())
        {
            heap.push_back({input[mini.listPosition][nextIdx],mini.listPosition,nextIdx});
            std::push_heap(heap.begin(),heap.end(),comparator);
        }
    }
    
    return result;
}

int main(void)
{
    std::vector<int> v1 = {1,3,8,15,105};
    std::vector<int> v2 = {2,3,10,11,16,20,25};
    std::vector<int> v3 = {-2,100,1000};
    std::vector<int> v4 = {-1,0,14,18};
    
    auto result = merge({v1,v2,v3,v4});
    
    for(auto i : result)
        std::cout << i << ' ';
    std::cout << '\n';
    return 0;
}
