/*
624K	63MS
$Description$
��һ����СΪN�ļ���$S=\{x_1,x_2,....,x_n\}$��$x_i=0��1$����������֮���һЩ�߼�����Ľ������x1 and x2=1�����߼�������AND OR XOR���֣����Ƿ����һ����������������ȡֵ������
$Solution$
���ڱ��⣬�����������ÿ���߼����㣺
1��A AND B=0.��Ҫ��A��B��ͬʱΪ1����Ȼ��ͬʱΪ1����ôAȡ1ʱ��B����ȡ0��Bȡ1ʱ��A����ȡ0.���ԣ�����A+n->B, B+n->A��
2��A AND B=1.��Ҫ��A��BͬʱΪ1�����仰˵��A��B������0.��Ҫ��ô��������ͼ���أ�����֪�����ж�һ��2-sat�����Ƿ���ںϷ������ķ����ǣ�������ж���û������ͬ�������ͬһ����ͨ������
������ҪA��B��������1����ô���Ǿ���A��B����ѡ0ʱ�޽⼴�ɡ�Ҳ����˵������A->A+n, B->B+n�������Ļ������繹ͼ��ɺ�A����ȡ0����ô���ڴ��ڱ�A->A+n������AҲ����ȡ1����ô�Ͳ�������һ���Ϸ����������ԣ����������ܱ�֤���кϷ������Ļ���һ����Aȡ1��ѡA+n�ڵ㣩�������
3��A OR B=0.��Ҫ��A��BͬʱΪ0.��2���ơ�
4��A XOR B=0.��Ҫ��A=B�����ԣ�AΪ0/1ʱ��B����Ϊ0/1��ͬ��BΪ0/1ʱ��A����Ϊ0/1.������ӱߣ�A->B,B->A,A+n->B+n,B+n->A+n��

����ĳ����Ϊ���Ƴ�ì�ܡ�x->y��ʾѡx�����ѡy.

ע�������±��Ǵ�0��ʼ�� 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2005,M=4e6+5;

int n,m,H[N],Enum,nxt[M],to[M];
int top,sk[N],dfn[N],low[N],id,bel[N],cnt;
bool ins[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!dfn[v=to[i]]) Tarjan(v), low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ins[sk[top--]]=0;
		}while(x!=sk[top+1]);
	}
}

int main()
{
	n=read(),m=read();
	int a,b,c; char opt[6];
	for(int i=1; i<=m; ++i)
	{
		a=read()+1,b=read()+1,c=read(),scanf("%s",opt);
		if(opt[0]=='A')
			if(c) AddEdge(a,a+n),AddEdge(b,b+n);
			else AddEdge(a+n,b),AddEdge(b+n,a);
		else if(opt[0]=='O')
			if(c) AddEdge(a,b+n),AddEdge(b,a+n);
			else AddEdge(a+n,a),AddEdge(b+n,b);
		else//Xor
			if(c) AddEdge(a,b+n),AddEdge(b,a+n),AddEdge(a+n,b),AddEdge(b+n,a);
			else AddEdge(a,b),AddEdge(b,a),AddEdge(a+n,b+n),AddEdge(b+n,a+n);
	}
	for(int i=1; i<=n<<1; ++i)
		if(!dfn[i]) Tarjan(i);
	bool f=1;
	for(int i=1; i<=n; ++i)
		if(bel[i]==bel[i+n]) {f=0; break;}
	puts(f?"YES":"NO");

	return 0;
}
