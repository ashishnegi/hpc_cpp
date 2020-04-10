#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>

static void BM_noLockAdd(benchmark::State& state) {
    long add = 0;
    int N = 1024;
    for (auto _ : state) {
        for (int i = 0; i < N; ++i) {
            benchmark::DoNotOptimize(add++);
        }
    }

    benchmark::ClobberMemory();
}

volatile long mutex_add = 0;
std::mutex mutex_lock;

static void BM_MultiThreadedMutexAdd(benchmark::State& state) {
    if (state.thread_index == 0) {
        mutex_add = 0;
    }

    int N = 1024;
    while (state.KeepRunning()) {
        for (int i = 0; i < N; ++i) {
            std::lock_guard<std::mutex> guard(mutex_lock);
            mutex_add += 1;
            benchmark::DoNotOptimize(mutex_add);
        }
    }

    benchmark::ClobberMemory();
}

std::atomic_long atomic_add = 0;

static void BM_MultiThreadedAtomicAdd(benchmark::State& state) {
    if (state.thread_index == 0) {
        atomic_add = 0;
    }

    int N = 1024;
    while (state.KeepRunning()) {
        for (int i = 0; i < N; ++i) {
            benchmark::DoNotOptimize(atomic_add++);
        }
    }

    benchmark::ClobberMemory();
}

#define ARGS(N) ->Threads(N)->UseRealTime();

// Register the function as a benchmark
BENCHMARK(BM_noLockAdd);
BENCHMARK(BM_MultiThreadedMutexAdd) ARGS(1);
BENCHMARK(BM_MultiThreadedMutexAdd) ARGS(2);
BENCHMARK(BM_MultiThreadedMutexAdd) ARGS(4);
BENCHMARK(BM_MultiThreadedMutexAdd) ARGS(8);
BENCHMARK(BM_MultiThreadedMutexAdd) ARGS(12);
BENCHMARK(BM_MultiThreadedMutexAdd) ARGS(16);
BENCHMARK(BM_MultiThreadedMutexAdd) ARGS(32);
BENCHMARK(BM_MultiThreadedAtomicAdd) ARGS(1);
BENCHMARK(BM_MultiThreadedAtomicAdd) ARGS(2);
BENCHMARK(BM_MultiThreadedAtomicAdd) ARGS(4);
BENCHMARK(BM_MultiThreadedAtomicAdd) ARGS(8);
BENCHMARK(BM_MultiThreadedAtomicAdd) ARGS(12);
BENCHMARK(BM_MultiThreadedAtomicAdd) ARGS(16);
BENCHMARK(BM_MultiThreadedAtomicAdd) ARGS(32);
