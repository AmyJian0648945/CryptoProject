################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --display_error_number --diag_warning=225 --abi=coffabi --opt_for_speed=2 --gen_opt_info=2 --call_assumptions=2 --single_inline --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


