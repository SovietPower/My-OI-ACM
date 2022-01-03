/*
1800kb	160ms
���Կ���������Ҫά��һ����͹�ǡ�
�ȶ�б�ʴ�С��������б�������С��ֱ����һ���ᱣ���ģ���Ϊ����͹������ϵ����Ρ�
ά��һ������ջ��ջ��Ϊ��ǰ�ɼ�ֱ��(����б������)��
������һ��ֱ��lʱ�����Է��� ���l��ջ��ֱ��l'�Ľ���p�� l'��ջǰ��ջ��ֱ�� �Ľ���p'����࣬��ôl�Ḳ��l'(ֱ�������һ��ֱ�ߵĽ������Ҳ���ԣ�)������l'����l��
���p��p'�Ҳ࣬����ջ��ֱ�ߣ�����l��ջ������غϣ���ô������ֱ��Ӧ�ûḲ��l'������l'����l��
��б�ʷ��Ÿı�ʱ���Ҳ��һ���ġ�����ջ�Ĺ���Ӧ������p��p'���Ҳࡣ
����ж���ֱ��б����ͬ���ؾ���ֱ�߻Ḳ�ǽؾ�С��ֱ�ߡ������������ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e4+5;

int n,sk[N],top,Ans[N];
struct Line{
	int k,b,id;
	bool operator <(const Line &a)const{
		return k==a.k?b>a.b:k<a.k;
	}
}l[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
bool Check(int a,int b,int c){//p(l_a&l_b) is on the left of p'(l_b&l_c)
	return 1ll*(l[a].b-l[b].b)*(l[c].k-l[b].k)<=1ll*(l[b].b-l[c].b)*(l[b].k-l[a].k);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) l[i].k=read(),l[i].b=read(),l[i].id=i;
	std::sort(l+1,l+1+n), sk[top=1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(l[i].k==l[i-1].k) continue;
		while(top>1 && Check(i,sk[top],sk[top-1])) --top;//x=(b2-b1)/(k1-k2)
		sk[++top]=i;
	}
	for(int i=1; i<=top; ++i) Ans[i]=l[sk[i]].id;
	std::sort(Ans+1,Ans+1+top);
	for(int i=1; i<=top; ++i) printf("%d ",Ans[i]);

	return 0;
}
