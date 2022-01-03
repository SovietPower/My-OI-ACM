/*
���ȿ���ѯ��[1,n]��ô�� 
�� f[i][0/1]��ʾ[1,i]��0/1��β�Ĳ�ͬ�����и��� 
��if(A[i]) f[i][1] = f[i-1][0] + f[i-1][1] + 1 , f[i][0] = f[i-1][0]
 if(!A[i]) f[i][0] = f[i-1][0] + f[i-1][1] + 1 , f[i][1] = f[i-1][1]
�����룬������д�ɾ��������: f[i,0] f[i,1] 1 = f[i-1,0] f[i-1,1] 1 * M
���˲�д�ˡ������д�Ƚ��鷳 
���ɵ�ԭ����Ϊ0/1��λ�� �ֱ�Ϊ����������1,2�� 1,2�еľ���M[0/1] 
[l,r]��dpֵ�����������˻��Ľ�� ans = f[i,0]+f[i,1]( f[i,0] f[i,1] 1 = 0 0 1 * M[l,r] )

ע: Modifyʱ��ǲ�Ҫ������-- 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=1e5+5,mod=1e9+7;
const int M[2][3][3]={{1,0,0,1,1,0,1,0,1},{1,1,0,0,1,0,0,1,1}};//0 1

int n,m,A[N];
char s[N];
struct Matrix
{
	int mat[3][3];
//	Matrix() {memset(mat,0,sizeof mat);}
	Matrix operator *(const Matrix &a)const
	{
		Matrix res;
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j)
			{
				res.mat[i][j]=0;
				for(int k=0; k<3; ++k)
					res.mat[i][j] += 1LL*mat[i][k]*a.mat[k][j]%mod,
					res.mat[i][j] >= mod ? res.mat[i][j]-=mod : 0;//����ϲ������Щ-- 
			}
		return res;
	}
};
struct Seg_Tree
{
	Matrix mat[N<<2];
	bool tag[N<<2];
	inline void PushUp(int rt)
	{
		mat[rt]=mat[rt<<1]*mat[rt<<1|1];
	}
	inline void Init(int rt,int opt)
	{
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j)
				mat[rt].mat[i][j]=M[opt][i][j];
//		if(opt)
//			mat[rt].mat[0][0]=mat[rt].mat[0][1]=mat[rt].mat[1][1]=mat[rt].mat[2][1]=mat[rt].mat[2][2]=1;
//		else
//			mat[rt].mat[0][0]=mat[rt].mat[1][0]=mat[rt].mat[1][1]=mat[rt].mat[2][0]=mat[rt].mat[2][2]=1;
	}
	void Swap(int rt)
	{
//		for(int i=0; i<3; ++i)//swap(Line 1,Line 2)
//			std::swap(mat[rt].mat[0][i], mat[rt].mat[1][i]);
//		for(int i=0; i<3; ++i)//swap(Column 1,Column 2)
//			std::swap(mat[rt].mat[i][0], mat[rt].mat[i][1]);
		std::swap(mat[rt].mat[0][0],mat[rt].mat[1][0]),
		std::swap(mat[rt].mat[0][1],mat[rt].mat[1][1]),
		std::swap(mat[rt].mat[0][2],mat[rt].mat[1][2]),
		std::swap(mat[rt].mat[0][0],mat[rt].mat[0][1]),
		std::swap(mat[rt].mat[1][0],mat[rt].mat[1][1]),
		std::swap(mat[rt].mat[2][0],mat[rt].mat[2][1]),
		tag[rt]^=1;
	}
	void PushDown(int rt)
	{
		Swap(rt<<1), Swap(rt<<1|1);
		tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		tag[rt]=0;
		if(l==r)
			if(A[l]) Init(rt,1);
			else Init(rt,0);
		else
		{
			int m=l+r>>1;
			Build(l,m,rt<<1), Build(m+1,r,rt<<1|1);
			PushUp(rt);
		}
	}
	void Modify_Flip(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) Swap(rt);//, tag[rt]^=1;//WA
		else
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			if(L<=m) Modify_Flip(l,m,rt<<1,L,R);
			if(m<R) Modify_Flip(m+1,r,rt<<1|1,L,R);
			PushUp(rt);
		}
	}
	Matrix Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mat[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(l,m,rt<<1,L,R)*Query(m+1,r,rt<<1|1,L,R);
			else return Query(l,m,rt<<1,L,R);
		else return Query(m+1,r,rt<<1|1,L,R);
	}
}t;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
#ifndef ONLINE_JUDGE
//	freopen("1.in","r",stdin);
#endif

	int T=read();
	while(T--)
	{
		n=read(),m=read();
		scanf("%s",s+1);
		for(int i=1; i<=n; ++i) A[i]=s[i]-'0';
		t.Build(1,n,1);
		int opt,l,r; Matrix res;
		while(m--)
		{
			opt=read(),l=read(),r=read();
			if(opt==1) t.Modify_Flip(1,n,1,l,r);
			else
				res = t.Query(1,n,1,l,r),
				printf("%d\n",(res.mat[2][0]+res.mat[2][1])%mod);
		}
	}
	return 0;
}
