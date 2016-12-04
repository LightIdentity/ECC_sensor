// Elliptic Curve Values: To be filled in according to NIST standards
// 2 2  97 19 5 1
#include <stdlib.h>
#include<time.h>
#include<stdio.h>
#include "encoder.h"
extern struct AffPoint G;
/*
NIST CURVE
#define a -3 // For E(a,b)
#define b 0X64210519e59c80e70fae9ab72243049feb8deecc146b9b1 // For E(a,b)
#define p 6277101735386680763835789423207666416083908700390324961279 // Large Prime number
#define n 19 // Order of elliptic curve
#define Gx 0x188da80eb03099f67cbf20eb43a18800f4ff0afd82ff1012 // Initial point G x co-ordinate
#define Gy 0x07192b95ffc8da78631011ed6b24cdd573f977a11e794811 // Initial point G y co-ordinate
*/
//#include "mminv.h"
//#include "pointmath.h"

long seed;
long PriB=11; 
struct AffPoint PubB={2580,1224};

/*
	Naming Convention:

	Public keys: 
		PubB, PubA
	Private keys:
		PriB, PriA
		
*/

void SeedGen(){
	seed= time(NULL);
}

void initialize()
{
	//Function prepares Public and Private keys for Alice and Bob
	//Calls functions private_key() and public_key() as required and initialises PubA, PubB, PriA and PriB
	//printf("Initialising...\n");

	G.x=Gx;
	G.y=Gy;

	PriB=PrivateKey();
	PubB = PublicKey(PriB);

}

unsigned m1,m2;

void  InputM()
{
	//unsigned m1,m2;
	// Input message
	//printf("Enter integer:\n");
	scanf("%u %u",&m1,&m2);
	//return m;
}

long PrivateKey()
{
	//Calculate Private key
	// Generate random integer less than n
	//printf("PriKey Calc...\n");
	return(rand()%n);
	
}

struct AffPoint PublicKey(long Pri)
{
	//Calculate Public key
	//printf("PubKeycalc...\n");
	struct AffPoint Pub = PointMul(G,Pri);
	return Pub;
	
}

struct EncryptedMessage encrypt(unsigned m1, unsigned m2)
{
	//generate k
	SeedGen();
	srand(seed+=seed);
	unsigned k=rand()%n;
	struct EncryptedMessage EM;
	
	//Calculate y
	struct AffPoint y;	

	y=PointMul(PubB,k);

	//printf("y is (%u,%u)\n",y.x,y.y);
	//Generate c and c0

	EM.c0=PointMul(G,k);
	EM.c.x=(y.x*m1)%p;
	EM.c.y=(y.y*m2)%p;
	
	//Encrypted message:
	//printf("Encrypt-\nc0.x is %u  c0.y is %u  cx is %u  cy is %u\n",EM.c0.x,EM.c0.y,EM.c.x,EM.c.y);	
	return EM;
}

struct AffPoint decrypt(struct EncryptedMessage EM )
{
	struct AffPoint y;
	//printf("Cipher:\n{c0x,c0y}{cx,cy} :{%u,%u,%u,%u}\n",EM.c0.x,EM.c0.y,EM.c.x,EM.c.y);
	struct AffPoint m;

	// Calculate y
	y=PointMul(EM.c0,PriB);
	//printf("Y:(%u,%u)\n",y.x,y.y);
	//m=(c1y1(inv) mod p, c2y2(inv) mod p)

	m.x= (((EM.c.x%p) * MulInv(y.x,p))%p);
	m.y= (((EM.c.y%p) * MulInv(y.y,p))%p);
	
	//printf("m1 = %u,m2 = %u\n",m1,m2);
	return(m);
	
	
	
}
/*

int main()
{
	initialize();
	InputM();
	struct EncryptedMessage E=encrypt(m1,m2);
	printf("In main, c0.x is %u c0.y is %u", E.c0.x,E.c0.y);
	struct AffPoint m= decrypt(E);
	printf("Decrypted Message: (%u, %u )\n",m.x,m.y);
	
	return 0;
}
  
*/

 
 
