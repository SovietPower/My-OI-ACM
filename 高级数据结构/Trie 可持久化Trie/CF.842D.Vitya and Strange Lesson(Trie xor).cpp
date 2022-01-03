/*
���ֻ��������������Խ����зŵ�01Tire������ 
�ڲ������������Tire�ϲ������е�mex�����ף��Ӹ�λ����λ ���0λ������û����������0�ݹ飻������1 
(0λ���ϵ��������� �� ������Ҷ�ӽڵ㶼��ֵ)
�������� ��x�ڵ�ǰλ��1����ת0/1������ 
���������н���ʣ����һ����mex�����������ԭ����mex��һ���� 
��ÿ�β���Ҫ�޸�ԭ���У�las^=opt���� 
ע����Ҫȥ�� ��Ϊ���ж�ĳλ��rt�µ������е�������ʱ����Ҫnum[rt]����ͬ������Ȼ������(����ͼ) 
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
				if(!rt->nxt[1]) return res;//���涼û�й� 
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
