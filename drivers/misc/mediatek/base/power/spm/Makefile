subdir-ccflags-y += -DSECURE_SERIAL_8250

ifeq (y, $(filter y, $(CONFIG_MACH_MT6768) $(CONFIG_MACH_MT6785)))
obj-y += common_v1/
else
obj-y += common/
endif
obj-y += $(MTK_PLATFORM)/

# Put the platform SPM headers ahead of the generic ones in
# base/power/include so that mtk_spm_reg.h resolves to the per-SoC file.
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/spm/$(MTK_PLATFORM)
