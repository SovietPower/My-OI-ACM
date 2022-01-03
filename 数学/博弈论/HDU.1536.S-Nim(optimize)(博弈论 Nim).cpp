/*
374MS 13072K
$Description$
����һ������S��ÿ��ֻ����S��ĳ��Ԫ�ظ�����ʯ�ӡ�ÿ�������ж���ѯ�ʣ�ѯ�ʸ���m��ʯ�Ӹ������������Ƿ��ʤ���ж������ݡ�
$Solution$
���ȶԲ��������Ÿ��򡣶���ÿ����Ҫ��sgֵ���Լ��仯��
����ÿ�εݹ���Ҫ����vis[N]�Ƚϡ���
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=10002;

int n,A[N],sg[N+3];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Get_SG(int x)
{
	if(sg[x]!=-1) return sg[x];
	bool vis[N+3];
	memset(vis,0,sizeof vis);
	for(int j=1; j<=n&&A[j]<=x; ++j)
		vis[Get_SG(x-A[j])]=1;
	for(int j=0; ; ++j)
		if(!vis[j]) return sg[x]=j;
}

int main()
{
	while(n=read(),n)
	{
		for(int i=1; i<=n; ++i) A[i]=read();
		std::sort(A+1,A+1+n);
		memset(sg,0xff,sizeof sg);
		int m=read();
		while(m--)
		{
			int mx=read(),res=0;
			for(int i=1; i<=mx; ++i) res^=Get_SG(read());
			putchar(res?'W':'L');
		}
		putchar('\n');
	}
	return 0;
}
