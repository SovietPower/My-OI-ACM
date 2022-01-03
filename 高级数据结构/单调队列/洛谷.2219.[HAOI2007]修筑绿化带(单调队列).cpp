/*
���ڴ�ľ������ö�٣�����С�ľ�����Ҫ������������������һ�����κ͵���Сֵ 
Ԥ����S2[i][j]��ʾ��(i,j)Ϊ���½ǵ�C*D�ľ���ͣ� 
Ȼ�����������������Сֵ�������Ƚ�ÿ�п���һ�����У�����ÿ����y���õ�һ��[y-(B-3),y]����Сֵ 
�������к�õ�Minr[][]����ÿ�еĽ���ͬ���Ĳ������Ϳ��Եõ�Min[x][y]��ʾ([x-A+3,x],[y-B+3,y])����С���κ� 
����ע�ⵥ�����д������S2��S2��ʾ����C*D�ĺ�,not a single point!���Զ˵�Ӧ����([x-A+C+1],[y-B+D+1]) 
*/
#include <cstdio>
#include <cctype>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1005,MAXIN=6e5;

int n,m,A,B,C,D,S[N][N],S1[N][N],S2[N][N],q[N],Minr[N][N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
//void Debug(int a[N][N],int s,int s2)
//{
//	puts("Debug");
//	for(int i=s; i<=n; ++i,putchar('\n'))
//		for(int j=s2; j<=m; ++j) printf("%d ",a[i][j]);
//	putchar('\n');
//}
void Pre()
{
	for(int i=C+1; i<n; ++i)//��1~C,n���ò��� 
	{
		int h=1,t=0;
		for(int j=D+1; j<m; ++j)
		{
			while(h<=t && S2[i][q[t]]>=S2[i][j]) --t;
			q[++t]=j;
			if(q[h]<=j-B+D+1) ++h;
			Minr[i][j]=S2[i][q[h]];
		}
	}
//	Debug(S,1,1);
//	Debug(S1,A,B);
//	Debug(S2,C,D);
//	Debug(Minr,2,2);
}
void Solve()
{
	int res=0;
	for(int j=D+1; j<m; ++j)//ö��С���οɷŷ�Χ����+1��+1������ε�λ�� 
	{
		int h=1,t=0;
		for(int i=C+1; i<n; ++i)
		{
			while(h<=t && Minr[q[t]][j]>=Minr[i][j]) --t;
			q[++t]=i;
			if(q[h]<=i-A+C+1) ++h;
			if(res<S1[i+1][j+1]-Minr[q[h]][j]) res=S1[i+1][j+1]-Minr[q[h]][j];
		}
	}
	printf("%d",res);
}

int main()
{
	n=read(),m=read(),A=read(),B=read(),C=read(),D=read();
	if(n<=2||m<=2) {putchar('0'); return 0;}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			S[i][j]=read()+S[i][j-1]+S[i-1][j]-S[i-1][j-1];
	for(int i=A; i<=n; ++i)
		for(int j=B; j<=m; ++j)
			S1[i][j]=S[i][j]-S[i][j-B]-S[i-A][j]+S[i-A][j-B];
	for(int i=C+1; i<=n; ++i)
		for(int j=D+1; j<=m; ++j)
			S2[i][j]=S[i][j]-S[i][j-D]-S[i-C][j]+S[i-C][j-D];
	Pre(), Solve();

	return 0;
}
