#include <iostream>
#include <algorithm>
#include <vector>

struct Candidate
{
    int student;
    int _time;
    int recommendation;
    
    bool operator<(const Candidate& c) const
    {
        if(this->recommendation == c.recommendation)
            return this->_time < c._time;
        return this->recommendation > c.recommendation;
    }
};

bool comp(const Candidate& c1,const Candidate& c2) { return c1.student < c2.student; }

int N,M;
std::vector<Candidate> v;

int main(int argc,char* argv[])
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    
    std::cin >> N; // N개의 사진틀
    std::cin >> M; // M명의 추천 횟수
    for(int i = 0; i < M; i++)
    {
        std::sort(v.begin(),v.end()); // 먼저 정렬

        int stu; std::cin >> stu;
        
        bool check = false;
        
        for(int j = 0; j < (int)v.size(); j++)
        {
            if(v[j].student == stu) // 후보가 이미 존재
            {
                check = true;
                v[j].recommendation++; // 추천 수 증가
            }
            v[j]._time++; // 각 후보들 게시된 시간 증가
        }
        if(!check) // 후보가 없었음
        {
            if((int)v.size()+1 > N) // 후보를 새로 추가하면 사진틀 용량 초과
            {
                std::sort(v.begin(),v.end());
                v.pop_back(); // 최하위 후보 사진 철거
            }
            
            v.push_back({stu,0,1});
        }
    }
    
    std::sort(v.begin(),v.end(),comp);
    for(int i = 0; i < (int)v.size(); i++)
        std::cout << v[i].student << " ";
    std::cout << '\n';
    return 0;
}
