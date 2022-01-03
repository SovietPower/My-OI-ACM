/*
1400kb	460ms
$Description$
��$n$���������һ��������Ҫ$1$ʱ�̣�������$v_i$�����棨ֻ���һ�Σ���
ÿһʱ��ֻ����һ��������ÿ������ֻ����$[l_i,r_i]$��ʱ����������������档
$n\leq5000,l_i,r_i\leq10^8$��
$Solution$
��Ϊɶ����ѵ�$O(n^2\log n)$�������������ٷ���⣺https://wenku.baidu.com/view/c64d851ba8114431b90dd846.html��
���ȿ����ܷ���������ΪҪ��������������Ҫ�߶����Ż������ӶȻ����е�ߣ����Կ���BZOJ4276��BZOJ2034������ ���䷶Χ1e8����
����ͬһʱ���ж������Ҫ���ʱ�����г�ͻ��������Ȼ��ѡ��ֵ��ߵġ�
���ǰ�����Ӵ�С���������������ѡ����ôһ����ѡ����ֻ���ܵ���ͬ�����ʱ�̵�������ѡ��������ֻ��ѡһ������Ȼѡ�����ţ���
�����ڵ������ǣ�����ڱ�ѡĳЩ���������£��жϵ�ǰ�ܲ���ѡ��
����ÿ�����������ж�һ�£�������$n^3$�����Ǻ����ܹ�smg��
���ǽ��������䰴��˵�����Ҫѡ������Ӧ�þ�����ǰ�ţ���������ʱ�䡣�����ǰ������Ϊʱ�����������ͳ��԰�ǰ����������󼷡�
����ʵ�֣��Ե�ǰ����iö���������ʱ�̣������ǰʱ��û������Ͱ��Ÿ�����
�����赱ǰʱ�̵�����Ϊx����r[x]>r[i]�����Խ�x���󼷣��������ܰ�xƥ�䵽��һ��λ�þͳɹ�ƥ�䣬����i�Ͳ�����ƥ���ˣ�
���r[x]<=r[i]�����԰�i����һ��ʱ�̷š�
ʱ�̿϶�����ֱ��ö�١����Ƿ������õ�ʱ�����ֻ��$n$������ÿ��λ�õ���һ����ƥ���λ�á�
���Զ�������ɢ��һ�¾����ˡ�
> ̰���㷨��ȷ�Ե�һ������
�����������㷨���Ӵ�Сһ��һ��ƥ�䣬һ����һ����ƥ���У���ôһֱ��ƥ�����档 
���Ӷ�$O(n^2)$��
�и�С�Ż��ǣ�����˵��x�����֮ǰ����Ϊ�����У������û��Ҫ����DFS�ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5005;

int ref[N],lk[N],tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int l,r,v;
	bool operator <(const Node &x)const{
		return v>x.v;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Lower(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline int Upper(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<=x) l=mid+1;
		else r=mid;
	return l;
}
bool DFS(int x,int l,int r)
{
	if(l>r) return 0;
	int p=lk[l];
	if(!p) return lk[l]=x,1;
	if(A[p].r>A[x].r)
		if(!tag[p]&&DFS(p,l+1,A[p].r)) return lk[l]=x,1;
		else return tag[p]=1,0;
	return DFS(x,l+1,r);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=(Node){ref[i]=read(),read(),read()};
	std::sort(ref+1,ref+1+n); ref[n+1]=1e9;
	for(int i=2; i<=n; ++i) ref[i]=std::max(ref[i-1]+1,ref[i]);
	for(int i=1; i<=n; ++i) A[i].l=Lower(A[i].l,n), A[i].r=Upper(A[i].r,n+1)-1;

	std::sort(A+1,A+1+n); long long ans=0;
	for(int i=1; i<=n; ++i)
		if(DFS(i,A[i].l,A[i].r)) ans+=A[i].v;
	printf("%lld\n",ans);

	return 0;
}
