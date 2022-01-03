/*
2392kb	792ms
$Description$
����$n,m,c$��$Q$��ѯ�ʣ�ÿ��ѯ�ʸ���$2*c$��ģ�崮�������ڶ��ٸ�$n*m$�������г��ֹ������̵�ÿ������������״̬��
$n\leq 100,m\leq 12,c\leq 6,Q\leq 5$��
$Solution$
ģ�崮ֻ��$2$�У��������������������������DP��
����$(i,j)$������ӣ�ֻ��Ҫ����$(i-1,j)$�Ƿ�ƥ����ģʽ���ĵ�һ�У�$(i,j)$ƥ�䵽ģʽ���ڶ��е��ġ�
������$f[i][j][S][x][y]$��ʾ����ǰΪ$(i,j)$��$i-1$��ƥ����ģʽ����һ�е�λ��״̬Ϊ$S$��$S$��$k$λΪ$1$˵��$(i-1,k)$ƥ���˵�һ�У�����$i$��ƥ�䵽ģʽ����һ�е�λ��$x$��ƥ�䵽�ڶ���$y$��
ת��ʱö�������ַ�����KMPԤ�����������һλ��
���Ӷ�$O(nm2^{m-c+1}c^2)$��$S$ֻ���$m-c+1$λ����
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=13;
const LL LIM=(LL)1e18;

int f[2][(1<<12)+1][7][7];

struct KMP
{
	int s[N],fail[N],to[N][3];
	char tmp[N];
	void Build(const int n)
	{
		scanf("%s",tmp+1);
		for(int i=1; i<=n; ++i) s[i]=tmp[i]=='W'?0:(tmp[i]=='B'?1:2);
		for(int i=2,j=0; i<=n; ++i)
		{
			while(j && s[i]!=s[j+1]) j=fail[j];
			fail[i]=s[i]==s[j+1]?++j:0;
		}
		s[n+1]=233;
		for(int i=0; i<=n; ++i)
			for(int c=0; c<3; ++c)
			{
				int j=i;
				while(j && s[j+1]!=c) j=fail[j];
				to[i][c]=s[j+1]==c?j+1:0;
			}
	}
}s1,s2;

inline void Clear(int (*f)[7][7],const int lim,const int C)
{
	for(int s=0; s<=lim; ++s)
		for(int a=0; a<=C; ++a)
			for(int b=0; b<=C; ++b) f[s][a][b]=0;
}

int main()
{
	int n,m,C,Q; scanf("%d%d%d%d",&n,&m,&C,&Q);
	int lim=(1<<m-C+1)-1; LL pw3=1;
	for(int i=n*m; i; --i) pw3=3ll*pw3, pw3>=LIM&&(pw3%=mod);
	pw3%=mod;

	while(Q--)
	{
		s1.Build(C), s2.Build(C);
		int p=0; memset(f[p],0,sizeof f[p]);
		f[p][0][0][0]=1;
		for(int i=1; i<=n; ++i)
		{
			Clear(f[p^1],lim,C);// memset(f[p^1],0,sizeof f[p^1]);//״̬�ٰ� 
			for(int s=0; s<=lim; ++s)
			{
				LL tmp=0;
				for(int a=0; a<=C; ++a)
					for(int b=0; b<=C; ++b)
						tmp+=f[p][s][a][b];
				f[p^1][s][0][0]=tmp%mod;
			}
			p^=1;
			for(int j=1; j<=m; ++j)
			{
				p^=1, Clear(f[p],lim,C);// memset(f[p],0,sizeof f[p]);
				for(int s=0; s<=lim; ++s)
					for(int a=0; a<=C; ++a)
						for(int b=0,v; b<=C; ++b)
							if((v=f[p^1][s][a][b]))
								for(int c=0; c<3; ++c)
								{
									int ta=s1.to[a][c],tb=s2.to[b][c];
									if(j<C) Add(f[p][s][ta][tb],v);
									else if(!(s>>j-C&1))
										if(ta!=C) Add(f[p][s][ta][tb],v);
										else Add(f[p][s|(1<<j-C)][ta][tb],v);
									else if(tb!=C)
										if(ta!=C) Add(f[p][s^(1<<j-C)][ta][tb],v);
										else Add(f[p][s][ta][tb],v);
								}
			}
		}
		LL ans=0;
		for(int s=0; s<=lim; ++s)
			for(int a=0; a<=C; ++a)
				for(int b=0; b<=C; ++b) ans+=f[p][s][a][b];
		printf("%d\n",(int)((pw3+mod-ans%mod)%mod));
	}
	return 0;
}
