/*
31ms	0KB
$Description$
���ж��ٸ��������������գ��Ҽ����е����Ԫ�ز�����$K$��
$K\leq 10^9$��
$Solution$
������Ͼ��Ƕ�����յ����Կռ䡣
����һ�������� �򻯵Ľ����ξ��� ��ʽ�󣬻������Կռ�һһ��Ӧ��
�������Կռ�ļ������Կ��ǻ��ļ�����Ҳ�������ռ�������Ի�����

���Կռ�����Ԫ�أ����ǻ����Ļ�������Ԫ�ص����ͣ����λһ��ȡ����
������**����$\leq K$������򻯽����ξ�����ʽ**������ÿ��Ԫ�صĵ�һ������Ԫ��λ�ô�����Ԫ���ڸô�Ϊ$0$���Ļ��ĸ������ɡ�

ֱ����λDP����Ҫ�ǣ���ǰλ$i$����ǰ�����Ѻ��ж��ٸ�Ԫ��$j$���Ƿ����Ͻ硣
�����Ͻ�ʱ��
����ǰλΪ$0$�����λ���½�һ��Ԫ�أ��ҷ�����Ϊ$2^{j-1}$����֤ǰ$j$��Ԫ���ڸ�λ���Ϊ$0$����
����ǰλΪ$1$������λ�½�Ԫ�أ��򷽰���Ϊ$1$������λ���½�Ԫ�أ��򷽰���Ϊ$2^{j-1}$����֤ǰ$j$��Ԫ���ڸ�λ���Ϊ$1$����

**PS��**Ҫע��ͳ�����仯��λDP��ͬ���ǣ������Ͻ�ʱ�����������ֻ��$1$�֣���ǰλ��$1$��ֻ����ͨ���ڸ�λ�½�һ��Ԫ��ʵ�֣������� �Ƿ����Ͻ� ��һά������仯��
*/
#include <bits/stdc++.h>
#define pc putchar
#define mod 1000000007
typedef long long LL;
const int N=50;

int A[N],f[N][N][2];
LL pw[N];

int DFS(int bit,int cnt,bool lim)
{
	if(~f[bit][cnt][lim]) return f[bit][cnt][lim];
	if(!bit) return 1;
	LL res=0;
	if(!lim) res=DFS(bit-1,cnt+1,0)+pw[cnt]*DFS(bit-1,cnt,0);
	else
		res=(cnt?pw[cnt-1]:1ll)*DFS(bit-1,cnt,!A[bit])+ //���λΪ0 
			(A[bit] ? DFS(bit-1,cnt+1,1)+(cnt?pw[cnt-1]:0ll)*DFS(bit-1,cnt,1) : 0); //���λΪ1 
	res%=mod;
	return f[bit][cnt][lim]=res;
}

int main()
{
	int K,bit=0; scanf("%d",&K);
	while(K) A[++bit]=K&1, K>>=1;
	pw[0]=1;
	for(int i=1; i<=bit; ++i) pw[i]=pw[i-1]<<1;

	memset(f,0xff,sizeof f);
	printf("%d\n",DFS(bit,0,1));

	return 0;
}
