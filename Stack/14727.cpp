#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
long long result = 0;

struct Stick
{
	int x;
	int nx;
	int height;
};

int main(int argc,char* argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	stack<Stick> s;

	cin >> N;
	for(int i = 0; i < N; i++)
	{
		long long height;
		cin >> height;

		while(!s.empty() && s.top().height > height)
		{
			result = max(result,(long long)(i-s.top().x) * (long long)s.top().height);
			s.pop();
		}
		s.push({s.empty() ? 0 : s.top().nx+1 , i , static_cast<int>(height)});
	}
	while(!s.empty())
	{
		result = max(result,(long long)(N-s.top().x) * (long long)s.top().height);
		s.pop();
	}

	cout << result << '\n';
	return 0;
}
