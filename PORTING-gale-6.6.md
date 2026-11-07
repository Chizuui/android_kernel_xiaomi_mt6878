# gale-6.6 port status

Port of the Xiaomi **gale** (MT6768 / Helio G85) platform into a 6.6 kernel,
starting from the `android_kernel_xiaomi_mt6878` (ruby / MT6877) 6.6 tree as
the base, because that tree already carries the MediaTek vendor stack ported
past the 4.19 APIs.

Branch: `dev/gale-6.6` (git worktree of `android_kernel_xiaomi_mt6878`).

## What was done

### Platform bring-up
- `MACH_MT6768` platform option in `arch/arm64/Kconfig.platforms`, modelled on
  `MACH_MT6877` but selecting the legacy SPM/EMI power path
  (`MTK_SYS_CIRQ`, `MTK_PLAT_SRAM_FLAG`, `MTK_EMI_LEGACY`, `MTK_DRAMC`,
  `MTK_CQDMA`) instead of LPM.
- `PINCTRL_MT6768` Kconfig + Makefile wiring with `pinctrl-mt6768.c`.
- DTS: `mt6768.dts`, `gale.dts`, `gale/cust.dtsi`, the `cust_mt6768_*`
  fragments, and the supporting dtsi files (touchscreen, fingerprint,
  foursemi, mt6370, mt6370_pd, rt9471, tcpc_config).
- `dt-bindings`: MT6768 pinfunc, msdc, larb-port, gce and clk headers.
- `gale_defconfig` derived from `ruby_defconfig` with the platform switched
  to mt6768. All referenced symbols were validated against Kconfig.

### Vendor stack
- All 60 `mt6768` platform directories imported (466 files), covering
  `base/power` (spm, eem, dcm, mcdi, power_gs, clkbuf, drcc, ppm, qos,
  swpm, gpu bw), camera, display, thermal, connectivity, pmic, cmdq and the
  rest.
- MT6768 static and unified power tables wired into the existing
  `leakage_table_v2` / `upower_v2` hooks.
- PMIC: kept the 6.6 port that ruby already carried for platform neutral
  files, kept the gale versions for `upmu.c` (MT6358) and the mt6360 charger
  (Ruby product detection does not apply to gale).

### API port (4.19 -> 6.6)
- `struct timeval`, `do_gettimeofday`, `getnstimeofday`,
  `get_monotonic_coarse` -> `timespec64` / `ktime_get_real_ts64` /
  `ktime_get_coarse_ts64`. This touched ~90 files across MTK, mtk-vcodec,
  mi_disp, tee, alarm-dev, mtk_trace and the AFE control code.
- `kallsyms_lookup_name` is unexported: added
  `drivers/misc/mediatek/include/mtk_kallsyms_compat.h` resolving through
  `kallsyms_on_each_symbol`, and routed the trace marker lookups through it.
- `class_create(THIS_MODULE, name)` -> `class_create(name)`.
- `access_ok(VERIFY_x, addr, size)` -> `access_ok(addr, size)`.
- `get_user_pages(..., vmas)` -> `get_user_pages(..., pages)` in m4u.
- `alarm-dev`: `struct timespec` -> `timespec64`, `rtc_time_to_tm` ->
  `rtc_time64_to_tm`, and the removed `compat_get_timespec` /
  `compat_put_timespec` replaced with explicit 32-bit marshalling.
- Fixed the gps and wlan compatibility shims so they only apply below 5.0;
  the gps one also had an invalid lvalue assignment.

## Not done / needs work

1. **Nothing has been compiled yet.** This environment has no `make` and no
   aarch64 GNU toolchain, so the tree is unverified. Build it on Linux/WSL:
   ```
   make O=out ARCH=arm64 gale_defconfig
   make O=out ARCH=arm64 -j$(nproc)
   ```
2. **MT6768 clock drivers are missing.** `CONFIG_COMMON_CLK_MT6768*` does not
   exist in this tree. The defconfig entries were removed rather than left
   dangling. `clk-mt6768-*` sources need to be ported.
3. **MTK_LPM_MT6768 does not exist.** gale uses the legacy SPM path, so LPM is
   not enabled, but anything expecting LPM symbols will need attention.
4. **SND_SOC_MT6768_MT6359 audio machine driver is missing.** The
   `sound/soc/mediatek` machine driver for MT6768 has not been ported.
5. **Camera ISP for MT6768.** `cameraisp` folders are imported, but the image
   sensor drivers under `imgsensor/src/mt6768` still need hardware validation.
6. **No boot test.** Expect driver probe failures on first boot; they need to
   be worked through per subsystem with dmesg.

## Suggested order for the next session

1. Build and collect the first wave of compile errors.
2. `base/power` (spm, eem, dcm) and `pmic` — needed before anything else runs.
3. Clock drivers (`clk-mt6768-*`) — without these, most peripherals fail probe.
4. Thermal, then display (`video/mt6768`).
5. Connectivity (wlan/bt), then camera.
