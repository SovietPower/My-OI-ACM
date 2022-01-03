/*
124ms	16900KB
$Description$
����һ��$n\times m$��$01$���������ѡ��һЩ�к�һЩ�в����������е�$01$��ת�������������ʣ�¶��ٸ�$1$��
$n\leq20,m\leq10^5$��
$Solution$
$n$��ôС��Ҫ�뵽һ�ǿ���״ѹ״̬�����ǿ���ö��ѡ����Щ�С�
������ȷ����ѡ��Щ��֮��ÿһ�е�ѡ����ȷ���ģ�ȡ���벻���õ���״̬��$1$���ٵ��Ǹ�����
��ô����$y$Ϊ��һ�е�����״̬������״ѹ��ʾ������,����һ�еĴ�Ϊ$B[y]=\min(y��0�ĸ���,y��1�ĸ���)$��$B[y]$����Ԥ����õ�������ʹ�е�״̬��$x$��Ϊ$y$������Ҫ��ת����Ϊ$x\ \mathbb{xor}\ y$��
״̬��ͬ������Ȼ���Ժϲ���������$A[x]$��ʾ״̬Ϊ$x$���еĸ�����
��ô��������ѡ��ת����Ϊ$s$����$ans_s=\sum_{x\ \mathbb{xor}\ y=s}A[x]\times B[y]$��
�������$FWT$�����ˡ�
���Ӷ�$O(2^n\log 2^n)=O(2^nn)$��
~~��������ʱ��Ȼ���ᱬint��~~$FWT$ʱ�ᱬint�����ǿ�longlong�����˲���Ҫȡģ��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 50000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<20)+5;

int col[100005];
LL A[N],B[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void FWT(LL *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j; k<j+mid; ++k)
			{
				LL x=a[k], y=a[k+mid];//LL!
				a[k]=x+y, a[k+mid]=x-y;
				if(opt==-1) a[k]>>=1, a[k+mid]>>=1;//������������ans>>n����
			}
}

int main()
{
	int n=read(),m=read(),lim=1<<n;
	for(int i=0; i<n; ++i)
	{
		register char c=gc(); while(!isdigit(c)) c=gc();
		col[0]|=c-'0'<<i;
		for(int j=1; j<m; ++j) col[j]|=gc()-'0'<<i;
	}
	for(int i=0; i<m; ++i) ++A[col[i]];//cnt
	for(int i=1; i<lim; ++i) B[i]=B[i>>1]+(i&1);//bitcount
	for(int i=1; i<lim; ++i) B[i]=std::min(B[i],n-B[i]);
	FWT(A,lim,1), FWT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]*=B[i];
	FWT(A,lim,-1);
	int ans=n*m;
	for(int i=0; i<lim; ++i) ans=std::min(ans,(int)A[i]);
	printf("%d\n",ans);

	return 0;
}
