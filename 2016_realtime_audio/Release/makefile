################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c6000

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./audioSamplecfg_c.obj" \
"./audioSamplecfg.obj" \
"./src_audio/process_audio.obj" \
"./src_audio/audioSample_main.obj" \
"./src_audio/audioSample_io.obj" \
"./src_speech_crypto/wavpcm_io.obj" \
"./src_speech_crypto/main.obj" \
"./src_speech_crypto/encode.obj" \
"./src_speech_crypto/decode.obj" \
"./src_speech_crypto/codec.obj" \
-l"libc.a" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\edma3_drv_bios_c674.lib" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\edma3_drv_bios_sample.lib" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\edma3_rm_bios.lib" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\pmi_ctl_evm6748.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\pmi.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\pscl_cfg_evm6748.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\pscl.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\ti.pspiom.gpio.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\ti.pspiom.i2c.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\ti.pspiom.mcasp.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\ti.pspiom.platforms.codec.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\ti.pspiom.platforms.evm6748.audio.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\ti.pspiom.platforms.evm6748.evmInit.a674" \
-l"E:\Work\DSP TA\workspace_v5\2013_realtime_audio\libs\ti.pspiom.psc.a674" \
"../libs/edma3_drv_bios_c674.lib" \
"../libs/edma3_drv_bios_sample.lib" \
"../libs/edma3_rm_bios.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src_speech_crypto/subdir_vars.mk
-include src_audio/subdir_vars.mk
-include libs/subdir_vars.mk
-include subdir_rules.mk
-include src_speech_crypto/subdir_rules.mk
-include src_audio/subdir_rules.mk
-include libs/subdir_rules.mk
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
all: 2013_realtime_audio.out

# Tool invocations
2013_realtime_audio.out: $(OBJS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -O2 --display_error_number --diag_warning=225 --abi=coffabi -z -m"2013_realtime_audio.map" --warn_sections -i"C:/ti/ccsv5/tools/compiler/c6000/lib" -i"E:/Work/DSP TA/workspace_v5/2013_realtime_audio/libs" -i"C:/ti/ccsv5/tools/compiler/c6000/include" -i"C:/ti/bios_5_41_11_38/packages/ti/rtdx/lib/c6000" -i"C:/ti/bios_5_41_11_38/packages/ti/bios/lib" --reread_libs --rom_model -o "2013_realtime_audio.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_SRCS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(C6000_EXECUTABLE_OUTPUTS__QUOTED)$(GEN_CMDS__QUOTED) "2013_realtime_audio.out"
	-$(RM) "src_speech_crypto\codec.pp" "src_speech_crypto\decode.pp" "src_speech_crypto\encode.pp" "src_speech_crypto\main.pp" "src_speech_crypto\wavpcm_io.pp" "src_audio\audioSample_io.pp" "src_audio\audioSample_main.pp" "src_audio\process_audio.pp" "audioSamplecfg_c.pp" 
	-$(RM) "audioSamplecfg.pp" 
	-$(RM) "src_speech_crypto\codec.obj" "src_speech_crypto\decode.obj" "src_speech_crypto\encode.obj" "src_speech_crypto\main.obj" "src_speech_crypto\wavpcm_io.obj" "src_audio\audioSample_io.obj" "src_audio\audioSample_main.obj" "src_audio\process_audio.obj" "audioSamplecfg.obj" "audioSamplecfg_c.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
