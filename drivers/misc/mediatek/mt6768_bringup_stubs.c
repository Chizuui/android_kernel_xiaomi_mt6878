// SPDX-License-Identifier: GPL-2.0
/* MT6768 6.6 bringup stubs for legacy MTK platform APIs not ported. */
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/clk.h>

struct cmdq_pkt;
void __weak *GIC_DIST_BASE;
void __iomem __weak *thermal_base;
void __iomem __weak *auxadc_ts_base;
int __weak thermal_phy_base;
int __weak auxadc_ts_phy_base;
int __weak apmixed_phy_base;
struct clk __weak *therm_main;
__weak unsigned char thermal_atm_t[4096]; // type-unsound bringup placeholder

int __weak cmdq_sec_pkt_set_data(struct cmdq_pkt *pkt, u64 dapc_engine, u64 port_sec_engine, u32 sec_mode, u32 cmdq_mdp_meta) { return 0; }
int __weak exec_ccci_kern_func_by_md_id(int md_id, unsigned int id, char *buf, unsigned int len) { return -ENODEV; }
int __weak sspm_ipi_send_sync(int ipi_id, int opt, void *buffer, int slot, void *retbuf, int retslot) { return -EOPNOTSUPP; }
int __weak sspm_ipi_send_sync_ex(int ipi_id, int opt, void *buffer, int slot, void *retbuf, int retslot) { return -EOPNOTSUPP; }
int __weak mtk_spk_send_ipi_buf_to_dsp(void *data_buffer, u32 data_size) { return -EOPNOTSUPP; }
int __weak mtk_spk_recv_ipi_buf_from_dsp(char *buffer, unsigned short size, u32 *buf_len) { return -EOPNOTSUPP; }
unsigned int __weak mt_irq_get_pending_vec(unsigned int start_irq) { return 0; }
unsigned int __weak mt_irq_get_pending_hw(unsigned int irq) { return 0; }
void __weak mt_irq_set_pending_hw(unsigned int irq) { }
unsigned int __weak mt_irq_get_pol_hw(unsigned int hwirq) { return 0; }
int __weak get_cpu_target_tj(void) { return 125000; }
int __weak tscpu_get_min_gpu_pwr(void) { return 0; }
int __weak mtktscpu_limited_dmips; // ponytail: zero cap, add real limiter when mt6768 tscpu ported.

int __weak mtk_thermal_get_cpu_info(int *nocores, int **cpufreq, int **cpuloading){if(nocores)*nocores=0;if(cpufreq)*cpufreq=NULL;if(cpuloading)*cpuloading=NULL;return 0;}


int __weak cmdq_sec_pkt_write_reg(void *pkt, u32 addr, u64 base, u32 data, u32 mask) { return 0; }
int __weak dram_steps_freq(unsigned int step) { return 0; }
int __weak dvfsrc_set_power_model_ddr_request(unsigned int level) { return 0; }
int __weak exec_ccci_kern_func(unsigned int id, char *buf, unsigned int len) { return -1; }
void __weak ged_kpi_output_gfx_info2(long long t_gpu, unsigned int cur_freq, unsigned int cur_max_freq, u64 ulPre_fence_done_time, u64 ul_ui_done_time) {}
unsigned int __weak get_cur_ddr_opp(void) { return 0; }
unsigned int __weak get_cur_vcore_opp(void) { return 0; }
unsigned int __weak get_ddr_type(void) { return 0; }
int __weak get_immediate_cpuB_wrap(void) { return 25000; }
unsigned int __weak get_smem_start_addr(int id, int *size) { return 0; }
int __weak is_dvfsrc_enabled(void) { return 0; }
int __weak is_infra_timeout(void) { return 0; }
void __weak lastbus_timeout_dump(void) {}
int __weak mtk_ccci_open_port(int md_id, int port, void *handler, int flags) { return -1; }
int __weak mtk_ccci_read_data(int md_id, int port, char *buf, unsigned int size) { return -1; }
int __weak mtk_ccci_release_port(int md_id, int port) { return 0; }
int __weak mtk_ccci_request_port(int md_id, int port, int flags, char *name) { return -1; }
int __weak mtk_ccci_send_data(int md_id, int port, char *buf, unsigned int size) { return -1; }
int __weak sched_isolate_cpu(int cpu) { return -1; }
int __weak sched_unisolate_cpu(int cpu) { return -1; }

void __weak aee_kernel_warning(const char *module, const char *msg, ...) {}
int __weak battery_get_bat_temperature(void) { return 250; }
int __weak fgauge_read_IM_current(void *data) { return 0; }
int __weak gauge_get_int_property(void *prop) { return 0; }
void __weak ged_kpi_output_gfx_info(long long t_gpu, unsigned int cur_freq, unsigned int cur_max_freq) {}
int __weak get_rac(void) { return 100; }
int __weak is_battery_init_done(void) { return 0; }
void __weak lbat_min_en_setting(int en) {}
void __weak lbat_service_init(void) {}
void __weak lbat_set_fg_current_limit_en_setting(int en) {}
int __weak mt635x_auxadc_get_v_in(void *chip, int channel) { return 0; }
int __weak mtkts_bts_get_hw_temp(void) { return 25000; }
int __weak mt6357_get_v_in(void *dev, int channel) { return 0; }
unsigned int __weak pmic_get_register_value(void *pmu, unsigned int reg) { return 0; }

void __weak ged_kpi_output_gfx_info2_fp(void) {}
int __weak get_immediate_cpuL_wrap(void) { return 25000; }
int __weak get_thermal_slope_intercept(int id, int mode) { return 0; }
void __weak lbat_dump_reg(void) {}
void __weak lbat_resume(void) {}
void __weak lbat_suspend(void) {}
void __weak mt_eint_print_status(void) {}
void __weak mt_irq_get_pending(void) {}
void __weak mt_irq_mask_all(void) {}
void __weak mt_irq_mask_restore(void) {}
void __weak mt_irq_set_pending(void) {}
void __weak mt_irq_unmask_for_sleep_ex(void) {}
void __weak mtkTTimer_cancel_timer(void) {}
void __weak mtkTTimer_start_timer(void) {}

int __weak mt_gpufreq_get_thermal_limit_index(void) { return 0; }
void __weak mt_gpufreq_thermal_protect(int idx) {}
int __weak mtk_gpufreq_register(void *info) { return 0; }
void __weak m4u_sec_init(void) {}

int __weak get_immediate_gpu_wrap(void) { return 25000; }
unsigned int __weak mt_get_ckgen_freq(int id) { return 0; }

#include <linux/tracepoint.h>
struct tracepoint __aligned(8) __weak __tracepoint_idle_cg;
struct tracepoint __aligned(8) __weak __tracepoint_dpidle;
struct tracepoint __aligned(8) __weak __tracepoint_sodi;
struct tracepoint __aligned(8) __weak __tracepoint_sodi3;
void __weak __traceiter_idle_cg(void *data, unsigned int val) {}


int __weak init_utch(void) { return 0; }
