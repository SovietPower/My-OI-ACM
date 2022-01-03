/*
31ms	700KB
д�˽�һ�죬����4��Խ��Խ�鷳...mmp...
��ʵ�ܺ�д...
�ȼ�������·�̶��ɹ�ȥ�����������Ȼ��ٲ������ʱ�Ĵ�Ϊ$ans=\sum\limits_{i=1}^nL_i$��
Ȼ���$i=1\sim n$ö�١������ʱ������������$L_i$�ľ��룬�ʹ�֮ǰ����
���Լ�$W,G$�ֱ��ʾ֮ǰ�ɹ���$water$�ж��١�֮ǰ�ɹ���$grass$�ж��١�
��Ȼ�������ԣ����ɹ���$W$·�̱���ι�ȥ���������Ļ����ɹ���$G$·�̱���߹�ȥ���ٲ����Ļ���������ֹ�$water$�������β���������û���ֹ�$water$����$grass$�����߲���������
���Զ���$L_i$��������Ҫ��$W$ת�ƹ�����������$t=\min\{L_i,2W\}$��$W$��·���ܱ��$2W$��������Ϊ�ǽ�ԭ�ȵķ��滻���Σ���Ҳ������Ҫ��֮ǰ$\frac t2$·�̵ķɱ�Ϊ��Ӿ���������$t$����������$ans$+=$\frac t2\times2$��$W$-=$\frac t2$��Ϊ�˱���С����$W$*=$2$����ʱ����$W$-=$t$����
�����ʱ$L_i-t$�Բ�Ϊ$0$����ôͬ����$G$ת�ơ�
����Ϊ$0$������������������/�ߡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

char s[N];
LL A[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); LL ans=0;
	for(int i=1; i<=n;++i) ans+=A[i]=read();
	scanf("%s",s+1);
	LL W=0,G=0;
	for(int i=1,cost=5; i<=n; ++i)
	{
		if(s[i]=='G') G+=A[i]<<1;
		else if(s[i]=='W') W+=A[i]<<1, cost=3;
		LL rest=A[i],t;
		t=std::min(rest,W), rest-=t, ans+=t, W-=t;
		t=std::min(rest,G), rest-=t, ans+=t<<1, G-=t;
		ans+=rest*cost;
	}
	printf("%I64d\n",ans);

	return 0;
}
