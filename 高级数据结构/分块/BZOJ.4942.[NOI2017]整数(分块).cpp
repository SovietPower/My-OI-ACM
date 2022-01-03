/*
18148kb	3740ms
[�ο�����](https://www.luogu.org/blog/ShadowassIIXVIIIIV/solution-p3822)��

���û�м�������һ����������������λ����̯���Ӷ���$O(1)$�ģ�Ҫ��$O(n)$��λ��������Ҫ$O(n)$�β�������
���������м���...��Ȼ������λ�Ͳ����ˡ�
��ô���ǰѼ�����ɼӷ����ֱ�ά�����ϵ���$inc$�ͼ�������$dec$�Ƕ�󡣲�ѯʱ��Ȼ����ֱ����λ�����Ҫ�ж�һ�º����Ƿ���Ҫ��λ��
�Դ���$set$ά��һ��$inc,dec$���в�ͬλ��λ�ã��ҵ���ѯλ�����һ����ͬ��λ�ã���һ�´�С��ϵ�Ϳ����ˡ�

����ά����λ���Ƚ���Ȼ�������߶���ά��ÿһλ���������$a\times2^b$���$(2^{a_1}+2^{a_2}+...)2^n$���������ͳ�����$\log$��(�s�F����)�s��ߩ��ߡ�
ע�⵽$a$����󣬶����߶�����ÿ��λ���ǿ��Ա�ʾ$16$��$32$λ�ġ�ֱ�Ӱ�$a$����$b$λ����������= =����Ҳ���ǰ�$a$�ӵ�$b$�Ǹ�λ�ü��ɡ����ȡ$32$λ��ô��һ����Ȼ��ֻ���λһ�εģ����Ӱ������λ�ã���
��$32$λ����ֱ����`unsigned int`����Ȼ����Ϳ��Եõ���֮���⼸λ��ֵ���ж��Ƿ��λ����һ���������֮ǰ���֮��Ĵ�С��ϵ���ɣ�

ע�⵽����߶�����ʵûʲô��Ҫ���ֿ飬ÿ��ά��$32$λ��ֵ��ÿ��ֻҪ�ڶ�Ӧ���ϼӣ�Ȼ������λ���ɡ�
���Ӷ�$O(n\log n)$��`set`...����

������λ����$\geq$λ��������$32$λ�����$31$λ����$1$λ���ˡ���
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define pc putchar
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef unsigned int uint;
const int N=1e6+5;

uint inc[N],dec[N];
std::set<int> st;
char IN[MAXIN],*SS=IN,*TT=IN,OUT[N<<1],*O=OUT;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Modify(uint a,uint b,uint *A,uint *B)//a�ڴ���ǰ��Ҫȡabs����uint��
{//2^5=32
	int p=b>>5,q=b&31;
	uint tmp=A[p],delta=(a>>31-q)>>1; A[p]+=(a<<q);//uint
	delta+=(A[p]<tmp); std::set<int>::iterator it;
	if(A[p]!=B[p]) st.insert(p);
	else if((it=st.find(p))!=st.end()) st.erase(it);
	while(delta)
	{
		tmp=A[++p], A[p]+=delta, delta=A[p]<tmp;
		if(A[p]!=B[p]) st.insert(p);
		else if((it=st.find(p))!=st.end()) st.erase(it);
	}
}
void Query()
{
	int b=read(),p=b>>5,q=b&31,ans=((inc[p]^dec[p])>>q)&1;
	uint v1=inc[p]&((1<<q)-1),v2=dec[p]&((1<<q)-1);//inc[p]%(2^q) ȡ���ÿ�p����Ĳ��� 
	if(v1<v2) *O++=((ans^1)+48);//��λ 
	else if(v1>v2||/*st.empty()||*/*st.begin()>=p) *O++=(ans+48);
	else
	{
		std::set<int>::iterator it=st.lower_bound(p); --it;
		*O++=((inc[*it]>dec[*it]?ans:ans^1)+48);
	}
	*O++='\n';
}

int main()
{
	st.insert(N);
	for(int T=read(),a=(read(),read(),read()),b; T--; )
		switch(read())
		{
			case 1: a=read(),b=read(),Modify(a>0?a:-a,b,a>0?inc:dec,a>0?dec:inc); break;
			case 2: Query();
		}
	fwrite(OUT,1,O-OUT,stdout);

	return 0;
}
