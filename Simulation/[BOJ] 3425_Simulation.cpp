#include <stack>
#include <vector>
#include <string>
#include <iostream>

#define ISALPHA(x) ('A' <= x && x <= 'Z')
#define ISNUMBER(x) ('0' <= x && x <= '9' || x == '-')
#define ABS(x) (x >= 0 ? x : -x)
#define RANGE(x) (0 <= x && x <= 1000000000)

#define NUM "NUM"
#define DUP "DUP"
#define ADD "ADD"
#define END "END"
#define POP "POP"
#define INV "INV"
#define SWP "SWP"
#define SUB "SUB"
#define MUL "MUL"
#define DIV "DIV"
#define MOD "MOD"
#define END "END"
#define QUIT "QUI"

using namespace std;

int main(int argc, const char * argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    while(1)
    {
        int loop = 0,cnt = 0;
        stack<long long> s;
        vector<string> cmds; // cmds : 명령어 리스트
        vector<long long> priority; // NUM 명령어의 숫자
        string element = "";
        
        while(1)
        {
            element = "";
            cin >> element;
            //getchar();
            if(element == "QUIT")
                return 0;
                
            if(element.length() > 0)
            {
                if(ISALPHA(element[0]))
                {
                    string cmd = element.substr(0,3);
                    
                    if(cmd == END)
                    {
                        cmds.push_back(cmd);
                        break;
                    }
                    else if(cmd == NUM)
                    {
                        string num = "";
                        long long temp;
                        
                        cin >> num;
                        //getchar();
                        
                        temp = stoi(num);
                        cmds.push_back(cmd);
                        priority.push_back(temp);
                    }
                    else if(cmd == POP || cmd == INV || cmd == DUP || cmd == SWP || cmd == ADD || cmd == SUB || cmd == MUL || cmd == DIV || cmd == MOD)
                    {
                        cmds.push_back(cmd);
                    }
                }
            }
            else
                break;
        }
        
        if(element.length() <= 0)
            continue;
        
        cin >> cnt;
        //getchar();
        
        for(int i = 0; i < cnt; i++)
        {
            long long num;
            bool error = false;
            
            cin >> num;
            //getchar();
            
            loop = 0;
            s.push(num); // 스택에 숫자 넣고 시작!
            for(int j = 0; j < (int)cmds.size(); j++) // 명령어 갯수만큼 순회
            {
                string cmd = cmds[j];
                
                if(cmd == END)
                {
                    break;
                }
                else if(cmd == NUM)
                {
                    long long pri = priority[loop++];
                    s.push(pri);
                }
                else
                {
                    if(s.size() < 1)
                    {
                        error = true;
                        break;
                    }
                    
                    if(cmd == POP || cmd == INV || cmd == DUP)
                    {
                        if(cmd == POP) // 맨 위 숫자 제거
                            s.pop();
                        else if(cmd == INV) // 부호 바꾸기
                        {
                            long long t = s.top();
                            t = -t;
                            s.pop();
                            s.push(t);
                        }
                        else // 맨 위 숫자 복제 후 또 넣기
                        {
                            long long t = s.top();
                            s.push(t);
                        }
                    }
                    else
                    {
                        if(s.size() < 2)
                        {
                            error = true;
                            break;
                        }
                        
                        long long first = s.top(); s.pop();
                        long long second = s.top(); s.pop();
                        long long after;
                        bool minus = false;
                        
                        if(cmd == SWP) // 맨 위에서 1,2번째 숫자 Swap
                        {
                            s.push(first);
                            s.push(second);
                        }
                        else if(cmd == ADD)
                        {
                            after = first + second;
                            if(!RANGE(ABS(after)))
                            {
                                error = true;
                                break;
                            }
                            s.push(after);
                        }
                        else if(cmd == SUB)
                        {
                            after = second - first;
                            if(!RANGE(ABS(after)))
                            {
                                error = true;
                                break;
                            }
                            s.push(after);
                        }
                        else if(cmd == MUL)
                        {
                            after = first * second;
                            if(!RANGE(ABS(after)))
                            {
                                error = true;
                                break;
                            }
                            s.push(after);
                        }
                        else if(cmd == DIV)
                        {
                            if(first == 0)
                            {
                                error = true;
                                break;
                            }
                            if((first > 0 && second < 0) || (first < 0 && second > 0))
                                minus = true;
                            
                            after = ABS(ABS(second) / ABS(first));
                            if(minus)
                                after = -after;
                            
                            if(!RANGE(ABS(after)))
                            {
                                error = true;
                                break;
                            }
                            
                            s.push(after);
                        }
                        else if(cmd == MOD)
                        {
                            if(first == 0)
                            {
                                error = true;
                                break;
                            }
                            if(second < 0)
                                minus = true;
                            
                            after = ABS(second) % ABS(first);
                            if(minus)
                                after = -after;
                            
                            if(!RANGE(ABS(after)))
                            {
                                error = true;
                                break;
                            }
                            s.push(after);
                        }
                    }
                }
            } // for j
            
            if(error)
            {
                cout << "ERROR\n";
            }
            else
            {
                if(s.size() == 1)
                {
                    long long result = s.top();
                    cout << result << '\n';
                }
                else
                {
                    cout << "ERROR\n";
                }
            }
            while(!s.empty())
                s.pop();
        } // for i
        cout << '\n';
    } // while
    
    return 0;
}

