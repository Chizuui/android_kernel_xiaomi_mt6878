/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 */

#ifndef __MT_SPM_REG_H___
#define __MT_SPM_REG_H___

#if defined(CONFIG_MACH_MT6763)

#include "spm_v4/mtk_spm_reg_mt6763.h"

#elif defined(CONFIG_MACH_MT6739)

#include "spm_v4/mtk_spm_reg_mt6739.h"

#elif defined(CONFIG_MACH_MT6771)

#include "spm_v4/mtk_spm_reg_mt6771.h"

#elif defined(CONFIG_MACH_MT6768)

/*
 * MT6768 keeps its SPM register map in the legacy spm/mt6768 tree.
 * Include it directly here, otherwise the per-SoC header would shadow the
 * dispatcher on the include path and leave the platform symbols undefined.
 */
#include "../../spm/mt6768/mtk_spm_reg.h"

#endif

#endif /* __MT_SPM_REG_H___ */

