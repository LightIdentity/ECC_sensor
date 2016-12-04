
//Function to return multiplicative inverse using Extended Euclid's Algorithm
// ux ≣ 1 mod v 
// Given u, v
//To find: x
//Returns -1 if MI does not exist or if Input is invalid

#define IsEven(X) (X& 0X01)==0
#define IsOdd(X) (X & 0X01)==1
#define swap(X,Y) X^=Y; Y^=X;X^=Y
int MulInv(int u,int v)
{

//returns u(inv) mod v
//assumes v is positive
if(v<0){
	return -1;
}
// Makes sure u>v

while(u<0 || u<v)
{
	u+=v;
}

int u1,u2,u3;
int k,t1,t2,t3;

//remove trailing 0s until atleast one of the numbers is odd
 
for(k=0;IsEven(u) && IsEven(v);++k)
{	u>>=1; v>>=1;
}
	
//initializations

u1=1;
u2=0;
u3=u;	// u3 equals u initially
t1=v;	// t1 is v initially
t2=u-1;	// t2 is u-1 init 
t3=v;	// t3 is v init

do{
	do{
		if(IsEven(u3)){
			if(IsOdd(u1)||IsOdd(u2)){
				u1+=v;
				u2+=u;
			}
			u1>>=1;
			u2>>=1;
			u3>>=1;
		}
		if(IsEven(t3)||u3<t3){
			swap(u1,t1);
			swap(u2,t2);
			swap(u3,t3);
		}

	}while(IsEven(u3));

	while(u1<t1||u2<t2){
		u1+=v;
		u2+=u;
	}
	
	u1-=t1;
	u2-=t2;
	u3-=t3;
	
 }while(t3>0);

 while(u1>=v&& u2>=u){
	u1-=v;
	u2-=u;
 }
 u1<<=k;
 u2<<=k;
 u3<<=k;
if(u3==1)
	return (u1);
else{
	//Not coprime
	 return -1;}
}
