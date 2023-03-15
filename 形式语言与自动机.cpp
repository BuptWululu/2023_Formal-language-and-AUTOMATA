#include <bits/stdc++.h>
#define N 2000
using namespace std;
int n; //DFA״̬���� 
struct graph{
	//��Ȩ��Ϣ 
	int to;		//��һ��״̬ 
	int type;	//ת��ʱ������Ϊ0/1 
};
vector<graph> edge[N];	//NFAÿ��״̬�ߵ���Ϣ 
map<set<int> ,int> id;	//״̬���϶�Ӧ�ı�� 
map<set<int> ,bool> vis;	//�Ƿ񱻱����� 
queue<set<int> > line;	//�����д洢��δ����������״̬ 
char ch[100]; //�������ĵ�һ������ 
bool F[N];	//�洢ÿ�����Ƿ�Ϊ����״̬ 
int GetId(string s) //��q��ͷ���ַ���תΪ���� 
{
	int len=s.size(),sco=0;
	for(int i=len-1;i>=0;i--)
	{
		if(s[i]=='q') break;
		sco=sco*10+(s[i]-'0');
	}
	return sco;
}
int GetDot(string s) //����״̬�ı�� 
{
	if(s=="N") return 0;
	string ret="";
	bool flag=0;
	int len=s.size();
	bool is_F=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='e') is_F=1;
		if(s[i]==']') break;
		if(flag)
			ret=ret+s[i];
		if(s[i]=='[')
			flag=1;
	}
	if(is_F) F[GetId(ret)]=1;
	return GetId(ret);
}
void connect(int now,string s,int type) //���� 
{
	if(s=="N") return ;
	int len=s.size();
	string tem="";
	bool flag=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]==','||s[i]==']')
		{
			graph g;
			g.to=GetId(tem);
			g.type=type;
			edge[now].push_back(g);
			tem="";
			flag=0;
		}
		if(flag)
		{
			tem=tem+s[i];
		}
		if(s[i]=='q')
		{
			flag=1;
		}
	}
	return ;
}
bool find_F(set<int> now) //�ж�״̬�������Ƿ�������״̬ 
{
	for(set<int>::iterator it=now.begin();it!=now.end();it++)
	{
		if(F[*it])
		return 1;
	}
	return 0;
}
void Print(set<int> now,set<int> Next,int type) //������� 
{
	set<int>::iterator it;
	int Now_id,Next_id;
	
	if(now.size()==1)
	Now_id=*now.begin();
	else
	Now_id=id[now];
	
	if(Next.size()==1)
	Next_id=*Next.begin();
	else
	Next_id=id[Next];
	
	if(type==1)
	{
		if(find_F(now))
		{
			printf("(e)");
		}
		if(Next.empty())
		printf("q%d\tN\t",Now_id);
		else
		printf("q%d\tq%d\t",Now_id,Next_id);
	}
	else
	{
		if(Next.empty())
		printf("N\n");
		else
		printf("q%d\n",Next_id);
	}
	return ;
}
void find_next(set<int> now,int type)
{
	set<int> Next;
	Next.clear();
	//�ҳ���ǰ״̬�����ܵ����״̬�������¼���Next 
	for(set<int>::iterator it=now.begin();it!=now.end();it++)
	{
		int len=edge[*it].size();
		for(int i=0;i<len;i++)
		{
			graph g=edge[*it][i];
			if(g.type==type)
			Next.insert(g.to);
		}
	}
	// �����һ��״̬���ϻ�û������ͼ������ 
	if(!vis[Next]&&!Next.empty())
	{
		line.push(Next);
		vis[Next]=1;
		if(Next.size()>1)
		id[Next]=++n;
	}
	//��� 
	Print(now,Next,type);
	return ;
}
int main()
{
	//freopen("data2.txt","r",stdin);
	//freopen("output.txt","w",stdout);
    gets(ch);	//�ѵ�һ�����ĵ� 
    string st,aim1,aim2;
    while(cin>>st>>aim1>>aim2)
    {
        n=max(GetDot(st),n); //�õ�NFA��״̬��
		//���� 
        connect(GetDot(st),aim1,1);
        connect(GetDot(st),aim2,2);
    }
    printf("\t\t0\t1\n(s)");
    set<int> now;
    now.insert(0);
	line.push(now);
   	vis[now]=1;
   	//���д洢δ��������״̬����״̬�����β 
	while(!line.empty())
	{
   		find_next(line.front(),1);
   		find_next(line.front(),2);
  		line.pop();
	}
    return 0;
}
