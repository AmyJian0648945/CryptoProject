################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
library/ciphers/ripemd-160/hashtest.obj: ../library/ciphers/ripemd-160/hashtest.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="library/ciphers/ripemd-160/hashtest.pp" --obj_directory="library/ciphers/ripemd-160" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

library/ciphers/ripemd-160/rmd160.obj: ../library/ciphers/ripemd-160/rmd160.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="library/ciphers/ripemd-160/rmd160.pp" --obj_directory="library/ciphers/ripemd-160" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

