savedcmd_/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.o := arm-linux-gnueabihf-gcc -Wp,-MMD,/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/.hi.o.d -nostdinc -I/home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include -I./arch/arm/include/generated -I/home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include -I./include -I/home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi -I./arch/arm/include/generated/uapi -I/home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi -I./include/generated/uapi -include /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/compiler-version.h -include /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kconfig.h -include /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -D__LINUX_ARM_ARCH__=7 -fmacro-prefix-map=/home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/= -std=gnu11 -fshort-wchar -funsigned-char -fno-common -fno-PIE -fno-strict-aliasing -fno-dwarf2-cfi-asm -mno-fdpic -fno-ipa-sra -mtp=cp15 -mabi=aapcs-linux -mfpu=vfp -funwind-tables -marm -Wa,-mno-warn-deprecated -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -Os -fno-allow-store-data-races -fstack-protector-strong -fomit-frame-pointer -ftrivial-auto-var-init=zero -fno-stack-clash-protection -fstrict-flex-arrays=3 -fno-strict-overflow -fno-stack-check -fconserve-stack -Wall -Wundef -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Werror=strict-prototypes -Wno-format-security -Wno-trigraphs -Wno-frame-address -Wno-address-of-packed-member -Wframe-larger-than=1024 -Wno-main -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-dangling-pointer -Wvla -Wno-pointer-sign -Wcast-function-type -Wno-array-bounds -Wno-alloc-size-larger-than -Wimplicit-fallthrough=5 -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wenum-conversion -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-restrict -Wno-packed-not-aligned -Wno-format-overflow -Wno-format-truncation -Wno-stringop-overflow -Wno-stringop-truncation -Wno-missing-field-initializers -Wno-type-limits -Wno-shift-negative-value -Wno-maybe-uninitialized -Wno-sign-compare -mstack-protector-guard=tls -mstack-protector-guard-offset=1208  -DMODULE  -DKBUILD_BASENAME='"hi"' -DKBUILD_MODNAME='"hi"' -D__KBUILD_MODNAME=kmod_hi -c -o /home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.o /home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.c  

source_/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.o := /home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.c

deps_/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.o := \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/FUNCTION_ALIGNMENT) \
    $(wildcard include/config/CC_IS_GCC) \
    $(wildcard include/config/X86_64) \
    $(wildcard include/config/ARM64) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/compiler_attributes.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/compiler-gcc.h \
    $(wildcard include/config/RETPOLINE) \
    $(wildcard include/config/ARCH_USE_BUILTIN_BSWAP) \
    $(wildcard include/config/SHADOW_CALL_STACK) \
    $(wildcard include/config/KCOV) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/init.h \
    $(wildcard include/config/HAVE_ARCH_PREL32_RELOCATIONS) \
    $(wildcard include/config/STRICT_KERNEL_RWX) \
    $(wildcard include/config/STRICT_MODULE_RWX) \
    $(wildcard include/config/LTO_CLANG) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/build_bug.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
    $(wildcard include/config/OBJTOOL) \
  arch/arm/include/generated/asm/rwonce.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/rwonce.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kasan-checks.h \
    $(wildcard include/config/KASAN_GENERIC) \
    $(wildcard include/config/KASAN_SW_TAGS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/int-ll64.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/uapi/asm/bitsperlong.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitsperlong.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/bitsperlong.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/posix_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/stddef.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/stddef.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/posix_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/posix_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kcsan-checks.h \
    $(wildcard include/config/KCSAN) \
    $(wildcard include/config/KCSAN_WEAK_MEMORY) \
    $(wildcard include/config/KCSAN_IGNORE_ATOMICS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/stringify.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kernel.h \
    $(wildcard include/config/PREEMPT_VOLUNTARY_BUILD) \
    $(wildcard include/config/PREEMPT_DYNAMIC) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_CALL) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_KEY) \
    $(wildcard include/config/PREEMPT_) \
    $(wildcard include/config/DEBUG_ATOMIC_SLEEP) \
    $(wildcard include/config/SMP) \
    $(wildcard include/config/MMU) \
    $(wildcard include/config/PROVE_LOCKING) \
    $(wildcard include/config/TRACING) \
    $(wildcard include/config/FTRACE_MCOUNT_RECORD) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/stdarg.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/align.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/const.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/const.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/const.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/limits.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/limits.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/limits.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/linkage.h \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/linkage.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/container_of.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/bitops.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/bits.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/bits.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/typecheck.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/kernel.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/sysinfo.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/generic-non-atomic.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/CPU_32v6K) \
    $(wildcard include/config/THUMB2_KERNEL) \
    $(wildcard include/config/CPU_XSC3) \
    $(wildcard include/config/CPU_FA526) \
    $(wildcard include/config/ARM_HEAVY_MB) \
    $(wildcard include/config/ARM_DMA_MEM_BUFFERABLE) \
    $(wildcard include/config/CPU_SPECTRE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/barrier.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/bitops.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/irqflags.h \
    $(wildcard include/config/TRACE_IRQFLAGS) \
    $(wildcard include/config/PREEMPT_RT) \
    $(wildcard include/config/IRQSOFF_TRACER) \
    $(wildcard include/config/PREEMPT_TRACER) \
    $(wildcard include/config/DEBUG_IRQFLAGS) \
    $(wildcard include/config/TRACE_IRQFLAGS_SUPPORT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/cleanup.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/irqflags.h \
    $(wildcard include/config/CPU_V7M) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/ARM_THUMB) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/CPU_ENDIAN_BE8) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/hwcap.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/hwcap.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/irqflags.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/percpu.h \
    $(wildcard include/config/CPU_V6) \
    $(wildcard include/config/ARM_HAS_GROUP_RELOCS) \
    $(wildcard include/config/ARM_MODULE_PLTS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/insn.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/percpu.h \
    $(wildcard include/config/DEBUG_PREEMPT) \
    $(wildcard include/config/HAVE_SETUP_PER_CPU_AREA) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/threads.h \
    $(wildcard include/config/NR_CPUS) \
    $(wildcard include/config/BASE_SMALL) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/percpu-defs.h \
    $(wildcard include/config/DEBUG_FORCE_WEAK_PER_CPU) \
    $(wildcard include/config/AMD_MEM_ENCRYPT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/non-atomic.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/non-instrumented-non-atomic.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/builtin-__fls.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/builtin-__ffs.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/builtin-fls.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/builtin-ffs.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/ffz.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/fls64.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/sched.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/hweight.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/arch_hweight.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/const_hweight.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/lock.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/atomic.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/GENERIC_ATOMIC64) \
    $(wildcard include/config/ARM_LPAE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/prefetch.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/processor.h \
    $(wildcard include/config/HAVE_HW_BREAKPOINT) \
    $(wildcard include/config/BINFMT_ELF_FDPIC) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/hw_breakpoint.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/unified.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/vdso/processor.h \
    $(wildcard include/config/ARM_ERRATA_754327) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/cache.h \
    $(wildcard include/config/ARM_L1_CACHE_SHIFT) \
    $(wildcard include/config/AEABI) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/CPU_SA1100) \
    $(wildcard include/config/CPU_SA110) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/cmpxchg-local.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/atomic/atomic-arch-fallback.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/atomic/atomic-long.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/atomic/atomic-instrumented.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/instrumented.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kmsan-checks.h \
    $(wildcard include/config/KMSAN) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/instrumented-lock.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/le.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/byteorder.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/byteorder/little_endian.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/byteorder/little_endian.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/swab.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/swab.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/swab.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/swab.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/byteorder/generic.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/hex.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kstrtox.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/log2.h \
    $(wildcard include/config/ARCH_HAS_ILOG2_U32) \
    $(wildcard include/config/ARCH_HAS_ILOG2_U64) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/math.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/div64.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/compiler.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/div64.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/minmax.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/panic.h \
    $(wildcard include/config/PANIC_TIMEOUT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/printk.h \
    $(wildcard include/config/MESSAGE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_QUIET) \
    $(wildcard include/config/EARLY_PRINTK) \
    $(wildcard include/config/PRINTK) \
    $(wildcard include/config/PRINTK_INDEX) \
    $(wildcard include/config/DYNAMIC_DEBUG) \
    $(wildcard include/config/DYNAMIC_DEBUG_CORE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kern_levels.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/ratelimit_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/param.h \
  arch/arm/include/generated/uapi/asm/param.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/param.h \
    $(wildcard include/config/HZ) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/param.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/spinlock_types_raw.h \
    $(wildcard include/config/DEBUG_SPINLOCK) \
    $(wildcard include/config/DEBUG_LOCK_ALLOC) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/spinlock_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/lockdep_types.h \
    $(wildcard include/config/PROVE_RAW_LOCK_NESTING) \
    $(wildcard include/config/LOCKDEP) \
    $(wildcard include/config/LOCK_STAT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/once_lite.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sprintf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/static_call_types.h \
    $(wildcard include/config/HAVE_STATIC_CALL) \
    $(wildcard include/config/HAVE_STATIC_CALL_INLINE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/instruction_pointer.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/module.h \
    $(wildcard include/config/MODULES) \
    $(wildcard include/config/SYSFS) \
    $(wildcard include/config/MODULES_TREE_LOOKUP) \
    $(wildcard include/config/LIVEPATCH) \
    $(wildcard include/config/STACKTRACE_BUILD_ID) \
    $(wildcard include/config/ARCH_USES_CFI_TRAPS) \
    $(wildcard include/config/MODULE_SIG) \
    $(wildcard include/config/GENERIC_BUG) \
    $(wildcard include/config/KALLSYMS) \
    $(wildcard include/config/TRACEPOINTS) \
    $(wildcard include/config/TREE_SRCU) \
    $(wildcard include/config/BPF_EVENTS) \
    $(wildcard include/config/DEBUG_INFO_BTF_MODULES) \
    $(wildcard include/config/JUMP_LABEL) \
    $(wildcard include/config/EVENT_TRACING) \
    $(wildcard include/config/KPROBES) \
    $(wildcard include/config/KUNIT) \
    $(wildcard include/config/MODULE_UNLOAD) \
    $(wildcard include/config/CONSTRUCTORS) \
    $(wildcard include/config/FUNCTION_ERROR_INJECTION) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/list.h \
    $(wildcard include/config/LIST_HARDENED) \
    $(wildcard include/config/DEBUG_LIST) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/poison.h \
    $(wildcard include/config/ILLEGAL_POINTER_VALUE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/stat.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/stat.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/stat.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/time.h \
    $(wildcard include/config/POSIX_TIMERS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/cache.h \
    $(wildcard include/config/ARCH_HAS_CACHE_LINE_SIZE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/math64.h \
    $(wildcard include/config/ARCH_SUPPORTS_INT128) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/math64.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/time64.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/time64.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/time.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/time_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/time32.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/timex.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/timex.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/timex.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/time32.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/time.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/uidgid.h \
    $(wildcard include/config/MULTIUSER) \
    $(wildcard include/config/USER_NS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/highuid.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/buildid.h \
    $(wildcard include/config/CRASH_CORE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/mm_types.h \
    $(wildcard include/config/HAVE_ALIGNED_STRUCT_PAGE) \
    $(wildcard include/config/MEMCG) \
    $(wildcard include/config/USERFAULTFD) \
    $(wildcard include/config/PER_VMA_LOCK) \
    $(wildcard include/config/ANON_VMA_NAME) \
    $(wildcard include/config/SWAP) \
    $(wildcard include/config/NUMA) \
    $(wildcard include/config/NUMA_BALANCING) \
    $(wildcard include/config/SCHED_MM_CID) \
    $(wildcard include/config/HAVE_ARCH_COMPAT_MMAP_BASES) \
    $(wildcard include/config/MEMBARRIER) \
    $(wildcard include/config/AIO) \
    $(wildcard include/config/MMU_NOTIFIER) \
    $(wildcard include/config/TRANSPARENT_HUGEPAGE) \
    $(wildcard include/config/ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH) \
    $(wildcard include/config/HUGETLB_PAGE) \
    $(wildcard include/config/IOMMU_SVA) \
    $(wildcard include/config/KSM) \
    $(wildcard include/config/LRU_GEN) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/mm_types_task.h \
    $(wildcard include/config/SPLIT_PTLOCK_CPUS) \
    $(wildcard include/config/ARCH_ENABLE_SPLIT_PMD_PTLOCK) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/cpumask.h \
    $(wildcard include/config/FORCE_NR_CPUS) \
    $(wildcard include/config/HOTPLUG_CPU) \
    $(wildcard include/config/DEBUG_PER_CPU_MAPS) \
    $(wildcard include/config/CPUMASK_OFFSTACK) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/bitmap.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/find.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/string.h \
    $(wildcard include/config/BINARY_PRINTF) \
    $(wildcard include/config/FORTIFY_SOURCE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/errno.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/errno.h \
  arch/arm/include/generated/uapi/asm/errno.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/errno.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/errno-base.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/string.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/string.h \
    $(wildcard include/config/KASAN) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/bug.h \
    $(wildcard include/config/BUG_ON_DATA_CORRUPTION) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/bug.h \
    $(wildcard include/config/DEBUG_BUGVERBOSE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/CPU_ENDIAN_BE32) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/bug.h \
    $(wildcard include/config/BUG) \
    $(wildcard include/config/GENERIC_BUG_RELATIVE_POINTERS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/instrumentation.h \
    $(wildcard include/config/NOINSTR_VALIDATION) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/gfp_types.h \
    $(wildcard include/config/KASAN_HW_TAGS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/numa.h \
    $(wildcard include/config/NODES_SHIFT) \
    $(wildcard include/config/NUMA_KEEP_MEMINFO) \
    $(wildcard include/config/HAVE_ARCH_NODE_DEV_GROUP) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/page.h \
    $(wildcard include/config/CPU_COPY_V4WT) \
    $(wildcard include/config/CPU_COPY_V4WB) \
    $(wildcard include/config/CPU_COPY_FEROCEON) \
    $(wildcard include/config/CPU_COPY_FA) \
    $(wildcard include/config/CPU_XSCALE) \
    $(wildcard include/config/CPU_COPY_V6) \
    $(wildcard include/config/KUSER_HELPERS) \
    $(wildcard include/config/VMAP_STACK) \
    $(wildcard include/config/HAVE_ARCH_PFN_VALID) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/glue.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/pgtable-2level-types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/memory.h \
    $(wildcard include/config/NEED_MACH_MEMORY_H) \
    $(wildcard include/config/PAGE_OFFSET) \
    $(wildcard include/config/HIGHMEM) \
    $(wildcard include/config/DRAM_BASE) \
    $(wildcard include/config/DRAM_SIZE) \
    $(wildcard include/config/XIP_KERNEL) \
    $(wildcard include/config/HAVE_TCM) \
    $(wildcard include/config/ARM_PATCH_PHYS_VIRT) \
    $(wildcard include/config/PHYS_OFFSET) \
    $(wildcard include/config/DEBUG_VIRTUAL) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sizes.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/kasan_def.h \
    $(wildcard include/config/KASAN_SHADOW_OFFSET) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/getorder.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/memory_model.h \
    $(wildcard include/config/FLATMEM) \
    $(wildcard include/config/SPARSEMEM_VMEMMAP) \
    $(wildcard include/config/SPARSEMEM) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/pfn.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/auxvec.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/auxvec.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/auxvec.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/auxvec.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kref.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/spinlock.h \
    $(wildcard include/config/PREEMPTION) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/preempt.h \
    $(wildcard include/config/PREEMPT_COUNT) \
    $(wildcard include/config/TRACE_PREEMPT_TOGGLE) \
    $(wildcard include/config/PREEMPT_NOTIFIERS) \
  arch/arm/include/generated/asm/preempt.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/preempt.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/thread_info.h \
    $(wildcard include/config/THREAD_INFO_IN_TASK) \
    $(wildcard include/config/GENERIC_ENTRY) \
    $(wildcard include/config/HAVE_ARCH_WITHIN_STACK_FRAMES) \
    $(wildcard include/config/HARDENED_USERCOPY) \
    $(wildcard include/config/SH) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/restart_block.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/current.h \
    $(wildcard include/config/CURRENT_POINTER_IN_TPIDRURO) \
    $(wildcard include/config/CC_IS_CLANG) \
    $(wildcard include/config/CLANG_VERSION) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/ARM_THUMBEE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/VFPv3) \
    $(wildcard include/config/IWMMXT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/traps.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/bottom_half.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/lockdep.h \
    $(wildcard include/config/DEBUG_LOCKING_API_SELFTESTS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/smp.h \
    $(wildcard include/config/UP_LATE_INIT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/smp_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/llist.h \
    $(wildcard include/config/ARCH_HAVE_NMI_SAFE_CMPXCHG) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/smp.h \
  arch/arm/include/generated/asm/mmiowb.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/mmiowb.h \
    $(wildcard include/config/MMIOWB) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/spinlock_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rwlock_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/spinlock.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rwlock.h \
    $(wildcard include/config/PREEMPT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/INLINE_SPIN_LOCK) \
    $(wildcard include/config/INLINE_SPIN_LOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK_BH) \
    $(wildcard include/config/UNINLINE_SPIN_UNLOCK) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/GENERIC_LOCKBREAK) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/INLINE_READ_LOCK) \
    $(wildcard include/config/INLINE_WRITE_LOCK) \
    $(wildcard include/config/INLINE_READ_LOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_LOCK_BH) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_READ_TRYLOCK) \
    $(wildcard include/config/INLINE_WRITE_TRYLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_BH) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQRESTORE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/refcount.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rbtree.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rbtree_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rcupdate.h \
    $(wildcard include/config/PREEMPT_RCU) \
    $(wildcard include/config/TINY_RCU) \
    $(wildcard include/config/RCU_STRICT_GRACE_PERIOD) \
    $(wildcard include/config/RCU_LAZY) \
    $(wildcard include/config/TASKS_RCU_GENERIC) \
    $(wildcard include/config/RCU_STALL_COMMON) \
    $(wildcard include/config/NO_HZ_FULL) \
    $(wildcard include/config/KVM_XFER_TO_GUEST_WORK) \
    $(wildcard include/config/RCU_NOCB_CPU) \
    $(wildcard include/config/TASKS_RCU) \
    $(wildcard include/config/TASKS_TRACE_RCU) \
    $(wildcard include/config/TASKS_RUDE_RCU) \
    $(wildcard include/config/TREE_RCU) \
    $(wildcard include/config/DEBUG_OBJECTS_RCU_HEAD) \
    $(wildcard include/config/PROVE_RCU) \
    $(wildcard include/config/ARCH_WEAK_RELEASE_ACQUIRE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/context_tracking_irq.h \
    $(wildcard include/config/CONTEXT_TRACKING_IDLE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rcutree.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/maple_tree.h \
    $(wildcard include/config/MAPLE_RCU_DISABLED) \
    $(wildcard include/config/DEBUG_MAPLE_TREE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rwsem.h \
    $(wildcard include/config/RWSEM_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_RWSEMS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/err.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/osq_lock.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/completion.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/swait.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/wait.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/wait.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/uprobes.h \
    $(wildcard include/config/UPROBES) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/page-flags-layout.h \
  include/generated/bounds.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/workqueue.h \
    $(wildcard include/config/DEBUG_OBJECTS_WORK) \
    $(wildcard include/config/FREEZER) \
    $(wildcard include/config/WQ_WATCHDOG) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/timer.h \
    $(wildcard include/config/DEBUG_OBJECTS_TIMERS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/ktime.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/jiffies.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/ktime.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/timekeeping.h \
    $(wildcard include/config/GENERIC_CMOS_UPDATE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/clocksource_ids.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/debugobjects.h \
    $(wildcard include/config/DEBUG_OBJECTS) \
    $(wildcard include/config/DEBUG_OBJECTS_FREE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/seqlock.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/mutex.h \
    $(wildcard include/config/MUTEX_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_MUTEXES) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/debug_locks.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/percpu_counter.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/percpu.h \
    $(wildcard include/config/RANDOM_KMALLOC_CACHES) \
    $(wildcard include/config/NEED_PER_CPU_PAGE_FIRST_CHUNK) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/mmdebug.h \
    $(wildcard include/config/DEBUG_VM) \
    $(wildcard include/config/DEBUG_VM_IRQSOFF) \
    $(wildcard include/config/DEBUG_VM_PGFLAGS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/CPU_HAS_ASID) \
    $(wildcard include/config/VDSO) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kmod.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/umh.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/gfp.h \
    $(wildcard include/config/ZONE_DMA) \
    $(wildcard include/config/ZONE_DMA32) \
    $(wildcard include/config/ZONE_DEVICE) \
    $(wildcard include/config/CONTIG_ALLOC) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/mmzone.h \
    $(wildcard include/config/ARCH_FORCE_MAX_ORDER) \
    $(wildcard include/config/CMA) \
    $(wildcard include/config/MEMORY_ISOLATION) \
    $(wildcard include/config/ZSMALLOC) \
    $(wildcard include/config/UNACCEPTED_MEMORY) \
    $(wildcard include/config/LRU_GEN_STATS) \
    $(wildcard include/config/MEMORY_HOTPLUG) \
    $(wildcard include/config/COMPACTION) \
    $(wildcard include/config/MEMORY_FAILURE) \
    $(wildcard include/config/PAGE_EXTENSION) \
    $(wildcard include/config/DEFERRED_STRUCT_PAGE_INIT) \
    $(wildcard include/config/HAVE_MEMORYLESS_NODES) \
    $(wildcard include/config/SPARSEMEM_EXTREME) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/list_nulls.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/nodemask.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/random.h \
    $(wildcard include/config/VMGENID) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/random.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/ioctl.h \
  arch/arm/include/generated/uapi/asm/ioctl.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/ioctl.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/ioctl.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/irqnr.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/irqnr.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/prandom.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/once.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/jump_label.h \
    $(wildcard include/config/HAVE_ARCH_JUMP_LABEL_RELATIVE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/pageblock-flags.h \
    $(wildcard include/config/HUGETLB_PAGE_SIZE_VARIABLE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/page-flags.h \
    $(wildcard include/config/ARCH_USES_PG_UNCACHED) \
    $(wildcard include/config/PAGE_IDLE_FLAG) \
    $(wildcard include/config/ARCH_USES_PG_ARCH_X) \
    $(wildcard include/config/HUGETLB_PAGE_OPTIMIZE_VMEMMAP) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/local_lock.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/local_lock_internal.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/memory_hotplug.h \
    $(wildcard include/config/HAVE_ARCH_NODEDATA_EXTENSION) \
    $(wildcard include/config/ARCH_HAS_ADD_PAGES) \
    $(wildcard include/config/MEMORY_HOTREMOVE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/notifier.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/srcu.h \
    $(wildcard include/config/TINY_SRCU) \
    $(wildcard include/config/NEED_SRCU_NMI_SAFE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rcu_segcblist.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/srcutree.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rcu_node_tree.h \
    $(wildcard include/config/RCU_FANOUT) \
    $(wildcard include/config/RCU_FANOUT_LEAF) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/topology.h \
    $(wildcard include/config/USE_PERCPU_NUMA_NODE_ID) \
    $(wildcard include/config/SCHED_SMT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/arch_topology.h \
    $(wildcard include/config/ACPI_CPPC_LIB) \
    $(wildcard include/config/GENERIC_ARCH_TOPOLOGY) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/topology.h \
    $(wildcard include/config/ARM_CPU_TOPOLOGY) \
    $(wildcard include/config/BL_SWITCHER) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/topology.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sysctl.h \
    $(wildcard include/config/SYSCTL) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/sysctl.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/elf.h \
    $(wildcard include/config/ARCH_USE_GNU_PROPERTY) \
    $(wildcard include/config/ARCH_HAVE_ELF_PROT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/elf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/vdso_datapage.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/datapage.h \
    $(wildcard include/config/ARCH_HAS_VDSO_DATA) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/clocksource.h \
    $(wildcard include/config/GENERIC_GETTIMEOFDAY) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/vdso/processor.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/vdso/gettimeofday.h \
    $(wildcard include/config/ARM_ARCH_TIMER) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/OABI_COMPAT) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/unistd.h \
  arch/arm/include/generated/uapi/asm/unistd-eabi.h \
  arch/arm/include/generated/asm/unistd-nr.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/vdso/cp15.h \
    $(wildcard include/config/CPU_CP15) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/user.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/elf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/elf-em.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kobject.h \
    $(wildcard include/config/UEVENT_HELPER) \
    $(wildcard include/config/DEBUG_KOBJECT_RELEASE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sysfs.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kernfs.h \
    $(wildcard include/config/KERNFS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/idr.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/radix-tree.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/xarray.h \
    $(wildcard include/config/XARRAY_MULTI) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sched/mm.h \
    $(wildcard include/config/MMU_LAZY_TLB_REFCOUNT) \
    $(wildcard include/config/ARCH_HAS_MEMBARRIER_CALLBACKS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sched.h \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_NATIVE) \
    $(wildcard include/config/SCHED_INFO) \
    $(wildcard include/config/SCHEDSTATS) \
    $(wildcard include/config/SCHED_CORE) \
    $(wildcard include/config/FAIR_GROUP_SCHED) \
    $(wildcard include/config/RT_GROUP_SCHED) \
    $(wildcard include/config/RT_MUTEXES) \
    $(wildcard include/config/UCLAMP_TASK) \
    $(wildcard include/config/UCLAMP_BUCKETS_COUNT) \
    $(wildcard include/config/KMAP_LOCAL) \
    $(wildcard include/config/CGROUP_SCHED) \
    $(wildcard include/config/BLK_DEV_IO_TRACE) \
    $(wildcard include/config/COMPAT_BRK) \
    $(wildcard include/config/CGROUPS) \
    $(wildcard include/config/BLK_CGROUP) \
    $(wildcard include/config/PSI) \
    $(wildcard include/config/PAGE_OWNER) \
    $(wildcard include/config/EVENTFD) \
    $(wildcard include/config/CPU_SUP_INTEL) \
    $(wildcard include/config/TASK_DELAY_ACCT) \
    $(wildcard include/config/STACKPROTECTOR) \
    $(wildcard include/config/ARCH_HAS_SCALED_CPUTIME) \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_GEN) \
    $(wildcard include/config/POSIX_CPUTIMERS) \
    $(wildcard include/config/POSIX_CPU_TIMERS_TASK_WORK) \
    $(wildcard include/config/KEYS) \
    $(wildcard include/config/SYSVIPC) \
    $(wildcard include/config/DETECT_HUNG_TASK) \
    $(wildcard include/config/IO_URING) \
    $(wildcard include/config/AUDIT) \
    $(wildcard include/config/AUDITSYSCALL) \
    $(wildcard include/config/UBSAN) \
    $(wildcard include/config/UBSAN_TRAP) \
    $(wildcard include/config/TASK_XACCT) \
    $(wildcard include/config/CPUSETS) \
    $(wildcard include/config/X86_CPU_RESCTRL) \
    $(wildcard include/config/FUTEX) \
    $(wildcard include/config/COMPAT) \
    $(wildcard include/config/PERF_EVENTS) \
    $(wildcard include/config/RSEQ) \
    $(wildcard include/config/FAULT_INJECTION) \
    $(wildcard include/config/LATENCYTOP) \
    $(wildcard include/config/FUNCTION_GRAPH_TRACER) \
    $(wildcard include/config/BCACHE) \
    $(wildcard include/config/SECURITY) \
    $(wildcard include/config/BPF_SYSCALL) \
    $(wildcard include/config/GCC_PLUGIN_STACKLEAK) \
    $(wildcard include/config/X86_MCE) \
    $(wildcard include/config/KRETPROBES) \
    $(wildcard include/config/RETHOOK) \
    $(wildcard include/config/ARCH_HAS_PARANOID_L1D_FLUSH) \
    $(wildcard include/config/RV) \
    $(wildcard include/config/USER_EVENTS) \
    $(wildcard include/config/ARCH_TASK_STRUCT_ON_STACK) \
    $(wildcard include/config/PREEMPT_NONE) \
    $(wildcard include/config/PREEMPT_VOLUNTARY) \
    $(wildcard include/config/DEBUG_RSEQ) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/sched.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/pid.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rculist.h \
    $(wildcard include/config/PROVE_RCU_LIST) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sem.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/sem.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/ipc.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rhashtable-types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/ipc.h \
  arch/arm/include/generated/uapi/asm/ipcbuf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/ipcbuf.h \
  arch/arm/include/generated/uapi/asm/sembuf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/sembuf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/shm.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/shm.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/hugetlb_encode.h \
  arch/arm/include/generated/uapi/asm/shmbuf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/shmbuf.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/shmparam.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kmsan_types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/plist.h \
    $(wildcard include/config/DEBUG_PLIST) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/hrtimer.h \
    $(wildcard include/config/HIGH_RES_TIMERS) \
    $(wildcard include/config/TIME_LOW_RES) \
    $(wildcard include/config/TIMERFD) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/hrtimer_defs.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/timerqueue.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/seccomp.h \
    $(wildcard include/config/SECCOMP) \
    $(wildcard include/config/HAVE_ARCH_SECCOMP_FILTER) \
    $(wildcard include/config/SECCOMP_FILTER) \
    $(wildcard include/config/CHECKPOINT_RESTORE) \
    $(wildcard include/config/SECCOMP_CACHE_DEBUG) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/seccomp.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/seccomp.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/seccomp.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/unistd.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/resource.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/resource.h \
  arch/arm/include/generated/uapi/asm/resource.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/resource.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/resource.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/latencytop.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sched/prio.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sched/types.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/signal_types.h \
    $(wildcard include/config/OLD_SIGACTION) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/signal.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/signal.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/signal.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/signal-defs.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/uapi/asm/sigcontext.h \
  arch/arm/include/generated/uapi/asm/siginfo.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/asm-generic/siginfo.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/syscall_user_dispatch.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/task_io_accounting.h \
    $(wildcard include/config/TASK_IO_ACCOUNTING) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/posix-timers.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/alarmtimer.h \
    $(wildcard include/config/RTC_CLASS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/uapi/linux/rseq.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kcsan.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rv.h \
    $(wildcard include/config/RV_REACTORS) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/livepatch_sched.h \
  arch/arm/include/generated/asm/kmap_size.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/kmap_size.h \
    $(wildcard include/config/DEBUG_KMAP_LOCAL) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/sync_core.h \
    $(wildcard include/config/ARCH_HAS_SYNC_CORE_BEFORE_USERMODE) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/kobject_ns.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/moduleparam.h \
    $(wildcard include/config/ALPHA) \
    $(wildcard include/config/IA64) \
    $(wildcard include/config/PPC64) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/rbtree_latch.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/error-injection.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/error-injection.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/tracepoint-defs.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/static_key.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/linux/dynamic_debug.h \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/module.h \
    $(wildcard include/config/ARM_UNWIND) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/include/asm-generic/module.h \
    $(wildcard include/config/HAVE_MOD_ARCH_SPECIFIC) \
    $(wildcard include/config/MODULES_USE_ELF_REL) \
    $(wildcard include/config/MODULES_USE_ELF_RELA) \
  /home/opa/embedded/fpga/xilinx/zynq/linux-xlnx/arch/arm/include/asm/unwind.h \

/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.o: $(deps_/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.o)

$(deps_/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/kernel_modules/package/hi/hi.o):
