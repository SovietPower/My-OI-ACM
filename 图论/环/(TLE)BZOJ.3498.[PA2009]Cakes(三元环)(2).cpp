/*
TLE
$Description$
n����m���ߵ�����ͼ��ÿ�����е�Ȩ����������һ����Ԫ��(i,j,k),i<j<k���乱��Ϊmax{ai,aj,ak}����������Ԫ���Ĺ��׺͡�
$Solution$
����n����m���ߵ�ͼ������ÿһ���ߣ�ö�������˵��ж������ٵĶ˵���ڽӵ㣬�ж��Ƿ񹹳���Ԫ���������������жϴ�����m�����γ�һ����ȫͼʱ�ﵽ��󣬼�O(m*sqrt(m))��
�������������ߣ����ǿ���ֱ��ö�ٶ�����С�ġ�
Ȼ������д��ôTLE�ˡ��������ӶȲ�С��ÿ��һ������set��log��
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=250005;

int n,m,val[N],Link[N],dgr[N];
std::set<int> s[N];
std::vector<int> vec[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	++dgr[u], vec[u].push_back(v), s[u].insert(v);
}
long long Calc(int x,int y)
{
	const std::vector<int> &X=vec[x];
	long long res=0; int v=std::max(val[x],val[y]);
	for(int i=0,l=X.size(); i<l; ++i) if(s[y].count(X[i])) res+=std::max(v,val[X[i]]);
	return res;
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i) val[i]=read();
	for(int i=1,u,v; i<=m; ++i)
		u=read(), v=read(), val[u]>val[v]?AddEdge(u,v):AddEdge(v,u);//��������ͼ�Ļ���/3������ 
	long long ans=0;
	for(int x=1; x<=n; ++x)
	{
		const std::vector<int> &X=vec[x];
		for(int j=0,l=X.size(); j<l; ++j)
			ans+=dgr[x]<dgr[X[j]]?Calc(x,X[j]):Calc(X[j],x);
	}
	printf("%lld",ans);

	return 0;
}
