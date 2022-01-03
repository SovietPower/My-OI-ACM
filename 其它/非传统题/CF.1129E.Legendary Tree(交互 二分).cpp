/*
187ms	0KB
$Description$
��һ��$n$�������������Ҫ��$11111$��ѯ����ȷ�������������̬��ÿ��ѯ������������ǿ��Ҳ��ཻ�ĵ㼯$S,T$��һ����$u$������������������$x\in S,y\in T$����$x\to y$������$u$�ĵ��$(x,y)$��������
$n\leq500$��
$Solution$
����������$1$Ϊ�������������֪��$y$�Ƿ���$x$�������ڣ�ѯ��$S=\{1\},T=\{y\},u=x$�Ϳ����ˣ�ͬ��������չ��ĳ�㼯���ж��ٸ�����$x$�����ڣ���
��ô����ÿ����$i$��ѯ��$S=\{1\},T=\{2,3,...,n\},u=i$���Ϳ���֪��$i$�����Ĵ�С$size_i$��
��ʲô���ء��������е㰴$size_i$�Ӵ�С������ô��������ÿ����ĸ��ڵ�һ����������ߡ�
��PS��������л����������������������������$1...i$�������м���$i+1$�������ҵ�һ����ҵĵ�$p$������$a_1,a_2,...,a_p$û�е���$i+1$�������У�Ȼ���$i+1$���뵽$a_p$���漴�ɡ���Ҫ$O(n\log n)$��ѯ�ʡ���
���Ǵ�������ɨ������У���ÿ���ڵ��ҳ���ֱ���Ķ��ӡ�
���赱ǰ�ǵ�$i$����$i$���滹û���ҵ����׵ĵ㼯��$P$�����Ȳ�һ��$P$���Ƿ�û�е���$i$�������С�$S=\{1\},T=P,u=i$ѯ��һ�μ��ɡ�
��$P$�д���$i$�����ڵĵ㣬���Զ����ҳ�$P$������һ��$i$�Ķ���$P_j$������$(i,p)$��Ȼ���ٶ�$P'=\{P_{j+1},P_{j+2},...\}$�����ظ��ϱ߹��̼��ɡ�
ѯ�ʴ���$O(n\log n)+2n$��������ʵ�����$<5500$������$200$������=-=��
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define pc putchar
#define Flush() fflush(stdout)
#define gc() getchar()
typedef long long LL;
const int N=505;

int id[N],sz[N],fa[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline bool cmp(int a,int b)
{
	return sz[a]>sz[b];
}
int Query_Size(int x,int n)
{
	printf("1\n1\n%d\n",n-1);
	for(int i=2; i<=n; ++i) printf("%d ",i);
	return printf("\n%d\n",x),Flush(),read();
}
int Query_Exist(int x,const std::vector<int> &vec,int r)//vec�д���x�����еĵ� 
{
	printf("1\n1\n%d\n",r);
	for(int i=0; i<r; ++i) printf("%d ",vec[i]);
	return printf("\n%d\n",x),Flush(),read();
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) id[i]=i;
	sz[1]=n;
	for(int i=2; i<=n; ++i) sz[i]=Query_Size(i,n);
	std::sort(id+1,id+1+n,cmp);
	std::vector<int> vec;
	for(int i=n; i; --i)
	{
		int x=id[i];
		std::vector<int> P=vec,tmp;
		while(!P.empty()&&Query_Exist(x,P,P.size()))
		{
			int l=1,r=P.size(),mid;
			while(l<r)
				if(Query_Exist(x,P,mid=l+r>>1)) r=mid;
				else l=mid+1;
			fa[P[--l]]=x;
			auto it=P.begin();
			while(l--) tmp.push_back(*it++);
			P.erase(P.begin(),++it);
		}
		for(auto v:P) tmp.push_back(v);
		vec=tmp, vec.push_back(x);
	}
	puts("ANSWER");
	for(int i=2; i<=n; ++i) printf("%d %d\n",fa[i],i);

	return 0;
}
