/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdint.h>
#include <inttypes.h>
#include "montgomery.h"
#include "asm_func.h"
#include "mp_arith.h"
#include "performance_counters.h"

uint32_t a[32];
uint32_t b[32];
uint32_t N[32];
uint32_t r[32];
uint32_t N_prime0[32];

int main()
{
    uint32_t res[32] = {0};
    init_platform();
	
    int i = 0;
    uint32_t a1[32] = {0x4b0afbba, 0xb3270d27, 0xfef81247, 0x9c028fde, 0x873a8d9d, 0x74150080, 0x21c3a9a5, 0x04b6f5a7, 0x465ab66a, 0xf0af88c6, 0x4210ad08, 0x3178b33b, 0x520fa2fe, 0xfabbcfe3, 0x51a66eb0, 0x1c1a6807, 0x57dc7837, 0x651c9e46, 0x21c0b44a, 0xaba36ace, 0x82f4820e, 0xf6a0e49f, 0xf489dab2, 0x93df7bae, 0x74203419, 0xbd13b6fd, 0x4135e9f9, 0x046d1052, 0xc0a7108c, 0x191a0cc0, 0x607fc341, 0x2c261c9b};
    uint32_t b1[32] = {0xf1d2b3e2, 0x925c0577, 0x825c7977, 0x0cc1e17c, 0x179e2466, 0x0abf48a4, 0x839b99e3, 0x7b52c351, 0xc643edb7, 0x51c28d81, 0xdb0242ba, 0x87069825, 0xb4e0aae5, 0x87b90b9b, 0x8026f877, 0xfd3b0911, 0x67498835, 0x9e56065e, 0x634a379e, 0xc2281d7e, 0x7793f6b9, 0x4a15cd7c, 0xd5d7c345, 0xdf354cd4, 0x5dfdb200, 0x2a7f0547, 0x88da4e10, 0xedf5af44, 0x2982780e, 0x8ac21ffd, 0xb5118fec, 0x63a68886};
    uint32_t N1[32] = {0x575bb461, 0x1a3042d4, 0x95d708c1, 0x9a02f06b, 0x7582491e, 0x947f45f7, 0x6b785070, 0xa35e54c5, 0xba07c851, 0x29fb66a2, 0xd893feb0, 0xa2ebe291, 0x08a64bd1, 0x5ab21338, 0xb451c21d, 0x330e7700, 0xa812c547, 0x633354b3, 0x9439c77f, 0x7de168b7, 0xd199da8f, 0x44fdd142, 0x8ce3e7f1, 0xb807a6ae, 0x5173de8c, 0xe2fe1c98, 0x4d51689c, 0x5cfa7887, 0x54f0f9b9, 0x4b71a0e2, 0xbae33525, 0xb5d738a0};
    uint32_t n_prime1[32] = {0x16f2105f, 0xfdddd2ad, 0x95f75ac0, 0xa8c30990, 0xf655e370, 0x8720517c, 0x886839eb, 0xabeb253b, 0xdb6a3b3a, 0x6bf8258a, 0x3a62d68d, 0x6a346d25, 0x208996eb, 0x217db098, 0xa2f73e93, 0x24b76402, 0xcd4545e4, 0x97a3727b, 0x7ab207b7, 0x913832ef, 0x9996349c, 0xda3718a1, 0xab631b76, 0x694a7470, 0x93cb8bfa, 0x408f5cc3, 0xd34ef659, 0x57aa7bc7, 0xa1a8404b, 0x6730f4f7, 0xbb489ebf, 0x401b0f1d};
    xil_printf("\n\n\n\n\n\n");

    init_performance_counters(1);
    uint32_t t1= get_cycle_counter();
    mont(a1, b1, N1, n_prime1, res, 32);
    uint32_t t1_stop= get_cycle_counter();
    xil_printf("\nmont_mul_test1 = 0x");
        for( i = 31; i >=0 ; i--){
        	xil_printf("%08x  ", res[i]);
        }
    xil_printf("Cycles_1 = %d\r\n\r\n", t1_stop - t1);

    uint32_t a2[32] = {0x95401e33, 0xf2e5f538, 0xcd340e16, 0x5fe4fd66, 0xac500fe0, 0x748f18fe, 0xdad8575e, 0xce2058bb, 0x00c35266, 0xd51c8064, 0xfefeb38e, 0xc7ed29eb, 0xdb438313, 0x6550e48e, 0x02489732, 0xedaf8b6b, 0x5dd5313d, 0xa328f036, 0x419a784e, 0x23d635bb, 0x25143077, 0x48996382, 0xaa396499, 0xf24a2910, 0xb60ee4dc, 0xdfede44c, 0x69f174f6, 0x917d544c, 0x3c80aecf, 0xc90096c4, 0xc52a6c88, 0x07d92c14};
    uint32_t b2[32] = {0xd7040630, 0xc765f25a, 0x4a7230d6, 0x395c2b8b, 0xaec10e86, 0xb62173f6, 0x72096da0, 0xc0ed3b81, 0x240e4293, 0xac5a2199, 0x5d05fed8, 0xadcae3e6, 0x22704082, 0x3b74cdb2, 0x51f0df68, 0xde5b7e6f, 0x66dc5f67, 0x0a836d5e, 0x32edcdb9, 0x4332989f, 0xedef232c, 0x25167785, 0x34d884aa, 0xfdf337de, 0xd7532d14, 0xa4b160f1, 0xf833b81c, 0xaa9589fb, 0xef7f7ade, 0x6ccff27d, 0x747a7bb0, 0x1f8042e7};
    uint32_t N2[32] = {0xc6df4c85, 0x08e49be7, 0xe6f266e4, 0x450ca4b0, 0x028def7e, 0x3bdf79cf, 0xd3c65a9b, 0xd278192c, 0x08fd96bf, 0x5d635e17, 0xac3f28b1, 0x8449d487, 0xdd42688c, 0x61419fe8, 0x6b674328, 0x8f6bd9e2, 0x8e47420e, 0x94711c9e, 0x22f7165a, 0x2485755e, 0x61561df6, 0xf664e91d, 0xd97d05ce, 0xf221e0fd, 0xfd772f68, 0xf1856267, 0xe9041ac4, 0x2fd12fc8, 0x34b9220f, 0x695e5d77, 0x6b079c2c, 0x86ad4952};
    uint32_t n_prime2[32] = {0x14d333b3, 0xc3b3be8f, 0x02ca4af0, 0xc43aba10, 0xde20e9cb, 0xc88222f9, 0x80860cc0, 0x315e4cf8, 0x0a2cc4f4, 0x16376d50, 0xcc1720b7, 0x8af0c35b, 0xc3ece9e9, 0x8f01dccc, 0x42d96568, 0xc02be3a4, 0x71e50c92, 0xb050887c, 0x4df93c3d, 0x75a13c65, 0xcd504fe2, 0x99ac5e4c, 0xc9f348e7, 0xb95f9a0e, 0xe170a1f0, 0x4769f246, 0x913001b4, 0xfc05df41, 0x63dc5efb, 0x9a863fbe, 0xc1f39f28, 0xf1295524};

    init_performance_counters(1);
    uint32_t t2= get_cycle_counter();
    mont(a2, b2, N2, n_prime2, res, 32);
    uint32_t t2_stop= get_cycle_counter();
    xil_printf("\nmont_mul_test2 = 0x");
        for( i = 31; i >=0 ; i--){
        	xil_printf("%08x  ", res[i]);
        }
    xil_printf("Cycles_2 = %d\r\n\r\n", t2_stop - t2);

    uint32_t a3[32] = {0xf484e847, 0x4ae251f1, 0xedfa617d, 0x58ab6bf4, 0x46bf4848, 0xf67c1061, 0x8811c17a, 0x578fde16, 0x493ee595, 0x1eafc4c3, 0xc4f11a2e, 0x8cb6fba7, 0x724c03a4, 0x2e6c1dbd, 0x57ebc43d, 0x3e6ee260, 0x4089c050, 0xf0384e03, 0x7357f72c, 0x87acb658, 0x7ea2490e, 0x61069112, 0x42e3f8b9, 0x9e778cef, 0x5cdf77c7, 0x10bce41c, 0x1121beec, 0x3db59a36, 0xc34620c5, 0xc6b030ae, 0xe8fc5934, 0x63a0a0cb};
    uint32_t b3[32] = {0xfeb1b9f4, 0xe91d3bec, 0xfb09354d, 0x07f21d6d, 0x9ece9e1b, 0x18def18b, 0x4119e1e9, 0x55c85f24, 0x60ef0e23, 0x10e8ab54, 0x1e95cdcc, 0x4373912f, 0x6f42204d, 0x7126650d, 0xb61c1c8d, 0x98af9011, 0xa42c03b4, 0xd29e0870, 0x7923cb60, 0xdf87cfe5, 0xde4fffa0, 0x3ce537ca, 0x201040c6, 0x6e54b058, 0x814c53dc, 0xf16243f0, 0x57decf64, 0x8d0d4f37, 0x9b6d93e5, 0x45396d71, 0x615213c4, 0x65f89f9f};
    uint32_t N3[32] = {0x4aeeb107, 0x5d78aa98, 0x6c55dd05, 0x6f5326c9, 0xf93f738c, 0xc10fa093, 0x20478120, 0x099d6d70, 0x833d9b82, 0x1248f3ed, 0xa43ed737, 0xc1c1da45, 0x9f23e5c7, 0xb17c3598, 0xe8938df6, 0x7ae59036, 0x9f84d87b, 0xc8710dc6, 0x249ee0f8, 0x46eeae2f, 0x66a3bb9b, 0xfeef4c6b, 0xc7b55eae, 0x7951dd0c, 0x0b4391e8, 0x141ad586, 0x1a568588, 0x908293dd, 0x472c0bea, 0x8d00abfe, 0xed17377f, 0x83a01efe};
    uint32_t n_prime3[32] = {0xe7d41349, 0x0c828dcd, 0x2dc06d90, 0x318f87bf, 0x1992ba09, 0x4b1bef10, 0x011ba664, 0xe3a7d9cf, 0x44449fbd, 0x89714d34, 0x6cd49cc4, 0x49c5b99d, 0xf90435b1, 0x38f037b7, 0xba9720db, 0x9641b106, 0xbca01d2a, 0xfdb82893, 0xbd7ce9c7, 0x372823e1, 0x4901cdde, 0xaa28d457, 0xe9f78c94, 0xb6e1e5b3, 0x5a79f7a6, 0xf5212a83, 0x2b1aab45, 0xa3924b69, 0x3c63a8af, 0x12fa121d, 0x7500bea0, 0xe58878e7};


   init_performance_counters(1);
   uint32_t t3= get_cycle_counter();
   mont(a3, b3, N3, n_prime3, res, 32);
   uint32_t t3_stop= get_cycle_counter();
       xil_printf("\nmont_mul_test3 = 0x");
           for( i = 31; i >=0 ; i--){
           	xil_printf("%08x  ", res[i]);
           }
       xil_printf("Cycles_3 = %d\r\n\r\n", t3_stop - t3);


    /*
    mp_add(a , b , res , 32);
    xil_printf("(a + b) = \r\n");
    xil_printf("0x%x",res[32]);
    for( i = 31; i >=0 ; i--){
    	xil_printf("%08x", res[i]);
    }


    res[32]=0;
    mp_sub(a , b , res , 32);
    xil_printf("\n\n(a - b) = \r\n");
    xil_printf("0x%x",res[32]);
    for( i = 31; i >=0 ; i--){
      	xil_printf("%08x", res[i]);
    }


    res[32]=0;
    mod_add(a , b , N, res , 32);
    xil_printf("\n\n(a + b) mod N =  \r\n");
    xil_printf("0x%x",res[32]);
    for( i = 31; i >=0 ; i--){
       	xil_printf("%08x", res[i]);
    }


    res[32]=0;
    mod_sub(a , b , N, res , 32);
    xil_printf("\n\n(a - b) mod N =  \r\n");
    xil_printf("0x%x",res[32]);
    for( i = 31; i >=0 ; i--){
        xil_printf("%08x", res[i]);
    }
    
	*/
    cleanup_platform();
    return 0;
}
