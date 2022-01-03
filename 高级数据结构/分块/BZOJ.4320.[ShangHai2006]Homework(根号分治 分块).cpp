/*
3656kb	1208ms
$\mathbb{mod}$һ����$y$����Сֵ�����Կ���ö��ʣ��ϵ��Ҳ����ö������$[0,y),[y,2y),[2y,3y)...$�е���Сֵ�����׺��СֵҲһ�������´𰸣����Ӷ���$O(\frac ny)$�ġ�ע�⵽$y>\sqrt n$ʱ��ö�ٴ���$<\sqrt n$��

���ǿ��Զ�$y$���ŷ��Σ���$m=\sqrt{V}$��$V$��ֵ�򣩡�
��$y\leq m$ʱ������ά��һ����СΪ$m$��Ͱ$s_i$����ʾģ��Ϊ$i$ʱ��$\min\{a\ \mathbb{mod}\ i,a\in S\}$��������һ����ʱ��������Ͱ��ֵ����ѯʱֱ�������
��$y>m$ʱ��ö��$[0,y),[y,2y),[2y,3y)...$��ЩȨֵ��������Сֵ��Ϊ�˷������ֱ�����׺��Сֵ��Ҳ����$0,y,2y...$��Щλ�õĺ�׺��Сֵ��
ö�ٵĸ��Ӷ���$O(\sqrt V)$�ģ���ô$O(1)$��һ��λ�õĺ�׺��Сֵ�ء�
����ÿ�β���$a$�Ͷ�$1\sim a$��Щλ����$a$ȡ$\min$�����Ƕ�ֵ��ֿ飬�������µĸ��Ӷ���$O(\sqrt V)$�ģ���ѯĳ��λ�õĺ�׺��Сֵ��$O(1)$�ġ�
Ȼ���ܸ��ӶȾ���$O(n\sqrt V)$�ˡ�

���׺��СֵҲ��������������һ�����Ƕ��١���Ϊֻ�в��룬����֮��Ҳ���Կ���ֻ��ɾ�����ұߵ�һ�����ǿ��Բ��鼯ά���ġ�ɾ��һ�������Ǻϲ�����λ�á�
���Ӷ�$O(n\sqrt V\alpha(V))$��Ҳ���Թ���
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+3,INF=1<<30,size=548;//(int)sqrt(3e5); //BZOJ�������汾�͵�����д��CE? = = 
//���ֵ(��ֵ)������N��N��һ������ȡģ����ܻ���С����
int g[size+3],bel[N],tag[size+3],mn[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline char GetOpt()
{
	register char c=gc();
	while(c!='A'&&c!='B') c=gc();
	return c;
}
inline void Add(const int x)
{
	for(int i=1; i<=size; ++i) g[i]=std::min(g[i],x%i);
	for(int i=0,l=bel[x]; i<l; ++i) tag[i]=std::min(tag[i],x);
	for(int i=bel[x]*size; i<=x; ++i) mn[i]=std::min(mn[i],x);
}
inline int Query(const int x)
{
	if(x<=size) return g[x];
	int res=INF;
	for(int i=0; i<N; i+=x)
		res=std::min(res,std::min(mn[i],tag[bel[i]])-i);
	return res;
}

int main()
{
	for(int i=0; i<=size; ++i) g[i]=INF, tag[i]=INF;
	for(int i=0; i<N; ++i) bel[i]=i/size, mn[i]=INF;
	for(int Q=read(); Q--; )
		switch(GetOpt())
		{
			case 'A': Add(read()); break;
			case 'B': printf("%d\n",Query(read())); break;
		}

	return 0;
}
