#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>
#include <chrono>
#include <thread>

namespace spinlocks
{
    class Spinlock
    {
        public:
        Spinlock() { flag.clear(); }

        void lock() {
            while (true) {
                int tryLefts = 10;
                while (tryLefts > 0) {
                    if (!flag.test_and_set()) {
                        return;
                    }
                    tryLefts -= 1;
                }

                // this is better than no sleeping
                // but it sleeps for more than 1 nanoseconds..
                // so it does not beat the mutex.
                std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            }
        }

        void unlock() {
            flag.clear();
        }

        private:
        std::atomic_flag flag;
    };

    Spinlock spinlock;
    volatile long dummy_x;
    volatile long *px = new long();
    volatile long &x = *px;

    static void BM_noSpinlockAdd(benchmark::State& state) {
        if (state.thread_index == 0) {
            x = 0;
        }

        while (state.KeepRunning()) {
            x += 1;
            benchmark::DoNotOptimize(x);
        }

        benchmark::ClobberMemory();
    }

    static void BM_SpinlockAdd(benchmark::State& state) {
        if (state.thread_index == 0) {
            x = 0;
        }

        while (state.KeepRunning()) {
            std::lock_guard<Spinlock> locked(spinlock);
            x += 1;
            benchmark::DoNotOptimize(x);
        }

        benchmark::ClobberMemory();
    }


    #define ARGS(N) ->Threads(N)->UseRealTime();

    // Register the function as a benchmark
    BENCHMARK(BM_noSpinlockAdd) ARGS(1);
    BENCHMARK(BM_noSpinlockAdd) ARGS(4);
    BENCHMARK(BM_noSpinlockAdd) ARGS(8);
    BENCHMARK(BM_SpinlockAdd) ARGS(1);
    BENCHMARK(BM_SpinlockAdd) ARGS(2);
    BENCHMARK(BM_SpinlockAdd) ARGS(4);
    BENCHMARK(BM_SpinlockAdd) ARGS(8);
    BENCHMARK(BM_SpinlockAdd) ARGS(12);
    BENCHMARK(BM_SpinlockAdd) ARGS(16);
}