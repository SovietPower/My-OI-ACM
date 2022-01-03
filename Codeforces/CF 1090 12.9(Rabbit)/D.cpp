#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,INF=0x3f3f3f3f;

int dgr[N],Enum,H[N],nxt[N<<1],to[N<<1],val[N],q[N];
bool vis[N],ban[N<<1];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AE(int u,int v)
{
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[u], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}

int main()
{
	int n=read(),m=read(); Enum=1;
	for(int i=1; i<=m; ++i) AE(read(),read());
	int X=0,Y=0;
	for(int i=1; i<=n; ++i)
		if(dgr[i]!=n-1)
		{
			X=i;
			for(int j=H[i]; j; j=nxt[j]) vis[to[j]]=1;
			for(int j=1; j<=n; ++j) if(!vis[j]&&i!=j) {Y=j; break;}
			break;
		}
	if(!X) return puts("NO"),0;

//	memset(val,0x3f,sizeof val);
	val[X]=n, val[Y]=1;
	printf("X:%d Y:%d\n",X,Y);
	int h=0,t=0,now=n-2; q[t++]=X;// q[t++]=Y;
	while(h<t)
	{
		int x=q[h++];
		if(x==Y) continue;
		for(int i=H[x],v; i; i=nxt[i])
		{
			if(ban[i]) continue;
			ban[i]=ban[i^1]=1;
//			if(!--dgr[v=to[i]])
			if(!val[v=to[i]])
				printf("%d->%d val:%d->%d\n",x,v,val[x],val[x]-1),
				val[v]=val[x]-1, q[t++]=v;
		}
	}
	int mn=n;
	for(int i=1; i<=n; ++i) val[i]>1&&(mn=std::min(mn,val[i]));
	printf("mn:%d\n",mn);
	for(int i=1; i<=n; ++i) if(!val[i]) val[i]=--mn;
	
//	if(h!=n) return puts("NO"),0;
	puts("YES");
	for(int i=1; i<=n; ++i) printf("%d ",val[i]); pc('\n');
	val[Y]=n;
	for(int i=1; i<=n; ++i) printf("%d ",val[i]); pc('\n');

	return 0;
}
