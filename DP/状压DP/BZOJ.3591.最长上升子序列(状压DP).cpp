/*
56872kb	1472ms
���⣺����$1\sim n$��һ�����е�һ������������У���ԭ���п��ܵ���������
$n\leq 15$��
$n$��С������[HDU 4352]����⣬����ֱ�Ӱ���$LIS$ʱ��״̬��������DP�����״̬��
״̬�����Ǹ����������ĵ���ջ��ÿ�����������ֿ��ܣ�û���ջ��������ջ�У�֮ǰ��ջ�е��Ǳ��滻���ˡ�
������һ��$n$λ����������ʾ����ջ��״̬$s$��Ȼ��ö��״̬$s$����ö��һ��û���ֹ��������ܺ�ת�ơ�
ת��ʱע��$LIS$���Ȳ��ܳ���$k$���Լ�Ҫ���γɸ�����$LIS$���ɣ����ڼ����������ڸ�����$LIS$�У�������$LIS$�е�ǰһ����Ҫ���ֹ�����һ����û���ֹ�����
���Ӷ�$O(n3^n)$���ӵ��֦���ⲻ��
��ʵ���԰ѷ�$0$��״̬�ӵ�һ��`queue`�����$3^n$��`for`��
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=20;

int main()
{
	static int A[N],id[N],pw[N],sta[N],lis[N],f[14348909];

	int n,K; scanf("%d%d",&n,&K);
	for(int i=1; i<=K; ++i) scanf("%d",&A[i]), id[--A[i]]=i;
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*3;

	int ans=0;
	f[0]=1, sta[A[0]=n]=1, sta[A[K+1]=n+1]=0;
	for(int s=0,v; s+1<pw[n]; ++s)
		if((v=f[s]))
		{
			int cnt=0,tot=0;
			for(int i=0,tmp=s; i<n; ++i,tmp/=3)
				tot+=((sta[i]=tmp%3)>0), sta[i]==1&&(lis[cnt++]=i);
			if(tot==n) {ans+=v; continue;}//�����ư�...���𰸲�ֻ��f[pw[n]-1] 
			lis[cnt]=20;
			for(int i=0; i<n; ++i)
				if(!sta[i])
				{
					if(id[i] && (!sta[A[id[i]-1]]||sta[A[id[i]+1]])) continue;
					int j=0;
					while(lis[j]<i) ++j;
					if(j==K) continue;//length>K
					f[s+pw[i]+(j==cnt?0:pw[lis[j]])]+=v;//pw[lis[j]] not pw[j]..
				}
		}
	printf("%d\n",ans);

	return 0;
}
