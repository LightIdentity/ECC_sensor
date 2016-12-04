// Functions for Point Arithmetic
//Requires function MulInv from mminv.c
/*
//Already defined in encryption program
#define a 2 // For E(a,b)
#define b 2 // For E(a,b)
#define p 17 // Large Prime number
#define n 19 // Order of elliptic curve
#define Gx 5 // Initial point G x co-ordinate
#define Gy 1 // Initial point G y co-ordinate
*/
//#include <stdlib.h>
//#include <time.h>
//#include <stdio.h>

#include "encoder.h"
int LeadingZeroCount(unsigned int k)
 {
         int count=0;
         int size=sizeof(k)*8; //Get number of bits
         while(k!=0)
         {
                 k>>=1;
                 count++;
         }
         return(size-count);
 
 }

int mod(int c,int d)
{
	if(c<0)
	{
	while(c<0)
		c+=d;
	return c;
	}
	else
	return c%d;
}

struct AffPoint PointMul(struct AffPoint P, unsigned int k)
{
        
    struct AffPoint R={-1,-1};    
    if(k>=n){
	unsigned int k2=mod(k,n);
	if(k2==0)
		return(R);
	else
		k=k2;
    }
    
    int i= LeadingZeroCount(k); 
    int length=sizeof(int)*8-i;
    unsigned mask=1;
        
    while(i>0){
        
        k<<=1;
        i--;
    }
    for(i=1;i<sizeof(int)*8;i++){
        mask<<=1;
    }
    
    for(i=0;i<length;++i)
    {    
        if(i==0) //First Iteration
		R=P;
	else{
        	//DOUBLE POINT
        	R=PointAdd(R,R);
	
        	if(k&mask)
        	{	    
            	//ADD POINT
            	R=PointAdd(R,P);
        	}
	}
        mask>>=1;            
    }
return R;
}



struct AffPoint PointAdd(struct AffPoint P, struct AffPoint Q)
{
	//returns P+Q
	int s=0;
	struct AffPoint R;	

	// CASE: P=Q Point Doubling
	if(P.x==Q.x && P.y==Q.y)
	{
		s=mod((mod((3*(P.x)*(P.x) + a),p)*MulInv((2*P.y),p)),p);
	}
	else
	{
		s=mod((mod((P.y-Q.y),p) * MulInv((P.x-Q.x),p)),p);

			
	}
	R.x = mod((s*s - P.x - Q.x),p);
	R.y = mod((s*(P.x - R.x) - P.y),p);
	return R;
}


struct AffPoint G={Gx,Gy};
