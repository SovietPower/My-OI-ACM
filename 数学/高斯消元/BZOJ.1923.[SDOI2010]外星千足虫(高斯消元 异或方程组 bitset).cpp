/*
1100kb	324ms
m�����̣�n��δ֪���������򷽳��顣
���ӶȱȽϸߣ���Ҫ����bitsetѹλ��
�о��Լ���ǰд��(���)��˹��Ԫ�Ǽٵġ������һ�ѧ����д��������Ҫ�ش���
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
const int N=1004,M=2004;

int n,m;
char s[N];
std::bitset<N> A[M];

bool Gauss()
{
	int ans=0;
	for(int r,c=0; c<n; ++c)
	{
		r=c;
		while(!A[r][c]&&r<m) ++r;
		if(r==m) return 0;//��������Ԫ(c)��
		ans=std::max(ans,r);
		if(r!=c) std::swap(A[r],A[c]);
		for(int i=0; i<m; ++i)//ֱ��ö�����з��̣�(��Ϊ��ǰλ��ϵ����1��ǰ��Ҳ����0��)�����Ͳ���Ҫ�ش��ˡ����A[i][n]����i�Ľ����	
			if(A[i].test(c)&&i!=c) A[i]^=A[c];//����������Щ��
//			if(A[i][c]&&i!=c) A[i]^=A[c];
	}
	printf("%d\n",ans+1);
	for(int i=0; i<n; ++i) puts(A[i].test(n)?"?y7M#":"Earth");
	return 1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int t,i=0; i<m; ++i){
		scanf("%s%d",s,&t), A[i][n]=t;
		for(int j=0; j<n; ++j)
			A[i][j]=s[j]-'0';
	}
	if(!Gauss()) puts("Cannot Determine");

	return 0;
}
