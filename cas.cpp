#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>
#include <chrono>
#include <thread>

namespace cas
{
    std::atomic_long x(0);

    static void BM_CASAdd(benchmark::State& state) {
        if (state.thread_index == 0) {
            x = 0;
        }

        while (state.KeepRunning()) {
            long read_x = x.load(std::memory_order_relaxed);
            while (!x.compare_exchange_strong(read_x, read_x + 1, std::memory_order_relaxed)) {}
            benchmark::DoNotOptimize(x);
        }

        benchmark::ClobberMemory();
    }

    #define ARGS(N) ->Threads(N)->UseRealTime();

    // Register the function as a benchmark
    BENCHMARK(BM_CASAdd) ARGS(1);
    BENCHMARK(BM_CASAdd) ARGS(2);
    BENCHMARK(BM_CASAdd) ARGS(4);
    BENCHMARK(BM_CASAdd) ARGS(8);
}