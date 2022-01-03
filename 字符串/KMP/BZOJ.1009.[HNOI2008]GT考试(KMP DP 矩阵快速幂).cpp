/*
824kb	24ms
设f[i][j]为当前是第i位考号、现在匹配到第j位(已有j-1位和A[]匹配)的方案数 
因为假如当前匹配j位，如果选择的下一位与A[j+1]不同，那么新的匹配位数是fail[j]而不是0，那么设由匹配j位转移到匹配k位的方案数为t[j][k] 
那么 f[i][j] = ∑f[i-1][k]*t[k][j]
这个式子是线性的，于是可以先计算出t矩阵的n次幂，最后乘以初始矩阵 
t矩阵枚举当前匹配多少位后，枚举下次选择的数即可，利用KMP计算现在匹配的位数 
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
	for(int i=0; i<m; ++i)//当前匹配到第i位 
		for(int k,j='0'; j<='9'; ++j)//选择下一位 
		{
			k=i;
			while(k && s[k]!=j) k=fail[k];
			if(s[k]==j) ++k;//第k位能匹配，转移到k+1位 
			if(k!=m) ++t.A[i][k]/*,t.A[i][k]>=mod?t.A[i][k]-=mod:0*/;//匹配完m位，不能加(虽然加上也不至于错) 
		}
	ans.A[0][0]=1;//初始: f[0][0]=1
	ans=ans*FP(t,n);
	int res=0;
	for(int i=0; i<m; ++i) res+=ans.A[0][i];//实际上ans是一个1*n的矩阵，与t(n*n)相乘后即1*n的矩阵，所以行还应是0 
	printf("%d",res%mod);

	return 0;
}
