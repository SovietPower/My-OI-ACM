/*
17916kb	368ms
$Description$
��һЩ���֣����ֳ�����˫�˶��У������߶�����ȡ�����������ջ��ֻ�ܴ�ĳһ��һ��һ��ȡ������ʽ����������ȡ��Щ���֣�ÿ���˶�������Լ�ȡ�������ֺͣ���������˸���ȡ�����١�
$n\leq10^6$��
$Solution$
��������ߵ�ջ�������$A_1\geq A_2$����ô����ȡ��$A_2$������һ����ȡ��$A_1$�����׬����Ȼ����Ҫȡ�������׬�����ֿ���ȡ�����������ú���ȡ�ߣ���ͬ����չ����������ݼ���һ�Σ����˶�������ȡ�ģ�����$i$Ϊ����ʱ������ȡ$A_{i-1}$���ܾͲ�׬�ˣ���
���ұߵ�ջͬ��
Ȼ���ܷ��֣�˭��ȡ����������ұߵ���ֻ�������ܸ����йأ����һ�������������ֿ���ͬʱȡ����������ң�������ֿ��ԡ���nb...�о���Ҫ֤��ܸ��ӣ�
��ô���ǾͿ��Դ��������ҵݼ�����һ���ˡ�ʣ�µĵȻ���˵��

����˫�˶��У������$A_{i-1}\leq A_i\geq A_{i+1}$��������ȡ��$A_{i-1}$����ô����һ��ȥȡ$A_i$������һ����ȡ��$A_{i+1}$������������ǹ̶��ģ�Ϊ$A_i-A_{i-1}-A_{i+1}$�������������ָȡ$A_{i-1}$���ˡ���ô���ǾͿ��Խ���������ѹ��һ������ȥ������
��ô���ǾͿ��Խ�������͹�����ȫ�ϲ����������б��ֻ�еݼ��ġ������ġ���͹�������������Ȼ������һ���ǴӴ�С����ѡ�ġ�

�����ϲ�����ջ����Ϊ��ߵݼ����Ѿ��ϲ��ˣ�Ҳû����͹����ˣ�����ֻʣ�µ�������ˡ�ͬ����˫�˶�����Щ��һ������ѡ�����ˡ�

���������֪��������֪�����ˡ�
ע��ϲ����Ԫ���ǿ��ܳ���$0$�ģ���λ��Ҫ�ٿ��������С�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

LL sk[N],A[N];
bool tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),top=0,sta=0;
	LL sum=0,ans=0;
	for(int i=1; i<=n; ++i)
	{
		sk[++top]=read();
		tag[top]=(sk[top]>0), sta^=(sk[top]>0), sum+=sk[top];
		while(top>2 && tag[top] && tag[top-1] && tag[top-2] && sk[top-1]>=std::max(sk[top-2],sk[top]))
			sk[top-2]=sk[top]+sk[top-2]-sk[top-1], top-=2;
	}
	int l=1,r=top,cnt=0,v=sta?1:-1;
	for(; tag[l]&&tag[l+1]&&sk[l]>=sk[l+1]; l+=2) ans+=v*(sk[l]-sk[l+1]);
	for(; tag[r]&&tag[r-1]&&sk[r]>=sk[r-1]; r-=2) ans+=v*(sk[r]-sk[r-1]);
	for(int i=l; i<=r; ++i) tag[i]&&(A[++cnt]=sk[i]);
	std::sort(A+1,A+1+cnt,std::greater<LL>());
	for(int i=1; i<=cnt; ++i) i&1?ans+=A[i]:ans-=A[i];
	printf("%lld %lld\n",sum+ans>>1,sum-ans>>1);

	return 0;
}
