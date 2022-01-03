/*
http://www.cnblogs.com/SovietPower/p/8427630.html
����O(n^3):f[i][j]��ʾ��ǰ��i����j�ε���С��ֵ W[i]��ʾ1~i���ܼ�ֵ S[i]��ʾ1~i��ԭ����ֵ֮�� 
���� f[i][j]=min{ f[k][j-1]+W[i]-W[k]-S[i]*(S[i]-S[k]) } (1��k<i)
������̿�����б���Ż� �������������и����ߵ��� 
*/
#include<cstdio>
#include<cctype>
#define gc() getchar()
typedef long long LL;
const int N=1e3+5;

int n,m,A[N],q[N];
LL W[N],S[N],f[N][2];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL Calc_X(int x,int y)
{
	return S[x]-S[y];
}
inline LL Calc_Y(int x,int y,int s)
{
	return (f[x][s]+S[x]*S[x]-W[x])-(f[y][s]+S[y]*S[y]-W[y]);
}
inline LL Calc_f(int x,int y,int s)
{
	return f[x][s]+W[y]-W[x]-S[x]*(S[y]-S[x]);
}

int main()
{
	while(n=read(),m=read(),n&&m)
	{
		S[0]=W[0]=0;
		for(int i=1;i<=n;++i)
			A[i]=read(), S[i]=S[i-1]+A[i], W[i]=W[i-1]+A[i]*S[i-1];
		for(int i=1;i<=n;++i) f[i][0]=W[i];
		int p=1;
		for(int h,t,j=1;j<=m;++j)//�����m+1�� 
		{
			h=t=1, q[1]=0;//i��0ת�ƾ���W[i] 
			p^=1;
			for(int i=1;i<=n;++i)
			{
				while(h<t && Calc_Y(q[h+1],q[h],p)<S[i]*Calc_X(q[h+1],q[h]))//���ߵ��� ���Զ��ڵ�ǰi�����Ϊ����ֵ�ģ�֮�󶼲����Ϊ����ֵ 
					++h;
				f[i][p^1]=Calc_f(q[h],i,p);
				while(h<t && Calc_Y(i,q[t],p)*Calc_X(q[t],q[t-1]) <= Calc_Y(q[t],q[t-1],p)*Calc_X(i,q[t]))//ά����β��͹������ 
					--t;
				q[++t]=i;
			}
		}
		printf("%lld\n",f[n][p^1]);
	}
	return 0;
}
