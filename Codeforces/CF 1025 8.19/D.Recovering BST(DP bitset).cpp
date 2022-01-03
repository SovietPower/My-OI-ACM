/*
93ms	100KB
f[l][r][rt]��ʾl~r��rtΪ���Ƿ���У�ת��ʱö��l,r,rt����ö�����������ĸ���������f[l][rt-1][lrt]==1 && f[rt+1][r][rrt]==1 && lrt,rrt������rt���� ʱ��f[l][r][rt]=1��
���һ��ö���ܹ���O(r-l)�ģ�һ��O(n^4)��
����һ�������Ƿ�Ϸ�������ֻ��Ҫ֪�������ܷ�ƴ������������L[l][k]/R[k][r]��ʾ��kΪ������/���Ƿ������쵽l/r��
��ô����[l,r]�Ϸ� ���ҽ�������k���� L[l][k]==1 && R[k][r]==1����[l,r]�Ϸ���Ϳ��Ը���k����L[l][r+1]��R[l-1][r]�ˡ�
����ֻ��ö������������ĸ������Ӷ�O(n^3)��
������bitset�Ż���
���ݸо���ˮ������L,R���¶����˻�����51����WA��
�����Ȼ�и��������������̰��ô����?
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
const int N=707;

int n,A[N];
std::bitset<N> ok[N],L[N],R[N],ans[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Gcd(int a,int b){
	return b?Gcd(b,a%b):a;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read(), L[i][i]=R[i][i]=1;
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j) ok[i][j]=ok[j][i]=(Gcd(A[i],A[j])>1);
	for(int len=0; len<n; ++len)//�����ó���Ϊ1���������һ�Ρ���
		for(int l=1,r; (r=l+len)<=n; ++l)
		{
			ans[l]=L[l]&R[r];
			if((ans[l]&ok[r+1]).count()) L[l][r+1]=1;
			if((ans[l]&ok[l-1]).count()) R[r][l-1]=1;//l-1�ǵڶ�ά�� 
		}
	puts(ans[1].count()?"Yes":"No");

	return 0;
}
