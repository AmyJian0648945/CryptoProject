################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
library/ciphers/aes/aes.obj: ../library/ciphers/aes/aes.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="library/ciphers/aes/aes.pp" --obj_directory="library/ciphers/aes" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

library/ciphers/aes/test.obj: ../library/ciphers/aes/test.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="library/ciphers/aes/test.pp" --obj_directory="library/ciphers/aes" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


