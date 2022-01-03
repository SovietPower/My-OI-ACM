/*
$Description$
给定一个$n$个点的二分图，每条边有边权。求一个边权最小的边集，使得删除该边集后不存在完备匹配。
$n\leq20$。
$Solution$
设点集为$S$，与$S$中的点相邻的点的并集为$N(S)$。由Hall定理，若存在点集$S$满足$|S|>|N(S)|$，则该图不存在完备匹配。
因为$n$很小，直接枚举所有子集$S$并贪心删相邻点即可。
另外topcoder跑得快，直接写$2^n*n^2$就好了。。
*/
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#define pb push_back
using namespace std;

class Revmatching
{
public:
	int sum[23];
	int smallest(vector<string> A)
	{
		int n=A.size(),ans=2e9;
		for(int s=1,all=1<<n; s<all; ++s)
		{
			memset(sum,0,sizeof sum);
			for(int i=0; i<n; ++i)
				if(s>>i&1)
					for(int j=0; j<n; ++j)
						sum[j]+=A[i][j]-'0';
			std::sort(sum,sum+n);
			int res=0;
			for(int i=n-__builtin_popcount(s); ~i; --i)
				res+=sum[i];
			ans=std::min(ans,res);
		}
		return ans;
	}
};
