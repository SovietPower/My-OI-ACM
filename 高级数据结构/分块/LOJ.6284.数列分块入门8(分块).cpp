/*
$Description$
给出一个长为n的数列，以及n个操作，操作涉及区间询问等于一个数c的元素，并将这个区间的所有元素改为c。
$Solution$
模拟一些数据可以发现，询问后一整段都会被修改，几次询问后数列可能只剩下几段不同的区间了。
那么还是暴力，每个块维护的是整个块是否仅被一种权值覆盖。查询时对于相同权值的块就可以O(1)统计；否则暴力统计并修改答案；不完整的块暴力。 
这样看似最差情况下每次需要O(n)的时间，但实际远远到不了 
假设初始序列都是同一个值，那么查询需要O(sqrt(n))，如果这时进行区间修改，那么最多会破坏首尾两个块的标记 
所以只能使后面的询问至多多2个块的暴力时间，所以均摊每次操作复杂度为O(sqrt(n)) 
换句话说，要想让一个操作耗费O(n)的时间，要先花费sqrt(n)个操作修改数列 
--by hzwer
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=1e6;

int n,size,sizen,A[N],tag[2000],bel[N],L[2000],R[2000];
bool cover[2000];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Count(int l,int r,int v)
{
	int res=0;
	for(int i=l; i<=r; ++i)
		if(A[i]==v) ++res; else A[i]=v;
	return res;
}
void Reset(int p,int l,int r,int vbef,int v)
{//Reset [L(p),l)&&(r,R(p)] to vbef,[l,r] to v
	for(int i=L[p]; i<l; ++i) A[i]=vbef;
	for(int i=l; i<=r; ++i) A[i]=v;
	int t=std::min(n,R[p]);
	for(int i=r+1; i<=t; ++i) A[i]=vbef;
	cover[p]=0;
}
int Get_scatter(int l,int r,int v)
{
	if(cover[bel[l]])
		if(tag[bel[l]]==v) return r-l+1;
		else Reset(bel[l],l,r,tag[bel[l]],v);
	else return Count(l,r,v);
	return 0;
}
int Query(int l,int r,int v)
{
	int res=Get_scatter(l,std::min(r,R[bel[l]]),v);

	if(bel[l]!=bel[r]) res+=Get_scatter(L[bel[r]],r,v);

	for(int i=bel[l]+1; i<bel[r]; ++i)
		if(cover[i])
			if(tag[i]==v) res+=bel[l]==bel[n]?sizen:size;
			else tag[i]=v;
		else
			res+=Count(L[i],R[i],v), cover[i]=1, tag[i]=v;
	return res;
}

int main()
{
	n=read(), size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1, A[i]=read();
	for(int i=1; i<=bel[n]; ++i) L[i]=(i-1)*size+1,R[i]=i*size;
	sizen=n-(bel[n]-1)*size;
	for(int l,r,c,i=1; i<=n; ++i)
		l=read(), r=read(), c=read(), printf("%d\n",Query(l,r,c));
	return 0;
}
