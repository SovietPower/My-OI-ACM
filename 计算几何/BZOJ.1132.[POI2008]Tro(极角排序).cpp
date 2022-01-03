/*
920kb	8544ms
���Ǳ�����ÿ��ö�������㣬�𰸾���$\frac12\sum_{k<j<i}(i-k)\times(j-k)$��
ע�⵽����з����ʣ����Թ̶�$k$��ö��$i,j$��$Ans=\frac12\sum_{k<i}(i-k)\sum_{k<j<i}(j-k)$��ǰ׺�ͼ��ɡ�
���и������ǲ�����з��ŵġ���ʼʱ�����е㰴����������ö��$k$��ʱ����������$i-k$������������Ϊ$i>k$��$i$����$k$���Ϸ�������֮�䲻�ᳬ��$180^{\circ}$�����Ų���䣬ֱ��ǰ׺�;����ˡ�
���ʱ���ƺ��ᱬ`double`����`long long`��ͺ��ˡ�
���Ӷ�$O(n^2\log n)$��
�������ֱ����������ļ��ǻ�б�ʣ�����Ҫÿ��cmp��һ�β����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3005;

struct Vec
{
	LL x,y;
	Vec(LL x=0,LL y=0):x(x),y(y) {}
	Vec operator +(const Vec &a)const {return Vec(x+a.x, y+a.y);}
	Vec operator -(const Vec &a)const {return Vec(x-a.x, y-a.y);}
	Vec operator *(const LL a)const {return Vec(x*a, y*a);}
	LL operator *(const Vec &a)const {return x*a.y-y*a.x;}
	inline bool operator <(const Vec &a)const {return y<a.y||(y==a.y&&x<a.x);}
}p[N],v[N];
typedef Vec Point;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool cmp(const Vec &a,const Vec &b)
{
	return a*b>0;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) p[i]=(Point){read(),read()};
	std::sort(p+1,p+1+n);
	LL ans=0;
	for(int i=1; i+2<=n; ++i)
	{
		for(int j=i+1; j<=n; ++j) v[j]=p[j]-p[i];
		std::sort(v+i+1,v+n+1,cmp);
		Vec s=v[i+1];
		for(int j=i+2; j<=n; ++j) ans+=s*v[j], s=s+v[j];
	}
	printf("%lld.%d\n",ans>>1,ans&1?5:0);

	return 0;
}
