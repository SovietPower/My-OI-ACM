/*
$Description$
����һ��$n$����Ķ���ͼ��ÿ�����б�Ȩ����һ����Ȩ��С�ı߼���ʹ��ɾ���ñ߼��󲻴����걸ƥ�䡣
$n\leq20$��
$Solution$
��㼯Ϊ$S$����$S$�еĵ����ڵĵ�Ĳ���Ϊ$N(S)$����Hall���������ڵ㼯$S$����$|S|>|N(S)|$�����ͼ�������걸ƥ�䡣
��Ϊ$n$��С��ֱ��ö�������Ӽ�$S$��̰��ɾ���ڵ㼴�ɡ�
����topcoder�ܵÿ죬ֱ��д$2^n*n^2$�ͺ��ˡ���
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
