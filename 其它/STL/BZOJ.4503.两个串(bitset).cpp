/*
2744kb	1372ms
������`bitset`����ƥ�䡣
ά��`bitset<N> Ans`��ʾÿ��λ���ܷ�ƥ��$T$����ö��$T$�е��ַ�$T_j$��ά��$Ans_i$�Ƿ��ܹ�ƥ��$T_j$��Ҳ����$S_{i+j}$���Ƿ���$T_j$��
������$26$��`bitset<N> Pos[26]`�õ�ÿ���ַ���$S$����Щλ���ϳ��ֹ������ֹ���λ����Ϊ$1$����
Ȼ��ö��$T_j$��$j\in[0,T|$����ʱ��$Ans_i$ÿ�ζ�����$Pos_{T_j}$����$j$λ�Ϳ����ˡ�������ͨ����Ͳ��������ˣ���ע�������ƣ�
�����$Ans_i$����$1$����$i$λ��ƥ��$T$����
���Ӷ�$O(\frac{nm}{w})$��
*/
#include <cctype>
#include <cstdio>
#include <bitset>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+3;

char S[N],T[N];
std::bitset<N> Ans,pos[26];
char IN[MAXIN],*SS=IN,*TT=IN;

int main()
{
	static int p[N];

	register char c;
	int n=0; while(isalpha(S[n]=gc())) ++n;//���и����з���=_= ����while��ʱ��n�ȱ�ӡ�
	int m=0; while(isalpha(T[m]=gc())||T[m]=='?') ++m;

	for(int i=0; i<n; ++i) pos[S[i]-97].set(i);
	Ans.set();
	for(int i=0; i<m; ++i) if(T[i]!='?') Ans&=pos[T[i]-97]>>i;

	int ans=0;
	for(int i=0; i<=n-m; ++i) if(Ans[i]==1) p[++ans]=i;
	printf("%d\n",ans);
	for(int i=1; i<=ans; printf("%d\n",p[i++]));

	return 0;
}
