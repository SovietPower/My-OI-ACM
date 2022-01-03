/*
944kb	116ms
��ͷDP��$m+1$����ͷ��״̬��Ҫ�������Ʊ�ʾ��$0$��ʾ�޲�ͷ��$1$��ʾ�������Ų�ͷ��$2$��ʾ�������Ų�ͷ��Ϊ�˷�������λ�Ķ�����д�����Ի���Ҫ����ϣ���״̬��
ת�Ƶ�ʱ�򣬶�������ϱ���������ͷ�����ĳ����ͷΪ$0$���ܺ�ת�ơ�����ͷ�$4$����������¡���д�ˡ���
����Ҫ�߾��ȡ���������Щϸ���ˡ�
ת��ʱ�����±߽����в�ͷ�Ͳ�ת�ƣ��᷽��ܶࡣ
ʵ�ʷ������������ر�࣬�߾�����������`long long `ʵ�֡�
��Ϊ״̬Ҳ���࣬����̽���Ч�ʱ���ʽ��ϣ�ߺܶࡣ��
���б����Ѵ�$*2$�������ߣ�����
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
	inline void operator +=(const BigInt &x)//����д ++b,b+=x.b ��Ϊ��&...
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
	#define mod 2501//״̬�������2200��
	int top,sk[mod],hash[mod];
	BigInt val[mod];
	Hash_Table() {top=0, memset(hash,0xff,sizeof hash);}
	inline void Init() {while(top) hash[sk[top--]]=-1;}
	inline BigInt& operator [](const int s)
	{//s������0 
		for(int x=s%mod; ; x=x+1==mod?0:x+1)
		{
			if(!~hash[x]) hash[x]=s, sk[++top]=x, val[x].Init();
			if(hash[x]==s) return val[x];
		}
	}
}f[2];

inline int Get(const int s,const int bit) {return s>>(bit<<1)&3;}//s��bitλ�õĲ�ͷ 
inline void Upd(int &s,int bit,int v) {bit<<=1, s|=3<<bit, s^=3<<bit, s|=v<<bit;}//��s��bitλ�õĲ�ͷ��Ϊv 
inline int Find(const int s,const int y,const int p)//�ҵ���yλ�õĲ�ͷp ����Ӧ�Ĳ�ͷ 
{
	int delta=p==1?1:-1/*����/������*/,sum=delta;//if(!p) return y;
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
				f[p].hash[f[p].sk[i]]<<=2;//������໨����ʱ����״̬��=-= �����˷����ǿ� 
//			f[p^1].Init();
//			for(int i=1,tot=f[p].top,s; i<=tot; ++i)
//				s=f[p].hash[f[p].sk[i]], f[p^1][s<<2]=f[p][s];
//			p^=1;
		}
	}
	Ans+=Ans, Ans.Print();

	return 0;
}
