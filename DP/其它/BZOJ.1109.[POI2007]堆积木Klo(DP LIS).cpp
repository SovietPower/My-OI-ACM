/*
2480kb	264ms
��ά$DP$��Ȼ�����Ի���һά����$f[i]$��ʾ��ǿ�ư�$i$�ŵ�$a_i$λ��ȥ��������ƥ��������Ŀ��
��ô$f[i]=\max\{f[j]\}+1$������$j<i,\ a_j<a_i,\ j-a_j\leq i-a_i$��������άƫ�򣬿���$CDQ$��

����������ʽ�����ƣ��ٹ۲�һ�£�������$a_i>a_j,\ i-a_i\geq j-a_j$�Ϳ����Ƴ�$i>j$��
����ֻҪ�������������Ϳ����ˣ�����άƫ��
ͬʱת�ƱȽ����⣬��$i-a_i$��С�������򣨵ڶ��ؼ���Ϊ$a_i$��С���󣩣���$a_i$��$LIS$���ɡ�

ע����ʵ���и�������$j-a_j\geq 0$��Ҫ�С�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int A[N],id[N],sk[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool cmp(int x,int y)
{
	return x-A[x]==y-A[y]?A[x]<A[y]:x-A[x]<y-A[y];
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(sk[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read(), id[i]=i;
	std::sort(id+1,id+1+n,cmp);
	int top=0; sk[0]=-1;
	for(int i=1,a=A[id[1]]; i<=n; a=A[id[++i]])
		if(id[i]-a>=0)//j-a[j]>=0��
			if(a>sk[top]) sk[++top]=a;
			else sk[Find(a,top)]=a;
	printf("%d\n",top);

	return 0;
}
