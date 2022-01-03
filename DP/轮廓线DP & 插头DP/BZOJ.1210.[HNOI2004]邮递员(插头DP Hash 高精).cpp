/*
154108kb	1396ms
插头DP。$m+1$个插头的状态需要用三进制表示：$0$表示无插头，$1$表示是左括号插头，$2$表示是右括号插头。为了方便用两位的二进制写。所以还需要个哈希表存状态。
转移的时候，对于左边上边这两个插头，如果某个插头为$0$，很好转移。否则就分$4$种情况讨论下。不写了。。
还需要高精度。其它就是些细节了。
转移时特判下边界外有插头就不转移，会方便很多。
实际方案数还不是特别多，高精可以用两个`long long `实现。
因为状态也不多，线性探测的效率比链式哈希高很多。。
还有别忘把答案$*2$（反向走）。。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define Base 1000000000
typedef long long LL;

int n,m;
struct BigInt
{
	int a[5];
	BigInt() {memset(a,0,sizeof a);}
	inline void Init() {memset(a,0,sizeof a);}
	inline void Set(int x) {a[0]=0; while(x) a[++a[0]]=x%Base, x/=Base;}
	inline int& operator [](int x) {return a[x];}
	inline BigInt operator +(const BigInt &x)const
	{
		BigInt res;
		int l=std::max(a[0],x.a[0]);
		for(int i=1; i<=l; ++i) res.a[i]+=a[i]+x.a[i], res[i]>=Base&&(++res.a[i+1]/*+=res.a[i]/Base*/, res.a[i]-=Base);
		++l;
		while(!res.a[l]) --l;
		res.a[0]=l;
		return res;
	}
	inline void operator =(const int x) {Set(x);}
	inline void operator +=(const BigInt &x) {*this=*this+x;}
	inline void Print()
	{
		printf("%d",a[a[0]]);
		for(int i=a[0]-1; i>0; --i) printf("%09d",a[i]);
		putchar('\n');
	}
}Ans;
struct Hash_Table
{
	#define mod 10007
	#define N 2800000//1010101010101010101010 //4^{11}=4194304 不是3^{11}。。
	int tot,top,sk[mod],H[mod],nxt[N],sta[N];
	BigInt val[N];
	Hash_Table() {tot=top=0;}
	inline void AE(int u,int v) {nxt[v]=H[u], H[u]=v;}
	inline void Init() {tot=0; while(top) H[sk[top--]]=0;}
	inline BigInt& operator [](const int s)
	{
		int x=s%mod;//s可能是0，边表里的需要是s+1。也可以初始化H[x]=-1。
		for(int i=H[x]; i; i=nxt[i])
			if(i==s+1) return val[s];
		if(!H[x]) sk[++top]=x;
		AE(x,s+1), sta[++tot]=s, val[s].Init();
		return val[s];
	}
}f[2];

inline int Get(const int s,const int bit) {return s>>(bit<<1)&3;}//s在bit位置的插头 
inline void Upd(int &s,int bit,int v) {bit<<=1, s|=3<<bit, s^=3<<bit, s|=v<<bit;}//将s在bit位置的插头改为v 
inline int Find(const int s,const int y,const int p)//找到与y位置的插头p 所对应的插头 
{
	int delta=p==1?1:-1/*向左/向右找*/,sum=delta;//if(!p) return y;
	for(int i=y+delta,v; ~i&&i<=m; i+=delta)//i=0~m-1!
		if(v=Get(s,i),sum+=v==1?1:(v==2?-1:0),!sum) return i;
	return -1;
}
void Work(const int n,const int m,const int x,const int y,Hash_Table &f,Hash_Table &g)
{
	f.Init();
	for(int i=1,tot=g.tot; i<=tot; ++i)
	{
		int s=g.sta[i],p1=Get(s,y-1),p2=Get(s,y),t1=p1?Find(s,y-1,p1):0,t2=p2?Find(s,y,p2):0;
		if(t1==-1||t2==-1) continue;//
		BigInt v=g.val[s];
		if(!v[0]) continue;
		if(!p1&&!p2) {if(x!=n&&y!=m) Upd(s,y-1,1), Upd(s,y,2), f[s]+=v;}
		else if(!p1&&p2)
		{
			if(y!=m) f[s]+=v;
			if(x!=n) Upd(s,y-1,p2), Upd(s,y,0), f[s]+=v;
		}
		else if(p1&&!p2)
		{
			if(x!=n) f[s]+=v;
			if(y!=m) Upd(s,y-1,0), Upd(s,y,p1), f[s]+=v;
		}
		else if(p1==1&&p2==1) Upd(s,y-1,0), Upd(s,y,0), Upd(s,t2,1), f[s]+=v;
		else if(p1==1&&p2==2) {if(x==n&&y==m) Ans+=v;}
		else if(p2==1) Upd(s,y-1,0), Upd(s,y,0), f[s]+=v;
		else if(p2==2) Upd(s,y-1,0), Upd(s,y,0), Upd(s,t1,2), f[s]+=v;
	}
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	if(m>n) std::swap(n,m); ::n=n, ::m=m;
	if(m==1) return puts("1"),0;//!
	int p=0; f[p].Init(), f[p][0]=1;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j) p^=1, Work(n,m,i,j,f[p],f[p^1]);
		if(i!=n)
		{
			p^=1, f[p].Init();
			for(int i=1,tot=f[p^1].tot,s; i<=tot; ++i)
				s=f[p^1].sta[i], f[p][s<<2]=f[p^1][s];
		}
	}
	Ans+=Ans, Ans.Print();

	return 0;
}
