################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="C:/Xilinx/14.2/ISE_DS/EDK/gnu/arm/nt64/arm-xilinx-linux-gnueabi/libc/usr/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


