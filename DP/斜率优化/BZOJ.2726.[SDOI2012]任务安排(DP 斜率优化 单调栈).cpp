/*
11172kb	1092ms(��ôһ��С�ľ�rank1��...)
��$t_i$��ʾ�ӹ�ʱ���ǰ׺�ͣ�$s_i$��ʾ����ϵ��$F_i$��ǰ׺�͡�
$f_i$��ʾ��$i$��Ϊĳһ�����С���ѡ���Ϊÿ�η��鶼��Ժ��������������Ӱ�죬���Զ���
����ϵ��$F_i$�ͺ��ˡ����ԣ�$$f_i=\min\{f_j+(t_i-t_j+S)*(s_n-s_j)\}$$
�𿪣�����д��ֱ����ʽ�ˣ�$f_i+t_is_j=f_j+t_js_j-Ss_j-s_nt_j+Ss_n+t_is_n$��
��Ϊб��$t_i$�����������Բ����õ������е���������ά�������Ƿ���ϵ�������ģ���������$s_j$�ǵ����ģ����Կ���ֱ���õ���ջά��һ����͹�ǣ�ÿ�β�ѯʱ��������ֺ��ʵ�б�ʡ�
��ջ��ʱ��Ҫд>=��>���С�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 1000000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;//���ݷ�Χ��3e5-- 

int n,S,t[N],s[N];
LL f[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int id,x; LL y;
}sk[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL Calc(int i,int j)
{
	return f[j]+1ll*(t[i]-t[j]+S)*(s[n]-s[j]);
}

int main()
{
	n=read(),S=read();
	for(int i=1; i<=n; ++i) t[i]=t[i-1]+read(),s[i]=s[i-1]+read();
	for(int i=1,top=0; i<=n; ++i)
	{
		int l=1,r=top,res=0;//l=1!
		while(l<=r)
		{
			int mid=l+r>>1;
			if(sk[mid].y-sk[mid-1].y<1ll*t[i]*(sk[mid].x-sk[mid-1].x)) res=mid, l=mid+1;
			else r=mid-1;
		}
		f[i]=Calc(i,sk[res].id);
		Node tmp=(Node){i,s[i],f[i]+1ll*t[i]*s[i]-1ll*S*s[i]-1ll*s[n]*t[i]};
		while(top && 1ll*(sk[top].y-sk[top-1].y)*(tmp.x-sk[top].x)>=1ll*(tmp.y-sk[top].y)*(sk[top].x-sk[top-1].x)) --top;
		sk[++top]=tmp;
	}
	printf("%lld\n",f[n]);

	return 0;
}
