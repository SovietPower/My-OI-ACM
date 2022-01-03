/*
309ms	4172kB
$Description$
��άƽ������$n$����ң�ÿ�������$(x_i,y_i)$������һ�������������$(X,Y)$��������$Y$��֪$X$��ȷ����
ÿ�������һ����λʱ���ڻ��򲹸����ƶ�һ����λ���ƶ������������ƶ�����$Y$ͬһ������������ң�ֱ���������䴦���������������ͬʱ�ڷǲ�����λ�õ�ĳ���������ȫ�����֡�
��$X$��ȷ������³��ֵ��������������������
$Solution$
����������ٵ����ѡ���
��֪���������������������ǣ����ǵ�$(X,Y)$�������پ�����ͬ����$|x_i-X|+|y_i-Y|$��ͬ��
����ö��$X$����࿼��$2n$����������$(X,Y)$��ߵ��ˣ�������������$|X-x_i|+|y_i-Y|$��ͬ��Ҳ����$|y_i-Y|-x_i$��ͬ��������ö��$X$����¼ĳ��ֵ�Ƿ���ּ��ɡ�
����$X$�ұߵľ���$|y_i-Y|+x_i$��ͬ��

Ȼ����ĳЩϸ�ڣ����������پ�����ͬ�ĵ�$i,j,k$��ǰ�������ܻ��������Ȼ��out��������������֡����Է���Ҫô��ǰ����$x$��ͬ��Ҫô��$x_i<x_j<x_k$��$k$�����֡�����ǰһ�������¼ÿ��ֵ��$las$����һ�������һ��$tag$���ɡ�
ע���¶����ͬʱ���ֵ������
���������д��Ҫע�⣬$x$��ͬ�ĵ�ֻ����$X$ö�ٵ�$x$ʱ����һ�δ𰸣����򲻶ԣ���
д����Щ�ң�����˵�ˡ����Լ�ģ���¾�ok��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=3e5+15,lim=1e5+2;

int tag[M],tmp[M],las[M];
struct Node
{
	int val,x;
	bool operator <(const Node &a)const
	{
		return x==a.x?val<a.val:x<a.x;
	}
}A[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),y=read();
		for(int i=1,X,Y; i<=n; ++i) X=read(), Y=read(), A[i]=(Node){std::abs(Y-y)-X+lim,X};//[-1e5,1e5)->(0,2e5]
		std::sort(A+1,A+1+n);
		int cnt=n;
		for(int i=1; i<n; ++i) if(A[i].x+1<A[i+1].x) A[++cnt]=(Node){0,A[i].x+1};
		A[++cnt]=(Node){0,0}, A[++cnt]=(Node){0,A[n].x+1}, std::sort(A+1,A+1+cnt);

		A[0].x=A[1].x-1, A[cnt+1].x=A[cnt].x+1;
		for(int i=1,ans=0,t,x,j,a; i<=cnt; i=j)
		{
			for(j=i,a=ans; A[j].x==A[i].x; ++j)
			{
				tmp[j]=a;
				if(t=A[j].val)
				{
					x=A[j].x;
					if(las[t])
						if(las[t]==x) tag[t]?++ans:ans+=2, las[t]=0, tag[t]=0;
						else if(!tag[t]) ans+=2, las[t]=x, tag[t]=1;
						else las[t]=x, tag[t]=0;
					else las[t]=x;
				}
			}
		}
		for(int i=1,t; i<=cnt; ++i) tag[t=A[i].val]=0, las[t]=0, t&&(A[i].val+=2*A[i].x);//(0,2e5)->(1e5,3e5)

		int mn=N,mx=0;
		for(int i=cnt,ans=0,t,x,j; i; i=j)
		{
			mn=std::min(mn,ans+tmp[i]), mx=std::max(mx,ans+tmp[i]);
			for(j=i; A[j].x==A[i].x; --j)
			{
				if(t=A[j].val)
				{
					x=A[j].x;
					if(las[t])
						if(las[t]==x) tag[t]?++ans:ans+=2, las[t]=0, tag[t]=0;
						else if(!tag[t]) ans+=2, las[t]=x, tag[t]=1;
						else las[t]=x, tag[t]=0;
					else las[t]=x;
				}
			}
		}
		for(int i=1; i<=cnt; ++i) tag[A[i].val]=0, las[A[i].val]=0;
		printf("%d %d\n",n-mx,n-mn);
	}

	return 0;
}
