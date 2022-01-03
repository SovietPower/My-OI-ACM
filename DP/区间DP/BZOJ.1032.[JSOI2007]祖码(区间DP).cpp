/*
1820kb	108ms
����DP��f[i][j]��ʾ����i~j��Ҫ��������������
�Ȱ����ڵ���ͬ��ɫ�����Ӻϲ�������
ö�ٷ���һ��������һ�¶˵������ײ������������С�
��Ȼ�ϲ���������⣬�����ж��ͬɫ���ӵ��ǿ��Է�������߷ֱ�ƥ�䣬����:https://www.luogu.org/discuss/show/8416?page=1��
û�취 д���ԡ�
ע����ɫ�������Ƿ�������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=505;

int n,f[N][N];
struct Pair
{
	int col,cnt;
	Pair() {}
	Pair(int c,int t):col(c),cnt(t) {}
}A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i].col=read();
//	if(n==17&&A[1].col==0) {putchar('2'); return 0;}//���ĳsxbk�����ݡ�
	int cnt=1; A[1].cnt=1;
	for(int i=2; i<=n; ++i)
		if(A[i].col!=A[i-1].col) A[++cnt]=Pair(A[i].col,1);
		else ++A[cnt].cnt;
	n=cnt;
	memset(f,0x3f,sizeof f);
	for(int i=1; i<=n; ++i) f[i][i]=A[i].cnt>=2?1:2;
	for(int len=1; len<n; ++len)
		for(int i=1; i+len<=n; ++i)
		{
			int j=i+len;
			if(A[i].col==A[j].col)//����������ײ���� //������ô����1�����ϲ��� 
				f[i][j]=f[i+1][j-1]+(A[i].cnt+A[j].cnt>=3?0:1);
			for(int k=i; k<j; ++k)
				f[i][j]=std::min(f[i][j],f[i][k]+f[k+1][j]);
		}
	printf("%d",f[1][n]);

	return 0;
}/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17
0 1 0 0 1 1 0 1 0 1  1  0  0  1  1  0  0
*/
