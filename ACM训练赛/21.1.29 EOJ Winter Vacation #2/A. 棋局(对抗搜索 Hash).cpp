#include <map>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=12,INF=0x3f3f3f3f;

int n,m,A[N][N],B[N][N],num[N];
LL End;
std::map<LL,int> mp;

bool Unzip(LL sta)
{
	int sum=0;
	for(int i=n; i; --i) sum+=(num[i]=sta%(m+1)), sta/=(m+1);
	return sum&1;
}
LL Zip()
{
	LL res=0;
	for(int i=1; i<=n; ++i) res=res*(m+1)+num[i];
	return res;
}
int DFS(LL sta)
{
	if(mp.find(sta)!=mp.end()) return mp[sta];
	if(sta==End) return 0;
	bool type=Unzip(sta);//0:A:max 1:B:min
	int res=type?INF:-INF;
	if(num[1]<m)
	{
		++num[1];
		if(type) res=std::min(res,DFS(Zip())-B[1][num[1]]);
		else res=std::max(res,DFS(Zip())+A[1][num[1]]);
		--num[1];
	}
	for(int i=2; i<=n; ++i)
		if(num[i-1]>num[i])
		{
			++num[i];
			if(type) res=std::min(res,DFS(Zip())-B[i][num[i]]);
			else res=std::max(res,DFS(Zip())+A[i][num[i]]);
			--num[i];
		}
	return mp[sta]=res;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) scanf("%d",&A[i][j]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) scanf("%d",&B[i][j]);
	for(int i=1; i<=n; ++i) num[i]=m; End=Zip();
	DFS(0);
	printf("%d",mp[0]);

	return 0;
}
