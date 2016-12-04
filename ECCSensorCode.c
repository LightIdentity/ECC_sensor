//Header Files
#include "encoder.h"
#include "ieee802154.h"
#include "config.h"

unsigned char Cipher[aMaxMACFrameSize];

extern struct AffPoint PubB;
extern unsigned char Msdu[];
extern unsigned char NodeStatus;
extern unsigned char  MsduLength;
extern unsigned char CipherLength;


//Function Declarations
/*
void EncryptArray(unsigned char *Msdu,int size);
void FormPublicKeyPkt(void);
*/


//Function Definitions

void GetPublicKey(){
    //Gets base's public key and stores in PubB
    
    int i,j;
    i=DataStartPsdu;
    PubB.x=0;
    PubB.y=0;
    
    int keysize =sizeof(long);
    
    for(j=(keysize-1);j>=0;j--){
        PubB.x += Psdu[i+j];
        PubB.x<<=8;
      
    }
    i+=sizeof(PubB.x);
    
    for(j=(keysize-1);j>=0;j--){
        PubB.y += Psdu[i+j];
        PubB.y<<=8;
        
    }
}
    
void EncryptArray(unsigned char *Msdu){
    int i=0,j;
   
    
    struct EncryptedMessage m;
    for(i=0;i<DataStartMsdu;++i)
        Cipher[i]=Msdu[i];
    
    
    /*
     Msdu[0] = NodeStatus; Msdu[1] = NODE_TYPE;
    Msdu[2] = NODE_TYPE >> 8;Msdu[3] = PERIODIC_DATA_PKT;
    Msdu[4] = BatteryVoltage; Msdu[5] = BatteryVoltage >> 8;
    Msdu[6] = Temperature; Msdu[7] = AccRawData.x;
    Msdu[8] = AccRawData.x >> 8; Msdu[9] = AccRawData.y;
    Msdu[10] = AccRawData.y >> 8; Msdu[11] = AccRawData.z;
    Msdu[12] = AccRawData.z >> 8;
     */
    // DataStartMsdu = 4
    
    // 01,23,45, 6-0,
    for(j=0;j<=4;j+=2){   // condition expression changed from i<=4 to j<=4
        m=encrypt(Msdu[j],Msdu[j+1]);
         Cipher[i++]=m.c0.x;
         Cipher[i++]=(m.c0.x>>8);
         Cipher[i++]=m.c0.y;
         Cipher[i++]=(m.c0.y>>8);
         Cipher[i++]=m.c.x;
         Cipher[i++]=(m.c.x>>8);
         Cipher[i++]=m.c.y;
         Cipher[i++]=(m.c.y>>8);
        
    }
     
    /*
    m=encrypt(Msdu[4],Msdu[5]);
    Cipher[i++]=m.c0.x;
    Cipher[i++]=(m.c0.x>>8);
    Cipher[i++]=m.c0.y;
    Cipher[i++]=(m.c0.y>>8);
    Cipher[i++]=m.c.x;
    Cipher[i++]=(m.c.x>>8);
    Cipher[i++]=m.c.y;
    Cipher[i++]=(m.c.y>>8);
     
    */
    
    m=encrypt(Msdu[6],0);
    Cipher[i++]=m.c0.x;
    Cipher[i++]=(m.c0.x>>8);
    Cipher[i++]=m.c0.y;
    Cipher[i++]=(m.c0.y>>8);
    Cipher[i++]=m.c.x;
    Cipher[i++]=(m.c.x>>8);
    Cipher[i++]=m.c.y;
    Cipher[i++]=(m.c.y>>8);
    
            
    for(j=7;j<MsduLength-1;j+=2){  //i replaced by j in condition expression
        m=encrypt(Msdu[j],Msdu[j+1]);
         Cipher[i++]=m.c0.x;
         Cipher[i++]=(m.c0.x>>8);
         Cipher[i++]=m.c0.y;
         Cipher[i++]=(m.c0.y>>8);
         Cipher[i++]=m.c.x;
         Cipher[i++]=(m.c.x>>8);
         Cipher[i++]=m.c.y;
         Cipher[i++]=(m.c.y>>8);
        
    }
    
    /*
    
    
    m=encrypt(Msdu[7],Msdu[8]);
    Cipher[i++]=m.c0.x;
    Cipher[i++]=(m.c0.x>>8);
    Cipher[i++]=m.c0.y;
    Cipher[i++]=(m.c0.y>>8);
    Cipher[i++]=m.c.x;
    Cipher[i++]=(m.c.x>>8);
    Cipher[i++]=m.c.y;
    Cipher[i++]=(m.c.y>>8);
    
    m=encrypt(Msdu[9],Msdu[10]);
    Cipher[i++]=m.c0.x;
    Cipher[i++]=(m.c0.x>>8);
    Cipher[i++]=m.c0.y;
    Cipher[i++]=(m.c0.y>>8);
    Cipher[i++]=m.c.x;
    Cipher[i++]=(m.c.x>>8);
    Cipher[i++]=m.c.y;
    Cipher[i++]=(m.c.y>>8);
            
    
    m=encrypt(Msdu[11],Msdu[12]);
    Cipher[i++]=m.c0.x;
    Cipher[i++]=(m.c0.x>>8);
    Cipher[i++]=m.c0.y;
    Cipher[i++]=(m.c0.y>>8);
    Cipher[i++]=m.c.x;
    Cipher[i++]=(m.c.x>>8);
    Cipher[i++]=m.c.y;
    Cipher[i++]=(m.c.y>>8);
     
     */
    
     CipherLength=i;
     
     
}

