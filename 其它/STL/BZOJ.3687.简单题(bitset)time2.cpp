/*
1484kb	2660ms
$Description$
��$n$���������Ӽ������͵����͡��������ĺ�$<=2*10^6$��
$Solution$
����֮ǰ����������Ϊs1,s2,...������Ϊs1^s2^...����
��ô���Ǽ���ai��֮ǰ���Ӽ���Ҫô����Ҫô����ai����s1,s2,...,s1^ai,s2^ai,...����ô��ǰ����Ϊ(s1^s2^...)^((s1+ai)^(s2+ai)^...)��
��f[i]��ʾ��Ϊi���Ӽ��ĳ��ִ�������ôf[i]+=f[i-ai]��
�ðɳ��˰�����Ǹ��������������Ϊi���Ӽ����ֶ��ٴΡ���Ϊֻ��Ҫ�ж��������λ���ż���Σ�������xor����ӡ�
f[i]^=f[i-ai]���� f�����ÿ��λ�������f��������ai���ÿ��λ�� �õ������顣��bitset�ͺ��ˡ�
*/
#include <cstdio>
#include <bitset>
#include <algorithm>
const int N=2e6+3;

std::bitset<N> f;

int main()
{
//	f.reset();
	int n,sum=0; scanf("%d",&n);
	f[0]=1;
	for(int x; n--; scanf("%d",&x), f^=f<<x, sum+=x);
	int ans=0;
	for(int i=1; i<=sum; ++i) if(f[i]) ans^=i;//if��ö�...(700ms) 1�ܶ��?
	//ans^=f[i]?i:0 Ҳ�� f[i]&&(ans^=i) �졣��������ٶȺܿ��ԭ��ɣ�
	printf("%d\n",ans);

	return 0;
}
