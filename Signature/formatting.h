// Reformatting the array //
void from8to16(uint8_t *input, uint16_t *output){
	int k;
	for (k=0;k<128;k++){
		uint16_t first8bits = ((uint16_t)input[2*k])<<8;
		uint16_t last8bits = (uint16_t)input[2*k+1];
		uint16_t newnumber = first8bits + last8bits;
		output[k] = newnumber;	
	}
}

void from16to8(uint16_t *input, uint8_t *output){
	int k;
	for (k=0;k<128;k++){
		uint8_t first8bits = (uint8_t)(input[k]>>8);
		uint8_t last8bits = (uint8_t)input[k];
		output[2*k] = first8bits;
		output[2*k+1] = last8bits;
	}
}
