
#ifdef TEST_ON
	uint32_t R[33] = {0};
	R[0] = 0x0001;
	uint32_t m[5] = {0x998E281A,0xC543B079,0x2CE6387F,0xB2B16F3F,0x37AF2027};
	uint32_t y3[5] = {0x76B78EFD,0x12BC9C42,0x2A764F79,0x6182B5D3,0x7FBAB408};
	uint32_t x3[5] = {0x45264014,0xD54960DE,0xE62D7186,0x1EE34005,0xCDB7A16A};
	uint32_t Rinv[5] = {0};
	uint32_t mInv[33] = {0};
	uint32_t result[5] = {0};
	uint32_t R2[4] = {0};
	uint32_t Rinv2[4] = {0};
	uint32_t mInv2[4] = {0};
	uint32_t y2[4] = {0xC09,0x372C2F40,0x9DC6DEB2,0x988CE22F};
	uint32_t x2[4] = {0x140F,0xCFAAA648,0x2B1FDB47,0xA3F32302};
	uint32_t m2[4] = {0x1D56,0x10F19B72,0x9DED7165,0xE4D278FB};
 	uint32_t e2[2] = {0x12423,0x52312423};
	uint32_t result2[4] = {0};
	R2[0] = 0x00010000;
	modularInverse(R,m,Rinv,33,5);
	printArrayNoSpaces32(Rinv,5);
	modularInverse(R2,m2,Rinv2,4,4);
	printArrayNoSpaces32(Rinv2,4);
	montExp(x2,m2,e2,result2,4,4,2);
	printArrayNoSpaces32(result2,4);
	modularInverse(m,R,mInv,5,33);
	mont(x3,y3,m,mInv,result,5,33);
	printArrayNoSpaces32(result,5);
	modularInverse(m2,R2,mInv2,4,4);
	mont(x2,y2,m2,mInv2,result2,4,4);
	printArrayNoSpaces32(result2,4);
#endif /* TEST_ON */
