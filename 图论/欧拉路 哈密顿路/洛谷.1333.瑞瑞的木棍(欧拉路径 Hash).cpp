#include <cstdio>
#include <cstring>
const int N=2e6+5,M=5e5+5,mod=2e6;
const int seed[5]={31,37,131,41};

int dgr[N],fa[M];
char s[15];
namespace Hash
{
	int cnt,val[N],pos[N];
	int Get_Hash(char *s)
	{
		int x=0,l=strlen(s);
		for(int i=0; i<l; ++i) x=(x+s[i]*seed[i%4])%mod;
		return x;
	}
	int Insert(char *s)
	{
		int p=Get_Hash(s);
		while(val[p]&&val[p]!=p){
			++p;
			if(p>=mod) p-=mod;
		}
		if(val[p]) return pos[p];
		val[p]=p;
		return pos[p]=++cnt;
	}
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	int p1,p2,r1,r2,t=0;
	for(int i=1; i<M; ++i) fa[i]=i;
	while(~scanf("%s",s))
	{
		p1=Hash::Insert(s);
		scanf("%s",s);
		p2=Hash::Insert(s);
		++dgr[p1], ++dgr[p2];
		r1=Find(p1), r2=Find(p2);
		if(r1!=r2) ++t,fa[r1]=r2;
	}
	if(t<Hash::cnt-1) {printf("Impossible"); return 0;}
	int tot=Hash::cnt; t=0;
	for(int i=1; i<=tot; ++i)
		if(dgr[i]&1) ++t;
	printf(t>2?"Impossible":"Possible");

	return 0;
}
