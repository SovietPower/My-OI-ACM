/*
$Description$
��һ���㣬ʹ����������ϡ����¡����ϡ������ĸ�����ˮ���������ٵ���󣬲������������ 
$Solution$
��Сֵ����ȶ���һ����mid 
����������ҳ�һ����������[up~down,left~right]�������������������һ������������ˮ������>=mid����OK�� 
�ֿ����ǣ����ڵ�ǰ��i�Ϸ����·��ֱ��ж��ٸ���Ϊup,down 
�ڱ䵽i+1��ʱ��up+=cnt[i], down-=cnt[i+1]��cnt[]Ϊĳ��ˮ����������������Ȼ����O(1)��һ�� 



*/
#include<cstdio>
#include<cctype>
#define gc() getchar()
const int N=



inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}


int main()
{
	
	
	
	
	
	
	
	

	return 0;
}
