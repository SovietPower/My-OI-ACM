/*
3360kb	84ms
**Manacher��**
��$R_i$��ʾ��$i$λ��Ϊ��β������Ĵ����ȣ�$L_i$��ʾ��$i$��ͷ������Ĵ����ȡ��𰸾���$\max\{R_i+L_{i+1}\}$��ʽ�ӿ��ܻ��в����ΪManacher����������ַ�����Ȼ����ֱ��ֻ��'#'λ�õ�$L_i+R_i$�Ϳ��Ը��´�����
Manacher��Ȼ�����λ��$i$����������Զ���������$ex_i$��
Ȼ����$i-j$����$L_j,\;j\in[i-ex_i+1,\ i]$��$j-i$����$R_j,\;j\in[i,i+ex_i-1]$��ע���ַ��������'#'�ģ���

��Ȼֻ��Ҫά����������$\max\{i\},\min\{i\}$�Ϳ����ˣ��������߶���������Ȼ������ȥд��
�����������Ȼ�����ã������ܷ�$O(1)$���£�Ҳ���Ǹ���һ��λ��Ȼ����ƹ���������ʾû�����= =��

���԰�...����$i-j$���ֵ����������λ�������$1$�ġ�����$j$���µ�$i$λ��ʱ��$i-j$��$\leq0$�ˡ�Ҳ��������ֻ����$L_{i-ex_i+1}=\max\{ex_i-1\}$�������$L_j=\max\{L_j,\ L_{j-1}-1\}$���Ƽ��ɡ�$R$ͬ��
������$O(n)$����

��Ȼ����ֻ��Ҫ��'#'��ͳ�ƣ�����ֻ������Щλ�ü��ɡ�

**��������**
�������������λ����������ÿ��λ�õ�����ĳ��ȾͿ����ˡ���
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int ex[N],L[N],R[N];
char s[N];

int Build()
{
	int n=strlen(s+1);
	for(int i=n; i; --i) s[i<<1]=s[i], s[(i<<1)-1]='#';
	s[0]='!', s[n<<1|1]='#', s[(n<<1)+2]='@';
	return n<<1|1;
}
void Manacher(const int n)
{
	for(int i=1,id,mx=0; i<=n; ++i)
	{
		if(i<mx) ex[i]=std::min(ex[2*id-i],mx-i);
		else ex[i]=1;
		while(s[i-ex[i]]==s[i+ex[i]]) ++ex[i];
		if(i+ex[i]>mx) mx=i+ex[i], id=i;
		L[i-ex[i]+1]=std::max(L[i-ex[i]+1],ex[i]-1);
		R[i+ex[i]-1]=std::max(R[i+ex[i]-1],ex[i]-1);
	}
}

int main()
{
	scanf("%s",s+1);
	int n=Build(); Manacher(n);
	for(int i=n-2; i>=1; i-=2) R[i]=std::max(R[i],R[i+2]-2);//i>=1 not i!
	for(int i=3; i<=n; i+=2) L[i]=std::max(L[i],L[i-2]-2);
	int ans=0;
	for(int i=1; i<=n; i+=2) if(L[i]&&R[i]) ans=std::max(ans,L[i]+R[i]);//if!
	printf("%d\n",ans);

	return 0;
}
