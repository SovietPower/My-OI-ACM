/*
3044kb	264ms
�ڶ�����ͳ�ƹ��ף������ڸ�����ͳ�ư��������������Ļ���д������DPд���仯���ܹ�= =��
Ȼ�����$f[x][a][b]$��ʾ��$x$�ڵ�������$a$�����޵Ĺ�·$b$�����޵���·����С���ѣ���Ҷ�ڵ㴦ͳ�ƹ��ף�ת�Ƶ�ʱ��ö�ٲ����ĸ����ɡ�
����$f$�����һά���Կ����ռ䣬�Ѳ��õı�Ż��գ�ͬһʱ��ֻ����$80+$�����ýڵ㡣

ע�����Ҷ�ӽڵ���ɸ�ֵ��������$id[x]$��ʱ��Ҫע�⣡�������������鸺�±꣩
O2�������棬���LOJ��O2���ˣ���BZOJ��WA= =������Ϊ�������С�����⣬����ʵ��$C$���鿪������$id$���±�ͷ��ʵ�$C$�Ķ���ռ���ȥ�ˣ��һ᲻��ָ��д��������������Ȼ����д����
Ȼ�������O2�Ż�������Ҫ����$C$����Ҳ�ܹ�=-=��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=4e4+5;

int n,son[N][2],A[N],B[N],C[N],id[N];
LL f[82][42][42];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void DFS(int x,int a,int b)
{
	static int tot=0,top=0,sk[N];
	int now=top?sk[top--]:++tot; id[x]=now;
	if(x>=n)
	{
		int A=::A[x],B=::B[x],C=::C[x];
		for(int i=0; i<=a; ++i)
			for(int j=0; j<=b; ++j) f[now][i][j]=1ll*C*(A+i)*(B+j);
		return;
	}
	int ls=son[x][0],rs=son[x][1];
	DFS(ls,a+1,b), DFS(rs,a,b+1);
	ls=id[ls], rs=id[rs];
	for(int i=0; i<=a; ++i)
		for(int j=0; j<=b; ++j)
			f[now][i][j]=std::min(f[ls][i+1][j]+f[rs][i][j],f[ls][i][j]+f[rs][i][j+1]);
	sk[++top]=ls, sk[++top]=rs;
}

int main()
{
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);

	int n=read(); ::n=n;
	for(int i=1,s,t; i<n; ++i) s=read(),t=read(),son[i][0]=s<0?n-1-s:s,son[i][1]=t<0?n-1-t:t;
	for(int i=n,l=n+n; i<l; ++i) A[i]=read(),B[i]=read(),C[i]=read();
	DFS(1,0,0), printf("%lld\n",f[id[1]][0][0]);

	return 0;
}
