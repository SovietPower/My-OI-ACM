/*
13240kb	3876ms->2980ms
**Ī�ӣ�**
��������ѯ�����⿼��һ��Ī�ӡ�
�����ƶ��Ҷ˵�$r\to r+1$��ʱ����ô���´𰸡�
��$r+1$��ߵ�һ����$A_{r+1}$С������$A_p$����ô$Ans$+=$(r+1-p)*A_{r+1}$��ͬ�����ҵ�$p$�ұߵ�һ����$A_p$С����$A_{p'}$��$Ans$+=$(p-p')*A_p$������$p'$��ߵ�һ����$A_{p'}$С����......
������ô����ȷ��һ���߽��أ�
��$[l,r+1]$����Сֵ��$A_x$����$RMQ$�õ���������$x$λ�ú�$Ans$+=$(x-l+1)*A_x$�Ϳ����ˡ�
����ߵ�һ����$A_i$С������λ�ÿ��Ե���ջά����������Ϊ$L_i$��
��Ϊÿ������Ϊ��Сֵʱ�������ǲ����ཻ�ģ���ž��ǻ��γ�һ�����νṹ�������ǿ�����һ������ǰ׺�͵Ķ���ά������Ϊ$sum_i=sum_{L_i}+(i-L_i)*A_i$���Ҷ˵���$i$����˵���$[1,i]$ʱ�Ĵ𰸣���
�����ƶ��Ҷ˵�$r\to r+1$��ʱ��$Ans$+=$sum_{r+1}-sum_x+(x-l+1)*A_x$���Ϳ���$O(1)$�����ˡ�
������˵㣬��Ҫ�ٷ���ά��һ��$sum$��
���Ӷ�$O(n\log n+n\sqrt{n})$��

**�Ż���**
����ѯ��$[l,r]$����$[l,r]$��������СֵΪ$A_p$��
��ô������˵���$[l,p]$���Ҷ˵���$[p,r]$�������䣬��Сֵ����$A_p$������$p$�Ĺ��׾���$A_p\times(p-l+1)\times(r-p+1)$��
�����������Ҷ˵㶼��$(p,r]$ʱ���𰸾���$sum_r+sum_{r-1}+...+sum_{p+1}-sum_p\times(r-p)$��
��$s_i=\sum_{j=1}^isum_j$����ô�𰸾���$s_r-s_p-sum_p\times(r-p)$��
ͬ��������������Ҷ˵���$[l,p)$ʱ������ά��һ��$s$��
Ԥ��������Ϳ�������$O(1)$�ش�ѯ���ˣ����Ӷ�$O(n\log n)$��

**�߶�����**
[���](https://blog.csdn.net/ruoruo_cheng/article/details/54585851)д��ͦ��ϸ�ģ�����дһд��
����$\sum_{i=l}^r\sum_{j=i}^r$��ѯ�ʣ���$[l,r]$�е�������д������������������˵��$l=1,\ r=5$��ÿ�����������СֵΪ��
$1\ \ 1\ \ 1\ \ 1\ \ 3\\1\ \ 1\ \ 1\ \ 1\\2\ \ 2\ \ 4\\2\ \ 2\\5$
��ѯ������Ϊ$[l,r]$ʱ���𰸾��ǵ�$1$�е���$r$���У�ǰ$l\sim r$�еĺ͡�
Ҳ����ÿ���Ҷ˵���$r-1$�ƶ���$r$���Ǹ�����$i\sim r,\ 1\leq i\leq r$�ֱ����һ��ֵ$\min\limits_{j=i}^r\{a_j\}$��Ҳ��������������ж��˵�$r$�С�
�����ʱѯ���Ҷ˵����$r$���Ǵ𰸾���$[l,r]$��ʱ������͡�

�۲�ÿһ�е�����ӣ�ÿ��$A_r$�Ḳ��$r$ǰ��һ�����䣬Ȼ��Ͳ������һ��һ���ˡ�
��$A_r$�Ḳ�ǵ��������$[p+1,r]$��$p$��$r$ǰ���һ����$A_r$С��λ�ã����Ե���ջԤ����
Ҳ�������ǰ�$[p+1,r]$��$val$�ĳ�$A_r$��Ȼ������λ�õ�$sum$+=$val$��

��ôά���أ�
�Ǵ�ʱ������$val$�ĺ�Ϊ$sum$�����䳤��Ϊ$len$��Ҫ�޸ĵ�ֵΪ$v$��������$[l,r]$�Ĵ𰸼���$his$��Ҳ����$[l,r]$�����е����ʷ�汾��$val$�ĺ͡�
��ô�޸ľ��ǣ�$sum'=v*len$������$his$���ǣ�$his'=his+sum'$����ʾ�����Ϊʲô��д��$+sum$��QAQ����

Ҫ���߶�����Чά�������޸ģ��͵���ά����Ǻϲ���
��ת���þ���д����������������$$\begin{bmatrix}len & sum & his \\\end{bmatrix}
\begin{bmatrix}
1 & a & c \\
0 & b & d \\
0 & 0 & 1 \\
\end{bmatrix}=\begin{bmatrix}len' & sum' & his' \\\end{bmatrix}$$

ά��$a,b,c,d$�ĸ�ֵ���޸ĵĲ�������$a=v,b=c=d=0$������$his$�Ĳ�����$d=1,a=b=c=0$����λ���󣨳�ʼ������$b=1,a=c=d=0$��
��Ȼ�����ò���$c$�����Ǿ����ϵ�ʱ���ı�$c$��������Ӱ��������ά����λ�ã�����Ҫά��$c$��
�������þ���Ľ���ɣ��Ϳ���ά����Ǻϲ��ˡ�

���Ӷ�$O(n\log n)$��

ST���һ��ά˳��һ��Ҫ�Ĺ�����
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <assert.h>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,INF=0x7fffffff;

int bel[N],A[N],sk[N],Log[N],pos[18][N];
LL suml[N],sumr[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,id;
	bool operator <(const Quries &x)const
	{
		return bel[l]==bel[x.l]?r<x.r:bel[l]<bel[x.l];
	}
}q[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Min(int x,int y)
{
	return A[x]<=A[y]?x:y;
}
inline int Query(int l,int r)
{
	int k=Log[r-l+1];
	return Min(pos[k][l],pos[k][r-(1<<k)+1]);
}
void Init_ST(const int n)
{
	for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
	for(int j=1; j<=Log[n]; ++j)
		for(int t=1<<j-1,i=n-t; i; --i)
			pos[j][i]=Min(pos[j-1][i],pos[j-1][i+t]);
}
inline LL UpdL(int l,int r)
{
	int p=Query(l,r);
	return suml[l]-suml[p]+1ll*(r-p+1)*A[p];
}
inline LL UpdR(int l,int r)
{
	int p=Query(l,r);
	return sumr[r]-sumr[p]+1ll*(p-l+1)*A[p];
}

int main()
{
	const int n=read(),Q=read(),size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=i/size, A[i]=read(), pos[0][i]=i;
	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};

	Init_ST(n), A[0]=-INF;
	for(int i=1,top=0; i<=n; ++i)
	{
		while(A[sk[top]]>A[i]) --top;
		sumr[i]=sumr[sk[top]]+1ll*(i-sk[top])*A[i], sk[++top]=i;
	}
	A[sk[0]=n+1]=-INF;
	for(int i=n,top=0; i; --i)
	{
		while(A[sk[top]]>A[i]) --top;
		suml[i]=suml[sk[top]]+1ll*(sk[top]-i)*A[i], sk[++top]=i;
	}
	std::sort(q+1,q+1+Q);
	LL Now=0;
	for(int i=1,l=1,r=0; i<=Q; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l>ln) Now+=UpdL(--l,r);//l�ļ� �� r�ļ� Ҫ�Ƚ��У�����ͻ����l>r����� Ȼ��Query��ʱ���gg�� 
		while(r<rn) Now+=UpdR(l,++r);
		while(l<ln) Now-=UpdL(l++,r);
		while(r>rn) Now-=UpdR(l,r--);
		Ans[q[i].id]=Now;
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
