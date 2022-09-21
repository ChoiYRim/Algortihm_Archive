#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Student
{
    int korean;
    int english;
    int math;
    string name;
};

int N;
vector<Student> stds;

bool comp(const Student& s1, const Student& s2)
{
    if(s1.korean == s2.korean && s1.english == s2.english && s1.math == s2.math) return s1.name < s2.name;
    if(s1.korean == s2.korean && s1.english == s2.english) return s1.math > s2.math;
    if(s1.korean == s2.korean) return s1.english < s2.english;
    return s1.korean > s2.korean;
}

int main(int argc, char* argv[])
{
    cin >> N;
    stds = vector<Student>(N);
    for(int i = 0; i < N; i++)
    {
        cin >> stds[i].name >> stds[i].korean >> stds[i].english >> stds[i].math;
    }
    
    sort(stds.begin(), stds.end(), comp);
    
    for(int i = 0; i < N; i++)
    {
        cout << stds[i].name << "\n";
    }
    return 0;
}
