/*
0ms	520kb
���������$x_{i+n}$����Լ��$\sum_{i=1}^m a_{ij}x_j\leq b_i$��дΪ$x_{i+n}=b_i-\sum_{i=1}^m a_{ij}x_j$��
Ŀ�꺯��Ϊ$\sum_{i=1}^n C_ix_i$��������$r,c$����$C_c>0$,$B_r>0$,$a_{rc}>0$���Ե�$r$�������е�$x_c$����������$x_c=B_r-\sum_{j!=c}a_{rj}x_j-x_{r+n}$��$x_c$��Ϊ��������$x_{r+n}$��Ϊ�ǻ���������Ȼ�����Ŀ�꺯���У��ǻ�����ȡ0����һ������ʹĿ�꺯������
��һ��ͨ��$Pivot(r,c)$(ת��)ʵ�֣�ͬʱҪ������Լ���е�$x_c$�滻����
������$B_r<0$��������$r$����һ��$a_{rc}<0$��$x_c$���������Ϳ���ʹ$B_r>0$��
��Ȼǰ��������$x_i>0,I\in [1,n+m]$��
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps 1e-8
const int N=25;
const double INF=1e9;

int n,m,id[50];
double A[N][N],Ans[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void Pivot(int r,int c)//r:Basic varivle c:Nonbasic variable
{//������������ǻ����� 
	std::swap(id[r+n],id[c]);
	double t=A[r][c]; A[r][c]=1;
	for(int i=0; i<=n; ++i) A[r][i]/=t;
	for(int i=0; i<=m; ++i)//��������ʽ�л��������� 
		if(fabs(A[i][c])>eps && i!=r)
		{
			t=A[i][c]; A[i][c]=0;
			for(int j=0; j<=n; ++j) A[i][j]-=t*A[r][j];
		}
}
bool Init()
{
	for(int r,c; ; )
	{
		r=c=0;
		for(int i=1; i<=m; ++i)//B[r]<0
			if(A[i][0]<-eps && (!r || rand()&1)) r=i;
		if(!r) return 1;
		for(int i=1; i<=n; ++i)//A[r][c]<0
			if(A[r][i]<-eps && (!c || rand()&1)) c=i;
		if(!c) return puts("Infeasible"),0;
		Pivot(r,c);
	}
}
bool Simplex()
{
	for(int r,c; ; )
	{
		r=c=0;
		for(int i=1; i<=n; ++i)//C[c]>0 
			if(A[0][i]>eps) {c=i; break;}
		if(!c) return 1;
		double mn=INF;//��һ��ϵ��Ϊ����Լ�������A[r][c] 
		for(int i=1; i<=m; ++i)
			if(A[i][c]>eps && A[i][0]/A[i][c]<mn) r=i, mn=A[i][0]/A[i][c];
		if(!r) return puts("Unbounded"),0;//��Լ��
		Pivot(r,c);
	}
}

int main()//x[i+n]=B[i]-��a[i][j]*x[j]
{
	srand(20180724);
	n=read(), m=read(); int type=read();
	for(int i=1; i<=n; ++i) A[0][i]=read();//Ŀ�꺯��ϵ��C[i] 
	for(int i=1; i<=m; ++i)
	{
		for(int j=1; j<=n; ++j) A[i][j]=read();
		A[i][0]=read();//B[i]
	}
	for(int i=1; i<=n; ++i) id[i]=i;
	if(Init() && Simplex())
	{
		printf("%.8lf\n",-A[0][0]);//������ʱ��Biϵ���Ǹ���s 
		if(type)
		{
			for(int i=1; i<=m; ++i) Ans[id[i+n]]=A[i][0];//��Ϊ��������xiȡֵ��Ϊbi���ǻ������ϵ�xiȡ0.
			for(int i=1; i<=n; ++i) printf("%.8lf ",Ans[i]);
		}
	}

	return 0;
}
