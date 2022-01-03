/*
$Description$
��һ����Ϊ$n$�Ķ����ƴ�����֤$01$�����ڡ������ѯ�ʲ�����$15$�Σ�ÿ��ѯ�������һ����Ϊ$n$�Ķ����ƴ���������᷵����Ĵ���Ŀ�괮�Ĳ�ͬλ����Ŀ��������һ��$0$��$1$��λ�á�
$n\leq 1000$��
$Solution$
ͨ��$0...$��$1...$�Ϳ����жϳ���һ������ʲô��Ȼ����֣���ÿ�������ж��Ƿ�ȫΪ$0/1$���Ϳ����ҵ���һ���ˡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n;
char s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Query()
{
	putchar('?'), puts(s); fflush(stdout);
	return read();
//	int t; scanf("%d",&t); return t;
}
inline void Fill(int l,int r,const char c)
{
	for(int i=l; i<=r; ++i) s[i]=c;
}
int Solve(const char q,const char c)
{
	for(int i=1; i<=n; ++i) s[i]=c;
	int l=2,r=n,mid,bef=Query(),tmp;
	while(l<r)
	{
		Fill(l,mid=l+r>>1,q), tmp=Query(), Fill(l,mid,c);
		if(std::abs(bef-tmp)==mid-l+1 && bef>tmp) return l;//ע��������䳤��ʱ��ֵ�����ǲ���� 
		if(std::abs(bef-tmp)<mid-l+1) r=mid;
		else l=mid+1;
	}
	return l;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) s[i]='0'; s[0]=' ', s[n+1]='\0';
	int t0=Query(); s[1]='1'; int t1=Query();
	int ans0, ans1;
	if(t0<t1) ans0=1, ans1=Solve('1','0');
	else ans1=1, ans0=Solve('0','1');
	printf("! %d %d\n",ans0,ans1);// fflush(stdout);

	return 0;
}
