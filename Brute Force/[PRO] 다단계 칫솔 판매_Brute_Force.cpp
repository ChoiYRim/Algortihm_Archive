#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

map<string,int> Index;
vector<int> answer;
vector<int> parent;

void init(vector<string>& enroll,vector<string>& referral)
{
    parent = vector<int>(enroll.size(),0);
    answer = vector<int>(enroll.size(),0);
    for(int i = 0; i < enroll.size(); i++)
    {
        string name = enroll[i];
        Index[name] = i;
    }
    
    for(int i = 0; i < referral.size(); i++)
    {
        string name = referral[i];
        
        // enroll의 i번째 사람을 name이라는 이름을 가진 자가 가입시킴.
        if(name != "-")
            parent[i] = Index[name];
        else
            parent[i] = -1;
    }
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount)
{
    init(enroll,referral);
        
    for(int i = 0; i < seller.size(); i++)
    {
        string name = seller[i];
        int cur    = Index[name];
        int income = amount[i]*90.0;
        int tax    = amount[i]*10.0;
        
        answer[cur] += income;
        cur = parent[cur];
        while(cur != -1)
        {
            income = tax-tax/10;
            
            if(tax/10 < 1)
            {
                answer[cur] += tax;
                break;
            }
            
            answer[cur] += income;
            tax /= 10;
            cur = parent[cur];
        }
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    auto v = solution({"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"}, {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"}, {"young", "john", "tod", "emily", "mary"}, {12, 4, 2, 5, 10});
    
    for(const auto& ele : v)
        printf("%3d ", ele);
    printf("\n");
    return 0;
}
