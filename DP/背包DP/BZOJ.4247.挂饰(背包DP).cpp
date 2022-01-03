/*
1048kb	624ms
���̰�ģ�������Ȼ��ѡ��Ȼ�����ģ�����Ҫ�ñ�����
�������ݷ�Χ����ֱ���ñ�����f[i][j]��ʾǰi����Ʒ��ʣ��j�����ӵ�����ֵ��
��Ϊû�й��ӵķ�ǰ���޷�ת�ƣ������Ȱ�Ai����
��Ϊ���ݶ� ��N*N��������bzoj���ܵĺ�������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2005;

int f[2][N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int a,val;
	bool operator <(const Node &x)const
	{
		return a>x.a;
	}
}A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=(Node){read(),read()};
	std::sort(A+1,A+1+n);
	memset(f,-0x3f,sizeof f);
	f[0][1]=0; int now=1,las=0;
	for(int i=1,s=1+A[i].a/*��ʼ������1��(����ai=0)*/; i<=n; s+=A[++i].a,las=now,now^=1)
		for(int j=0,a=A[i].a,v=A[i].val,l=std::min(n,s); j<=l; ++j)
			f[now][j]=std::max(f[las][j],f[las][std::max(j-a+1,1)]+v);
	int ans=0;
	for(int i=0; i<=n; ++i) ans=std::max(ans,f[las][i]);
	printf("%d\n",ans);

	return 0;
}
