#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>

namespace spinlocks
{
    class Spinlock
    {
        public:
        Spinlock() { flag.clear(); }

        void lock() {
            while (flag.test_and_set()) {}
        }

        void unlock() {
            flag.clear();
        }

        private:
        std::atomic_flag flag;
    };

    long *px = new long();
    long &x = *px;
    Spinlock spinlock;

    static void BM_noSpinLockAdd(benchmark::State& state) {
        if (state.thread_index == 0) {
            x = 0;
        }

        while (state.KeepRunning()) {
            benchmark::DoNotOptimize(x++);
        }

        benchmark::ClobberMemory();
    }

    static void BM_SpinlockAdd(benchmark::State& state) {
        if (state.thread_index == 0) {
            x = 0;
        }

        while (state.KeepRunning()) {
            std::lock_guard<Spinlock> locked(spinlock);
            benchmark::DoNotOptimize(x++);
        }

        benchmark::ClobberMemory();
    }


    #define ARGS(N) ->Threads(N)->UseRealTime();

    // Register the function as a benchmark
    BENCHMARK(BM_noSpinLockAdd) ARGS(1);
    BENCHMARK(BM_noSpinLockAdd) ARGS(4);
    BENCHMARK(BM_noSpinLockAdd) ARGS(8);
    BENCHMARK(BM_noSpinLockAdd) ARGS(12);
    BENCHMARK(BM_noSpinLockAdd) ARGS(16);
    BENCHMARK(BM_SpinlockAdd) ARGS(1);
    BENCHMARK(BM_SpinlockAdd) ARGS(4);
    BENCHMARK(BM_SpinlockAdd) ARGS(8);
    BENCHMARK(BM_SpinlockAdd) ARGS(12);
    BENCHMARK(BM_SpinlockAdd) ARGS(16);
}