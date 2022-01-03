/*
分块。对于块之外的，暴力修改、查询；
对于一整块内的，修改后sort使每一块块有序，询问时二分>=C的位置求个数 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e6+5;

int n,m,A[N],bel[N],size,blo[N],tag[N];//块是要有序的，要和原数组分开 

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Reset(int p)
{
	int l=(p-1)*size+1,r=min(p*size,n);//注意取min 不要超边界！
	for(int i=l;i<=r;++i)
		blo[i]=A[i];
	sort(blo+l,blo+1+r);//保证一块中的元素有序 
}
void Add(int l,int r,int v)
{
	int t=min(r,bel[l]*size);
	for(int i=l; i<=t; ++i)
		A[i]+=v;
	Reset(bel[l]);
	if(bel[l]!=bel[r])
	{
		for(int i=(bel[r]-1)*size+1; i<=r; ++i)
			A[i]+=v;
		Reset(bel[r]);
	}
	for(int i=bel[l]+1; i<bel[r]; ++i)
		tag[i]+=v;
}
int Find(int p,int x)//找到第一个 >= x 的位置 
{
	int l=(p-1)*size+1, r=min(p*size,n), m, R=r;
	while(l<=r)
	{
		m=l+r>>1;
		if(blo[m]<x) l=m+1;
		else r=m-1;
	}
	return R-l+1;
}
int Query(int l,int r,int v)
{
	int res=0, t=min(r,bel[l]*size);
	for(int i=l; i<=t; ++i)
		if(A[i]+tag[bel[l]]>=v) ++res;//别忘了加块的标记tag 
	if(bel[l]!=bel[r])
		for(int i=(bel[r]-1)*size+1; i<=r; ++i)
			if(A[i]+tag[bel[r]]>=v) ++res;
	for(int i=bel[l]+1; i<bel[r]; ++i)
		res+=Find(i,v-tag[i]);//查询一整块的值时，要减去块的加标记 
	return res;
}

int main()
{
	n=read(),m=read();size=sqrt(n);
	for(int i=1;i<=n;++i)
		A[i]=read(), bel[i]=(i-1)/size+1;
	for(int i=1;i<=bel[n];++i)//别忘了blo的初值 
		Reset(i);
	char opt[3];int l,r,v;
	while(m--)
	{
		scanf("%s",opt);l=read(),r=read(),v=read();
		if(opt[0]=='M')
			Add(l,r,v);
		else
			printf("%d\n",Query(l,r,v));
	}

	return 0;
}
