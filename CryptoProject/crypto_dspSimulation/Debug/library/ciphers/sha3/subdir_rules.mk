################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
library/ciphers/sha3/sha3-test.obj: ../library/ciphers/sha3/sha3-test.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="library/ciphers/sha3/sha3-test.pp" --obj_directory="library/ciphers/sha3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

library/ciphers/sha3/sha3.obj: ../library/ciphers/sha3/sha3.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="library/ciphers/sha3/sha3.pp" --obj_directory="library/ciphers/sha3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


