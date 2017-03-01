#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, m, num;

	while (cin >> n)
	{
		vector<int> s1, s2;
		for (int i = 0; i < n; ++ i)
		{
			cin >> num;
			s1.push_back(num);
		}
		cin >> m;
		for (int i = 0; i < m; ++ i)
		{
			cin >> num;
			s2.push_back(num);
		}
		int cnt = (n + m + 1) >> 1;
		int i = 0, j = 0;
		int median = -1;
		for ( ; i<n && j<m && cnt>0; -- cnt)
		{
			if (s1[i] < s2[j])
			{
				median = s1[i];			
				++ i;
			} else
			{
				median = s2[j];
				++ j;
			}
		}
		for ( ; i<n && cnt>0; ++ i, -- cnt)
		{
			median = s1[i];
		}
		for ( ; j<m && cnt>0; ++ j, -- cnt)
		{
			median = s2[j];
		}
		cout << median << endl;
	}

	return 0;
}
