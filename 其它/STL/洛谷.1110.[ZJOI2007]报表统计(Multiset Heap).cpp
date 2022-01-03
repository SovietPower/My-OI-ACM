/*
对于询问1，用堆代替multiset/Splay 
对于询问2，multiset 
1.注意哨兵元素 
2.注意multiset中删除时是删除某元素的一个位置，而不是这个元素！这个值会全部都删掉 
*/
#include<set>
#include<cstdio>
#include<cctype>
#include<algorithm>
const int N=5e5+5,M=N*3,INF=1e9;

int n,q,st[N],ed[N],Min=INF;
std::multiset<int> A;
std::multiset<int>::iterator it;
struct Heap
{
	int sz,A[M];
	inline int Top()
	{
		return A[1];
	}
	void Push(int x)
	{
		A[++sz]=x;
		int now=sz,nxt=now>>1;
		while(now>1 && A[nxt]>A[now])
			std::swap(A[nxt],A[now]), now=nxt, nxt=now>>1;
	}
	void Pop()
	{
		A[1]=A[sz--];
		int now=1,nxt;
		while(now<<1<=sz)
		{
			nxt=now<<1;
			if(A[nxt]>A[nxt+1] && nxt<sz) ++nxt;
			if(A[nxt]>=A[now]) break;
			std::swap(A[now],A[nxt]);
			now=nxt;
		}
	}
}h1,h2;

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
void Ins(int v)
{
	it=A.lower_bound(v);
	Min=std::min(Min,*it-v);
	Min=std::min(Min,v-(*--it));
	A.insert(v);
}
void Modify()
{
	int p=read(),v=read();
	if(p!=n)
		h2.Push(std::abs(st[p+1]-ed[p])),
		h1.Push(std::abs(st[p+1]-v));
	h1.Push(std::abs(ed[p]-v));
	ed[p]=v;
	if(Min) Ins(v);
}
inline int Query()
{
	while(h1.Top()==h2.Top()) h1.Pop(),h2.Pop();
	return h1.Top();
}

int main()
{
//	freopen("form.in","r",stdin);
//	freopen("form.out","w",stdout);

	n=read(),q=read();
	A.insert(-INF), A.insert(INF);
	st[1]=ed[1]=read(),Ins(st[1]);
	for(int i=2;i<=n;++i)
		st[i]=ed[i]=read(),h1.Push(std::abs(st[i]-st[i-1])),Ins(st[i]);
	char s[20];int p,v;
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='I') Modify();
		else if(s[4]=='G') printf("%d\n",Query());
		else printf("%d\n",Min);
	}

	return 0;
}
