#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<int> negative,positive,zero;

int positive_sum(vector<int>& v)
{
    int sum = 0;
    
    while(v.size())
    {
        int result;
        int first_biggest,second_biggest;
        
        if(v.size() > 1)
        {
            first_biggest = v.back();
            v.pop_back();
            
            second_biggest = v.back();
            if(second_biggest == 1)
            {
                result = first_biggest + second_biggest;
            }
            else
                result = (first_biggest * second_biggest);
        }
        else
        {
            first_biggest = v.back();
            result = first_biggest;
        }
        
        sum += result;
        v.pop_back();
    }
    
    return sum;
}

int negative_sum(vector<int>& v)
{
    int sum = 0;
    
    while(v.size())
    {
        int result;
        int first_smallest,second_smallest;
        
        if(v.size() > 1)
        {
            first_smallest = v.back();
            v.pop_back();
            
            second_smallest = v.back();
            result = (first_smallest * second_smallest);
        }
        else
        {
            result = 0;
            
            if(zero.size() <= 0)
                result = v.back();
            else
                zero.pop_back();
        }
        
        sum += result;
        v.pop_back();
    }
    
    return sum;
}

int main()
{
    int sum = 0;
    
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        if(tmp < 0)
            negative.push_back(tmp);
        else if(tmp > 0)
            positive.push_back(tmp);
        else
            zero.push_back(tmp);
    }
    
    sort(negative.begin(),negative.end(),greater<int>());
    sort(positive.begin(),positive.end(),less<int>());
    
    sum += positive_sum(positive);
    sum += negative_sum(negative);
    
    cout << sum << endl;
    return 0;
}
