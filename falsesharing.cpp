#include <benchmark/benchmark.h>
#include <vector>
#include <atomic>

namespace false_sharing
{
    const int NumThreads = 12;
    std::atomic_int global_nonshared[NumThreads];

    static void BM_FalseSharing2Global(benchmark::State& state) {
        if (state.thread_index == 0) {
            for (int i = 0; i < NumThreads; ++i) {
                global_nonshared[i] = 0;
            }
        }

        while (state.KeepRunning()) {
            benchmark::DoNotOptimize(global_nonshared[state.thread_index]++);
        }

        benchmark::ClobberMemory();
    }

    static void BM_FalseSharing2Local(benchmark::State& state) {
        std::atomic_int local_nonshared = 0;

        while (state.KeepRunning()) {
            benchmark::DoNotOptimize(local_nonshared++);
        }

        benchmark::ClobberMemory();
    }

    #define ARGS(N) ->Threads(N)->UseRealTime();

    // Register the function as a benchmark
    BENCHMARK(BM_FalseSharing2Global) ARGS(1);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2);
    BENCHMARK(BM_FalseSharing2Global) ARGS(4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(12);
    BENCHMARK(BM_FalseSharing2Local) ARGS(1);
    BENCHMARK(BM_FalseSharing2Local) ARGS(2);
    BENCHMARK(BM_FalseSharing2Local) ARGS(4);
    BENCHMARK(BM_FalseSharing2Local) ARGS(8);
    BENCHMARK(BM_FalseSharing2Local) ARGS(12);
} // namespace false_sharing

