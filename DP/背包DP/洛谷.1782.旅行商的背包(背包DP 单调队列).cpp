/*
朴素的多重背包是: f[i][j] = max{ f[i-1][j-k*v[i]]+k*w[i] }，复杂度O(nV*∑num_i) 
可以发现求max时有很多值是被重复枚举过的 
换一种方程表示形式，对于每个v[i]，设j=K*v[i]+r, K=j/v[i], r=j%v[i]，即按照%v[i]的余数分别进行dp 
枚举k=0~K-1，那么 f[i][j] = max{ f[i-1][k*v[i]+r]-k*w[i] } + K*w[i]
里面这一部分可以用单调队列维护。
复杂度大概就是O(nV)。二三层枚举相当于把0~V都跑了一遍且只有一遍。
另外二进制拆分也可做，复杂度O(nV*∑log(num_i))。由于数据随机下 num_i可能比较小，∑log(num_i)是期望O(n)的 
这种方法常数更小，所以比单调队列还快 
另一问最大数量只有5，直接V^2暴力。。
注意当前枚举的体积now与数量的限制: 当队首最优值的体积(用的数量k_h)+当前物品最大体积(个数上限num)<当前枚举的体积(k)时，要弹出队首 
另外最后直接输出f[V]?我觉得不太对啊，大概那m个物品一定会产生正权值？
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5;

int n,m,V,f[N],q[N],nm[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(),m=read(),V=read();
	for(int v,w,num,now,tmp,i=1; i<=n; ++i)
	{
		v=read(),w=read(),num=read();
		for(int j=0; j<v; ++j)
			for(int k=0,h=1,t=0; (now=k*v+j)<=V; ++k)//now:当前体积 
			{
				tmp=f[now]-k*w;
				while(h<=t && q[t]<tmp) --t;
				nm[++t]=k, q[t]=tmp;
				if(nm[h]+num<k) ++h;//每次仅会弹出一个元素 
				f[now]=q[h]+k*w;
			}
	}
	for(int a,b,c,i=1; i<=m; ++i)
	{
		a=read(),b=read(),c=read();
		for(int j=V; j; --j)
			for(int k=0; k<=j; ++k)
				f[j]=std::max(f[j],f[j-k]+(a*k+b)*k+c);
	}
//	int res=f[1];
//	for(int i=2; i<=V; ++i) res=std::max(res,f[i]);
	printf("%d",f[V]);

	return 0;
}
