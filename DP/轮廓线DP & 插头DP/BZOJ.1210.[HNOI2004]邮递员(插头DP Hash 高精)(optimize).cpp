/*
944kb	116ms
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
typedef long long LL;
const LL Base=(LL)1e18;

int n,m;
struct BigInt
{
	LL a,b;
	BigInt() {a=0, b=0;}
	inline void Init() {a=0, b=0;}
	inline void Set(int x) {a=x, b=0;}
	inline void operator =(const int x) {Set(x);}
	inline void operator +=(const BigInt &x)//不能写 ++b,b+=x.b 因为是&...
	{
		a+=x.a, a>=Base?(b+=x.b+1,a-=Base):b+=x.b;
	}
	inline void Print()
	{
		b ? printf("%lld%018lld",b,a) : printf("%lld\n",a);
		putchar('\n');
	}
}Ans;
struct Hash_Table
{
	#define mod 2501//状态数最多大概2200？
	int top,sk[mod],hash[mod];
	BigInt val[mod];
	Hash_Table() {top=0, memset(hash,0xff,sizeof hash);}
	inline void Init() {while(top) hash[sk[top--]]=-1;}
	inline BigInt& operator [](const int s)
	{//s可能是0 
		for(int x=s%mod; ; x=x+1==mod?0:x+1)
		{
			if(!~hash[x]) hash[x]=s, sk[++top]=x, val[x].Init();
			if(hash[x]==s) return val[x];
		}
	}
}f[2];

inline int Get(const int s,const int bit) {return s>>(bit<<1)&3;}//s在bit位置的插头 
inline void Upd(int &s,int bit,int v) {bit<<=1, s|=3<<bit, s^=3<<bit, s|=v<<bit;}//将s在bit位置的插头改为v 
inline int Find(const int s,const int y,const int p)//找到与y位置的插头p 所对应的插头 
{
	int delta=p==1?1:-1/*向左/向右找*/,sum=delta;//if(!p) return y;
	for(int i=y+delta,v; ~i&&i<=m; i+=delta)//i=0~m-1!
		if(v=Get(s,i),sum+=v==2?-1:v==1,!sum) return i;
	return -1;
}
void Work(const int n,const int m,const int x,const int y,Hash_Table &f,Hash_Table &g)
{
	f.Init();
	for(int i=1,tot=g.top; i<=tot; ++i)
	{
		int id=g.sk[i],s=g.hash[id],p1=Get(s,y-1),p2=Get(s,y),t1=p1?Find(s,y-1,p1):0,t2=p2?Find(s,y,p2):0;
		if(t1==-1||t2==-1) continue;//
		BigInt v=g.val[id];
		if(!v.a) continue;
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
			for(int i=1,tot=f[p].top; i<=tot; ++i)
				f[p].hash[f[p].sk[i]]<<=2;//这样会多花额外时间找状态吧=-= 不管了反正是快 
//			f[p^1].Init();
//			for(int i=1,tot=f[p].top,s; i<=tot; ++i)
//				s=f[p].hash[f[p].sk[i]], f[p^1][s<<2]=f[p][s];
//			p^=1;
		}
	}
	Ans+=Ans, Ans.Print();

	return 0;
}
