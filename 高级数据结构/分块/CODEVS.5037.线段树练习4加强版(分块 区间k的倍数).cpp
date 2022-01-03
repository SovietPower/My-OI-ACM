/*
如果用线段树，每个节点要再开k的空间，显然不行。但是分块可以(虽然空间依旧爆炸)

分块。用bloans[i][j]表示 第i块 模k为j 的有多少个 
对于不是整块的，查询时应判断 A[i]+tag[belong[i]] ==k || ==0 
对于整块，维护两个tag，一个是整块的加标记，另一个是整块的mod数标记tag2，初始时tag2为0 
当整块+v时，tag2 -=v。因为查询的应是 模k=0 的数的个数，整块+v后，这块要查的就是 模k=k-v ((k-v+v)%k=0)的个数 
这样就很巧妙地将整块加变成了改询问 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=2e5+5,MAXSZ=460;

int n,m,k,size,A[N],belong[N],bloans[MAXSZ][N],tag[MAXSZ],tag2[MAXSZ];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Update(int p,int v)
{
	--bloans[belong[p]][A[p]];
	A[p]+=v;
	if(A[p]>=k) A[p]-=k;
	++bloans[belong[p]][A[p]];
}
void Add(int l,int r,int v)
{
	int t=min(r,belong[l]*size);
	for(int i=l; i<=t; ++i)
		Update(i,v);
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1; i<=r; ++i)
			Update(i,v);
	for(int i=belong[l]+1; i<belong[r]; ++i)
	{
		tag[i]+=v, tag2[i]-=v;
		if(tag[i]>=k) tag[i]-=k;
		if(tag2[i]<0) tag2[i]+=k;
	}
}
int Query(int l,int r)
{
	int res=0, t=min(r,belong[l]*size);
	for(int i=l; i<=t; ++i)
		if(A[i]+tag[belong[l]]==k || !(A[i]+tag[belong[l]]))
			++res;
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1; i<=r; ++i)
			if(A[i]+tag[belong[r]]==k || !(A[i]+tag[belong[r]]))//beblong[l] belong[r]别写反了 
				++res;
	for(int i=belong[l]+1; i<belong[r]; ++i)
		res+=bloans[i][tag2[i]];
	return res;
}

int main()
{
	n=read(),m=read(),k=read();size=sqrt(n);
	for(int i=1;i<=n;++i)
	{
		A[i]=read()%k, belong[i]=(i-1)/size+1;
		if(A[i]<0) A[i]+=k;
		++bloans[belong[i]][A[i]];
	}
	char opt[9];int l,r,v;
	while(m--)
	{
		scanf("%s",opt);l=read(),r=read();
		if(opt[0]=='a')
			v=read(), Add(l,r,(v%k+k)%k);
		else
			printf("%d\n",Query(l,r));
	}

	return 0;
}
