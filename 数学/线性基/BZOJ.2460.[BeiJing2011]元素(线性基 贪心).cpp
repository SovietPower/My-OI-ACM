/*
832kb	64ms
$Description$
��һ���Ӽ���������Ԫ���±����Ͳ�Ϊ0���Ҽ�ֵ�����
$Solution$
����ֵ�Ӵ�С���β������Ի����������õ��ļ��Ͼ��Ǽ�ֵ�������ˡ�
̰�Ĳ��Լ�֤�������赱ǰѡȡ�ļ���S��ֵΪ{v1,v2,...,vn}�����Ϊ{id1,id2,...,idn}��������Ʒ�м�ֵ����ΪvMax(idMax)���ҵ�ǰ�����в�����vMax.
��ôvMaxһ�������滻��S�е�ĳ��Ԫ�أ�ʹ�ü�ֵ�͸���
�������ֱ�Ӳ���vMax��˵��S��{1}�����������ˣ���S��һ������һ���Ӽ������±��Xor�͵���idMax��
��$$ id[x1]^id[x2]^...^id[xn]=id[Max] $$
Ȼ��id[Max]���԰�����һ��Ԫ���滻����������x1����ô����ͬʱ���id[Max]^id[x1]��$$ id[Max]^id[x2]^...^id[xn]=id[x1] $$
�����Ϳ��԰�id[x1]���Ա�ʾ��������S���������id[x1]�Ļ���һ����ʾ����id[x1]�ģ���ΪS�����Ͳ�Ϊ0(�������id[x1]�ǲ�����id[x1]��)��
�����滻������Ի���֮ǰ�ǵȼ۵ġ�
дx&(1ll<<i)�Ļ�������1ll��(��Ȼ����ûӰ��)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1005;

LL base[69];
struct Node{
	LL id; int val;
	bool operator <(const Node &x)const{
		return val>x.val;
	}
}A[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i].id=read(), A[i].val=read();
	std::sort(A+1,A+1+n);
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		LL now=A[i].id;
		for(int j=60; ~j; --j)
			if(now&(1ll<<j))
				if(base[j]) now^=base[j];
				else {base[j]=now; break;}
		if(now) ans+=A[i].val;
	}
	printf("%d\n",ans);

	return 0;
}
