/*
$Description$
��һ����СΪ$k$�ļ���$S$��Ԫ��������ͬ����$[1,n]$�ڡ������ѯ�ʲ�����$60$�Σ�ÿ��ѯ�������$x,y$��������᷵��$\left[\ \min(|x-a|,a\in S)\leq \min(|y-a|,a\in S)\ \right]$��(TAK)��(NIE)Ϊ�档
����������һ���ڼ���$S$�г��ֹ�������
$Solution$
���Ƕ�����$[l,r]$���֣���Check(mid,mid+1)==1��������$[1,mid]$��һ������һ��������������$[mid+1,r]$��һ������һ������������$\log10^5=16$�ο���ȷ��һ����$A$��
���ڵڶ�������������$[1,A-1]$��$[A+1,n]$�зֱ���֡�
*/
#include <cstdio>

int n;

inline bool Query(int x,int y)
{
	static char s[7];
	if(y>n) return 1;//!
	printf("1 %d %d\n",x,y); fflush(stdout);
	return scanf("%s",s),s[0]=='T';
}
int Check(int l,int r)
{
	if(l>r) return 0;
	int mid,ans=0;
	while(l<=r)
		if(mid=l+r>>1, Query(mid,mid+1)) ans=mid,r=mid-1;
		else l=mid+1;
	return ans;
}

int main()
{
	int k; scanf("%d%d",&n,&k);
	int A=Check(1,n), B=Check(1,A-1);
	if(!B) B=Check(A+1,n);
	printf("2 %d %d\n",A,B); fflush(stdout);

	return 0;
}
