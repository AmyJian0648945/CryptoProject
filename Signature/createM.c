
int main(void){
	uint8_t m8[modLength*2] = {0};
	uint16_t m[modLength] = {0};
	RNG(m8,modLength*2);
	printArray8(m8,"m8",modLength*2);
	from8to16(m8,m,modLength*2);
	printArray16(m,"m",modLength);
	
	}