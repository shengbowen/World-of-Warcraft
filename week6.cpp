 //by Sheng Bowen
#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>
using namespace std;
const int  WARRIOR_NUM = 5;
const int  WEAPON_NUM = 3;//武器种类数
const int RED=0;
const int BLUE=1;
/*
string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。
*/
//===========================类的声明=====================================
//========================================================================
//========================================================================
class Warrior;
class Weapon
{
protected:
	int kindNo;//武器的种类编号 0 sword 1 bomb 2 arrow 
	Warrior * pWarrior;
	int forceValue;//武器的攻击力
public:
	Weapon(int kindNo_,Warrior* pWarrior_):kindNo(kindNo_),pWarrior(pWarrior_){}
	static string names[WEAPON_NUM];
	virtual void sunHao(){}//武器的损耗程度, 虚函数如果没有{}会出现link2001错误
	int getKindNo(){return kindNo;}
	int getForce(){return forceValue;}
	virtual void printInfo(){}
	virtual bool shiXiao(){ return false;}//武器是否失效即耗尽
};

class Sword:public Weapon
{
public:
	Sword(int kindNo_,Warrior* pWarrior_);
	virtual void sunHao()
	{
		forceValue=forceValue*0.8;
	}
	virtual void printInfo()
	{
		cout<<"sword("<<forceValue<<")";
	}
	virtual bool shiXiao()
	{
		if(forceValue==0)
			return true;
		return false;
	}
};

class Bomb:public Weapon
{
private:
	int use;
public:
	Bomb(int kindNo_,Warrior* pWarrior_,int use_=1):Weapon(kindNo_,pWarrior_),use(use_){}
	virtual void printInfo(){cout<<"bomb";}
	virtual void sunHao(){use--;}
	virtual bool shiXiao()
	{
		if(use==0)
			return true;
		return false;
	}
};
class Arrow:public Weapon
{
private:
	int count;//箭的数目
public:
	static int R;
	Arrow(int kindNo_,Warrior* pWarrior_,int count_=3):Weapon(kindNo_,pWarrior_),count(count_){Weapon::forceValue=R;}
	void shoot(Warrior* opponet);
	//{
	//	count--;
	//	//opponet->hurted();
	///*}
	virtual void sunHao()
	{
		count--;
	}
	virtual bool shiXiao()
	{
		if(count==0)
			return true;
		return false;
	}
	int getCount(){return count;}
	virtual void printInfo()
	{
		cout<<"arrow("<<count<<")";
	}
};


class City;
class Headquarter;
class BattleField;
class Warrior
{
	protected:
		Headquarter * pHeadquarter;
		City * pCity;//当前行进的城市
		//BattleFiled * bf;
		int kindNo; //武士的种类编号 0 dragon 1 ninja 2 iceman 3 lion 4 wolf
		int no;//武士的编号
		int life;//武士的生命值
		int force;//攻击力
		int cityNo;//前进到的的城市编号
	public:
		bool notSunHao;//对于炸弹自检时调用attck不损耗sword
		bool arrivedOpposite;//到达对方司令部
		bool battled;//在一个城市是否战斗过
		int cityElement;//取得所在城市的生命元数
		bool win;
		bool hasArrow;
		bool hasBomb;
		bool hasSword;
		static string names[WARRIOR_NUM];
		static int initialLifeValue [WARRIOR_NUM];
		static int initialForceValue[WARRIOR_NUM];
		Warrior( Headquarter * p,int no_,int kindNo_ );
		int getForce(){return force;}
		virtual void PrintResult(int nTime);
		/*virtual ~Warrior(){}*/
		virtual void attack(Warrior* oponent,int h){}
		virtual void fightBack(Warrior* attacker,int h){}
	    virtual void hurted(int harm){life=life-harm;}
		void initCityNo(BattleField&);
	    virtual int goForward(BattleField &,int time);//武士前进,返回到达的城市编号
		bool isDead();
		Headquarter * returnHead(){return pHeadquarter;}
		int getNo(){return no;}
		int getKindNo(){return kindNo;}
		int getLife(){return life;}
		void setLife(int value){life=value;}
		void setCityNo(int cityno){cityNo=cityno;};
		void getCityElement();//获取城市生命元
		virtual void shootEnemy(Warrior*,int){}
	     bool useBomb(Warrior*);
		 virtual void winTheBattle(){}
		 virtual void printWeapon(){}
		 virtual int getSwordForce(){return 0;}
};

//======================各个从武士基类派生的兵种=======================================
class Dragon:public Warrior
{
private:
	Weapon * pWeapon;//拥有一个武器
	double morale;//士气
public:
	friend class Wolf;
	Dragon(Headquarter *p,int no_,int kindNo);
	virtual ~Dragon(){if(pWeapon!=NULL)delete pWeapon; }//delete pWeapon;}
	virtual void PrintResult(int nTime);
	double getMorale(){return morale;}
	virtual void attack(Warrior* oponent,int h);
	virtual void fightBack(Warrior* attacker,int h);
	//virtual void hurted();
	virtual void shootEnemy(Warrior*,int);
	//virtual bool useBomb(Warrior*);
	virtual void winTheBattle();
	virtual void printWeapon();
	virtual int getSwordForce();
	
};

class Ninja:public Warrior
{
private:
	Weapon * pWeapon[2];//拥有2个武器
public:
	friend class Wolf;
	Ninja(Headquarter *p,int no_,int kindNo);
	virtual ~Ninja()
	{
		for(int i=0;i<2;i++)
			if(pWeapon[i]!=NULL)
				delete pWeapon[i];
	}//delete pWeapon[1]; delete pWeapon[0];}
	virtual void PrintResult(int nTime);
	virtual void attack(Warrior* oponent,int h);
	virtual void fightBack(Warrior* attacker,int h);
	//virtual void hurted();
	virtual void shootEnemy(Warrior*,int);
	//virtual bool useBomb(Warrior*);
	virtual void printWeapon();
	virtual int getSwordForce();
};

class Iceman:public Warrior
{
private:
	Weapon * pWeapon;//拥有一个武器
	int step;
public:
	friend class Wolf;
	Iceman(Headquarter *p,int no_,int kindNo);
	virtual ~Iceman(){if(pWeapon!=NULL) delete pWeapon;}
	virtual void PrintResult(int nTime);
	virtual void attack(Warrior* oponent,int h);
	virtual void fightBack(Warrior* attacker,int h);
	//virtual void hurted();
	virtual void shootEnemy(Warrior*,int);
	//virtual bool useBomb(Warrior*){};
	virtual void printWeapon();
	virtual int goForward(BattleField &,int time);//武士前进,返回到达的城市编号
	virtual int getSwordForce();
};

class Lion:public Warrior
{
private:
	int loyalty ;
public:
	friend class Wolf;
	int preLife;//保存站前的life
	static int k;
	virtual void hurted(int harm){ preLife=life;life=life-harm;}
	Lion(Headquarter *p,int no_,int kindNo);
	//virtual ~Lion(){delete pWeapon;}
	virtual void attack(Warrior* oponent,int h);
	virtual void fightBack(Warrior* attacker,int h);
	virtual void PrintResult(int nTime);
	int getLoyalty(){return loyalty;}
	void setLoylty(int i){loyalty=i;}
	virtual void printWeapon();

};

class Wolf:public Warrior
{
private:
	Weapon* pWeapon[3];
public:
	Wolf(Headquarter *p,int no_,int kindNo);
	~Wolf()
	{
			
		for(int i=0;i<3;i++)
			if(pWeapon[i]!=NULL)
				delete pWeapon[i];
	}
	virtual void attack(Warrior* oponent,int h);
	virtual void fightBack(Warrior* attacker,int h);
	void getWeapon(Warrior*);
	virtual void printWeapon();
	virtual void shootEnemy(Warrior*,int);
	virtual int getSwordForce();
};
//====================================================================================

class City
{
protected:
	int no;//城市的编号
	int element;//城市的生命元
	int flag;//城市的旗帜，0无旗，1红旗，2蓝旗
public:
	int enemyNum;
	int preWin;//上场战斗的胜方，1为红，2为蓝，0为平手
	int curWin;
	friend class Warrior;
	friend class BattleField;
	Warrior* pWarrior[2];//一个城市最多有1个红方和一个蓝方的兵p[0]存放red，p[1]存放blue
	City():no(0),element(0),flag(0){pWarrior[RED]=NULL;pWarrior[BLUE]=NULL;enemyNum=0;preWin=0;curWin=0;}
	City(int no_,int ele_,int flag_):no(no_),element(ele_),flag(flag_){pWarrior[RED]=NULL;pWarrior[BLUE]=NULL;enemyNum=0;preWin=0;curWin=0;}
	void createLife();//城市制造生命元
	void flagOperate();//升旗操作
	void battle();//战斗
	void setNo(int n){no=n;}
};

class Headquarter :public City
{
	private:
		int totalLifeValue;
		bool stopped;
		int totalWarriorNum;
		int color;
		int curMakingSeqIdx; //当前要制造的武士是制造序列中的第几个
		int warriorNum[WARRIOR_NUM]; //存放每种武士的数量
		Warrior * pWarriors[1000];
	public:
		friend class Warrior;
		friend  class Iceman;
		friend class BattleField;
		static int makingSeq[2][WARRIOR_NUM]; //武士的制作顺序序列
		void Init(int color_, int lv);
		~Headquarter ();
		int Produce(int nTime);
		string GetColor();
		int getLifeValue(){return totalLifeValue;}
		
};

class BattleField
{
private:
	Headquarter *phead[2];
	int N;//司令部间城市的个数
    City** pcity ;
	int time;//战场时钟
	//friend class Warrior;
public:
	//void battle(int time);//战斗
	void start(int m,int n);//初始化战场
	void run(int T);//战场运行,直到时间T
	friend class Warrior;
	friend class Iceman;
	void lionRun(int time);
	void collectLife(int time);//回收没有敌方战士的城市生命元
	void shootBattle(int time);//战场中射箭动作，从东向西输出
	void bombBattle(int time);//战场中使用bomb的动作
	void Battle(int time);//40分钟的战斗
	void rewardLife();//奖励武士生命元
	void recycleElement();//回收胜利战士手中的生命元
	//~BattleField();
};

//===========================类的声明结束=====================================
//========================================================================
//========================================================================



//===========================类方法的实现===================================
//=======================================================================
//========================================================================

Sword::Sword(int kindNo_,Warrior* pWarrior_):Weapon(kindNo_,pWarrior_)
	{
		forceValue=pWarrior->getForce()*0.2;
		//force=forceValue;
	}


void Arrow::shoot(Warrior* opponet)
	{
		count--;
	//opponet->hurted();
	}

Warrior::Warrior( Headquarter * p,int no_,int kindNo_ ) {
	no = no_;
	kindNo = kindNo_;
	pHeadquarter = p;
	//initCityNo();
	force=initialForceValue[kindNo_];
	hasArrow=false;
	hasBomb=false;
	hasSword=false;
	battled=false;
	win=false;
	notSunHao=false;
	cityElement=0;
	arrivedOpposite=false;
}
void Warrior::PrintResult(int nTime)
{
		int h=nTime/60;
		int min=nTime%60;
		string color =  pHeadquarter->GetColor();
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<setfill('0')<<min<<" "<<color<<" "<<names[kindNo]
		     <<" "<<no<<" born"<<endl;
		/*printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n"	,
				nTime, color.c_str(), names[kindNo].c_str(), no, initialLifeValue[kindNo],
				pHeadquarter->warriorNum[kindNo],names[kindNo].c_str(),color.c_str());*/
}

void Warrior::initCityNo(BattleField& bfield)
{
	if(pHeadquarter->GetColor()=="red")
		cityNo=0;
	else if(pHeadquarter->GetColor()=="red")
		cityNo=bfield.N+1;
}

void Warrior::getCityElement()
{
	int element=this->pCity->element;
	if(element!=0){
	this->pHeadquarter->totalLifeValue+=element;
	cout<<pHeadquarter->GetColor()<<" "<<names[kindNo]<<" "<<no<<" earned "<<element<<" elements for his headquarter"<<endl;
	this->pCity->element=0;}
}

void City::createLife()
{
	element=element+10;
}

Headquarter::~Headquarter()
{
	for(int i=0;i<1000;i++)
	{
		if(pWarrior[i]!=NULL)
			delete pWarrior[i];
	}
}
void Headquarter::Init(int color_, int lv)
{
	color = color_;
	totalLifeValue = lv;
	totalWarriorNum = 0;
	stopped = false;
	curMakingSeqIdx = 0;
	for( int i = 0;i < WARRIOR_NUM;i ++ )
		warriorNum[i] = 0;
}
//Headquarter::~Headquarter () {
//	for( int i = 0;i < totalWarriorNum;i ++ )
//		delete pWarriors[i];
//}
int Headquarter::Produce(int nTime)
{
	if(nTime%60==0)
	{
		if(Warrior::initialLifeValue[makingSeq[color][curMakingSeqIdx]] > totalLifeValue)
			return 0;

		int kindNo = makingSeq[color][curMakingSeqIdx];
		totalLifeValue -= Warrior::initialLifeValue[kindNo];
		curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM ;
		if(kindNo==0)
		{
		pWarriors[totalWarriorNum] = new Dragon( this,totalWarriorNum+1,kindNo);
		}
		else if(kindNo==1)
		{	
		pWarriors[totalWarriorNum] = new Ninja( this,totalWarriorNum+1,kindNo);
		}
		else if(kindNo==2)
		{
		pWarriors[totalWarriorNum] = new Iceman( this,totalWarriorNum+1,kindNo);
		}
		else if(kindNo==3)
		{
		pWarriors[totalWarriorNum] = new Lion( this,totalWarriorNum+1,kindNo);
		}
		else
		{
		pWarriors[totalWarriorNum] = new Wolf( this,totalWarriorNum+1,kindNo);
		}
		warriorNum[kindNo]++;
		pWarriors[totalWarriorNum]->PrintResult(nTime);
		pWarriors[totalWarriorNum]->setCityNo(this->no);
		if(GetColor()=="red")
			this->pWarrior[RED]=pWarriors[totalWarriorNum];  //司令部继承自CITY，因此也具备指向当前战士的指针
		else if(GetColor()=="blue")
			this->pWarrior[BLUE]=pWarriors[totalWarriorNum];
		totalWarriorNum ++;
		return 1;
	}
	else return 0;
}
string Headquarter::GetColor()
{
	if( color == 0)
		return "red";
	else
		return "blue";
}

//void BattleField::start()
//{
//	/*pcity=new City*[N];
//	for(int i=0;i<N;i++)
//		pcity[i]=new City();*/
//}

//====================warrior派生类函数实现===================
bool Warrior::isDead()
{
	if(Warrior::life<=0)
		return true;
	else return false;
}
int Warrior::goForward(BattleField &bfield,int time)
{
	if(Warrior::pHeadquarter->GetColor()=="red")
	{
		if(Warrior::cityNo < bfield.N && Warrior::isDead()==false)
		{
			bfield.pcity[cityNo]->pWarrior[RED]=NULL;
			++cityNo;
			Warrior::pCity=bfield.pcity[cityNo];
			bfield.pcity[cityNo]->pWarrior[RED]=this;
			battled=false;
			win=false;
			return cityNo;
		}  
		else if(Warrior::cityNo == bfield.N && Warrior::isDead()==false)
		{
			bfield.pcity[cityNo]->pWarrior[RED]=NULL;
			++cityNo;
			Warrior::pCity=bfield.pcity[cityNo];
			bfield.pcity[cityNo]->pWarrior[RED]=this;//到达敌军司令部
			bfield.pcity[cityNo]->enemyNum++;//记录司令部敌军数目
			battled=false;
			win=false;
			return bfield.N+1;
		}
	}
	else if(Warrior::pHeadquarter->GetColor()=="blue")
	{
		if(Warrior::cityNo >1 && Warrior::isDead()==false)
		{
			bfield.pcity[cityNo]->pWarrior[BLUE]=NULL;
			--cityNo;
			Warrior::pCity=bfield.pcity[cityNo];
		    bfield.pcity[cityNo]->pWarrior[BLUE]=this;
			battled=false;
			win=false;
			return cityNo;
		}
		else if(Warrior::cityNo ==1 && Warrior::isDead()==false)
		{	
			bfield.pcity[cityNo]->pWarrior[BLUE]=NULL;
			--cityNo;
			Warrior::pCity=bfield.pcity[cityNo];
		    bfield.pcity[cityNo]->pWarrior[BLUE]=this;
			bfield.pcity[cityNo]->enemyNum++;
			battled=false;
			win=false;
			return 0;
		}
	}
}

bool Warrior::useBomb(Warrior* p)
{
	int life1=this->getLife();
	int life2=p->getLife();
	int force1=this->getForce();
	int force2=p->getForce();
	int sw1=this->getSwordForce();
	int sw2=p->getSwordForce();

	Ninja* ptr1=dynamic_cast<Ninja*>(this);
	Ninja* ptr2=dynamic_cast<Ninja*>(p);
	if(this->pHeadquarter->GetColor()=="red")
	{
		if(cityNo%2!=0&&this->pCity->flag==0||this->pCity->flag==1)//主动攻击
		{

			life2=life2-force1-sw1;
			if(life2>0&&!ptr2)
			{
				life1=life1-force2/2+sw2;
			}
			if(life1<=0)return true;
			else return false;
		}
		else { 
			life1=life1-force2-sw2;
			if(life1<=0)return true;
			else return false;
		}
	}

	if(this->pHeadquarter->GetColor()=="blue")
	{
		if(cityNo%2==0&&this->pCity->flag==0||this->pCity->flag==2)//主动攻击
		{
			life2=life2-force1-sw1;
			if(life2>0&&!ptr2)
			{
				life1=life1-force2/2+sw2;
			}
			if(life1<=0)return true;
			else return false;
		}
		else { 
			life1=life1-force2-sw2;
			if(life1<=0)return true;
			else return false;
		}
	}

	//int c_no=this->cityNo;
	//int preLife1=this->getLife();
	//int preLife2=p->getLife();
	//if(this->pHeadquarter->GetColor()=="red")
	//{
	//	if(cityNo%2!=0&&this->pCity->flag==0||this->pCity->flag==1)//主动攻击
	//	{
	//		if(this->getForce()>p->getLife())
	//		/*this->attack(p);
	//		if(this->isDead())
	//		{
	//		this->setLife(preLife1);
	//		p->setLife(preLife2);
	//		return true;
	//		}
	//		this->setLife(preLife1);
	//		p->setLife(preLife2);*/
	//	}
	//	else { 
	//		p->attack(this);
	//		if(this->isDead())
	//		{
	//			this->setLife(preLife1);
	//			p->setLife(preLife2);
	//			return true;
	//		}
	//		this->setLife(preLife1);
	//		p->setLife(preLife2);
	//	}
	//}
	//else if(this->pHeadquarter->GetColor()=="blue")
	//{
	//	if(cityNo%2==0&&this->pCity->flag==0||this->pCity->flag==2)
	//	{
	//		this->attack(p);
	//		if(this->isDead())
	//		{
	//		this->setLife(preLife1);
	//		p->setLife(preLife2);
	//		return true;
	//		}
	//		this->setLife(preLife1);
	//		p->setLife(preLife2);
	//	}
	//	else { 
	//		p->attack(this);
	//		if(this->isDead())
	//		{
	//			this->setLife(preLife1);
	//			p->setLife(preLife2);
	//			return true;
	//		}
	//		this->setLife(preLife1);
	//		p->setLife(preLife2);
	//	}
	//}
	//return false;
}

Dragon::Dragon(Headquarter *p,int no_,int kindNo_):Warrior(p,no_,kindNo_)
{
	life=initialLifeValue[0];
	if(no_%3==0) {pWeapon=new Sword(no_%3,this); hasSword=true;}
	if(no_%3==1) {pWeapon=new Bomb(no_%3,this);hasBomb=true;}
	if(no_%3==2) {pWeapon=new Arrow(no_%3,this);hasArrow=true;}
	morale= (p->getLifeValue()*1.00) /(Warrior::initialLifeValue[kindNo]);
}
void Dragon::PrintResult(int nTime)
{
	Warrior::PrintResult(nTime);
	cout<<"Its morale is "<< fixed<<setprecision(2)<<getMorale()<<endl;
}

void Dragon::printWeapon()
{
	if(pWeapon!=NULL)//先判断
	{
		if(!pWeapon->shiXiao())
		{
			cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
			pWeapon->printInfo();
			cout<<endl;
		}
		//cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has no weapon"<<endl;
		else pWeapon=NULL;//消耗殆尽也视为无武器}
	}
	if(pWeapon==NULL){
		hasSword=false;hasBomb=false;hasArrow=false;
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has no weapon"<<endl;
	}
}
int Dragon::getSwordForce()
{
	if(hasSword)return pWeapon->getForce();
	else return 0;
}

void Dragon::attack(Warrior* oponent,int h)
{
	Lion* ptr=dynamic_cast<Lion*>(oponent);
	if(ptr)
	{
		ptr->preLife=ptr->getLife();	
	}
	int harm;
	if(hasSword)
	{   
		 harm=getForce()+pWeapon->getForce();
		 pWeapon->sunHao();
	}
	else harm=getForce();
	oponent->hurted(harm);
	//if(!oponent->isDead())
       oponent->fightBack(this,h);	
}

void Dragon::fightBack(Warrior* attacker,int h)
{
	Lion* ptr=dynamic_cast<Lion*>(attacker);
	if(ptr)
	{
		ptr->preLife=ptr->getLife();	
	}
	if(!this->isDead()){
	int harm;
	int force=getForce()/2;
	if(hasSword)
	{
		harm=force+pWeapon->getForce();
		pWeapon->sunHao();
	}
	else harm=force;
	attacker->hurted(harm);
	cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
	cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" "<<"fought back against "<<attacker->returnHead()->GetColor()
		<<" "<<attacker->names[attacker->getKindNo()]<<" "<<attacker->getNo()<<" in city "<<cityNo<<endl;
	}
}

void Dragon::winTheBattle()
{
	if(win) Dragon::morale+=0.2;
	else morale-=0.2;
}

void Dragon::shootEnemy(Warrior* emeny,int h)
{
	Arrow *ptr=dynamic_cast<Arrow*>(pWeapon);
	if(ptr->getCount()>0)
	{
		emeny->hurted(Arrow::R);
		ptr->sunHao();
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
		cout<<pHeadquarter->GetColor()<<" "<<names[kindNo]<<" "<<no<<" shot";
		if(!emeny->isDead()) cout<<endl;
		if(emeny->isDead()){
			//cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
			cout<<" and killed "<<emeny->returnHead()->GetColor()<<" "<<emeny->names[emeny->getKindNo()]<<" "<<emeny->getNo()<<endl;
		}
	}
}

//bool Dragon::useBomb(Warrior* emeny)
//{
//	
//}
//void Dragon::attack(Warrior *opponent)
//{
//	
//
//}

Ninja::Ninja(Headquarter *p,int no_,int kindNo_):Warrior(p,no_,kindNo_)
{
	life=initialLifeValue[1];
	if(no_%3==0) {pWeapon[0]=new Sword(no_%3,this); hasSword=true;}
	if(no_%3==1) {pWeapon[0]=new Bomb(no_%3,this);hasBomb=true;}
	if(no_%3==2) {pWeapon[0]=new Arrow(no_%3,this);hasArrow=true;}
	if((no_+1)%3==0) {pWeapon[1]=new Sword((no_+1)%3,this);hasSword=true;}
	if((no_+1)%3==1) {pWeapon[1]=new Bomb((no_+1)%3,this);hasBomb=true;}
	if((no_+1)%3==2) {pWeapon[1]=new Arrow((no_+1)%3,this);hasArrow=true;}
	//pWeapon[1]=new Weapon((no_+1)%3,this);
}
void Ninja::PrintResult(int nTime)
{
	Warrior::PrintResult(nTime);
	//cout<<"It has a "<<pWeapon[0]->names[Warrior::no%3]<<" and a "<<pWeapon[1]->names[(Warrior::no+1)%3]<<endl;
}

int Ninja::getSwordForce()
{
	if(hasSword){
		Weapon* temp;
		if(pWeapon[0]->getKindNo()==0)
		temp=pWeapon[0];
		else temp=pWeapon[1];
		return temp->getForce();
	}
	else return 0;
}

void Ninja::printWeapon()
{
	if(pWeapon[0]!=NULL)
	{
		if(pWeapon[0]->shiXiao()){
			if(pWeapon[0]->getKindNo()==0)hasSword=false;
			if(pWeapon[0]->getKindNo()==1)hasBomb=false;
			if(pWeapon[0]->getKindNo()==2)hasArrow=false;
			pWeapon[0]=NULL;
		}
	}
	if(pWeapon[1]!=NULL)
	{
		if(pWeapon[1]->shiXiao()){
			if(pWeapon[1]->getKindNo()==0)hasSword=false;
			if(pWeapon[1]->getKindNo()==1)hasBomb=false;
			if(pWeapon[1]->getKindNo()==2)hasArrow=false;
			pWeapon[1]=NULL;}
	}

	if(pWeapon[0]!=NULL && pWeapon[1]!=NULL)
	{
			int i=pWeapon[0]->getKindNo();
			int j=pWeapon[1]->getKindNo();
			cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
			if(i>j)
			{
				pWeapon[0]->printInfo();cout<<",";
				pWeapon[1]->printInfo();	
			}
			else {pWeapon[1]->printInfo();cout<<",";
				  pWeapon[0]->printInfo();}
			cout<<endl;
	}
	else if(pWeapon[0]!=NULL&&pWeapon[1]==NULL)
	{
		/*if(pWeapon[0]->getKindNo()==0){hasSword=true;hasBomb=false;hasArrow=false;}
		if(pWeapon[0]->getKindNo()==1){hasSword=false;hasBomb=true;hasArrow=false;}
		if(pWeapon[0]->getKindNo()==2){hasSword=false;hasBomb=false;hasArrow=true;}*/
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[0]->printInfo();cout<<endl;
	}
	else if(pWeapon[1]!=NULL&&pWeapon[0]==NULL)
	{
		/*if(pWeapon[1]->getKindNo()==0){hasSword=true;hasBomb=false;hasArrow=false;}
		if(pWeapon[1]->getKindNo()==1){hasSword=false;hasBomb=true;hasArrow=false;}
		if(pWeapon[1]->getKindNo()==2){hasSword=false;hasBomb=false;hasArrow=true;}*/
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[1]->printInfo();cout<<endl;
	}
	else if(pWeapon[0]==NULL&&pWeapon[1]==NULL)
	{
		hasSword=false;hasBomb=false;hasArrow=false;
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has no weapon"<<endl;
	}
}

void Ninja::attack(Warrior* oponent,int h)
{
	Lion* ptr=dynamic_cast<Lion*>(oponent);
	if(ptr)
	{
		ptr->preLife=ptr->getLife();	
	}
	int harm;
	Weapon* temp;
	if(hasSword)
	{   
		if(pWeapon[0]!=NULL){
		if(pWeapon[0]->getKindNo()==0)
			temp=pWeapon[0];}
		if(pWeapon[1]!=NULL){
		if(pWeapon[1]->getKindNo()==0)
		     temp=pWeapon[1];
		}
		 harm=getForce()+temp->getForce();
		 temp->sunHao();
	}
	else harm=getForce();
	oponent->hurted(harm);
	//if(!oponent->isDead())
       oponent->fightBack(this,h);
}

void Ninja::fightBack(Warrior* attacker,int h)
{
}

void Ninja::shootEnemy(Warrior* emeny,int h)
{
	Weapon *temp;
	if(pWeapon[0]!=NULL&&pWeapon[0]->getKindNo()==2)
		temp=pWeapon[0];
	else temp=pWeapon[1];
	Arrow *ptr=dynamic_cast<Arrow*>(temp);
	if(ptr->getCount()>0)
	{
		emeny->hurted(Arrow::R);
		ptr->sunHao();
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
		cout<<pHeadquarter->GetColor()<<" "<<names[kindNo]<<" "<<no<<" shot";
		if(!emeny->isDead()) cout<<endl;
		if(emeny->isDead()){
			//cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
			cout<<" and killed "<<emeny->returnHead()->GetColor()<<" "<<emeny->names[emeny->getKindNo()]<<" "<<emeny->getNo();
			cout<<endl;
		}
	}
}


Iceman::Iceman(Headquarter *p,int no_,int kindNo_):Warrior(p,no_,kindNo_)
{
	life=initialLifeValue[2];
	step=0;
	if(no_%3==0) {pWeapon=new Sword(no_%3,this); hasSword=true;}
	if(no_%3==1) {pWeapon=new Bomb(no_%3,this);hasBomb=true;}
	if(no_%3==2) {pWeapon=new Arrow(no_%3,this);hasArrow=true;}
}
void Iceman::PrintResult(int nTime)
{
	Warrior::PrintResult(nTime);
	//cout<<"It has a "<<pWeapon->names[Warrior::no%3]<<endl;
}

int Iceman::getSwordForce()
{
	if(hasSword){
		return pWeapon->getForce();
	}
	else return 0;
}

int Iceman::goForward(BattleField &bfield,int time)
{
	step++;
	Warrior::goForward(bfield,time);
	if(step==2)
	{
		step=0;
		if(life-9>0)
			life-=9;
		else life=1;
		force+=20;
	}
	return 1;
}

void Iceman::attack(Warrior* oponent,int h)
{
	Lion* ptr=dynamic_cast<Lion*>(oponent);
	if(ptr)
	{
		ptr->preLife=ptr->getLife();	
	}
	int harm;
	if(hasSword)
	{   
		 harm=getForce()+pWeapon->getForce();
		 pWeapon->sunHao();
	}
	else harm=getForce();
	oponent->hurted(harm);
	//if(!oponent->isDead())
       oponent->fightBack(this,h);
}

void Iceman::printWeapon()
{
	if(pWeapon!=NULL)
	{
		if(!pWeapon->shiXiao())
		{
			cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
			pWeapon->printInfo();
			cout<<endl;
		}
		else 
		{
			hasSword=false;hasBomb=false;hasArrow=false;
			cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has no weapon"<<endl;
			pWeapon=NULL;
		}
	}
	else {
		hasSword=false;hasBomb=false;hasArrow=false;
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has no weapon"<<endl;}
}

void Iceman::fightBack(Warrior* attacker,int h)
{
	Lion* ptr=dynamic_cast<Lion*>(attacker);
	if(ptr)
	{
		ptr->preLife=ptr->getLife();	
	}
	if(!this->isDead())
	{
	int harm;
	int force=getForce()/2;
	if(hasSword)
	{
		harm=force+pWeapon->getForce();
		pWeapon->sunHao();
	}
	else harm=force;
	attacker->hurted(harm);
	cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
	cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" "<<"fought back against "<<attacker->returnHead()->GetColor()
	<<" "<<attacker->names[attacker->getKindNo()]<<" "<<attacker->getNo()<<" in city "<<cityNo<<endl;
	}
}

void Iceman::shootEnemy(Warrior* emeny,int h)
{
	Arrow *ptr=dynamic_cast<Arrow*>(pWeapon);
	if(ptr->getCount()>0)
	{
		emeny->hurted(Arrow::R);
		ptr->sunHao();
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
		cout<<pHeadquarter->GetColor()<<" "<<names[kindNo]<<" "<<no<<" shot";
		if(!emeny->isDead()) cout<<endl;
		if(emeny->isDead()){
			//cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
			cout<<" and killed "<<emeny->returnHead()->GetColor()<<" "<<emeny->names[emeny->getKindNo()]<<" "<<emeny->getNo();
			cout<<endl;
		}
	}
}

Lion::Lion(Headquarter *p,int no_,int kindNo_):Warrior(p,no_,kindNo_)
{
	life=initialLifeValue[3];
	loyalty=pHeadquarter->getLifeValue();
}
void Lion::PrintResult(int nTime)
{
	Warrior::PrintResult(nTime);
	cout<<"Its loyalty is "<<getLoyalty()<<endl;
}

void Lion::attack(Warrior* oponent,int h)
{
	int harm;
	 harm=getForce();
	 Lion* ptr=dynamic_cast<Lion*>(oponent);
	if(ptr)
	{
		ptr->preLife=ptr->getLife();	
	}
    oponent->hurted(harm);
       oponent->fightBack(this,h);
}

void Lion::fightBack(Warrior* attacker,int h)
{
	Lion* ptr=dynamic_cast<Lion*>(attacker);
	if(ptr)
	{
		ptr->preLife=ptr->getLife();	
	}
	if(!this->isDead())
	{
	int harm;
    harm=getForce()/2;
	attacker->hurted(harm);
	cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
	cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" "<<"fought back against "<<attacker->returnHead()->GetColor()
		<<" "<<attacker->names[attacker->getKindNo()]<<" "<<attacker->getNo()<<" in city "<<cityNo<<endl;
	}
	//else if(this->isDead())//如果lion被杀死
	//{
	//	int l=attacker->getLife();
	//	l+=preLife;
	//	attacker->setLife(l);
	//}
}

void Lion::printWeapon()
{
	cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has no weapon"<<endl;
}
Wolf::Wolf(Headquarter *p,int no_,int kindNo_):Warrior(p,no_,kindNo_)
{
	life=initialLifeValue[4];
	pWeapon[0]=NULL;  //0为sword  1为bomb 2为arrow
	pWeapon[1]=NULL;
	pWeapon[2]=NULL;
}

int Wolf::getSwordForce()
{
	if(hasSword){
		Weapon* temp;
		if(pWeapon[0]->getKindNo()==0)
			temp=pWeapon[0];
		else if(pWeapon[1]->getKindNo()==0)
			temp=pWeapon[1];
		else temp=pWeapon[2];
		return temp->getForce();
	}
	else return 0;
}

 void Wolf::shootEnemy(Warrior* emeny,int h)
{
	Arrow *ptr=dynamic_cast<Arrow*>(pWeapon[2]);
	if(ptr->getCount()>0)
	{
		emeny->hurted(Arrow::R);
		ptr->sunHao();
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
		cout<<pHeadquarter->GetColor()<<" "<<names[kindNo]<<" "<<no<<" shot";
		if(!emeny->isDead()) cout<<endl;
		if(emeny->isDead()){
			//cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"35 ";
			cout<<" and killed "<<emeny->returnHead()->GetColor()<<" "<<emeny->names[emeny->getKindNo()]<<" "<<emeny->getNo();
			cout<<endl;
		}
	}

}



void Wolf::getWeapon(Warrior* war)
{
	Dragon* ptr1=dynamic_cast<Dragon*>(war);
	Ninja* ptr2=dynamic_cast<Ninja*>(war);
	Iceman* ptr3=dynamic_cast<Iceman*>(war);
	Lion* ptr4=dynamic_cast<Lion*>(war);
	Wolf* ptr5=dynamic_cast<Wolf*>(war);
	if(ptr1)
	{
		if(ptr1->pWeapon!=NULL)
		{
			int kind=ptr1->pWeapon->getKindNo();
			if(pWeapon[kind]==NULL)
				pWeapon[kind]=ptr1->pWeapon;
		}
	}
	if(ptr3)
	{
		if(ptr3->pWeapon!=NULL)
		{
			int kind=ptr3->pWeapon->getKindNo();
			if(pWeapon[kind]==NULL)
				pWeapon[kind]=ptr3->pWeapon;
		}
	}
	if(ptr2)
	{
		if(ptr2->pWeapon[0]!=NULL)
		{
			int kind=ptr2->pWeapon[0]->getKindNo();
			if(pWeapon[kind]==NULL)
				pWeapon[kind]=ptr2->pWeapon[0];
		}
		if(ptr2->pWeapon[1]!=NULL)
		{
			int kind=ptr2->pWeapon[1]->getKindNo();
			if(pWeapon[kind]==NULL)
				pWeapon[kind]=ptr2->pWeapon[1];
		}
	}
	if(ptr4) return;
	if(ptr5)
	{
		if(ptr5->pWeapon[0]!=NULL)
		{
			int kind=ptr5->pWeapon[0]->getKindNo();
			if(pWeapon[kind]==NULL)
				pWeapon[kind]=ptr5->pWeapon[0];
		}
		if(ptr5->pWeapon[1]!=NULL)
		{
			int kind=ptr5->pWeapon[1]->getKindNo();
			if(pWeapon[kind]==NULL)
				pWeapon[kind]=ptr5->pWeapon[1];
		}
		if(ptr5->pWeapon[2]!=NULL)
		{
			int kind=ptr5->pWeapon[2]->getKindNo();
			if(pWeapon[kind]==NULL)
				pWeapon[kind]=ptr5->pWeapon[2];
		}
	}
	if(pWeapon[0]!=NULL) hasSword=true;
	if(pWeapon[1]!=NULL) hasBomb=true;
	if(pWeapon[2]!=NULL) hasArrow=true;
}

void Wolf::attack(Warrior* oponent,int h)
{
	int harm;
	if(hasSword)
	{   
		 harm=getForce()+pWeapon[0]->getForce();
		 pWeapon[0]->sunHao();
	}
	else harm=getForce();
	oponent->hurted(harm);
	//if(!oponent->isDead())
       oponent->fightBack(this,h);
	   if(oponent->isDead())
		   getWeapon(oponent);
}

void Wolf::fightBack(Warrior* attacker,int h)
{
	if(!this->isDead())
	{
		int harm;
		int force=getForce()/2;
		if(hasSword)
		{
			harm=force+pWeapon[0]->getForce();
			pWeapon[0]->sunHao();
			//if(pWeapon[0]->shiXiao())
		}
		else harm=force;
		attacker->hurted(harm);
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" "<<"fought back against "<<attacker->returnHead()->GetColor()
		<<" "<<attacker->names[attacker->getKindNo()]<<" "<<attacker->getNo()<<" in city "<<cityNo<<endl;
		if(attacker->isDead())
			getWeapon(attacker);
	}
}

void Wolf::printWeapon()
{
	if(pWeapon[0]!=NULL)
	{
		if(pWeapon[0]->shiXiao()){
			pWeapon[0]=NULL;
			hasSword=false;
		}
	}
	if(pWeapon[1]!=NULL)
	{
		if(pWeapon[1]->shiXiao()){
			pWeapon[1]=NULL;
			hasBomb=false;
		}
	}
	if(pWeapon[2]!=NULL)
	{
		if(pWeapon[2]->shiXiao()){
			pWeapon[2]=NULL;
			hasArrow=false;
		}
	}

	if(pWeapon[0]!=NULL&&pWeapon[1]!=NULL&&pWeapon[2]!=NULL)
	{
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
				pWeapon[2]->printInfo();cout<<",";
				pWeapon[1]->printInfo();cout<<",";	
				pWeapon[0]->printInfo();cout<<endl;
	}
	else if(pWeapon[0]!=NULL&&pWeapon[1]==NULL&&pWeapon[2]==NULL)
	{
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[0]->printInfo();cout<<endl;
	}
	else if(pWeapon[1]!=NULL&&pWeapon[2]==NULL&&pWeapon[0]==NULL)
	{
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[1]->printInfo();cout<<endl;
	}
	else if(pWeapon[2]!=NULL&&pWeapon[1]==NULL&&pWeapon[0]==NULL)
	{
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[2]->printInfo();cout<<endl;
	}
	else if(pWeapon[0]!=NULL&&pWeapon[1]!=NULL&&pWeapon[2]==NULL)
	{
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[1]->printInfo();cout<<",";
		pWeapon[0]->printInfo();cout<<endl;
	}
	else if(pWeapon[0]!=NULL&&pWeapon[2]!=NULL&&pWeapon[1]==NULL)
	{
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[2]->printInfo();cout<<",";
		pWeapon[0]->printInfo();cout<<endl;
	}
	else if(pWeapon[1]!=NULL&&pWeapon[2]!=NULL&&pWeapon[0]==NULL)
	{
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has ";
		pWeapon[2]->printInfo();cout<<",";
		pWeapon[1]->printInfo();cout<<endl;
	}
	else if(pWeapon[1]==NULL&&pWeapon[2]==NULL&&pWeapon[0]==NULL)
	{
		hasSword=false;hasBomb=false;hasArrow=false;
		cout<<returnHead()->GetColor()<<" "<<names[kindNo]<<" "<<no<<" has no weapon"<<endl;
	}
}


void BattleField::start(int m,int n)//m为司令部生命元，n为司令部间城市数
{
	N=n;
	Headquarter *RedHead,*BlueHead;//如果不是指针，开辟内存，函数结束后就被释放了
	RedHead=new Headquarter();
	BlueHead=new Headquarter();
	RedHead->Init(0,m);
	BlueHead->Init(1,m);
	phead[RED]=RedHead;
	phead[BLUE]=BlueHead;
	pcity=new City*[n+2];
	pcity[0]=RedHead;
	pcity[0]->setNo(0);
	pcity[n+1]=BlueHead;
	pcity[n+1]->setNo(n+1);
	for(int i=1;i<=N;i++)
	{
		pcity[i]=new City();
		pcity[i]->setNo(i);
	}
}

//BattleField::~BattleField()
//{
//
//	delete phead[RED];
//	delete phead[BLUE];
//	for(int i=1;i<=N;i++)
//	{
//		delete pcity[i];
//	}
//}

void BattleField::lionRun(int time)
{
	int h=time/60; 
	for(int i=0;i<=N;i++)
	{
		if(pcity[i]->pWarrior[RED]!=NULL)
		{
			Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[RED]);
			if(ptr&&ptr->getLoyalty()<=0){
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"05 ";
				cout<<"red lion "<<ptr->getNo()<<" ran away"<<endl;
				pcity[i]->pWarrior[RED]=NULL;
			}
		}
	}
	for(int i=1;i<=N+1;i++)
	{
		if(pcity[i]->pWarrior[BLUE]!=NULL)
		{
			Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[BLUE]);
			if(ptr&&ptr->getLoyalty()<=0){
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"05 ";
				cout<<"blue lion "<<ptr->getNo()<<" ran away"<<endl;
				pcity[i]->pWarrior[BLUE]=NULL;
			}
		}
	}
}
void BattleField::collectLife(int time)
{
	for(int i=1;i<=N;i++)
	{
		if(pcity[i]->pWarrior[RED]!=NULL^pcity[i]->pWarrior[BLUE]!=NULL)
		{
			if(pcity[i]->pWarrior[RED]!=NULL)
			{
				int h=time/60; 
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"30 ";
				pcity[i]->pWarrior[RED]->getCityElement();
			}
			else 
			{
				int h=time/60; 
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"30 ";
				pcity[i]->pWarrior[BLUE]->getCityElement();
			}
		}
	}
}

void BattleField::shootBattle(int time)
{
	int h=time/60;
	for(int i=0;i<=N+1;i++)
	{
		
		if(pcity[i]->pWarrior[RED]!=NULL && i<N && pcity[i+1]->pWarrior[BLUE]!=NULL)
		{
			if(pcity[i]->pWarrior[RED]->hasArrow)
				pcity[i]->pWarrior[RED]->shootEnemy(pcity[i+1]->pWarrior[BLUE], h);
		}
		if(pcity[i]->pWarrior[BLUE]!=NULL && i>1 && pcity[i-1]->pWarrior[RED]!=NULL)
		{
			if(pcity[i]->pWarrior[BLUE]->hasArrow)
				pcity[i]->pWarrior[BLUE]->shootEnemy(pcity[i-1]->pWarrior[RED],h);
		}	
	}
}

void BattleField::bombBattle(int time)
{
	int h=time/60;
	for(int i=1;i<=N;i++)
	{
		if(pcity[i]->pWarrior[RED]!=NULL && pcity[i]->pWarrior[BLUE]!=NULL)
		{
			if(!pcity[i]->pWarrior[RED]->isDead()&&!pcity[i]->pWarrior[BLUE]->isDead())
			{
			if(pcity[i]->pWarrior[RED]->hasBomb)
			{
				if(pcity[i]->pWarrior[RED]->useBomb(pcity[i]->pWarrior[BLUE])){
					pcity[i]->pWarrior[RED]->setLife(0);
					pcity[i]->pWarrior[BLUE]->setLife(0);
					cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"38 ";
					cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()
						<<" used a bomb and killed blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()<<endl;
					pcity[i]->pWarrior[RED]=NULL;
					pcity[i]->pWarrior[BLUE]=NULL;
				}
			}
			if(pcity[i]->pWarrior[BLUE]!=NULL){
			if(pcity[i]->pWarrior[BLUE]->hasBomb)
			{
				if(pcity[i]->pWarrior[BLUE]->useBomb(pcity[i]->pWarrior[RED])){
					pcity[i]->pWarrior[BLUE]->setLife(0);
					pcity[i]->pWarrior[RED]->setLife(0);
					cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"38 ";
					cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()
						<<" used a bomb and killed red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()<<endl;
					pcity[i]->pWarrior[RED]=NULL;
					pcity[i]->pWarrior[BLUE]=NULL;
				}
			
			}
			}
			}
		}
	}
}

void BattleField::Battle(int time)
{
	int h=time/60; 
	for(int i=1;i<=N;i++)
	{
		if(pcity[i]->pWarrior[RED]!=NULL&&pcity[i]->pWarrior[BLUE]!=NULL)
		{
			//如果城市里有一个武士已被敌方射死
			if(!pcity[i]->pWarrior[RED]->isDead() && pcity[i]->pWarrior[BLUE]->isDead())//只有红武士存货
			{
				pcity[i]->preWin=pcity[i]->curWin;
				pcity[i]->curWin=1;
				pcity[i]->pWarrior[RED]->win=true;
				///pcity[i]->pWarrior[RED]->winTheBattle();//dragon的士气增减
				//pcity[i]->pWarrior[BLUE]->winTheBattle();//dragon的士气增减
				pcity[i]->pWarrior[RED]->cityElement+=pcity[i]->element;
							pcity[i]->element=0;

				if((pcity[i]->flag==0 && pcity[i]->no%2!=0)||pcity[i]->flag==1)
				{
					Dragon* ptr=dynamic_cast<Dragon*>(pcity[i]->pWarrior[RED]);//红武士发起进攻
					if(ptr&&ptr->getMorale()>0.8&& !ptr->isDead())
					{
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()<<" yelled in city "<<i<<endl;
					}
				}	

				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
				cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()
				<<" earned "<<pcity[i]->pWarrior[RED]->cityElement<<" "<<"elements for his headquarter"<<endl;
				//获取武器
				Wolf* ptr=dynamic_cast<Wolf*>(pcity[i]->pWarrior[RED]);
				if(ptr)
				ptr->getWeapon(pcity[i]->pWarrior[BLUE]);		
			}
			else if(pcity[i]->pWarrior[RED]->isDead() && !pcity[i]->pWarrior[BLUE]->isDead())//只有兰武士存活
			{
				pcity[i]->preWin=pcity[i]->curWin;
				pcity[i]->curWin=2;
				pcity[i]->pWarrior[BLUE]->win=true;
				//pcity[i]->pWarrior[RED]->winTheBattle();//dragon的士气增减
				//pcity[i]->pWarrior[BLUE]->winTheBattle();//dragon的士气增减
				pcity[i]->pWarrior[BLUE]->cityElement+=pcity[i]->element;
							pcity[i]->element=0;
				if((pcity[i]->flag==0 && pcity[i]->no%2==0)||pcity[i]->flag==2)//蓝武士发起进攻
				{
					Dragon* ptr=dynamic_cast<Dragon*>(pcity[i]->pWarrior[BLUE]);
					if(ptr&&ptr->getMorale()>0.8&& !ptr->isDead()){
					cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
					cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()<<" yelled in city "<<i<<endl;}
				}
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
				cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()
				<<" earned "<<pcity[i]->pWarrior[BLUE]->cityElement<<" "<<"elements for his headquarter"<<endl;
				Wolf* ptr=dynamic_cast<Wolf*>(pcity[i]->pWarrior[BLUE]);
				if(ptr)
					ptr->getWeapon(pcity[i]->pWarrior[RED]);
			}


			if(!pcity[i]->pWarrior[RED]->isDead() && !pcity[i]->pWarrior[BLUE]->isDead())//都没死，以防有武士被提前射死
			{
				if((pcity[i]->flag==0 && pcity[i]->no%2!=0)||pcity[i]->flag==1)//红武士发起进攻
				{
					cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
					cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()
					<<" attacked blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()
						<<" in city "<<i<<" with "<<pcity[i]->pWarrior[RED]->getLife()<<" elements and force "<<pcity[i]->pWarrior[RED]->getForce()<<endl;
					pcity[i]->pWarrior[RED]->attack(pcity[i]->pWarrior[BLUE],h);
					pcity[i]->pWarrior[RED]->battled=true;
					pcity[i]->pWarrior[BLUE]->battled=true;
					//判断胜负，输出死亡
					if(pcity[i]->pWarrior[RED]->isDead())
					{
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()<<" was killed in city "<<i<<endl;
						pcity[i]->pWarrior[RED]->win=false;
						if(!pcity[i]->pWarrior[BLUE]->isDead())
						{
							Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[RED]);
							if(ptr)
							{
								int life=pcity[i]->pWarrior[BLUE]->getLife()+ptr->preLife;
								pcity[i]->pWarrior[BLUE]->setLife(life);
							}
							pcity[i]->pWarrior[BLUE]->win=true;
							pcity[i]->preWin=pcity[i]->curWin;
							pcity[i]->curWin=2;//当前蓝方胜利
							pcity[i]->pWarrior[BLUE]->cityElement=+pcity[i]->element;
							pcity[i]->element=0;
							cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
							cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()
							<<" earned "<<pcity[i]->pWarrior[BLUE]->cityElement<<" "<<"elements for his headquarter"<<endl;
						}
					}
					if(pcity[i]->pWarrior[BLUE]->isDead())
					{
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()<<" was killed in city "<<i<<endl;
						pcity[i]->pWarrior[BLUE]->win=false;	
						if(!pcity[i]->pWarrior[RED]->isDead())
						{
							Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[BLUE]);
							if(ptr)
							{
								int life=pcity[i]->pWarrior[RED]->getLife()+ptr->preLife;
								pcity[i]->pWarrior[RED]->setLife(life);
							}
							pcity[i]->pWarrior[RED]->win=true;
							pcity[i]->preWin=pcity[i]->curWin;
							pcity[i]->curWin=1;//当前红方胜利
							pcity[i]->pWarrior[RED]->cityElement+=pcity[i]->element;
							pcity[i]->element=0;
						}
					}

					if(pcity[i]->pWarrior[RED]!=NULL)
					pcity[i]->pWarrior[RED]->winTheBattle();//dragon的士气增减
					if(pcity[i]->pWarrior[BLUE]!=NULL)
					pcity[i]->pWarrior[BLUE]->winTheBattle();

					Dragon* ptr=dynamic_cast<Dragon*>(pcity[i]->pWarrior[RED]);
					if(ptr&&ptr->getMorale()>0.8&& !ptr->isDead())
					{
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()<<" yelled in city "<<i<<endl;
					}
					if(pcity[i]->pWarrior[RED]!=NULL)
					{
						if(!pcity[i]->pWarrior[RED]->isDead()&&pcity[i]->pWarrior[RED]->cityElement!=0)
						{
							cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
							cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()
							<<" earned "<<pcity[i]->pWarrior[RED]->cityElement<<" "<<"elements for his headquarter"<<endl;
						}
					}

				}
					
					//if(pcity[i]->pWarrior[RED]->isDead()&&!pcity[i]->pWarrior[BLUE]->isDead())
					//	pcity[i]->pWarrior[BLUE]->getCityElement();//其中一方胜利时获取城市生命元  否则都不获取
					//if(pcity[i]->pWarrior[BLUE]->isDead()&&!pcity[i]->pWarrior[RED]->isDead())
					//	pcity[i]->pWarrior[RED]->getCityElement();

				else if((pcity[i]->flag==0 && pcity[i]->no%2==0)||pcity[i]->flag==2)//蓝武士发起进攻
				{
					cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
					cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()
						<<" attacked red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()
						<<" in city "<<i<<" with "<<pcity[i]->pWarrior[BLUE]->getLife()<<" elements and force "<<pcity[i]->pWarrior[BLUE]->getForce()<<endl;
					pcity[i]->pWarrior[BLUE]->attack(pcity[i]->pWarrior[RED],h);
					pcity[i]->pWarrior[RED]->battled=true;
					pcity[i]->pWarrior[BLUE]->battled=true;
					//判断胜负，输出死亡

					if(pcity[i]->pWarrior[BLUE]->isDead())
					{
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()<<" was killed in city "<<i<<endl;
						pcity[i]->pWarrior[BLUE]->win=false;	
						if(!pcity[i]->pWarrior[RED]->isDead())
						{
							Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[BLUE]);
							if(ptr)
							{
								int life=pcity[i]->pWarrior[RED]->getLife()+ptr->preLife;
								pcity[i]->pWarrior[RED]->setLife(life);
							}
							pcity[i]->pWarrior[RED]->win=true;
							pcity[i]->preWin=pcity[i]->curWin;
							pcity[i]->curWin=1;//当前hong方胜利
							pcity[i]->pWarrior[RED]->cityElement+=pcity[i]->element;
							pcity[i]->element=0;
							if(pcity[i]->pWarrior[RED]!=NULL)
									pcity[i]->pWarrior[RED]->winTheBattle();//dragon的士气增减
							if(pcity[i]->pWarrior[BLUE]!=NULL)
									pcity[i]->pWarrior[BLUE]->winTheBattle();
							cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
							cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()
							<<" earned "<<pcity[i]->pWarrior[RED]->cityElement<<" "<<"elements for his headquarter"<<endl;
						}
					}

					if(pcity[i]->pWarrior[RED]->isDead())
					{
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]<<" "<<pcity[i]->pWarrior[RED]->getNo()<<" was killed in city "<<i<<endl;
						pcity[i]->pWarrior[RED]->win=false;
						if(!pcity[i]->pWarrior[BLUE]->isDead())
						{
							Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[RED]);
							if(ptr)
							{
								int life=pcity[i]->pWarrior[BLUE]->getLife()+ptr->preLife;
								pcity[i]->pWarrior[BLUE]->setLife(life);
							}
							pcity[i]->pWarrior[BLUE]->win=true;
							pcity[i]->preWin=pcity[i]->curWin;
							pcity[i]->curWin=2;//当前蓝方胜利
						    pcity[i]->pWarrior[BLUE]->cityElement+=pcity[i]->element;
							pcity[i]->element=0;
						}
					}

					//胜负处理,如果
						if(pcity[i]->pWarrior[RED]!=NULL)
						pcity[i]->pWarrior[RED]->winTheBattle();//dragon的士气增减
						if(pcity[i]->pWarrior[BLUE]!=NULL)
					   pcity[i]->pWarrior[BLUE]->winTheBattle();
						Dragon* ptr=dynamic_cast<Dragon*>(pcity[i]->pWarrior[BLUE]);
						if(ptr&&ptr->getMorale()>0.8&& !ptr->isDead())
						{
							cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
							cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()<<" yelled in city "<<i<<endl;
						}
						if(pcity[i]->pWarrior[BLUE]!=NULL){
							if(!pcity[i]->pWarrior[BLUE]->isDead()&&pcity[i]->pWarrior[BLUE]->cityElement!=0)
							{
								cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
								cout<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]<<" "<<pcity[i]->pWarrior[BLUE]->getNo()
								<<" earned "<<pcity[i]->pWarrior[BLUE]->cityElement<<" "<<"elements for his headquarter"<<endl;
							}
						}
					
				}		
		}//城市里两个士兵都没有死。
		
		//上述过程完后则城市里战斗如果不是平局必有一死一生或者平局
		if(pcity[i]->pWarrior[RED]!=NULL&&pcity[i]->pWarrior[BLUE]!=NULL)
		{
			if(!pcity[i]->pWarrior[RED]->isDead()&&!pcity[i]->pWarrior[BLUE]->isDead())
			{
				pcity[i]->curWin=0;
			}
		}
		if(pcity[i]->preWin==pcity[i]->curWin && pcity[i]->curWin!=0)
		{
					if(pcity[i]->curWin==1 && pcity[i]->flag!=1)
					{
						pcity[i]->flag=1;
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"red flag raised in city "<<i<<endl;
					}
					else if(pcity[i]->curWin==2 && pcity[i]->flag!=2)
					{
						pcity[i]->flag=2;
						cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"40 ";
						cout<<"blue flag raised in city "<<i<<endl;
					}
		}
		if(pcity[i]->pWarrior[RED]!=NULL)
		{
			if(!pcity[i]->pWarrior[RED]->isDead()&&pcity[i]->pWarrior[RED]->win==false&&pcity[i]->pWarrior[RED]->battled==true)
		{
			Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[RED]);
			if(ptr)
			{
				int l=ptr->getLoyalty();
				l-=Lion::k;
				ptr->setLoylty(l);
			}
		}
		}
		if(pcity[i]->pWarrior[BLUE]!=NULL)
		{
			if(!pcity[i]->pWarrior[BLUE]->isDead()&&pcity[i]->pWarrior[BLUE]->win==false&&pcity[i]->pWarrior[BLUE]->battled==true)
			{
				Lion* ptr=dynamic_cast<Lion*>(pcity[i]->pWarrior[BLUE]);
				if(ptr)
				{
					int l=ptr->getLoyalty();
					l-=Lion::k;
					ptr->setLoylty(l);
				}
			}
		}

	    }
	}
}


void BattleField::rewardLife()
{
	for(int i=0;i<=N;i++){
		if(pcity[i]->pWarrior[RED]!=NULL)
			if(pcity[i]->pWarrior[RED]->win && phead[RED]->getLifeValue()>=8) //pcity[i]->pWarrior[RED]->battled==true&&
			{
				int life=pcity[i]->pWarrior[RED]->getLife();
				life+=8;
				pcity[i]->pWarrior[RED]->setLife(life);
				phead[RED]->totalLifeValue-=8;
			}
	}
	for(int i=N;i>=1;i--){
		if(pcity[i]->pWarrior[BLUE]!=NULL)
			if(pcity[i]->pWarrior[BLUE]->win && phead[BLUE]->getLifeValue()>=8)//pcity[i]->pWarrior[RED]->battled==true&&
			{
				int life=pcity[i]->pWarrior[BLUE]->getLife();
				life+=8;
				pcity[i]->pWarrior[BLUE]->setLife(life);
				phead[BLUE]->totalLifeValue-=8;
			}
	}

}

void::BattleField::recycleElement()
{
	for(int i=1;i<=N;i++)
	{
		if(pcity[i]->pWarrior[RED]!=NULL)
		{
		if(pcity[i]->pWarrior[RED]->cityElement>0)
		{
			phead[RED]->totalLifeValue+=pcity[i]->pWarrior[RED]->cityElement;
			pcity[i]->pWarrior[RED]->cityElement=0;
		}	
		}	
	}
	for(int i=N;i>=1;i--)
	{
		if(pcity[i]->pWarrior[BLUE]!=NULL)
		{
		if(pcity[i]->pWarrior[BLUE]->cityElement>0)
		{
			phead[BLUE]->totalLifeValue+=pcity[i]->pWarrior[BLUE]->cityElement;
			pcity[i]->pWarrior[BLUE]->cityElement=0;
		}
		}
	}
}

void BattleField::run(int T)
{
	int t=0;
	while(T+1){	
	phead[RED]->Produce(t);
	phead[BLUE]->Produce(t);	
	if(phead[RED]->enemyNum>=2||phead[BLUE]->enemyNum>=2)
			break;
	if(t%60==5)
	{
		lionRun(t);
	}

	if(t%60==10){
		//从左向右输出  因此红方跟蓝方的行走方法有所不同
		for(int i=N;i>=0;i--)
		{
			if(pcity[i]->pWarrior[RED]!=NULL)
			pcity[i]->pWarrior[RED]->goForward(*this,t);
		}
		for(int i=1;i<N+2;i++)
		{
			if(pcity[i]->pWarrior[BLUE]!=NULL)
			pcity[i]->pWarrior[BLUE]->goForward(*this,t);
		}

		if(pcity[0]->pWarrior[BLUE]!=NULL)
		{
			int h=t/60; 
			if(!pcity[0]->pWarrior[BLUE]->arrivedOpposite)
			{
			cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"10";
			cout<<" "<<"blue "<<pcity[0]->pWarrior[BLUE]->names[pcity[0]->pWarrior[BLUE]->getKindNo()]
			<<" "<<pcity[0]->pWarrior[BLUE]->getNo()<<" reached red headquarter "<<"with "<<pcity[0]->pWarrior[BLUE]->getLife()<<" elements and force "<<pcity[0]->pWarrior[BLUE]->getForce()<<endl;
			pcity[0]->pWarrior[BLUE]->arrivedOpposite=true;
			}
			if(pcity[0]->enemyNum==2)
			{
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"10 ";
				cout<<"red headquarter was taken"<<endl;
			}
		}

		for(int i=1;i<=N;i++)
		{
			if(pcity[i]->pWarrior[RED]!=NULL)
			{
			int h=t/60; 
			cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"10";
			cout<<" "<<"red "<<pcity[i]->pWarrior[RED]->names[pcity[i]->pWarrior[RED]->getKindNo()]
			<<" "<<pcity[i]->pWarrior[RED]->getNo()<<" marched to city "<<i<<" with "<<pcity[i]->pWarrior[RED]->getLife()<<" elements and force "<<pcity[i]->pWarrior[RED]->getForce()<<endl;
			}
			if(pcity[i]->pWarrior[BLUE]!=NULL)
			{
			int h=t/60; 
			cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"10";
			cout<<" "<<"blue "<<pcity[i]->pWarrior[BLUE]->names[pcity[i]->pWarrior[BLUE]->getKindNo()]
			<<" "<<pcity[i]->pWarrior[BLUE]->getNo()<<" marched to city "<<i<<" with "<<pcity[i]->pWarrior[BLUE]->getLife()<<" elements and force "<<pcity[i]->pWarrior[BLUE]->getForce()<<endl;
			}

		}
		if(pcity[N+1]->pWarrior[RED]!=NULL)
		{
			int h=t/60; 
			if(!pcity[N+1]->pWarrior[RED]->arrivedOpposite)
			{
			cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"10";
			cout<<" "<<"red "<<pcity[N+1]->pWarrior[RED]->names[pcity[N+1]->pWarrior[RED]->getKindNo()]
			<<" "<<pcity[N+1]->pWarrior[RED]->getNo()<<" reached blue headquarter "<<"with "<<pcity[N+1]->pWarrior[RED]->getLife()<<" elements and force "<<pcity[N+1]->pWarrior[RED]->getForce()<<endl;
			pcity[N+1]->pWarrior[RED]->arrivedOpposite=true;
			}
			if(pcity[N+1]->enemyNum==2)
			{
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"10 ";
				cout<<"blue headquarter was taken"<<endl;
			}
		}	
	}

	
	//20分钟生产生命元
	if(t%60==20)
	{
		for(int i=1;i<=N;i++)
			pcity[i]->createLife();
	}
    
	if(t%60==30)
		collectLife(t);

	if(t%60==35)
		shootBattle(t);

	if(t%60==38)
		bombBattle(t);

	if(t%60==40)
	{
		Battle(t);
		rewardLife();
		recycleElement();
	}

	if(t%60==50)
	{
		int h=t/60; 
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"50 ";
		cout<<phead[RED]->totalLifeValue<<" elements in red headquarter"<<endl;
		cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"50 ";
		cout<<phead[BLUE]->totalLifeValue<<" elements in blue headquarter"<<endl;

		for(int i=1;i<=N;i++)
		{
			if(pcity[i]->pWarrior[RED]!=NULL)
			{
				if(pcity[i]->pWarrior[RED]->isDead())
					pcity[i]->pWarrior[RED]=NULL;
			}
			if(pcity[i]->pWarrior[BLUE]!=NULL)
			{
				if(pcity[i]->pWarrior[BLUE]->isDead())
					pcity[i]->pWarrior[BLUE]=NULL;
			}
		}
	}

	if(t%60==55)
	{
		int h=t/60;
		for(int i=0;i<=N+1;i++)
		{
			
			if(pcity[i]->pWarrior[RED]!=NULL){
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"55 ";
				pcity[i]->pWarrior[RED]->printWeapon();}
		}
		for(int i=0;i<=N+1;i++)
		{
			if(pcity[i]->pWarrior[BLUE]!=NULL){
				cout<<setw(3)<<setfill('0')<<h<<":"<<setw(2)<<"55 ";
				pcity[i]->pWarrior[BLUE]->printWeapon();}
		}
	}

	t++;
	T--;
	}
}

//===========================================================
int Arrow::R=0;//静态变量不初始化会造成link2001错误
int Lion::k=0;
string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
int Warrior::initialLifeValue [WARRIOR_NUM];//这里必须加上，否则有连接错误
int Warrior::initialForceValue[WARRIOR_NUM];
int Headquarter::makingSeq[2][WARRIOR_NUM] = { { 2,3,4,1,0 },{3,0,1,2,4} }; //两个司令部武士的制作顺序序列
string Weapon::names[WEAPON_NUM] = {"sword","bomb","arrow"};

int main()
{
	int t;
	int m;
	int n;
	int r;
	int k;
	int T;
	/*Headquarter RedHead,BlueHead;*/
	scanf("%d",&t);
	int nCaseNo = 1;
	while ( t -- ) {
		cout<<"Case "<<nCaseNo++<<":"<<endl;
		//printf("Case%d\n",nCaseNo++);
		scanf("%d %d %d %d %d",&m,&n,&r,&k,&T);
		//scanf("%d",&m);
		for( int i = 0;i < WARRIOR_NUM;i ++ )
			scanf("%d", & Warrior::initialLifeValue[i]);
		for( int i = 0;i < WARRIOR_NUM;i ++ )
			scanf("%d", & Warrior::initialForceValue[i]);
		BattleField newfield;
		newfield.start(m,n);
		Arrow::R=r;
		Lion::k=k;
		newfield.run(T);
		int nTime = 0;
	}
	return 0;
}
