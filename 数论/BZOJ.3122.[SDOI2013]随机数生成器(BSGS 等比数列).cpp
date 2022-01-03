/*
2788kb	336ms
�������ѧ���ı��������С���
Xi = A*X_{i-1}+B (mod P)�����Ի��ɵȲ�����(����һ����ʹ���ұߵ�B�ܽ����������Ҫ��ȥһ��B����ϵ��Ҫ*A����ô��������ͬʱ+B/(A-1)) 
�ɵȲ����е�n�ʽ�ɵ� Xn + B/(A-1) = A^{n-1}*(X_0 + B/(A-1)) (mod P)
ֻ��A�Ĵ����ǲ�֪���ģ����ұ߳�(��)��������BSGS�� 
Ҫע�����ʽ���� A=1 �� A=0 ʱ��������ģ�Ҫ���С�
����𰸺���ȡģ��+1(���ģʲô����) 
~~��tm�ɲ���sb -> �������2ҲҪģP����666~~
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (100005)
typedef long long LL;
const int N=1e5+7;

LL P,A,B,X,pur;

struct Hash
{
	int H[N],Enum,nxt[N],to[N],res[N],val[N];//�����ʵ�СһЩ ����յ�����¸��� 
	void Init(){
		Enum=0, memset(H,0,sizeof H);
	}
	void AddEdge(int id,int v)
	{
		int x=v%mod;
		for(int i=H[x]; i; i=nxt[i])
			if(val[i]==v) {to[i]=id; return;}
		to[++Enum]=id, nxt[Enum]=H[x], H[x]=Enum, val[Enum]=v;
	}
	int Query(int v)
	{
		for(int i=H[v%mod]; i; i=nxt[i])
			if(val[i]==v) return to[i];
		return -1;
	}
}hs;
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
void Ex_gcd(int a,int b,LL &x,LL &y){
	if(!b) x=1ll,y=0ll;
	else Ex_gcd(b,a%b,y,x),y-=a/b*x;
}
LL inv(int v,int p){
	LL x,y; Ex_gcd(v,p,x,y);
	return (x%p+p)%p;
}
LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%P)
		if(k&1) t=x*t%P;
	return t;
}
int BSGS()//A^x = pur (mod P)
{
	pur=(pur+B*inv(A-1,P)%P)*inv(X+B*inv(A-1,P)%P,P)%P;
	if(gcd(A,P)!=1) return -1;
	hs.Init();
	int m=ceil(sqrt(P-1));
	LL t=pur,AM;
	for(int i=0; i<=m; ++i,t=t*A%P) hs.AddEdge(i,t);
	t=AM=FP(A,m);
	for(int res,i=1; i<=m; ++i,t=t*AM%P)
		if((res=hs.Query(t))!=-1) return (1ll*i*m-res)%P+1ll;
	return -1;
}

int main()
{
	int T=read();
	while(T--)
	{
		P=read(),A=read(),B=read(),X=read(),pur=read();
		if(pur==X) printf("1\n");
		else if(!A){//���ֻ����B��x_i = 0*x_{i-1}+B = B 
			printf("%d\n",B==pur?2:-1);
		}
		else if(A==1){//X_1+x*B = pur(mod p) -> x = (pur-X_1)*inv(B) (mod p)
			if((pur=(pur-X+P)%P)%gcd(B,P)) printf("-1\n");
			else printf("%d\n",(int)(pur*inv(B,P)%P+1ll));
		}
		else printf("%d\n",BSGS());
	}
	return 0;
}
