/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2024 MediaTek Inc.
 *
 * kallsyms_lookup_name() stopped being exported in 5.7, so vendor drivers
 * that resolve kernel symbols by name cannot call it directly. Provide a
 * small emulation built on kallsyms_on_each_symbol().
 */

#ifndef __MTK_KALLSYMS_COMPAT_H
#define __MTK_KALLSYMS_COMPAT_H

#include <linux/kallsyms.h>
#include <linux/string.h>

struct mtk_kallsyms_lookup {
	const char *name;
	unsigned long addr;
};

static inline int mtk_kallsyms_lookup_cb(void *data, const char *name,
					 unsigned long addr)
{
	struct mtk_kallsyms_lookup *lookup = data;

	if (lookup->addr)
		return 0;

	if (name && !strcmp(name, lookup->name)) {
		lookup->addr = addr;
		return 1;
	}

	return 0;
}

static inline unsigned long mtk_kallsyms_lookup_name(const char *name)
{
	struct mtk_kallsyms_lookup lookup = {
		.name = name,
		.addr = 0,
	};

	if (!name || !*name)
		return 0;

	kallsyms_on_each_symbol(mtk_kallsyms_lookup_cb, &lookup);

	return lookup.addr;
}

#endif /* __MTK_KALLSYMS_COMPAT_H */
