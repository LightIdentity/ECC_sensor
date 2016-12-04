#define a 2 
#define b 2
#define p 7789
#define n 19 // Order of elliptic curve
#define Gx 5 // Initial point G x co-ordina
#define Gy 1

#define DataStartMsdu 0//4 //Index of MSDU from which sensor readings are stored
#define DataStartPsdu 9//13 //Index of MSDU from which sensor readings are stored


struct AffPoint{
	// Struct for point in Affine format (x,y)
	unsigned int x;
	unsigned int y;
};

struct EncryptedMessage{
	struct AffPoint c0;
	struct AffPoint c;
};

// Function Declarations

extern int MulInv();
extern void initialize();
extern long PrivateKey();
extern struct AffPoint PublicKey(long);
extern void InputM();
extern struct AffPoint decrypt();
extern struct EncryptedMessage encrypt(unsigned,unsigned);


extern void EncryptArray(unsigned char *Msdu);
extern  void FormPublicKeyPkt(void); 


extern void DecryptCipher(void);
extern void GetPublicKey(void);

struct AffPoint PointMul(struct AffPoint P, unsigned int k);
struct AffPoint PointAdd(struct AffPoint P, struct AffPoint Q);


extern unsigned char Cipher[];
extern volatile unsigned char Psdu[];
extern unsigned int  message[];
