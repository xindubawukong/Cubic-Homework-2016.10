/*
	1 上
	2 下
	3 前
	4 后
	5 左
	6 右 
	
	
	1 黄 
	2 白 
	3 蓝 
	4 绿 
	5 橙
	6 粉 
*/

#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
typedef unsigned int uint;
#define pb push_back

struct Recorder
{
	vector<string> rec;
	map<string,string> go,go0;
	void record(string s) {rec.pb(s);}
	void zuofanchange()
	{
		map<string,string>::iterator it;
		for (it=go.begin();it!=go.end();it++)
			go0[(*it).first]=(*it).second;
		go["zhuanR"]=go0["zhuanD"];
		go["zhuanRi"]=go0["zhuanDi"];
		go["zhuanL"]=go0["zhuanU"];
		go["zhuanLi"]=go0["zhuanUi"];
		go["zhuanB"]=go0["zhuanB"];
		go["zhuanBi"]=go0["zhuanBi"];
		go["zhuanD"]=go0["zhuanL"];
		go["zhuanDi"]=go0["zhuanLi"];
		go["zhuanF"]=go0["zhuanF"];
		go["zhuanFi"]=go0["zhuanFi"];
		go["zhuanU"]=go0["zhuanR"];
		go["zhuanUi"]=go0["zhuanRi"];
	}
	void youfanchange()
	{
		zuofanchange();
		zuofanchange();
		zuofanchange();
	}
	void qianfanchange()
	{
		map<string,string>::iterator it;
		for (it=go.begin();it!=go.end();it++)
			go0[(*it).first]=(*it).second;
		go["zhuanR"]=go0["zhuanR"];
		go["zhuanRi"]=go0["zhuanRi"];
		go["zhuanL"]=go0["zhuanL"];
		go["zhuanLi"]=go0["zhuanLi"];
		go["zhuanB"]=go0["zhuanD"];
		go["zhuanBi"]=go0["zhuanDi"];
		go["zhuanD"]=go0["zhuanF"];
		go["zhuanDi"]=go0["zhuanFi"];
		go["zhuanF"]=go0["zhuanU"];
		go["zhuanFi"]=go0["zhuanUi"];
		go["zhuanU"]=go0["zhuanB"];
		go["zhuanUi"]=go0["zhuanBi"];
	}
	void houfanchange()
	{
		qianfanchange();
		qianfanchange();
		qianfanchange();
	}
	void zuozhuanchange()
	{
		qianfanchange();
		youfanchange();
		houfanchange();
	}
	void youzhuanchange()
	{
		qianfanchange();
		zuofanchange();
		houfanchange();
	}
	void output()
	{
		go["zhuanR"]="zhuanR";
		go["zhuanRi"]="zhuanRi";
		go["zhuanL"]="zhuanL";
		go["zhuanLi"]="zhuanLi";
		go["zhuanB"]="zhuanB";
		go["zhuanBi"]="zhuanBi";
		go["zhuanD"]="zhuanD";
		go["zhuanDi"]="zhuanDi";
		go["zhuanF"]="zhuanF";
		go["zhuanFi"]="zhuanFi";
		go["zhuanU"]="zhuanU";
		go["zhuanUi"]="zhuanUi";
		static vector<string> ans;
		for (uint i=0;i<rec.size();i++)
		{
			if (go.find(rec[i])!=go.end()) ans.pb(go[rec[i]]);
			else if (rec[i]=="zuofan") zuofanchange();
			else if (rec[i]=="youfan") youfanchange();
			else if (rec[i]=="qianfan") qianfanchange();
			else if (rec[i]=="houfan") houfanchange();
			else if (rec[i]=="zuozhuan") zuozhuanchange();
			else youzhuanchange();
		}
		for (int i=1;i<=5;i++) ans.pb("");
		for (uint i=0;i+5<ans.size();i++)
		{
			if (ans[i]==ans[i+1]&&ans[i]==ans[i+2]&&ans[i]==ans[i+3])
			{
				i+=3;
				continue;
			}
			cout<<ans[i]<<endl;
		}
	}
} recorder;
struct Mian
{
	int mm[4][4];
	int * operator [](int x) {return mm[x];}
	void make(int x)
	{
		for (int i=1;i<=3;i++)
			for (int j=1;j<=3;j++) mm[i][j]=x;
	}
	Mian shunzhuan()
	{
		static int _mm[4][4];
		_mm[1][1]=mm[3][1];
		_mm[1][2]=mm[2][1];
		_mm[1][3]=mm[1][1];
		_mm[2][1]=mm[3][2];
		_mm[2][2]=mm[2][2];
		_mm[2][3]=mm[1][2];
		_mm[3][1]=mm[3][3];
		_mm[3][2]=mm[2][3];
		_mm[3][3]=mm[1][3];
		for (int i=1;i<=3;i++)
			for (int j=1;j<=3;j++) mm[i][j]=_mm[i][j];
		return *this;
	}
	Mian nizhuan()
	{
		shunzhuan();
		shunzhuan();
		shunzhuan();
		return *this;
	}
};
Mian nizhuan(Mian x) {return x.nizhuan();}
Mian shunzhuan(Mian x) {return x.shunzhuan();}
struct MoFang
{
	Mian mian[7];
	MoFang() {}
	void zuofan(bool flag=true)
	{
		if (flag) recorder.record("zuofan");
		mian[3].nizhuan();
		mian[4].shunzhuan();
		mian[0]=mian[1];
		mian[1]=nizhuan(mian[6]);
		mian[6]=nizhuan(mian[2]);
		mian[2]=nizhuan(mian[5]);
		mian[5]=nizhuan(mian[0]);
	}
	void youfan(bool flag=true)
	{
		if (flag) recorder.record("youfan");
		zuofan(false);
		zuofan(false);
		zuofan(false);
	}
	void qianfan(bool flag=true)
	{
		if (flag) recorder.record("qianfan");
		mian[5].shunzhuan();
		mian[6].nizhuan();
		mian[0]=mian[1];
		mian[1]=shunzhuan(shunzhuan(mian[4]));
		mian[4]=shunzhuan(shunzhuan(mian[2]));
		mian[2]=mian[3];
		mian[3]=mian[0];
	}
	void houfan(bool flag=true)
	{
		if (flag) recorder.record("houfan");
		qianfan(false);
		qianfan(false);
		qianfan(false);
	}
	void zuozhuan(bool flag=true)
	{
		if (flag) recorder.record("zuozhuan");
		qianfan(false);
		youfan(false);
		houfan(false);
	}
	void youzhuan(bool flag=true)
	{
		if (flag) recorder.record("youzhuan");
		qianfan(false);
		zuofan(false);
		houfan(false);
	}
	void zhuanR(bool flag=true)
	{
		if (flag) recorder.record("zhuanR");
		mian[6].shunzhuan();
		int i;
		for (i=1;i<=3;i++) mian[0][i][3]=mian[1][i][3];
		for (i=1;i<=3;i++) mian[1][i][3]=mian[3][i][3];
		for (i=1;i<=3;i++) mian[3][i][3]=mian[2][i][3];
		for (i=1;i<=3;i++) mian[2][i][3]=mian[4][4-i][1];
		for (i=1;i<=3;i++) mian[4][i][1]=mian[0][4-i][3];
	}
	void zhuanRi(bool flag=true)
	{
		if (flag) recorder.record("zhuanRi");
		zhuanR(false);
		zhuanR(false);
		zhuanR(false);
	}
	void zhuanL(bool flag=true)
	{
		if (flag) recorder.record("zhuanL");
		youfan(false);
		youfan(false);
		zhuanR(false);
		zuofan(false);
		zuofan(false);
	}
	void zhuanLi(bool flag=true)
	{
		if (flag) recorder.record("zhuanLi");
		zhuanL(false);
		zhuanL(false);
		zhuanL(false);
	}
	void zhuanB(bool flag=true)
	{
		if (flag) recorder.record("zhuanB");
		qianfan(false);
		youfan(false);
		zhuanR(false);
		zuofan(false);
		houfan(false);
	}
	void zhuanBi(bool flag=true)
	{
		if (flag) recorder.record("zhuanBi");
		zhuanB(false);
		zhuanB(false);
		zhuanB(false);
	}
	void zhuanD(bool flag=true)
	{
		if (flag) recorder.record("zhuanD");
		zuofan(false);
		zhuanR(false);
		youfan(false);
	}
	void zhuanD_2(bool flag=true)
	{
		zhuanU(false);
		recorder.record("zhuanU");
		youzhuan(false);
		recorder.record("youzhuan");
	}
	void zhuanDi(bool flag=true)
	{
		if (flag) recorder.record("zhuanDi");
		zhuanD(false);
		zhuanD(false);
		zhuanD(false);
	}
	void zhuanF(bool flag=true)
	{
		if (flag) recorder.record("zhuanF");
		houfan(false);
		youfan(false);
		zhuanR(false);
		zuofan(false);
		qianfan(false);
	}
	void zhuanFi(bool flag=true)
	{
		if (flag) recorder.record("zhuanFi");
		zhuanF(false);
		zhuanF(false);
		zhuanF(false);
	}
	void zhuanU(bool flag=true)
	{
		if (flag) recorder.record("zhuanU");
		youfan(false);
		zhuanR(false);
		zuofan(false);
	}
	void zhuanUi(bool flag=true)
	{
		if (flag) recorder.record("zhuanUi");
		zhuanU(false);
		zhuanU(false);
		zhuanU(false);
	}
	void init()
	{
		int i,j,k;
		for (i=1;i<=3;i++)
			for (j=1;j<=3;j++) cin>>mian[1][i][j];
		for (i=1;i<=3;i++)
		{
			for (j=1;j<=3;j++) cin>>mian[5][i][j];
			for (j=1;j<=3;j++) cin>>mian[3][i][j];
			for (j=1;j<=3;j++) cin>>mian[6][i][j];
			for (j=1;j<=3;j++) cin>>mian[4][i][j];
		}
		for (i=1;i<=3;i++)
			for (j=1;j<=3;j++) cin>>mian[2][i][j];
		int sum[7]={0,0,0,0,0,0,0};
		for (k=1;k<=6;k++)
			for (i=1;i<=3;i++)
				for (j=1;j<=3;j++) sum[mian[k][i][j]]++;
		for (i=1;i<=6;i++)
			if (sum[i]!=9)
			{
				printf("Wrong!\n");
				exit(0);
			}
	}
	void luanzhuan(int n)
	{
		srand(time(0));
		for (int i=1;i<=n;i++)
		{
			int x=rand()%100+1;
			if (x<=5) zuofan();
			else if (x<=10) youfan();
			else if (x<=15) qianfan();
			else if (x<=20) houfan();
			else if (x<=25) zuozhuan();
			else if (x<=30) youzhuan();
			else if (x<=35) zhuanR();
			else if (x<=40) zhuanRi();
			else if (x<=45) zhuanL();
			else if (x<=50) zhuanLi();
			else if (x<=55) zhuanU();
			else if (x<=60) zhuanUi();
			else if (x<=65) zhuanB();
			else if (x<=70) zhuanBi();
			else if (x<=75) zhuanF();
			else if (x<=80) zhuanFi();
			else if (x<=85) zhuanD();
			else if (x<=90) zhuanDi();
			else x=2333;
		}
	}
	void guiwei()
	{
		int i;
		for (i=1;i<=6;i++)
			if (mian[i][2][2]==2) break;
		switch (i)
		{
			case 1:qianfan();qianfan();break;
			case 2:break;
			case 3:qianfan();break;
			case 4:houfan();break;
			case 5:zuofan();break;
			case 6:youfan();break;
		}
		if (mian[3][2][2]==6) youzhuan();
		else if (mian[3][2][2]==4) youzhuan(),youzhuan();
		else if (mian[3][2][2]==5) zuozhuan();
	}
	bool check1()
	{
		if (mian[2][1][2]!=2) return false;
		if (mian[2][2][1]!=2) return false;
		if (mian[2][2][3]!=2) return false;
		if (mian[2][3][2]!=2) return false;
		return true;
	}
	void work1()//在最底层做出十字
	{
		while (!check1())
		{
			for (int i=1;i<=4;i++)
			{
				if (mian[2][1][2]==2&&mian[3][3][2]!=mian[3][2][2])
				{
					zhuanF();
					zhuanF();
					zhuanU();
				}
				zhuanD_2();
			}
			for (int i=1;i<=4;i++)
			{
				if (mian[3][2][1]==2)
				{
					zhuanLi();
					zhuanUi();
					zhuanL();
					break;
				}
				if (mian[3][2][3]==2)
				{
					zhuanR();
					zhuanU();
					zhuanRi();
					break;
				}
				if (mian[3][1][2]==2)
				{
					zhuanU();
					zhuanF();
					zhuanUi();
					zhuanFi();
					i--;
					continue;
				}
				if (mian[3][3][2]==2)
				{
					zhuanF();
					i--;
					continue;
				}
				youzhuan();
			}
			for (int i=1;i<=4;i++)
			{
				if (mian[1][3][2]==2)
				{
					while (mian[3][2][2]!=mian[3][1][2]) zhuanD_2();
					zhuanF();
					zhuanF();
					break;
				}
				zhuanU();
			}
		}
	}
	bool check2()
	{
		for (int i=1;i<=3;i++)
			for (int j=1;j<=3;j++)
				if (mian[2][i][j]!=2) return false;
		return true;
	}
	void work2()//拼好最底层，侧面都是"山"形 
	{
		while (!check2())
		{
			for (int i=1;i<=4;i++)
			{
				if (mian[2][1][3]==2&&mian[3][3][3]!=mian[3][2][2])
				{
					zhuanR();
					zhuanU();
					zhuanRi();
				}
				zhuanD_2();
			}
			for (int i=1;i<=4;i++)
			{
				if (mian[3][3][3]==2)
				{
					zhuanR();
					zhuanU();
					zhuanRi();
					break;
				}
				if (mian[3][3][1]==2)
				{
					zhuanLi();
					zhuanUi();
					zhuanL();
					break;
				}
				if (mian[3][1][3]==2)
				{
					while (mian[2][1][3]==2) zhuanD_2();
					zhuanR();
					zhuanUi();
					zhuanRi();
					break;
				}
				if (mian[3][1][1]==2)
				{
					while (mian[2][1][1]==2) zhuanD_2();
					zhuanLi();
					zhuanU();
					zhuanL();
					break;
				}
				youzhuan();
			}
			for (int i=1;i<=4;i++)
			{
				if (mian[1][3][3]==2)
				{
					while (mian[3][1][3]!=mian[6][2][2]) zhuanD_2();
					zhuanR();
					zhuanU();
					zhuanU();
					zhuanRi();
					zhuanUi();
					zhuanUi();
					zhuanFi();
					zhuanU();
					zhuanF();
					break;
				}
				zhuanU();
			}
		}
	}
	bool check3()
	{
		if (mian[3][2][3]!=mian[3][2][2]) return false;
		if (mian[6][2][1]!=mian[6][2][2]) return false;
		if (mian[3][2][1]!=mian[3][2][2]) return false;
		if (mian[5][2][3]!=mian[5][2][2]) return false;
		if (mian[4][2][1]!=mian[4][2][2]) return false;
		if (mian[4][2][3]!=mian[4][2][2]) return false;
		if (mian[6][2][3]!=mian[6][2][2]) return false;
		if (mian[5][2][1]!=mian[5][2][2]) return false;
		return true;
	}
	void work3()//拼好下面两层
	{
		while (!check3())
		{
			if (mian[3][2][3]==mian[3][2][2]&&mian[6][2][1]==mian[6][2][2])
			{
				youzhuan();
				continue;
			}
			if (mian[3][2][3]==mian[6][2][2]&&mian[3][2][2]==mian[6][2][1])
			{
				for (int i=1;i<=2;i++)
				{
					zhuanR();
					zhuanU();
					zhuanU();
					zhuanRi();
					zhuanU();
				}
				zhuanFi();
				zhuanUi();
				zhuanF();
				continue;
			}
			if (mian[3][2][3]!=1&&mian[6][2][1]!=1)
			{
				zhuanF();
				zhuanU();
				zhuanF();
				zhuanU();
				zhuanF();
				zhuanUi();
				zhuanFi();
				zhuanUi();
				zhuanFi();
				continue;
			}
			for (int i=1;i<=4;i++)
			{
				if (mian[3][2][2]==mian[3][1][2]&&mian[1][3][2]==mian[6][2][2]) break;
				if (mian[6][2][2]==mian[6][1][2]&&mian[1][2][3]==mian[3][2][2]) break;
				zhuanU();
			}
			if (mian[3][2][2]==mian[3][1][2]&&mian[1][3][2]==mian[6][2][2])
			{
				zhuanF();
				zhuanU();
				zhuanF();
				zhuanU();
				zhuanF();
				zhuanUi();
				zhuanFi();
				zhuanUi();
				zhuanFi();
			}
			else if (mian[6][2][2]==mian[6][1][2]&&mian[1][2][3]==mian[3][2][2])
			{
				zhuanRi();
				zhuanUi();
				zhuanRi();
				zhuanUi();
				zhuanRi();
				zhuanU();
				zhuanR();
				zhuanU();
				zhuanR();
			}
			youzhuan();
		}
	}
	bool check4()
	{
		if (mian[1][1][2]!=1) return false;
		if (mian[1][2][1]!=1) return false;
		if (mian[1][2][3]!=1) return false;
		if (mian[1][3][2]!=1) return false;
		return true;
	}
	void work4()//拼好顶层十字
	{
		while (!check4())
		{
			for (int i=1;i<=4;i++)
				if (mian[1][3][2]==1||mian[1][2][3]==1) zhuanU();
			if (mian[1][3][2]==1) zhuanU();
			zhuanF();
			zhuanR();
			zhuanU();
			zhuanRi();
			zhuanUi();
			zhuanFi();
		}
	}
	bool check5()
	{
		for (int i=1;i<=3;i++)
			for (int j=1;j<=3;j++)
				if (mian[1][i][j]!=1) return false;
		return true;
	}
	void go5()
	{
		zhuanR();
		zhuanU();
		zhuanRi();
		zhuanU();
		zhuanR();
		zhuanU();
		zhuanU();
		zhuanRi();
	}
	void work5()//拼好顶层
	{
		while (!check5())
		{
			bool flag=false;
			for (int i=1;i<=4;i++)
			{
				if (mian[1][3][1]==1&&mian[1][1][1]!=1&&mian[1][1][3]!=1&&mian[1][3][3]!=1)
				{
					flag=true;
					go5();
					break;
				}
				youzhuan();
			}
			if (flag) continue;
			for (int i=1;i<=4;i++)
			{
				if (mian[1][3][1]==1&&mian[1][1][3]==1&&mian[1][1][1]!=1&&mian[1][3][3]!=1)
				{
					flag=true;
					go5();
					break;
				}
				youzhuan();
			}
			if (flag) continue;
			for (int i=1;i<=4;i++)
			{
				if (mian[1][1][1]==1&&mian[1][3][1]==1&&mian[1][1][3]!=1&&mian[1][3][3]!=1)
				{
					flag=true;
					zuozhuan();
					go5();
					break;
				}
				youzhuan();
			}
			if (flag) continue;
			go5();
		}
	}
	bool pan11() {return mian[5][1][1]==mian[5][2][2]&&mian[4][1][3]==mian[4][2][2];}
	bool pan31() {return mian[5][1][3]==mian[5][2][2]&&mian[3][1][1]==mian[3][2][2];}
	bool pan13() {return mian[6][1][3]==mian[6][2][2]&&mian[4][1][1]==mian[4][2][2];}
	bool pan33() {return mian[3][1][3]==mian[3][2][2]&&mian[6][1][1]==mian[6][2][2];}
	bool check6()
	{
		if (!pan11()||!pan31()||!pan13()||!pan33()) return false;
		return true;
	}
	void go6()
	{
		zhuanR();
		zhuanBi();
		zhuanR();
		zhuanF();
		zhuanF();
		zhuanRi();
		zhuanB();
		zhuanR();
		zhuanF();
		zhuanF();
		zhuanR();
		zhuanR();
	}
	void work6()//将顶层四个角调整好
	{
		while (!check6())
		{
			bool flag=false;
			for (int i=1;i<=4;i++)
			{
				if (pan11()&&!pan13()&&!pan31()&&!pan33())
				{
					flag=true;
					go6();
					break;
				}
				youzhuan();
			}
			if (flag) continue;
			for (int i=1;i<=2;i++)
			{
				if (pan11()&&pan33()&&!pan13()&&!pan31())
				{
					flag=true;
					youzhuan();
					go6();
					break;
				}
				youzhuan();
			}
			if (flag) continue;
			for (int i=1;i<=4;i++)
			{
				if (pan11()&&pan31()&&!pan13()&&!pan33())
				{
					flag=true;
					youzhuan();
					go6();
					break;
				}
				youzhuan();
			}
			if (flag) continue;
			zhuanU();
		}
	}
	bool check7()
	{
		if (mian[3][1][2]!=mian[3][2][2]) return false;
		if (mian[5][1][2]!=mian[5][2][2]) return false;
		if (mian[6][1][2]!=mian[6][2][2]) return false;
		if (mian[4][1][2]!=mian[4][2][2]) return false;
		return true;
	}
	void work7()//顶层四条边调整好 
	{
		while (!check7())
		{
			for (int i=1;i<=4;i++)
			{
				if (mian[4][1][2]==mian[4][2][2]) break;
				youzhuan();
			}
			zhuanR();
			zhuanUi();
			zhuanR();
			zhuanU();
			zhuanR();
			zhuanU();
			zhuanR();
			zhuanUi();
			zhuanRi();
			zhuanUi();
			zhuanR();
			zhuanR();
		}
	}
	void solve()
	{
		luanzhuan(10);
		guiwei();
		work1();//在最底层做出十字
		work2();//拼好最底层，侧面都是"山"形 
		work3();//拼好下面两层
		work4();//拼好顶层十字
		work5();//拼好顶层
		work6();//将顶层四个角调整好
		work7();//顶层四条边调整好 
		guiwei();
	}
	void outit()
	{
		cout<<endl;
		int i,j;
		for (i=1;i<=3;i++)
		{
			cout<<" ";
			for (j=1;j<=3;j++) cout<<"  ";
			for (j=1;j<=3;j++) cout<<mian[1][i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
		for (i=1;i<=3;i++)
		{
			for (j=1;j<=3;j++) cout<<mian[5][i][j]<<" ";
			cout<<" ";
			for (j=1;j<=3;j++) cout<<mian[3][i][j]<<" ";
			cout<<" ";
			for (j=1;j<=3;j++) cout<<mian[6][i][j]<<" ";
			cout<<" ";
			for (j=1;j<=3;j++) cout<<mian[4][i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
		for (i=1;i<=3;i++)
		{
			cout<<" ";
			for (j=1;j<=3;j++) cout<<"  ";
			for (j=1;j<=3;j++) cout<<mian[2][i][j]<<" ";
			cout<<endl;
		}
		cout<<endl<<endl;
	}
} mofang;
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	mofang.init();
	mofang.solve();
	mofang.outit();
	recorder.output();
	return 0;
}
