/*
824kb	24ms
��f[i][j]Ϊ��ǰ�ǵ�iλ���š�����ƥ�䵽��jλ(����j-1λ��A[]ƥ��)�ķ����� 
��Ϊ���統ǰƥ��jλ�����ѡ�����һλ��A[j+1]��ͬ����ô�µ�ƥ��λ����fail[j]������0����ô����ƥ��jλת�Ƶ�ƥ��kλ�ķ�����Ϊt[j][k] 
��ô f[i][j] = ��f[i-1][k]*t[k][j]
���ʽ�������Եģ����ǿ����ȼ����t�����n���ݣ������Գ�ʼ���� 
t����ö�ٵ�ǰƥ�����λ��ö���´�ѡ��������ɣ�����KMP��������ƥ���λ�� 
*/
#include <cstdio>
#include <cstring>
const int N=23;

int n,m,mod,fail[N];
char s[N];
struct Matrix
{
	int A[N][N];
	Matrix operator *(const Matrix &a)const
	{
		Matrix res;
		for(int i=0; i<m; ++i)
			for(int j=0; j<m; ++j)
			{
				res.A[i][j]=0;
				for(int k=0; k<m; ++k)
					res.A[i][j]+=A[i][k]*a.A[k][j];
				res.A[i][j]%=mod;
			}
		return res;
	}
	void Print()
	{
		for(int i=0; i<m; ++i,putchar('\n'))
			for(int j=0; j<m; ++j) printf("%d ",A[i][j]);
		putchar('\n');
	}
}t,ans;

void Get_Fail()
{
//	fail[0]=fail[1]=0;
	for(int j,i=1; i<m; ++i)
	{
		j=fail[i];
		while(j && s[i]!=s[j]) j=fail[j];
		fail[i+1]= s[i]==s[j]?j+1:0;
	}
}
Matrix FP(Matrix x,int k)
{
	Matrix t=x; --k;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}

int main()
{
	scanf("%d%d%d%s",&n,&m,&mod,s);
	Get_Fail();
	for(int i=0; i<m; ++i)//��ǰƥ�䵽��iλ 
		for(int k,j='0'; j<='9'; ++j)//ѡ����һλ 
		{
			k=i;
			while(k && s[k]!=j) k=fail[k];
			if(s[k]==j) ++k;//��kλ��ƥ�䣬ת�Ƶ�k+1λ 
			if(k!=m) ++t.A[i][k]/*,t.A[i][k]>=mod?t.A[i][k]-=mod:0*/;//ƥ����mλ�����ܼ�(��Ȼ����Ҳ�����ڴ�) 
		}
	ans.A[0][0]=1;//��ʼ: f[0][0]=1
	ans=ans*FP(t,n);
	int res=0;
	for(int i=0; i<m; ++i) res+=ans.A[0][i];//ʵ����ans��һ��1*n�ľ�����t(n*n)��˺�1*n�ľ��������л�Ӧ��0 
	printf("%d",res%mod);

	return 0;
}
