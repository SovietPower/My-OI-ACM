/*
异或只有两种情况，可以将序列放到01Tire树上做 
在不异或的情况下在Tire上查找序列的mex很容易，从高位到低位 如果0位置上数没有满，则向0递归；否则向1 
(0位置上的数都满了 即 其子树叶子节点都有值)
异或情况下 若x在当前位有1，则反转0/1继续走 
由于异或具有结合率，异或一次求mex和异或多个数求原数列mex是一样的 
故每次不需要修改原数列，las^=opt即可 
注意需要去重 因为在判断某位置rt下的区间中的数都有时，需要num[rt]，相同的数显然不能算(画个图) 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=3e5+5,B=20;

int n,m,A[N],bit[36];
struct Node
{
	int val;
	Node *nxt[2];
	Node() {val=0, memset(nxt,NULL,sizeof nxt);}
}*rt,pool[N*19];
Node *new_Node()
{
	static int cnt=0;
	return &pool[cnt++];
}
Node *root=new_Node();
struct Trie
{
	void Insert(int n)
	{
		rt=root;
		for(int i=B; i; --i)
		{
//			printf("I i:%d bit[i]:%d n:%d %d %d\n",i,bit[i],n,n&bit[i],rt->val);
			bool id=n&bit[i];
			if(!rt->nxt[id])
				rt->nxt[id]=new_Node();
			++rt->val, rt=rt->nxt[id];
		}
		++rt->val;//..!
	}
	inline Node *to(Node *rt,bool p)
	{
		if(!rt->nxt[p]) rt->nxt[p]=new_Node();
		return rt->nxt[p];
	}
	int Query_Mex(int x)
	{
		int res=0; rt=root;
		for(int i=B; i; --i)
		{
			if(x&bit[i])
				if(!rt->nxt[1]) return res;//后面都没有过 
				else if(rt->nxt[1]->val < 1<<i-1) rt=rt->nxt[1];//,puts("C");
				else rt=to(rt,0), res+=(1<<i-1);//,puts("A");
			else
				if(!rt->nxt[0]) return res;
				else if(rt->nxt[0]->val < 1<<i-1) rt=rt->nxt[0];//,puts("D");
				else rt=to(rt,1), res+=(1<<i-1);//,puts("B");
//			printf("Q %d:%d %d   %d %d\n",x,i,res,bit[i],x&bit[i]);
		}
		return res;
	}
}t;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("842.in","r",stdin);
#endif

	for(int i=1; i<=B; ++i) bit[i] = 1<<i-1;
	n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	int cnt=1;
	for(int i=2; i<=n; ++i)
		if(A[i]!=A[i-1]) A[++cnt]=A[i];
	n=cnt;
	for(int i=1; i<=n; ++i) t.Insert(A[i]);
	int x=0;
	while(m--)
		x^=read(), printf("%d\n",t.Query_Mex(x));

	return 0;
}
