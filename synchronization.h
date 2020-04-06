#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>

static void BM_Add(benchmark::State& state) {
    int add = 0;

    for (auto _ : state) {
        add += 1;
        benchmark::DoNotOptimize(add);
    }

    benchmark::ClobberMemory();
}

static void BM_MutexAdd(benchmark::State& state) {
    std::mutex lock;
    int add = 0;

    for (auto _ : state) {
        std::lock_guard<std::mutex> guard(lock);
        add += 1;
        benchmark::DoNotOptimize(add);
    }

    benchmark::ClobberMemory();
}

static void BM_AtomicAdd(benchmark::State& state) {
    std::atomic_int add = 0;
    for (auto _ : state) {
        add++;
        benchmark::DoNotOptimize(add);
    }

    benchmark::ClobberMemory();
}
