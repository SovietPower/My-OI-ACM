/*
46ms	3100KB
$Description$
����������Ϊ$n$������$x_i,y_i$��ÿ�������ѡ��$i,j$����$x_i=x_i\ \mathbb{xor}\ x_j$��$i,j$������ȣ���Ҫ�����ɴβ�����ʹ��$x$���$y$����������������������ܶ���$10^6$���޽����$-1$��
$n\leq10^4,\ 0\leq x_i,y_i\leq10^9$��
$Solution$
�������������������ʣ�
1. ����ǿ���ģ����������������
2. ���Խ�����������`a^=b,b^=a,a^=b`��
�������Ի��������$x$�����Ի������$y$�д���Ԫ�ز��ܱ�$x$��ʾ��������ô�޽⡣
���Ƿ��ֶ��ڲ������Ի��е�Ԫ��$x_i$���õ�$y_i$�Ǻ����׵ģ�ֻ��Ҫ��һ�������Ի���$\mathbb{xor}$��$y_i$��Ҫ�����Щ����
���������Ի��е�Ԫ�أ�����$t$��������֮�䲻�Ǻܺ�������$t$��$x_i$��Ӧ��$y_i$��Ҫ$\mathbb{xor}$��Щ��д��һ��$t$λ�����������ɵڶ������ʣ����ǿ��Ը�˹��Ԫ�����$t\times t$�ľ�������һ�������Ǿ��������Ӹ�λ����λ����ͬ��֮��ͻ���Ӱ���ˣ����ǿ���$\mathbb{xor}$���������
���ɵ�һ�����ʣ�����˹��Ԫ�Ĺ��̷�����������������Ǿ��󣬾Ϳ��Ի�ԭ��$y$���顣
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define BIT 29
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=10005,M=BIT+2;

int x[N],y[N],base[M],is_base[N],b[M],sx[M],sy[N];
std::vector<pr> ans,opt;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) x[i]=read();
	for(int i=1; i<=n; ++i) y[i]=read();
	for(int i=1; i<=n; ++i)
	{
		is_base[i]=-1;
		for(int j=BIT,s=0; ~j; --j)
			if(x[i]>>j&1)
				if(base[j]) x[i]^=x[base[j]], s^=sx[j];
				else
				{
					is_base[i]=j, base[j]=i, sx[j]=s|(1<<j);
					break;
				}
	}
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		int s=0;
		for(int j=BIT; ~j; --j)
			if(y[i]>>j&1)
				if(base[j]) y[i]^=x[base[j]], s^=sx[j];
				else return puts("-1"),0;
		if(~is_base[i]) {b[cnt]=i, sy[cnt++]=s; continue;}//���Ե���0������
		ans.push_back(mp(i,i));
		for(int j=BIT; ~j; --j) if(s>>j&1) ans.push_back(mp(i,base[j]));
	}
	for(int i=0; i<cnt; ++i)
	{
		int s=sy[i]; sy[i]=0;
		for(int j=0; j<cnt; ++j) if(s>>is_base[b[j]]&1) sy[i]|=1<<j;
	}
	for(int i=0; i<cnt; ++i)
	{
		if(!(sy[i]>>i&1))
			for(int j=i+1; j<cnt; ++j)
				if(sy[j]>>i&1)
				{
					opt.push_back(mp(b[i],b[j]));
					opt.push_back(mp(b[j],b[i]));
					opt.push_back(mp(b[i],b[j]));
					std::swap(sy[i],sy[j]);
					break;
				}
		if(sy[i]>>i&1)
			for(int j=i+1; j<cnt; ++j)
				if(sy[j]>>i&1)
					opt.push_back(mp(b[j],b[i])), sy[j]^=sy[i];
	}
	for(int i=0; i<cnt; ++i)
	{
		if(!(sy[i]>>i&1)) ans.push_back(mp(b[i],b[i]));
		for(int j=i+1; j<cnt; ++j)
			if(sy[i]>>j&1) ans.push_back(mp(b[i],b[j]));
	}
	std::reverse(opt.begin(),opt.end());
	for(auto v:opt) ans.push_back(v);
	printf("%d\n",ans.size());
	for(auto v:ans) printf("%d %d\n",v.first,v.second);

	return 0;
}
