/*
$Description$
������Ϊ$n$������$c_i$��$m$����Ϊ$n$������$a_i$���������㣺$c_i\not\mid a_i,\quad a_i\&a_{i+1}=0$��
$n\leq 50��m\leq 15��0\leq a_i<2^m��0<c_i\leq 2^m$.
$Solution$
DP�����ƶ�����ֵ�йصģ�������$f_i$��ʾ��$i$�������β������$a$�ĸ�����
ת�Ƽ�$f_i=\sum_{j,i\&j=0}f_j$��$i\&j=0$��Ҫ$3^n$ö�ٲ������Ӽ������ǻ�����д��$i\&(\sim j)=i$����$i$��$\sim j$���Ӽ��������Ȱ���һ�ε�DP�����±귴ת���Ϳ����ø�άǰ׺���Ż�ö�ٳ����ˡ�
������ö���Ӽ��Ĳ������Ͱ�DP���鷴ת������$f_i=f_{\sim i}��$Ȼ��ö��$i$���Ӽ�����$f_i$��
����$c_i\not\mid a_i$�����ƣ�ÿ��ת���꽫�±�Ϊ$c_i$������$f_i$��Ϊ$0$���ɡ�
����ת��$n$�ξͿ����ˡ����Ӷ�$O(nm2^m)$��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 1000000000
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=(1<<15)+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	static int f[N],tmp[N];

	for(int T=read(); T--; )
	{
		int n=read(),m=read(),lim=(1<<m)-1;
		memset(f,0,sizeof f);
		f[0]=1;
		for(int i=1; i<=n; ++i)
		{
//			for(int s=0; s<=lim; ++s) tmp[s^lim]=f[s];
//			for(int s=0; s<=lim; ++s) f[s]=tmp[s];
			for(int s=0; s<=lim; s+=2) std::swap(f[s],f[s^lim]);
			for(int j=0; j<m; ++j)
				for(int s=0; s<=lim; ++s)
					if(!(s>>j&1)) Add(f[s],f[s|(1<<j)]);
			int ci=read();
			for(int j=0; j<=lim; j+=ci) f[j]=0;
		}
		LL ans=0;
		for(int i=0; i<=lim; ++i) ans+=f[i];
		printf("%d\n",(int)(ans%mod));
	}
	return 0;
}
