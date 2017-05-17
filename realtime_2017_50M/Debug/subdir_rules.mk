################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
audioSamplecfg.cmd: ../audioSample.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf Script Compiler'
	"C:/ti/xdctools_3_22_04_46/tconf" -b -Dconfig.importPath="C:/ti/bios_5_41_11_38/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

audioSamplecfg.s??: audioSamplecfg.cmd
audioSamplecfg_c.c: audioSamplecfg.cmd
audioSamplecfg.h: audioSamplecfg.cmd
audioSamplecfg.h??: audioSamplecfg.cmd
audioSample.cdb: audioSamplecfg.cmd

audioSamplecfg.obj: ./audioSamplecfg.s?? $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/include" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/src_audio" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/src_speech_crypto" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/Debug" --include_path="C:/ti/bios_5_41_11_38/packages/ti/bios/include" --include_path="C:/ti/bios_5_41_11_38/packages/ti/rtdx/include/c6000" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="audioSamplecfg.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

audioSamplecfg_c.obj: ./audioSamplecfg_c.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/include" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/src_audio" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/src_speech_crypto" --include_path="U:/Documents/PnD/DSP/realtime_2017_50M/Debug" --include_path="C:/ti/bios_5_41_11_38/packages/ti/bios/include" --include_path="C:/ti/bios_5_41_11_38/packages/ti/rtdx/include/c6000" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="audioSamplecfg_c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


