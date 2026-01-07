#ifndef __UTATOMIC_FLAGS_H__
#define __UTATOMIC_FLAGS_H__

#include "../utconfig.h"
#if UTB_CONFIG_ENABLE_ATOMIC == UTB_YES

#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED		0
#endif
#ifndef __ATOMIC_CONSUME
#define __ATOMIC_CONSUME		1
#endif
#ifndef __ATOMIC_ACQUIRE
#define __ATOMIC_ACQUIRE		2
#endif
#ifndef __ATOMIC_RELEASE
#define __ATOMIC_RELEASE		3
#endif
#ifndef __ATOMIC_ACQ_REL
#define __ATOMIC_ACQ_REL		4
#endif
#ifndef __ATOMIC_SEQ_CST
#define __ATOMIC_SEQ_CST		5
#endif

namespace utb {
   enum class memory_order : int {
        Relaxed = __ATOMIC_RELAXED,
        Consume = __ATOMIC_CONSUME,
        Acquire = __ATOMIC_ACQUIRE,
        Release = __ATOMIC_RELEASE,
        AcqRel = __ATOMIC_ACQ_REL,
        SeqCst = __ATOMIC_SEQ_CST
    };
    namespace modifier {
        enum  basic_atomic_gcc_memory_order_modifier  {
            Mask          = 0x0ffff,
            ModifierMask  = 0xffff0000,
            HleAcquire    = 0x10000,
            HleRelease    = 0x20000
        };
        using memory_order = basic_atomic_gcc_memory_order_modifier;
    }
    inline  memory_order operator | (memory_order mMemOrder, modifier::memory_order mod) {
        return memory_order(int(mMemOrder) | int(mod));
    }

    inline  memory_order operator & (memory_order mMemOrder, modifier::memory_order mod) {
        return memory_order(int(mMemOrder) & int(mod));
    }

    namespace internal {
        template <typename TFlag>
        struct atomic_flag {
            using flag_type = TFlag;
            flag_type __flag;

            constexpr atomic_flag(const flag_type& flag) : __flag(flag) { }
        };
    }
} // namespace utb


#endif // UTB_CONFIG_ENABLE_ATOMIC
#endif // __UTATOMIC_FLAGS_H__