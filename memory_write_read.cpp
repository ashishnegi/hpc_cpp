#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>

#define REPEAT2(x) x x
#define REPEAT8(x) REPEAT2(x) REPEAT2(x) REPEAT2(x) REPEAT2(x)
#define REPEAT32(x) REPEAT8(x) REPEAT8(x) REPEAT8(x) REPEAT8(x)
#define REPEAT(x) REPEAT32(x) REPEAT32(x)

template <class Word>
static void BM_WriteSeq(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    void* const end = vec1.data() + vec1.size();
    Word* const pStart = static_cast<Word*>(start);
    Word* const pEnd = static_cast<Word*>(end);
    register Word fill(0);

    while (state.KeepRunning()) {
        for (volatile Word *p = pStart; p < pEnd;) {
            REPEAT(*p++ = fill;)
        }
    }
}

template <class Word>
static void BM_ReadSeq(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    void* const end = vec1.data() + vec1.size();
    Word* const pStart = static_cast<Word*>(start);
    Word* const pEnd = static_cast<Word*>(end);
    register Word fill(0);

    while (state.KeepRunning()) {
        for (volatile Word *p = pStart; p < pEnd;) {
            REPEAT(fill = *p++;)
        }
    }
}

#define ARGS() ->RangeMultiplier(2)->Range(1024, 8*1024*1024)->UseRealTime();

// Register the function as a benchmark
BENCHMARK_TEMPLATE(BM_WriteSeq, char) ARGS();
BENCHMARK_TEMPLATE(BM_WriteSeq, int) ARGS();
BENCHMARK_TEMPLATE(BM_WriteSeq, long) ARGS();
BENCHMARK_TEMPLATE(BM_ReadSeq, char) ARGS();
BENCHMARK_TEMPLATE(BM_ReadSeq, int) ARGS();
BENCHMARK_TEMPLATE(BM_ReadSeq, long) ARGS();
