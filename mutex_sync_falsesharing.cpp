#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>

namespace false_sharing
{
    volatile long mutex_add_before = 0;
    std::mutex mutex_lock;
    volatile long mutex_add_after = 0;
    volatile long *mutex_add_far_p = new long(0);
    volatile long& mutex_add_far = *mutex_add_far_p;

    static void BM_FalseSharingMutexAddBefore(benchmark::State& state) {
        if (state.thread_index == 0) {
            mutex_add_before = 0;
        }

        while (state.KeepRunning()) {
            std::lock_guard<std::mutex> guard(mutex_lock);
            mutex_add_before += 1;
            benchmark::DoNotOptimize(mutex_add_before);
        }

        benchmark::ClobberMemory();
    }

    static void BM_FalseSharingMutexAddAfter(benchmark::State& state) {
        if (state.thread_index == 0) {
            mutex_add_after = 0;
        }

        while (state.KeepRunning()) {
            std::lock_guard<std::mutex> guard(mutex_lock);
            mutex_add_after += 1;
            benchmark::DoNotOptimize(mutex_add_after);
        }

        benchmark::ClobberMemory();
    }

    static void BM_FalseSharingMutexAddFar(benchmark::State& state) {
        if (state.thread_index == 0) {
            mutex_add_far = 0;
        }

        while (state.KeepRunning()) {
            std::lock_guard<std::mutex> guard(mutex_lock);
            mutex_add_far += 1;
            benchmark::DoNotOptimize(mutex_add_far);
        }

        benchmark::ClobberMemory();
    }

    #define ARGS(N) ->Threads(N)->UseRealTime();

    // Register the function as a benchmark
    BENCHMARK(BM_FalseSharingMutexAddBefore) ARGS(1);
    BENCHMARK(BM_FalseSharingMutexAddBefore) ARGS(2);
    BENCHMARK(BM_FalseSharingMutexAddBefore) ARGS(4);
    BENCHMARK(BM_FalseSharingMutexAddBefore) ARGS(8);
    BENCHMARK(BM_FalseSharingMutexAddBefore) ARGS(12);
    BENCHMARK(BM_FalseSharingMutexAddAfter) ARGS(1);
    BENCHMARK(BM_FalseSharingMutexAddAfter) ARGS(2);
    BENCHMARK(BM_FalseSharingMutexAddAfter) ARGS(4);
    BENCHMARK(BM_FalseSharingMutexAddAfter) ARGS(8);
    BENCHMARK(BM_FalseSharingMutexAddAfter) ARGS(12);
    BENCHMARK(BM_FalseSharingMutexAddFar) ARGS(1);
    BENCHMARK(BM_FalseSharingMutexAddFar) ARGS(2);
    BENCHMARK(BM_FalseSharingMutexAddFar) ARGS(4);
    BENCHMARK(BM_FalseSharingMutexAddFar) ARGS(8);
    BENCHMARK(BM_FalseSharingMutexAddFar) ARGS(12);
} // namespace false_sharing

