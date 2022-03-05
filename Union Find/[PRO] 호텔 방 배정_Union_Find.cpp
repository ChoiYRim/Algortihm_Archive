#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

unordered_map<ll,ll> room;

ll find(ll number)
{
    if(room[number] == 0)
        return number;
    return room[number] = find(room[number]);
}

vector<ll> solution(ll k, vector<ll> room_number)
{
    vector<ll> answer;
    
    for(const auto& number : room_number)
    {
        ll empty_number = find(number);
        answer.push_back(empty_number);
        room[empty_number] = empty_number+1;
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    auto v = solution(10,{1,3,4,1,3,1});
    return 0;
}
