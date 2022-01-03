/*
39460kb	3068ms
����DFS�õ��������С���������һ���������У�`[A[B[E][F[H][I]]][C][D[G]]]`��
�Ǳ���$D,E$�����̾��룬���ǽ�$D,E$�����������ȡ����`][[][]]][][`��Ȼ��ȥ������ƥ������ţ��õ���`]][[`��
����$D,E$�����ϵ���̾���Ϊ$4$����Ϊ���һ�������žͱ�ʾ����һ�㣬�ұ�һ�������žͱ�ʾ����һ�㡣

��һ�������һ����Ԫ��$(a,b)$����ʾ�����䣨ȥ��ƥ�����ź�ģ�����������`]]..][..[`��һ��$a$��`]`��$b$��`[`��
������������Ҷ˵�ľ������$a+b$������Ҫά������$a+b$�������������ڵ��������룬�������������Ҷ˵㶼�Ǻڵ���ܸ��´𰸣���
�����������״̬�ֱ���$(a_1,b_1),(a_2,b_2)$��
����������ϲ����״̬�ǣ�
$b_1\leq a_2$ʱ��$=(a_1+a_2-b_1,\ b_2)$
$b_1>a_2$ʱ��$=(a_1,\ b_2+b_1-a_2)$
$a+b$��ֵ��ʵ����$a_1+b_2+|a_2-b_1|=a_1+b_2+\max(a_2-b_1,\ b_1-a_2)=\max(a_1-b_1+(a_2+b_2),\ a_1+b_1+(b_2-a_2))$��
Ҳ�����������Ĵ������ָ��·�ʽ���������$\max\{a-b\}+$�������$\max\{a+b\}$�����ǣ��������$\max\{a+b\}+$�������$\max\{b-a\}$��
�������Ƕ�ÿ������ά��$a,b,\max\{a-b\},\max\{b-a\},\max\{a+b\}$��
��ע����´���Ҫ�����˵㶼�Ǻڵ㣬�����ܸ���$\max\{a-b\}$��Ҫ���������Ҷ˵���������˵�����Ǻڵ㣬ͬ�����$\max\{b-a\}$��Ҫ����������˵��������Ҷ˵�����Ǻڵ㣬��$\max\{a+b\}$����Ҫ�����������Ҷ˵��Ƿ����Ϊ�ڵ�ά������ֵ����
��������ϲ����$a-b$������$b_1,a_2$�Ĵ�С��ϵ������$a_1-b_1+a_2-b_2$��$b-a$����$b_1-a_2+b_2-a_2$��Ҳ�������������������Ϣ����ֱ����Ӻϲ���
����$max\{a-b\}$���������������$\max\{a-b\}$�õ�������$\max\{a_1-b_1\}+a_2-b_2$�õ����������$a_2,b_2$�Ǳ�ѡ�ģ�

��$\max\{a-b\}$Ϊ$vab$��$\max\{b-a\}$Ϊ$vba$��
���ڰ���������˵��������Ҷ˵�Ϊ�ڵ��$\max\{a+b\}$������$vr$���ˣ���Ӧ�ľͼ���$vl$�����ϲ������������ʱ��Ҫô�Ǵ�����ӵ�$vr_l$ֱ��ת�ƣ�Ҫô��������ӵĺ�+�Ҷ��ӵ�һЩ��ת�ơ�
���ϲ��õ�$a+b$��ʱ���������ģ�$\max(a_1-b_1+(a_2+b_2),\ a_1+b_1+(b_2-a_2))$��Ҳ����Ҫô���������$a-b+$�������$\max\{a+b\}$����$a_l-b_l+vr_r$��Ҫô���������$a-b+$�������$\max\{b-a\}$����$a_l+b_l+vba_r$��
$vr$ͬ��

��״̬$a,b$�Լ���$4$��$\max$���ܺϲ��ˣ�ά��һ�¾ͺÿ��������������ɣ�ͦ�����ģ�
���Ӷ�$O(n\log n)$��

ע�⽨����ʱ����ǽ���`[A[B[E][F[H][I]]][C][D[G]]]`�����ĳ���$3n$�����У�$A,B,...$������ǵ�ı�š��޸ĵ�ʱ��Ķ�Ӧ��ĸλ�ü��ɡ�����Ϊ����ȥ����ĸ��������һ���ģ����Ҳ��ʱ��Ҳֻ�ǲ�����ĸ֮�����������
�Զ˵����Ϊ�ڵ��Ҫ�����ĳ���ǰ׵�������ţ�����ֵ���$-INF$���ɡ�
���Ǹо�����������԰�...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=N*3,INF=1<<29;

int A[M],Enum,H[N],nxt[N<<1],to[N<<1],pos[N],col[N];//0:close 1:open
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S M<<2
	int ans[S],a[S],b[S],vab[S],vba[S],vl[S],vr[S];//vab:max{a-b} vba:max{b-a} vl:max{a+b}����˵�Ϊ�ڵ� 
	#undef S
	inline void Init(int p,int rt)
	{
		a[rt]=A[p]==-2, b[rt]=A[p]==-1, ans[rt]=-INF;//a�������� b�������š���
		if(A[p]<0 || col[A[p]]) vab[rt]=vba[rt]=vl[rt]=vr[rt]=-INF;
		else vab[rt]=vba[rt]=vl[rt]=vr[rt]=0;
	}
	inline void Update(int rt)
	{
		int l=ls,r=rs;
		a[rt]=a[l]+std::max(0,a[r]-b[l]), b[rt]=b[r]+std::max(0,b[l]-a[r]);
		ans[rt]=std::max(std::max(ans[l],ans[r]),std::max(vab[l]+vr[r],vl[l]+vba[r]));
		vab[rt]=std::max(vab[r],a[r]-b[r]+vab[l]);
		vba[rt]=std::max(vba[l],b[l]-a[l]+vba[r]);
		vl[rt] =std::max(vl[r],std::max(vab[l]+a[r]+b[r],vl[l]+b[r]-a[r]));
		vr[rt] =std::max(vr[l],std::max(a[l]-b[l]+vr[r],a[l]+b[l]+vba[r]));
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {Init(l,rt); return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int p)
	{
		if(l==r) {Init(l,rt); return;}
		int m=l+r>>1;
		p<=m ? Modify(lson,p) : Modify(rson,p);
		Update(rt);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline char GetOpt()
{
	register char c=gc();
	while(c!='C'&&c!='G') c=gc();
	return c;
}
void DFS(int x)
{
	static int Index=0;
	A[++Index]=-1, A[pos[x]=++Index]=x;
	for(int i=H[x]; i; i=nxt[i]) if(!pos[to[i]]) DFS(to[i]);
	A[++Index]=-2;
}

int main()
{
	#define S 1,cnt,1
	const int n=read(),cnt=n*3;
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS(1), T.Build(S);
	for(int Q=read(),tot=n,x; Q--; )
		switch(GetOpt())
		{
			case 'C': col[x=read()]^=1, tot+=col[x]?-1:1, T.Modify(S,pos[x]); break;
			case 'G': tot>1?printf("%d\n",T.ans[1]):tot==1?puts("0"):puts("-1"); break;
		}
	return 0;
}
