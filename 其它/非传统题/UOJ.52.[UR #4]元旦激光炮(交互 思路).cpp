/*
190ms	1704kb
$Description$
���������������ź���ģ����ȷֱ�Ϊ$n_a,n_b,n_c$������$a,b,c$������Ҫ�������Ԫ���е�$k$С����������Ե�������$100$��ѯ��ĳ�������еĵڼ������ĺ�����$n_a,n_b,n_c\leq 10^5$��
$Solution$
��Ȼ����������ö����������ĸ������У��������������ж��֡����������$log^2$�ġ�
�������ÿ��ȷ��һЩ���ȵ�$k$����С�������ǿ���ֱ�ӽ���Щ��ɾ����
�����Լ������������޳���(����INF)������ÿ�η�����������ĵ�$\lfloor\frac{k}{3}\rfloor$��Ԫ�أ������Ԫ����С�������ǰ$\lfloor\frac{k}{3}\rfloor$����ɾ��������$k$ÿ����С$\frac{1}{3}$����$k\leq2$ʱ���ǾͿ��Ժ����׵õ��𰸡�$k\leq 3\times 10^5$��౻��С$31$�α�Ϊ$2$����������Ϊ$93$��$k=2$ʱֱ��ѯ����������ǰ����λ�þͿ��Եõ��𰸡������ܲ����������ᳬ��$99$��
*/
#include "kth.h"
#include <algorithm>

int query_kth(int n_a, int n_b, int n_c, int k)
{
	const int myINF=0x7fffffff;
	int nowa=-1,nowb=-1,nowc=-1,delta,a,b,c,mn;
	while(k>2)
	{
		delta=k/3;
		a=nowa+delta<=n_a?get_a(nowa+delta):myINF,
		b=nowb+delta<=n_b?get_b(nowb+delta):myINF,
		c=nowc+delta<=n_c?get_c(nowc+delta):myINF;
		mn=std::min(a,std::min(b,c));
		if(mn==a) nowa+=delta;
		else if(mn==b) nowb+=delta;
		else if(mn==c) nowc+=delta;
		k-=delta;
	}
	int A[7];
	A[1]=get_a(nowa+1), A[2]=get_a(nowa+2);
	A[3]=get_b(nowb+1), A[4]=get_b(nowb+2);
	A[5]=get_c(nowc+1), A[6]=get_c(nowc+2);
	std::sort(A+1,A+7);
	return A[k];
}
