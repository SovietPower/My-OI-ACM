/*
$Description$
����һ����Ϊn������A����������Ϊn������B,C���������i����B[i]+C[i]=A[i]����B,C���зֱ�������[2*n/3]��Ԫ�ز�ͬ��
A��Ԫ�ظ�����ͬ��Ai,Bi,Ci��Ϊ�Ǹ�������
$Solution$
ȡk=[n/3]����B,C���зֳ����ݡ������Ƚ�A��������
B����1~kȡ0~k-1��C����k+1~2kȡk~2k-1��C 2k+1~nȡ0~k-1��B,C���ಿ�ֱַ�ΪAi��ȥ��һȷ������ 
������������C��������������2k+1~n��Ai������CiӦ�ǵݼ��ģ�������������Bi�ǵ�����(����)������B������2k+1~n�г����ظ���
��СֵB[2k+1]=A[2k+1]-C[2k+1]>=k+1������������Bi(i��[1,k])��
��Ai�Ǹ�����ͬ�ģ���ôһ���н⣻����Ҫ�����¡�
		 1~k			k+1~2k		   2k+1~n
Bi	0,1,2,...,k-1		Ai-Ci			Ai-Ci
Ci		Ai-Bi		k,k+1,...,2k-1	k-1,...,2,1,0
ע��k���ܵ�����ȡn/3��������������5��ʱ������1.2����Ԫ�ر�3�����٣�������3���ֻ����ظ�����n�Ƚϴ��ʱ�����ظ�������Ԫ�ؾͺ������ˡ�
 */
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
const int N=1e5+5;

int n;
std::pair<int,int> A[N];
struct Answer
{
	int id,b,c;
	bool operator <(const Answer &x)const {return id<x.id;}
}ans[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=mp(read(),i);
	std::sort(A+1,A+1+n);
	int k=(n+2)/3;
	for(int i=1; i<=k; ++i) ans[i].b=i-1, ans[i].c=A[i].first-i+1, ans[i].id=A[i].second;
	for(int i=k+1; i<=k<<1; ++i) ans[i].c=i-1, ans[i].b=A[i].first-i+1, ans[i].id=A[i].second;
	for(int i=k<<1|1; i<=n; ++i) ans[i].c=n-i, ans[i].b=A[i].first-n+i, ans[i].id=A[i].second;
	std::sort(ans+1,ans+1+n);
	puts("YES");
	for(int i=1; i<n; ++i) printf("%d ",ans[i].b);
	printf("%d\n",ans[n].b);
	for(int i=1; i<n; ++i) printf("%d ",ans[i].c);
	printf("%d",ans[n].c);

	return 0;
}
