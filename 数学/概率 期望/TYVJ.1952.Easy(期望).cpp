/*
��f[i]Ϊ��i�������÷֣�c[i]Ϊ��i�������������� 
����s[i]=='x',f[i]=f[i-1], c[i]=0
	s[i]=='0',f[i]=f[i-1]+2*c[i-1]+1, c[i]=c[i-1]+1
(��Ϊ (l+1)^2 = l^2+2l+1 -> (l+1)^2-l^2 = 2l+1,��������+1��Դ𰸶๱��2l+1)
(�е��ɻ�Ϊʲô��c[i-1]...����д����ȷʵ�ǡ�ÿһ��+2l+1 ʵ���Ѿ���ǰ�����е��������� ����(l+1)^2 �Ĺ���
 Ҳ����˵������'o'ʱ���Դ𰸵Ĺ��������Ե�)
	s[i]=='?',f[i]=f[i-1]+(2*c[i-1]+1)/2, c[i]=(c[i-1]+1)/2
(���ֿ����Ծ��ȣ����Զ���1/2��)
*/
#include<cstdio>
using namespace std;
const int N=3e5+5;

int n;
double f[N],c[N];//continuation
char s[N];

int main()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;++i)
		if(s[i]=='x')
			f[i]=f[i-1], c[i]=0;
		else if(s[i]=='o')
			f[i]=f[i-1]+2.0*c[i-1]+1, c[i]=c[i-1]+1;
		else
			f[i]=f[i-1]+c[i-1]+0.5, c[i]=0.5*c[i-1]+0.5;
	printf("%.4lf",f[n]);

	return 0;
}
