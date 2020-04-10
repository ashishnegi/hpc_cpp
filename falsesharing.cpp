#include <benchmark/benchmark.h>
#include <vector>
#include <atomic>

namespace false_sharing
{
    const int N = 1024;
    long global_nonshared[4096];

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
        long local_nonshared = 0;

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
    BENCHMARK(BM_FalseSharing2Global) ARGS(1, 4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2, 4);
    BENCHMARK(BM_FalseSharing2Global) ARGS(1, 8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2, 8);
    BENCHMARK(BM_FalseSharing2Global) ARGS(1, 16);
    BENCHMARK(BM_FalseSharing2Global) ARGS(2, 16);
    BENCHMARK(BM_FalseSharing2Local) ARGS(1, 0);
    BENCHMARK(BM_FalseSharing2Local) ARGS(2, 0);
} // namespace false_sharing

