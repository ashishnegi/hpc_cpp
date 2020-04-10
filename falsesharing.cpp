#include <benchmark/benchmark.h>
#include <vector>
#include <atomic>

namespace false_sharing
{
    const int N = 1024;
    std::atomic_int global_nonshared[4096];

    static void BM_FalseSharing2Global(benchmark::State& state) {
        if (state.thread_index == 0) {
            for (int i = 0; i < sizeof(global_nonshared)/sizeof(global_nonshared[0]); ++i) {
                global_nonshared[i] = 0;
            }
        }

        size_t pos = state.range_x() * state.thread_index;
        while (state.KeepRunning()) {
            for (int i = 0; i < N; ++i) {
                benchmark::DoNotOptimize(global_nonshared[pos]++);
            }
        }

        benchmark::ClobberMemory();
    }

    static void BM_FalseSharing2Local(benchmark::State& state) {
        std::atomic_int local_nonshared = 0;

        while (state.KeepRunning()) {
            for (int i = 0; i < N; ++i) {
                benchmark::DoNotOptimize(local_nonshared++);
            }
        }

        benchmark::ClobberMemory();
    }

    #define ARGS(N, M) ->Threads(N)->Arg(M)->UseRealTime();

    // Register the function as a benchmark
    BENCHMARK(BM_FalseSharing2Global) ARGS(1, 0);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2, 0);
    BENCHMARK(BM_FalseSharing2Global) ARGS(4, 0);
    BENCHMARK(BM_FalseSharing2Global) ARGS(8, 0);
    BENCHMARK(BM_FalseSharing2Global) ARGS(12, 0);
    BENCHMARK(BM_FalseSharing2Global) ARGS(1, 4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2, 4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(4, 4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(8, 4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(12, 4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(1, 8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2, 8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(4, 8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(8, 8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(12, 8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(1, 16);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2, 16);
    BENCHMARK(BM_FalseSharing2Global) ARGS(4, 16);
    BENCHMARK(BM_FalseSharing2Global) ARGS(8, 16);
    BENCHMARK(BM_FalseSharing2Global) ARGS(12, 16);
    BENCHMARK(BM_FalseSharing2Local) ARGS(1, 0);
    BENCHMARK(BM_FalseSharing2Local) ARGS(2, 0);
    BENCHMARK(BM_FalseSharing2Local) ARGS(4, 0);
    BENCHMARK(BM_FalseSharing2Local) ARGS(8, 0);
    BENCHMARK(BM_FalseSharing2Local) ARGS(12, 0);
} // namespace false_sharing

