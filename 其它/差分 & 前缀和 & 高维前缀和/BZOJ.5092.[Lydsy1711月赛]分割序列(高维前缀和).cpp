/*
6576kb	1748ms
���ȴ���$a_i$��ǰ׺����$s_i$����ô�ڶ�������$a_1,...,a_n$����$i$λ�ô��ֿ��ļ�ֵΪ��$s_i+s_i\ ^{\wedge}s_n$��
��Ȼ�и��ӣ������ɿ��Կ��ǰ�λ���㡣���$s_n$�ĵ�$k$λΪ$1$����$s_i$�ĵ�$k$λΪ$0$����$1$���׶���$2^k$�����$s_n$�ĵ�$k$λΪ$0$����ô$s_i$��$k$λΪ$0$����Ϊ$0$��Ϊ$1$����Ϊ$2*2^k$��
Ҳ����˵����Ҫ���Ƿ����$i\leq n$��$s_i$�ĵ�$k$λΪ$1$��ǰ$k$λ������֮ǰ�����ƣ�ĳЩλ����Ϊ$1$����
����ȥ�󣬵�$k$λΪ$1$���������Ƶ��ǰ��λ��$i$���ж��Ƿ���$i\leq n$��
��Ϊ���ƾ���ĳЩλ����Ϊ$1$������λ���⣬Ҳ���ǳ����������ø�άǰ׺��ά������ĳ�����Ƶļ����У��ǰ��λ�þͿ����ˡ�
���Ӷ�$O(2^kk)$��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<20)+5;

int s[300005],f[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	static int pw[30];
	pw[0]=1;
	for(int i=1; i<=21; ++i) pw[i]=pw[i-1]<<1;

	int n=read(),mx=0;
	memset(f,0x3f,sizeof f);
	for(int i=1,t; i<=n; ++i)
		s[i]=s[i-1]^read(), mx=std::max(mx,s[i]), f[s[i]]=std::min(f[s[i]],i);
	int bit=1;
	while(pw[bit]<=mx) ++bit;
	for(int i=0,lim=1<<bit; i<bit; ++i)
		for(int s=0; s<lim; ++s)
			if(!(s&pw[i])) f[s]=std::min(f[s],f[s|pw[i]]);
	for(int i=1; i<=n; ++i)
	{
		int ans=0,t=0;
		for(int j=bit-1; ~j; --j)
			if(s[i]&pw[j]) ans|=pw[j];
			else if(f[t|pw[j]]<=i) t|=pw[j], ans+=pw[j+1];//+= not |=...
		printf("%d\n",ans);
	}
	return 0;
}
