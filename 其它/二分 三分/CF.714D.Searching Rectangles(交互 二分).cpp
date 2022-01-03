/*
$Description$
��һ��$n*n$�Ķ�άƽ�������������ཻ��������Σ�ÿ�ο���ѯ�����������м�����ȫ���������һ�������С�200��ѯ����ȷ�������������ꡣ
$Solution$
�����뵽���֡��������κ��񲻺��жϣ��Ǿ�ÿ�ζ����жϾ���������ĺ������ꡣ����Ϊ 8*26<200��
ǰ�Ĵζ���ʲô����֪��������ȷ����һ�����ε�λ�á�Ȼ��ڶ������ξͿ������������ˡ�
*/
#include <cstdio> 
#include <cctype>
#define gc() getchar()

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Query(int a,int b,int c,int d)
{
	printf("? %d %d %d %d\n",a,b,c,d);
	fflush(stdout);
	return read();
}

int main()
{
	int n=read();
	int x1,x2,y1,y2,x3,x4,y3,y4;
	int l=1, r=n, mid;
	while(l<=r){//x2
		if(Query(1,1,mid=l+r>>1,n)) x2=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=n;
	while(l<=r){//y2
		if(Query(1,1,x2,mid=l+r>>1)) y2=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=x2;
	while(l<=r){//x1
		if(Query(mid=l+r>>1,1,x2,y2)) x1=mid,l=mid+1;
		else r=mid-1;
	}
	l=1, r=y2;
	while(l<=r){//y1
		if(Query(x1,mid=l+r>>1,x2,y2)) y1=mid,l=mid+1;
		else r=mid-1;
	}
	l=1, r=n;
	while(l<=r){
		if(Query(1,1,mid=l+r>>1,n)-(x1>=1&&y1>=1&&x2<=mid&&y2<=n)) x4=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=n;
	while(l<=r){
		if(Query(1,1,x4,mid=l+r>>1)-(x1>=1&&y1>=1&&x2<=x4&&y2<=mid)) y4=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=x4;
	while(l<=r){
		if(Query(mid=l+r>>1,1,x4,y4)-(x1>=mid&&y1>=1&&x2<=x4&&y2<=y4)) x3=mid,l=mid+1;
		else r=mid-1;
	}
	l=1, r=y4;
	while(l<=r){
		if(Query(x3,mid=l+r>>1,x4,y4)-(x1>=x3&&y1>=mid&&x2<=x4&&y2<=y4)) y3=mid,l=mid+1;
		else r=mid-1;
	}
	printf("! %d %d %d %d %d %d %d %d\n",x1,y1,x2,y2,x3,y3,x4,y4);
	fflush(stdout);

	return 0;
}
