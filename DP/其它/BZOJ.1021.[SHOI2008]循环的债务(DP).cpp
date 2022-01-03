/*
28276kb	676ms
��ͬ���ĳ�Ʊ�ǿ��Էֿ����ǵġ�
����ʵ���������׾���(֤��?)�������ǿ����񱳰�һ��ȥ����
f[x][i][j]��ʾ��ǰx����Ʊ���� A��iԪ B��jԪ (C��sum-i-j)���轻������������(=(abs(��A)+abs(��B)+abs(��A+��B))/2)��
(i,j���ڱ������еĳ�Ʊ�Ļ����ϵģ���Ϊ��ʼ����f[0][sa][sb]=0������ת�ƺ�ļ۸��Ǹ��ݲ�ֵ���)
ת��ʱö��i,j����ö������A��a��x��ֵ��Ʊ��B��b��x��ֵ��Ʊ (�ݴ˿������Ҫ�����ĳ�Ʊ��)��
���Ӷȡ����������ܴ��ǿ�����Ϊ�ܶ�Ƿ�״̬�������ܵĲ�����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int val[7]={1,5,10,20,50,100},INF=0x3f3f3f3f;

int n,have[3][7],num[7],f[7][1002][1002];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int x1=read(),x2=read(),x3=read(),sa=0,sb=0,sc=0;
	for(int j=5; ~j; --j)
		num[j]+=(have[0][j]=read()), sa+=have[0][j]*val[j];
	for(int j=5; ~j; --j)
		num[j]+=(have[1][j]=read()), sb+=have[1][j]*val[j];
	for(int j=5; ~j; --j)
		num[j]+=(have[2][j]=read()), sc+=have[2][j]*val[j];
	int sum=sa+sb+sc;
	int ea=sa-x1+x3,eb=sb+x1-x2,ec=sum-ea-eb;
	memset(f,0x3f,sizeof f);
	f[0][sa][sb]=0;
	for(int x=0; x<6; ++x)
	{
		for(int i=0; i<=sum; ++i)
			for(int k,j=0; i+j<=sum; ++j)
			{
				if(f[x][i][j]>=INF) continue;
				k=sum-i-j;
				int nowa,nowb,deltaA,deltaB;
				for(int a=0; a<=num[x]; ++a)
				{
					deltaA=a-have[0][x], nowa=i+deltaA*val[x];
					if(nowa<0) continue;//����̫���x��Ʊ���� 
					for(int b=0; a+b<=num[x]; ++b)
					{
						deltaB=b-have[1][x], nowb=j+deltaB*val[x];
						if(nowb<0 || sum-nowa-nowb<0) continue;
						f[x+1][nowa][nowb]=std::min(f[x+1][nowa][nowb],f[x][i][j]+((std::abs(deltaA)+std::abs(deltaB)+std::abs(deltaA+deltaB))>>1));
					}
				}
			}
	}
	if(f[6][ea][eb]<INF) printf("%d",f[6][ea][eb]);
	else puts("impossible");

	return 0;
}
