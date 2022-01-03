/*
187ms	0KB
$Description$
有一棵$n$个点的树。你需要在$11111$次询问内确定出这棵树的形态。每次询问你给定两个非空且不相交的点集$S,T$和一个点$u$，交互库会告诉你满足$x\in S,y\in T$，且$x\to y$经过了$u$的点对$(x,y)$的数量。
$n\leq500$。
$Solution$
不妨假设以$1$为根。首先如果想知道$y$是否在$x$的子树内，询问$S=\{1\},T=\{y\},u=x$就可以了（同样可以扩展到某点集中有多少个点在$x$子树内）。
那么对于每个点$i$，询问$S=\{1\},T=\{2,3,...,n\},u=i$，就可以知道$i$子树的大小$size_i$。
有什么用呢。。把所有点按$size_i$从大到小排序，那么该序列中每个点的父节点一定在它的左边。
（PS：这个序列还可以增量构造出来：考虑在已有$1...i$的序列中加入$i+1$，二分找到一个最靠右的点$p$，满足$a_1,a_2,...,a_p$没有点在$i+1$的子树中，然后把$i+1$插入到$a_p$后面即可。需要$O(n\log n)$次询问。）
考虑从右往左扫这个序列，对每个节点找出它直属的儿子。
假设当前是点$i$，设$i$后面还没有找到父亲的点集是$P$。首先查一次$P$中是否没有点在$i$的子树中。$S=\{1\},T=P,u=i$询问一次即可。
若$P$中存在$i$子树内的点，可以二分找出$P$中最靠左的一个$i$的儿子$P_j$，连边$(i,p)$。然后再对$P'=\{P_{j+1},P_{j+2},...\}$继续重复上边过程即可。
询问次数$O(n\log n)+2n$。（数据实测最多$<5500$）（有$200$组数据=-=）
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
int Query_Exist(int x,const std::vector<int> &vec,int r)//vec中存在x子树中的点 
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
