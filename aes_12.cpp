#include<stdio.h>
void ShowWord(unsigned int w)
{
	for(int i = 1; i <= 8; i++)
	{
		unsigned int hexan = (w >> 32 - i*4) & 0xF;
		printf("%X", hexan);
	}
}

unsigned int RotWord(unsigned int w)
{
	//Dich vong trai 1 byte
	unsigned int byte1 = (w >> 24) & 0xFF;
	unsigned int byte234 = w & 0xFFFFFF;
	unsigned int rot = (byte234 << 8) | byte1;
	//printf("\n\tRotWord(%X) = ",w); ShowWord(rot);
	return rot;
}

unsigned int SubWord(unsigned int w)
{
	int S[] = {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 
				0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 
				0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15, 
				0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75, 
				0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84, 
				0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF, 
				0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8, 
				0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 
				0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73, 
				0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB, 
				0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79, 
				0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08, 
				0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A, 
				0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 
				0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF, 
				0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
			};
	unsigned int kq = 0;
	for(int i = 1; i <= 4; i++)	
	{
		unsigned int bytei = (w >> 32 - i*8) & 0xFF;
		unsigned int sub8 = S[bytei];
		kq = (kq << 8)|sub8;
	}
	//printf("\n\tSubWord(%X) = ",w); ShowWord(kq);
	return kq;
}

unsigned int XorRcon(unsigned int w, int j)
{     
     int Rc[] = {
                0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
                0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39
            };
	unsigned int byte1 = (w >> 24 ) & 0xFF;	
	unsigned int kqXor = (byte1 ^ Rc[j] ) & 0xFF;	
	unsigned int byte234 = w & 0xFFFFFF;	
	unsigned int kq = (kqXor << 24) | byte234;

	return kq;
}

unsigned int G(unsigned int w, int j)
{
	unsigned int rotW = RotWord(w);
	unsigned int subW = SubWord(rotW);
	unsigned int kq = XorRcon(subW, j);
	//printf("\n\tG(%X) = ",w); ShowWord(kq) ;
	return kq;
}

unsigned int* KeyExpansion(unsigned int Key[4])
{
	unsigned int *w = new unsigned int[44];
	w[0] = Key[0]; 	
	w[1] = Key[1]; 	
	w[2] = Key[2]; 	
	w[3] = Key[3];
	for(int i = 4; i < 44; i++)
	{
		if(i % 4 == 0) w[i] = G(w[i-1], i/4) ^ w[i-4];
		else w[i] = w[i-1]^ w[i-4];
		//printf("\nw[%d] = ", i); ShowWord(w[i]);
	}
	return w;
} 

unsigned int* AddRoundKey(unsigned int state[4], unsigned int *K)
{
	unsigned int *kq = new unsigned int[4];
	kq[0] = state[0] ^ K[0];
	kq[1] = state[1] ^ K[1];
	kq[2] = state[2] ^ K[2];
	kq[3] = state[3] ^ K[3];
//	printf("\nAddRoundKey\n");
//	for(int i=0; i<4; i++)
//	{ 
//		printf("\n\t"); ShowWord(kq[i]);
//	}
	return kq;
}

unsigned int* SubBytes(unsigned int state[4])
{
    unsigned int *kq = new unsigned int[4];
    for (int i = 0; i < 4; i++)
    	kq[i] = SubWord(state[i]);
//	printf("\nSubByte\n");
//	for(int i=0; i<4; i++)
//	{ 
//		printf("\n\t"); ShowWord(kq[i]);
//	}
    return kq;
}

unsigned int* ShiftRows(unsigned int state[4])
{
    unsigned int *kq = new unsigned int[4];
    for (int i = 0; i < 4; i++)
    {
		unsigned int byte1 = state[i] & 0xFF000000;
		unsigned int byte2 = state[(i+1)%4] & 0xFF0000;
		unsigned int byte3 = state[(i+2)%4] & 0xFF00;
		unsigned int byte4 = state[(i+3)%4] & 0xFF;
        kq[i] = byte1 | byte2 | byte3 | byte4;  // ghep ket qua
    }
//    printf("\nShiftRows:\n");
//	for(int i=0; i<4; i++)
//	{ 
//		printf("\n\t"); ShowWord(kq[i]);
//	}
    return kq;
}

unsigned int Nhan2(unsigned int w)
{
	unsigned int kq = w << 1;
	if(kq > 256) kq = kq ^ 0x11b;
	kq = kq & 0xFF;
	return kq;
}

unsigned int Nhan3(unsigned int w)
{
	unsigned int kq = w ^ Nhan2(w);
	kq = kq & 0xFF;
	return kq;
}

unsigned int NhanCot(unsigned int w)
{
    unsigned int kq;
    unsigned int byte1 = (w >> 24) & 0xFF;
    unsigned int byte2 = (w >> 16) & 0xFF;
    unsigned int byte3 = (w >> 8) & 0xFF;
    unsigned int byte4 = w & 0xFF;
	
	unsigned int kq1 = Nhan2(byte1) ^ Nhan3(byte2) ^ byte3 ^ byte4;
	unsigned int kq2 = byte1 ^ Nhan2(byte2) ^ Nhan3(byte3) ^ byte4;
	unsigned int kq3 = byte1 ^ byte2 ^ Nhan2(byte3) ^ Nhan3(byte4);
	unsigned int kq4 = Nhan3(byte1) ^ byte2 ^ byte3 ^ Nhan2(byte4);

    kq = (kq1 << 24) | (kq2 << 16) | (kq3 << 8) | kq4;
    //printf("\n\t"); ShowWord(kq);
    return kq;
}

unsigned int* MixColumns(unsigned int state[4])
{
    unsigned int *kq = new unsigned int[4];
	for (int i = 0; i < 4; i++) 
		kq[i] = NhanCot(state[i]);
    return kq;
}

void ShowMatrix(unsigned int w[4])
{
	for (int i = 0; i < 4; i++)
	{
		printf("\n\t"); ShowWord(w[i]);
	}
}

unsigned int* MahoaAES(unsigned int state[4], unsigned int key[4])
{
	unsigned int *w = KeyExpansion(key);
	state = AddRoundKey(state,&w[0]);
	for(int j = 1; j <= 9; j++)
	{
	state = SubBytes(state);
	state = ShiftRows(state);
	state = MixColumns(state);
	state = AddRoundKey(state, &w[4*j]);
	printf("\n Vong %d \n", j);
	 	ShowMatrix(state);

	}
	//Vong thu 10
	printf("\n Vong 10 \n");
	state = SubBytes(state);
	state = ShiftRows(state);	
	state = AddRoundKey(state, &w[40]);
	ShowMatrix(state);

	unsigned int *kq = new unsigned int[4];
	kq = state;
	return kq;
}


int main()
{
	//key= C281B1763B140EF7AB12EB2745F1F59F
	unsigned int w0 = 0xC281B176, w1 = 0x3B140EF7, w2 = 0xAB12EB27, w3 = 0x45F1F59F;
	unsigned int Key[] = {w0, w1, w2, w3};
	//input M = B104AADD 3AC293DF 787EFD2C F8065925
	unsigned int *state = new unsigned[4];
	state[0] = 0xB104AADD; state[1] = 0x3AC293DF; state[2] = 0x787EFD2C; state[3] = 0xF8065925;	
	//Bat dau test
	//ShowWord( w3 ) ; 	//test ham ShowWord
	//RotWord(w3) ;		//test ham RotWord
	//unsigned int rot = RotWord(w3);  // test ham WubWord
	//SubWord( rot ) ;
	//unsigned int g3 = G(w3, 1);  // test ham G
	//unsigned int *w = KeyExpansion(Key) ;// sinh khoa
//	state = AddRoundKey(state,Key) ;  //test ham AddRoundKey
//	state = SubBytes(state) ;		//test ham SubBytes
//	state = ShiftRows(state); 		//test ham Shiftrows
//	state = MixColumns(state);		//test ham MixColumns
	unsigned int *C = MahoaAES(state, Key) ;
	
	
	
//	unsigned int *C = MahoaAES(state, Key);
//	printf("\nBan ma:\n"); ShowMatrix(C);
//	unsigned int *M = GiaimaAES(C, Key);
//	printf("\nBan Giai ma:\n"); ShowMatrix(M);
}

