/*
1951ms	32664kb
��״����������
����˼·���䣨һά��չ����ά�����һ�е���ά������
����ÿһ�У������һ�У�����Ӱ���ֻ�Ƕ���һ�еĲ�����
��ô����ĳһ�У��������ĳ�β���ɾ�����ǵڼ��β�����һ�к������������ԭ�����е��ĸ�������ͬ���ǲ�k��ֵ���㡣
��Ϊ�ܹ�ֻ����q������ĳ�к������������ֱ����vector��ÿһ��ÿ�β��ں�����������һ��һ����
��k��ֵ����k�����ڵ������߶���ƽ�������С�����+��״����Ҳ���ԡ�
��Ϊ���ܶ�̬���㿪n+1����״���飬�������ߣ�ÿ�ζ�ÿһ������״������Ȼ��ĳ�ʼ״̬��
�������һ��Ҳ��һ�鼴�ɡ�
���Ӷ�$O(n\log^2n)$��������С�����������Ǳ��߶���������
�Ҿ�Ȼ�ñ߱��ÿһ�е�ѯ��mdzz��˳��ᷴ����
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int qx[N],qy[N],pos[N];
std::vector<LL> e[N],v[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct BIT
{
	int n,t[N*4];//2n! �ٿ�һ����ΪԤ���� 
	#define lb(x) (x&-x)
	inline void Add(int p)
	{
		for(; p<=n; p+=lb(p)) ++t[p];
	}
	inline void Delete(int p)
	{
		for(; p<=n; p+=lb(p)) --t[p];
	}
	inline int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
	void Init(int nn)
	{
		n=nn, ++t[n];
		for(int i=1; i<n; ++i) ++t[i]/*init:a[i]=1*/, t[i+lb(i)]+=t[i];//i+lb(i)>n
	}
	inline int Kth(int k)
	{
		int l=1,r=n,mid;
		while(l<r)
			if(Query(mid=l+r>>1)<k) l=mid+1;
			else r=mid;
		return l;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),q=read();
	for(int i=1; i<=q; ++i)
	{
		qx[i]=read(),qy[i]=read();
		if(qy[i]!=m) e[qx[i]].push_back(i);
	}

	T.Init(std::max(n,m)+q);
	for(int x=1; x<=n; ++x)
	{
		for(int i=0,j,l=e[x].size(); i<l; ++i)
			j=e[x][i], T.Delete(pos[j]=T.Kth(qy[j]));
		for(int i=0,l=e[x].size(); i<l; ++i) T.Add(pos[e[x][i]]);
	}
	for(int i=1,x,y,p; i<=q; ++i)
	{
		x=qx[i],y=qy[i];
		T.Delete(p=T.Kth(x));
		LL ans= p<=n?(LL)p*m:v[0][p-n-1];
		if(y!=m)
		{
			v[x].push_back(ans);
			ans= pos[i]<m?(1ll*(x-1)*m+pos[i]):v[x][pos[i]-m];
		}
		v[0].push_back(ans);
		printf("%lld\n",ans);
	}

	return 0;
}
