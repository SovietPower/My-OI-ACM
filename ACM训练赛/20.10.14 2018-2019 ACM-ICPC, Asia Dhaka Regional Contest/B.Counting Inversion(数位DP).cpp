/*
2791ms	95900KB
��λDP��������״ѹ״̬s��ʾǰ�漸λÿ���������˶��ٴΣ�����ö�ٺ����λʱͳ�����������
Ȼ������һ�� ��ǰλѡһ�������ж����ַ������ٳ��������������������
���ǱȽ�easy�ġ���λDP���Ӷȹ�Ȼ�Ѳ�hhh ���仯д�˾��ܹ���
ע�����������14��һ����������13�Σ���
*/
#include <bits/stdc++.h>
#define BIT 14
#define gc() getchar()
typedef long long LL;
const int N=555;

int bit,A[N];
LL pw[N],B[N],pw10[N];
std::unordered_map<LL,LL> f[15],g[15];

inline LL read()
{
	LL now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
LL DFS(int bit,LL s,bool lim,bool lead)
{
	if(!bit) return 0;
	if(!lim && !lead && f[bit].count(s)) return f[bit][s];//lead:another map
	else if(!lim && lead && g[bit].count(s)) return g[bit][s];

	LL res=0,tmp=s; int mx=lim?A[bit]:9;
	for(int i=0,now=0; i<=mx; ++i)
	{
		res+=DFS(bit-1,i?s+pw[i]:(lead?0:s+pw[i]),lim&&i==mx,lead&&!i)+1ll*now*(lim&&i==mx?B[bit-1]+1:pw10[bit-1]);
		now+=tmp%14, tmp/=14;
	}
	if(!lim && !lead) f[bit][s]=res;
	else if(!lim && lead) g[bit][s]=res;
	return res;
}
LL Calc(LL x)
{
	bit=0;
	for(LL tmp=x; tmp; A[++bit]=tmp%10,tmp/=10);
	for(int i=1; i<=bit; ++i) B[i]=A[i]*pw10[i-1]+B[i-1];
	return DFS(bit,0,1,1);
}

int main()
{
	pw[0]=pw10[0]=1;
	for(int i=1; i<=15; ++i) pw[i]=pw[i-1]*14,pw10[i]=pw10[i-1]*10;

	for(int TS=read(),Ts=1; Ts<=TS; ++Ts)
	{
		LL l=read(),r=read();
		printf("Case %d: %lld\n",Ts,Calc(r)-Calc(l-1));
	}

	return 0;
}
