#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>

template <class Word>
static void BM_WriteSeq(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    void* const end = vec1.data() + vec1.size();
    Word* const pStart = static_cast<Word*>(start);
    Word* const pEnd = static_cast<Word*>(end);
    Word fill(0);

    while (state.KeepRunning()) {
        for (Word *p = pStart; p < pEnd; ++p) {
            benchmark::DoNotOptimize(*p = fill);
        }
    }

    benchmark::ClobberMemory();
}

template <class Word>
static void BM_ReadSeq(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    void* const end = vec1.data() + vec1.size();
    Word* const pStart = static_cast<Word*>(start);
    Word* const pEnd = static_cast<Word*>(end);
    Word fill(0);

    while (state.KeepRunning()) {
        for (Word *p = pStart; p < pEnd; ++p) {
            benchmark::DoNotOptimize(fill = *p);
        }
    }

    benchmark::ClobberMemory();
}

#define ARGS() ->RangeMultiplier(2)->Range(1024, 2*1024*1024)->UseRealTime();

// Register the function as a benchmark
BENCHMARK_TEMPLATE(BM_WriteSeq, char) ARGS();
BENCHMARK_TEMPLATE(BM_WriteSeq, int) ARGS();
BENCHMARK_TEMPLATE(BM_WriteSeq, long) ARGS();
BENCHMARK_TEMPLATE(BM_ReadSeq, char) ARGS();
BENCHMARK_TEMPLATE(BM_ReadSeq, int) ARGS();
BENCHMARK_TEMPLATE(BM_ReadSeq, long) ARGS();
