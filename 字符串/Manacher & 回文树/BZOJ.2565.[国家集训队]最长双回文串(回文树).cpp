/*
23576kb	156ms
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
typedef long long LL;
const int N=1e5+5;

char s[N];
struct PAM
{
	int las,tot,fail[N],son[N][26],len[N],mx[N];

	PAM() {tot=1, fail[0]=1, len[1]=-1;}
	inline int Find(int x,int n)
	{
		while(s[n-len[x]-1]!=s[n]) x=fail[x];
		return x;
	}
	void Insert(int c,int n)
	{
		int p=Find(las,n);
		if(!son[p][c])
		{
			int np=++tot; fail[np]=son[Find(fail[p],n)][c];
			son[p][c]=np, len[np]=len[p]+2;
		}
		las=son[p][c];
	}
	void Build(char *s,const int n,const int opt)
	{
		if(opt) for(int i=1; i<=n; ++i) Insert(s[i]-'a',i), mx[i]=len[las];
		else for(int i=1; i<=n; ++i) Insert(s[i]-'a',i), mx[n-i+1]=len[las];//...
	}
}p1,p2;

int main()
{
	scanf("%s",s+1); int n=strlen(s+1);
	p1.Build(s,n,1), std::reverse(s+1,s+1+n), p2.Build(s,n,0);
	int ans=0;
	for(int i=1; i<n; ++i) ans=std::max(ans,p1.mx[i]+p2.mx[i+1]);
	printf("%d\n",ans);

	return 0;
}
