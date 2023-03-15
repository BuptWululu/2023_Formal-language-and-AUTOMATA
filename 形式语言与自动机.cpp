#include <bits/stdc++.h>
#define N 2000
using namespace std;
int n; //DFA状态总数 
struct graph{
	//边权信息 
	int to;		//下一个状态 
	int type;	//转移时的输入为0/1 
};
vector<graph> edge[N];	//NFA每个状态边的信息 
map<set<int> ,int> id;	//状态集合对应的编号 
map<set<int> ,bool> vis;	//是否被遍历过 
queue<set<int> > line;	//队列中存储还未被遍历过的状态 
char ch[100]; //用来消耗第一行输入 
bool F[N];	//存储每个点是否为最终状态 
int GetId(string s) //将q开头的字符串转为数字 
{
	int len=s.size(),sco=0;
	for(int i=len-1;i>=0;i--)
	{
		if(s[i]=='q') break;
		sco=sco*10+(s[i]-'0');
	}
	return sco;
}
int GetDot(string s) //返回状态的编号 
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
void connect(int now,string s,int type) //建边 
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
bool find_F(set<int> now) //判断状态集合中是否有最终状态 
{
	for(set<int>::iterator it=now.begin();it!=now.end();it++)
	{
		if(F[*it])
		return 1;
	}
	return 0;
}
void Print(set<int> now,set<int> Next,int type) //输出函数 
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
	//找出当前状态集合能到达的状态并加入新集合Next 
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
	// 如果下一个状态集合还没加入过就加入队列 
	if(!vis[Next]&&!Next.empty())
	{
		line.push(Next);
		vis[Next]=1;
		if(Next.size()>1)
		id[Next]=++n;
	}
	//输出 
	Print(now,Next,type);
	return ;
}
int main()
{
	//freopen("data2.txt","r",stdin);
	//freopen("output.txt","w",stdout);
    gets(ch);	//把第一行消耗掉 
    string st,aim1,aim2;
    while(cin>>st>>aim1>>aim2)
    {
        n=max(GetDot(st),n); //得到NFA总状态数
		//建边 
        connect(GetDot(st),aim1,1);
        connect(GetDot(st),aim2,2);
    }
    printf("\t\t0\t1\n(s)");
    set<int> now;
    now.insert(0);
	line.push(now);
   	vis[now]=1;
   	//队列存储未遍历过的状态，新状态加入队尾 
	while(!line.empty())
	{
   		find_next(line.front(),1);
   		find_next(line.front(),2);
  		line.pop();
	}
    return 0;
}
