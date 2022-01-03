/*
BZOJ:55576kb	5916ms	LOJ:35911ms	69728K Luogu:5049ms	88.89MB
���ȿ������ߣ���ѯ�ʰ�ʱ�����򡣶���ÿ����$[l,r]$���ֵ���ɫ�������$l$�����$r+1$ɾ������������Ҳ��ʱ������
����ѯ��$(x,t)$��������$t$ʱ�̣���$x$��Զ����ɫ��$x$�ľ��룬Ҳ���Ǵ�$x$��������������Ҫ�߶�Զ���ܾ���������ɫ��
���Ƕ��ִ𰸡���ô�ͳ��ˣ���������ɫ�Ƿ���$[x-mid,x+mid]$�г��ֹ���
���������Ƿ���ֹ�/ֻ����һ�ε����⣬ͨ���Ƕ�ÿ����ɫ��������ҵ�һ�����ֵ���ɫ��
��ÿ��λ��$i$��$pre_i$����ʾ$col_i$�ϴγ��ֵ�λ�á���ô$i$��$col_i$��ɫ�У��������һ�����ֵĵ��ҽ���$pre_i<l$��
�������Ƕ�������$pre_i<l$��λ�ø������Ǵ��ˡ��������Ҫ�������������Ǹ��ӶȾͳ���$O(n\log^3n)$����

��Ȼ�е���ƫ���ٿ�����Ҫ������⣺�������Ƿ���ֹ�������ɫ�����ǲ���Ҫ���ж�������ɫ�����ˣ�ֻҪ���ҵ�һ�ֲ��������г��ֹ�����ɫ�Ϳ����ˡ�
���һ����ɫ����$[l,r]$�г��ֹ�����ô����$pre_i<l$��$i>r$��Ҳ����˵������$[r+1,n]$���Ƿ����$pre_i<l$�Ϳ����ˣ�����$pre_i$����Сֵ��
ÿ����ɫ��$pre_i$���Կ�$k$��$set$ά����
��Ϊͬһ��λ�ÿ����ж�����ɫ��ÿ��λ�õ�$pre_i$���кܶ��ҿ�����ͬ�����Զ���ÿ��λ�û�Ҫ��һ��$multiset$�����ά��$\min\{pre_i\}$��֧��ɾ����
������OK�������Ӷ�$O(n\log^2n)$��

�ٿ���һ�¶����ܷ�ֱ�����߶����϶��֡�ʵ�����ǿ��Եġ�
[orz kcz](https://loj.ac/article/523)��
����һ��$mid$�����$Ans\geq mid$����$(x-mid,x+mid)$�в���������ɫ����$[x+mid,n]$����С��ǰ��$mn$����$mn\leq x-mid$��
����ʵ����Ҫ��һ������$i$��ʹ��$[i,n]$����С��ǰ��$mn$��������$mn+i\leq 2x$��$i$Խ����$mn$Խ��Խ���ײ���������������ʱ�𰸾���$\min\{i-x,\ x-\min\{pre_i\}\}$��һ�����Ҷ˵�һ������˵㣩��
��ô���߶�����������$i$�ء�
����һ���޽������
�������������߶�����$[l,r]$���䣺
��$x$����$[mid+1,r]$���䣬��$i$Ҳһ������$[mid+1,r]$���䡣
��$x$����$[l,mid]$���䣬��Ҫ�ж�һ��$i$�ܷ�����$[mid+1,r]$���䡣��Ϊ$i$Խ��$mn$Խ������ֻ��Ҫ����$i=mid+1$ʱ�Ƿ���о����ˡ�
������һ��$\log$����

ע�����$\min$��$[i,n]$�ģ�����ݹ鵽$[l,mid]$Ҫ��������ȡ$\min$��
�����߶����ϵĽڵ��Լ�$mn$����ɢ�����ֵ�򣬱Ƚϵ�ʱ����$ref[mid]$��ʵ��ֵ����$x$�Ƚϡ�
*/
#include <set>
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define INF 1000000000
typedef long long LL;
const int N=3e5+7;

int n,ref[N];
std::multiset<int> st[N];
char IN[MAXIN],*SS=IN,*TT=IN,OUT[3000000],*O=OUT;
struct Node
{
	int x,type,t;
	bool operator <(const Node &x)const
	{
		return t<x.t;
	}
}A[N<<1];
struct Quries
{
	int x,t,id;
	bool operator <(const Quries &x)const
	{
		return t<x.t;
	}
}q[N];
struct Heap
{
	std::priority_queue<int,std::vector<int>,std::greater<int> > a,b;
//	inline int Top() {return a.top();}
	inline void Insert(int x) {a.push(x);}
	inline void Delete(int x)
	{
		if(a.top()!=x) b.push(x);
		else
		{
			a.pop();
			while(!b.empty()&&a.top()==b.top()) a.pop(),b.pop();
		}
	}
}hp[N];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mn[S];
	#undef S
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	void Init(const int n)
	{
		for(int i=n<<2; i; --i) mn[i]=n;
	}
//	void Build(int l,int r,int rt)
//	{
//		if(l==r) {mn[rt]=hp[l].a.top(); return;}
//		int m=l+r>>1; Build(lson), Build(rson), Update(rt);
//	}
	void Modify(int l,int r,int rt,int p)
	{
		if(l==r) {mn[rt]=hp[l].a.top(); return;}
		int m=l+r>>1;
		p<=m?Modify(lson,p):Modify(rson,p);
		Update(rt);
	}
//	int Query(int l,int r,int rt,int x,int mnv)
//	{
//		if(l==r) return std::min(ref[l]-x,x-std::min(mnv,ref[mn[rt]]));
//		int m=l+r>>1;
//		if(x>ref[m] || ref[m]+1+std::min(mnv,ref[mn[rs]])<=x<<1) return Query(rson,x,mnv);
//		return Query(lson,x,std::min(mnv,ref[mn[rs]]));
//	}
	int Query(int x)
	{
		int l=1,r=n,rt=1,mnv=INF;
		while(l!=r)
		{
			int m=l+r>>1;
			if(x>ref[m]||ref[m]+1+std::min(mnv,ref[mn[rs]])<=x<<1) l=m+1, rt=rs;
			else mnv=std::min(mnv,ref[mn[rs]]), r=m, rt=ls;
		}
		return std::min(ref[l]-x,x-std::min(mnv,ref[mn[rt]]));
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void print(int x)
{
	static char obuf[13];
	if(x<0) x=-x, *O++='-';
	if(x)
	{
		int t=0; while(x) obuf[++t]=x%10+48, x/=10;
		while(t) *O++=obuf[t--];
	}
	else *O++='0';
}
//void print(int x)
//{
//	if(x<0) x=-x, *O++='-';
//	if(x>9) print(x/10);
//	*O++ = x%10+48;
//}
int Discrete(int n)
{
	static std::pair<int,int*> tmp[N<<1];
	for(int i=1; i<=n; ++i) tmp[i]=std::make_pair(A[i].x,&A[i].x);
	std::sort(tmp+1,tmp+1+n);
	int cnt=1; ref[*tmp[1].second=1]=tmp[1].first;
	for(int i=2; i<=n; ++i)
		ref[*tmp[i].second=tmp[i].first==tmp[i-1].first?cnt:++cnt]=tmp[i].first;
	return cnt;
}
void Solve(int p,int col,int &tot)
{
	static int tm[N];
	if(col>0)
	{
		tot+=!tm[col]++;
		std::multiset<int>::iterator it=st[col].lower_bound(p);//��˵дset���͵ĵ�������ȻҲ�ԡ���
		int nxt=*it, pre=it==st[col].begin()?0:*--it;
		hp[p].Insert(pre), T.Modify(1,n,1,p);
		hp[nxt].Delete(pre), hp[nxt].Insert(p), T.Modify(1,n,1,nxt);//nxt���Ҳ����n������Խ�� 
		st[col].insert(p);
	}
	else
	{
		col=-col, tot-=!--tm[col];
		std::multiset<int>::iterator it=st[col].find(p);
		int pre=it==st[col].begin()?0:(--it,*it++);
		hp[p].Delete(pre), T.Modify(1,n,1,p);
		st[col].erase(it++);
		hp[*it].Delete(p), hp[*it].Insert(pre), T.Modify(1,n,1,*it);
	}
}

int main()
{
	static int Ans[N];

	int n=read(),K=read(),Q=read(),cnt=0;
	for(int i=1,x,type; i<=n; ++i)
		x=read(), type=read(), A[++cnt]=(Node){x,type,read()}, A[++cnt]=(Node){x,-type,read()+1};
	std::sort(A+1,A+1+cnt);
	n=Discrete(cnt), ref[0]=-INF, ref[++n]=INF, ::n=n;

	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+Q);

	for(int i=1; i<=n; ++i) hp[i].Insert(n);
	for(int i=1; i<=K; ++i) hp[n].Insert(0), st[i].insert(n);
//	T.Build(1,n,1); A[cnt+1].t=INF;
	T.Init(n), T.Modify(1,n,1,n), A[cnt+1].t=INF;
	for(int i=1,now=1,tot=0; i<=Q; ++i)
	{
		while(A[now].t<=q[i].t) Solve(A[now].x,A[now].type,tot), ++now;
		Ans[q[i].id]=tot==K?T.Query(q[i].x):-1;
	}
	for(int i=1; i<=Q; ++i) print(Ans[i]), *O++='\n';//printf("%d\n",Ans[i]);
	fwrite(OUT,1,O-OUT,stdout);

	return 0;
}
