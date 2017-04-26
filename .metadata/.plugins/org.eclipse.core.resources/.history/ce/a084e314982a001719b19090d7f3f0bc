################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c6000

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./Key_Establishment/Source/verifySignature.obj" \
"./Key_Establishment/Source/signatureMessage.obj" \
"./Key_Establishment/Source/montExponentiation.obj" \
"./Key_Establishment/Source/modularInverse.obj" \
"./Key_Establishment/Source/modFunctions.obj" \
"./Key_Establishment/Source/maskGenerationFunction.obj" \
"./Key_Establishment/Source/keyEstablishmentFunctions.obj" \
"./Key_Establishment/Source/formatting.obj" \
"./Key_Establishment/Source/additionalFunctions.obj" \
"./library/ciphers/aes/test.obj" \
"./library/ciphers/aes/aes.obj" \
"./library/ciphers/ripemd-160/rmd160.obj" \
"./library/ciphers/ripemd-160/hashtest.obj" \
"./library/ciphers/sha1/shaTest.obj" \
"./library/ciphers/sha1/sha.obj" \
"./library/ciphers/sha2/sha2speed.obj" \
"./library/ciphers/sha2/sha2prog.obj" \
"./library/ciphers/sha2/sha2.obj" \
"./library/ciphers/sha3/sha3.obj" \
"./library/ciphers/sha3/sha3-test.obj" \
"./library/useSHA256.obj" \
"./library/useAES.obj" \
"./library/sha2speed.obj" \
"./library/sha2prog.obj" \
"./library/sha2.obj" \
"./library/hmac.obj" \
"./library/helpfulFunctions.obj" \
"./library/encryptDecrypt.obj" \
"./library/aes.obj" \
"./library/PRNG.obj" \
"./main.obj" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include library/subdir_vars.mk
-include library/ciphers/sha3/subdir_vars.mk
-include library/ciphers/sha2/subdir_vars.mk
-include library/ciphers/sha1/subdir_vars.mk
-include library/ciphers/ripemd-160/subdir_vars.mk
-include library/ciphers/aes/subdir_vars.mk
-include Key_Establishment/Source/subdir_vars.mk
-include subdir_rules.mk
-include library/subdir_rules.mk
-include library/ciphers/sha3/subdir_rules.mk
-include library/ciphers/sha2/subdir_rules.mk
-include library/ciphers/sha1/subdir_rules.mk
-include library/ciphers/ripemd-160/subdir_rules.mk
-include library/ciphers/aes/subdir_rules.mk
-include Key_Establishment/Source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: crypto_dspSimulation.out

# Tool invocations
crypto_dspSimulation.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --display_error_number --diag_warning=225 --abi=coffabi -z -m"crypto_dspSimulation.map" --warn_sections -i"C:/ti/ccsv5/tools/compiler/c6000/lib" -i"C:/ti/ccsv5/tools/compiler/c6000/include" --reread_libs --rom_model -o "crypto_dspSimulation.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_EXECUTABLE_OUTPUTS__QUOTED) "crypto_dspSimulation.out"
	-$(RM) "main.pp" "library\PRNG.pp" "library\aes.pp" "library\encryptDecrypt.pp" "library\helpfulFunctions.pp" "library\hmac.pp" "library\sha2.pp" "library\sha2prog.pp" "library\sha2speed.pp" "library\useAES.pp" "library\useSHA256.pp" "library\ciphers\sha3\sha3-test.pp" "library\ciphers\sha3\sha3.pp" "library\ciphers\sha2\sha2.pp" "library\ciphers\sha2\sha2prog.pp" "library\ciphers\sha2\sha2speed.pp" "library\ciphers\sha1\sha.pp" "library\ciphers\sha1\shaTest.pp" "library\ciphers\ripemd-160\hashtest.pp" "library\ciphers\ripemd-160\rmd160.pp" "library\ciphers\aes\aes.pp" "library\ciphers\aes\test.pp" "Key_Establishment\Source\additionalFunctions.pp" "Key_Establishment\Source\formatting.pp" "Key_Establishment\Source\keyEstablishmentFunctions.pp" "Key_Establishment\Source\maskGenerationFunction.pp" "Key_Establishment\Source\modFunctions.pp" "Key_Establishment\Source\modularInverse.pp" "Key_Establishment\Source\montExponentiation.pp" "Key_Establishment\Source\signatureMessage.pp" "Key_Establishment\Source\verifySignature.pp" 
	-$(RM) "main.obj" "library\PRNG.obj" "library\aes.obj" "library\encryptDecrypt.obj" "library\helpfulFunctions.obj" "library\hmac.obj" "library\sha2.obj" "library\sha2prog.obj" "library\sha2speed.obj" "library\useAES.obj" "library\useSHA256.obj" "library\ciphers\sha3\sha3-test.obj" "library\ciphers\sha3\sha3.obj" "library\ciphers\sha2\sha2.obj" "library\ciphers\sha2\sha2prog.obj" "library\ciphers\sha2\sha2speed.obj" "library\ciphers\sha1\sha.obj" "library\ciphers\sha1\shaTest.obj" "library\ciphers\ripemd-160\hashtest.obj" "library\ciphers\ripemd-160\rmd160.obj" "library\ciphers\aes\aes.obj" "library\ciphers\aes\test.obj" "Key_Establishment\Source\additionalFunctions.obj" "Key_Establishment\Source\formatting.obj" "Key_Establishment\Source\keyEstablishmentFunctions.obj" "Key_Establishment\Source\maskGenerationFunction.obj" "Key_Establishment\Source\modFunctions.obj" "Key_Establishment\Source\modularInverse.obj" "Key_Establishment\Source\montExponentiation.obj" "Key_Establishment\Source\signatureMessage.obj" 
	-$(RM) "Key_Establishment\Source\verifySignature.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
