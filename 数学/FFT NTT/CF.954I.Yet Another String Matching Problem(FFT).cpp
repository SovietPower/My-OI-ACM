/*
686ms	63900KB(1653ms	18800KB)
$Description$
����������$a,b$��ÿ�������ѡ��һ���ַ�����������������ȫ����Ϊ��һ���ַ�������$dis(a,b)$Ϊʹ��$a,b$����������С�޸Ĵ�����
����������$S,T$������$S$�����г�Ϊ$|T|$���Ӵ�$S'$�����$dis(S',T)$��
$1\leq|T|\leq|S|\leq125000$���ַ���Ϊ$a\sim f$��
$Solution$
����$dis(a,b)$��ô����һ�����鼯������ö��$a_i,b_i$�����$a_i\neq b_i$��$a_i,b_i$������һ�������ڣ��ͽ����Ǻϲ���$dis$++��
��Ҳ���Կ��ǽ�һ������ͼ����$a_i,b_i$�����ߡ���Ϊÿ����ͨ�����Ҫ���ͬһ���ַ�������$dis=�ڵ���(6)-��ͨ����$��
����ö��ÿһ��λ��$i\in[0,|S|-|T|]$��������Ҫ��ÿ��$j\in[0,|T|-1]$������һ���Ƿ���Ҫ�ϲ�$S_{i+j},T_j$�����Ӷ���$O(|S||T|)$�ġ�����ʵ������ֻ��Ҫ�жϣ���$6$���ַ�֮�䣬�Ƿ���ͬһλ���ϳ��ֹ����ֲ�ͬ�ַ��Ϳ����ˣ�Ȼ���԰����Ǻϲ�����
Ҳ����ö�����ֲ�ͬ���ַ�$a,b$����һ����������Щλ��ͬʱ�����ˣ�$S_i=a$��$T_i=b$����
��$f_i=[S_i=a],\ g_i=[T_i=b]$��$F(x)=\sum_{i=0}^{|T|-1}f_{x+i}g_i$��$F(x)$������$FFT$�����
��$F(x)\neq0$����ô$a,b$����ͬһλ�ó����ˣ���������$x$�����Ӵ��С�ö��$x$ʱ���Ժϲ�һ��$a,b$�Ϳ����ˡ�
�������Ӷ�$O(36n\log n+36n\alpha(n))$+FFT�Ĵ�����$CF$�Ƚ����ɹ���$BZOJ$�����ˡ���
��Ȼ�кܶ�����Ż��ĵط����������$f,g$��$FFT$������1653ms->686ms����
$CF$�ϻ������ָ��ŵ�������û̫��������
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=(1<<18)+5;
const double PI=acos(-1);

int rev[N],fa[6];
char S[N],T[N];
bool neq[N][6][6];
struct Complex
{
	double x,y;
	Complex(double x=0,double y=0):x(x),y(y) {}
	Complex operator +(const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}f[6][N],g[6][N],F[N];

void FFT(Complex *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1; Complex Wn(cos(PI/mid),opt*sin(PI/mid));
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0),t;
			for(int k=j; k<j+mid; ++k,w=w*Wn)
				a[k+mid]=a[k]-(t=w*a[k+mid]), a[k]=a[k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	scanf("%s%s",S,T);
	int n=strlen(S),m=strlen(T),lim=1,l=-1;
	while(lim<=n+m) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	std::reverse(T,T+m);//!

	for(int a=0; a<6; ++a)//!
	{
		const char aa=a+97;
		for(int i=0; i<n; ++i) f[a][i]=Complex(S[i]==aa,0);
		for(int i=0; i<m; ++i) g[a][i]=Complex(T[i]==aa,0);
		FFT(f[a],lim,1), FFT(g[a],lim,1);
	}
	for(int a=0; a<6; ++a)
		for(int b=0; b<6; ++b)
		{
			if(a==b) continue;
//			for(int i=0; i<lim; ++i) f[i].x=f[i].y=g[i].x=g[i].y=0;
//			for(int i=0; i<n; ++i) f[i]=Complex(S[i]==a,0);
//			for(int i=0; i<m; ++i) g[i]=Complex(T[i]==b,0);
//			FFT(f,lim,1), FFT(g,lim,1);
			for(int i=0; i<lim; ++i) F[i]=f[a][i]*g[b][i];
			FFT(F,lim,-1);
			for(int i=0; i<n; ++i) neq[i][a][b]=(int)(F[m+i-1].x+0.5);
		}
	for(int i=0; i<=n-m; ++i)
	{
		for(int j=0; j<6; ++j) fa[j]=j;
		int ans=0;
		for(int j=0; j<6; ++j)
			for(int k=0; k<6; ++k)
				if(neq[i][j][k]&&Find(j)!=Find(k)) ++ans,fa[fa[j]]=fa[k];
		printf("%d ",ans);
	}

	return 0;
}
