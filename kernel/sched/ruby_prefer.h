/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _KERNEL_SCHED_RUBY_PREFER_H
#define _KERNEL_SCHED_RUBY_PREFER_H

#include <linux/types.h>

struct rq;
struct task_struct;

#ifdef CONFIG_MTK_RUBY_BIG_TASK_ROTATION
/* Caller holds the RCU read lock while inspecting rq->curr. */
bool ruby_rotation_task_heavy(struct rq *rq);
#endif

#ifdef CONFIG_MTK_RUBY_SCHED_PREFER
int ruby_cpuset_prefer_cpu(struct task_struct *task);
int ruby_prefer_cpu(struct task_struct *p, int selected_cpu);
int ruby_migrate_misfit(struct rq *rq, struct task_struct *p);
#endif

#endif
