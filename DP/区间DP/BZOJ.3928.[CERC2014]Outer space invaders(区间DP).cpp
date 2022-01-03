/*
2260kb	544ms(2260kb	1768ms)
$Description$
��$n$�������ˣ���$i$�������˻���ʱ��$a_i$���֣��������$d_i$���ұ�����ʱ��$b_i$֮ǰ������
����һ������������ɱ�뾶Ϊ$r$��Բ�ڵ����������ˡ�$r$�������������ÿ����һ�λ�����$r$��λ���������������������˵���С����������
$n\leq 300, a_i,b_i,d_i\leq 10^4$��
$Solution$
���ǳ���ʱ����[l,r]�ڵĵ��ˣ�����Զ�ĵ��˾���Ϊ$d_{max}$����������Ҫ��һ�ΰ뾶$r=d_{max}$�Ĺ�������������
�������ѡ����$t$ʱ�̹������������Զ�ģ���ôʱ�������Խ$t$����������Ҳ�ᱻ˳������
�����ͻ��ֳ�����������������⡣
�ȶ�ʱ��������ɢ����Ȼ������DP���Ե�ǰ�����ҳ�������Զ�ĵ��ˣ�Ȼ��ö����������ʱ��$t$��
���Ӷ�$O(n^3)$��
��ΪҪ�Ҿ�����Զ�ģ������ȶԵ������򣬿�����Ч�Ż��������������ҽṹ��ȷʵҪ������������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=605;

int ref[N],f[N][N];
struct Node
{
	int l,r,dis;
	bool operator <(const Node &x)const
	{
		return dis>x.dis;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(),t=0;
		for(int i=1; i<=n; ++i) ref[++t]=A[i].l=read(),ref[++t]=A[i].r=read(),A[i].dis=read();
		std::sort(A+1,A+1+n);

		std::sort(ref+1,ref+1+t); int cnt=1;
		for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
		for(int i=1; i<=n; ++i) A[i].l=Find(A[i].l,cnt), A[i].r=Find(A[i].r,cnt);

		for(int len=0; len<cnt; ++len)
			for(int i=1; i+len<=cnt; ++i)
			{
				int j=i+len,mx=0;
				for(int k=1; k<=n; ++k)
					if(i<=A[k].l && A[k].r<=j) {mx=k; break;}
				if(!mx) {f[i][j]=0; continue;}
				int tmp=1000000000;
				for(int k=A[mx].l,R=A[mx].r,cost=A[mx].dis; k<=R; ++k)//����i~j����
					tmp=std::min(tmp,f[i][k-1]+f[k+1][j]+cost);
				f[i][j]=tmp;
			}
		printf("%d\n",f[1][cnt]);
	}
	return 0;
}
