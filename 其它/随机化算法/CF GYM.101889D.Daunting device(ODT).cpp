/*
77ms	400KB
$Description$
$n$��λ�ã���ʼÿ��λ����ɫ��Ϊ$1$��
$m$�β�����ÿ�θ���$p,x$�����㵱ǰ�ж��ٸ�λ����ɫΪ$p$�����ô𰸼������������$[l,r]$����$[l,r]$ȾɫΪ$x$��
���������ִ���������ɫ�ĳ��ִ�����
$Solution$
����Ҳ���㴿���������ֵ�ܶ࣬������س�����û�뵽������ODT���ֱ�������
ODT�Ļ��ܺ�д��ֱ�ӱ����������ˡ�
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Iter std::set<Node>::iterator
typedef long long LL;
const int N=1e5+5;

int sum[N];
struct Node
{
	int l,r,col;
	Node(int l=0,int r=-1,int col=0):l(l),r(r),col(col) {}
	bool operator <(const Node &x)const
	{
		return l==x.l?col<x.col:l<x.l;
	}
};
std::set<Node> st;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
Iter Split(int p)
{
	Iter it=st.lower_bound(Node(p));
	if(it!=st.end() && it->l==p) return it;
	--it;
	int l=it->l,r=it->r,col=it->col;
	st.erase(it), st.insert(Node(l,p-1,col));
	return st.insert(Node(p,r,col)).first;
}

int main()
{
	int n=read(),C=read(),m=read();
	sum[1]=n, st.insert(Node(1,n,1));
	for(; m--; )
	{
		int S=sum[read()],x=read(),A=read(),B=read(),l=(A+1ll*S*S)%n+1,r=(A+1ll*(S+B)*(S+B))%n+1;
		l>r&&(std::swap(l,r),0);
		Iter R=Split(r+1),L=Split(l),tmp=L;
		for(; L!=R; ++L) sum[L->col]-=L->r-L->l+1;
		st.erase(tmp,R), st.insert(Node(l,r,x)), sum[x]+=r-l+1;
	}
	int ans=sum[1];
	for(int i=2; i<=C; ++i) sum[i]>ans&&(ans=sum[i]);
	printf("%d\n",ans);

	return 0;
}
