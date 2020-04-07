#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>
#include <algorithm>

#define REPEAT2(x) x x
#define REPEAT8(x) REPEAT2(x) REPEAT2(x) REPEAT2(x) REPEAT2(x)
#define REPEAT32(x) REPEAT8(x) REPEAT8(x) REPEAT8(x) REPEAT8(x)
#define REPEAT(x) REPEAT32(x) REPEAT32(x)

template <class Word>
static void BM_WriteRand(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    Word* const pStart = static_cast<Word*>(start);
    register Word fill(0);

    size_t size = vec1.size() / sizeof(Word);
    std::vector<int> randPos(size);
    for (int i = 0; i < randPos.size(); ++i) {
        randPos[i] = i;
    }
    std::random_shuffle(randPos.begin(), randPos.end());

    while (state.KeepRunning()) {
        for (int pos = 0; pos < randPos.size();) {
            REPEAT(*(pStart + randPos[pos++]) = fill;)
        }
    }
}

template <class Word>
static void BM_WriteSeqIndex(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    Word* const pStart = static_cast<Word*>(start);
    register Word fill(0);

    size_t size = vec1.size() / sizeof(Word);
    std::vector<int> randPos(size);
    for (int i = 0; i < randPos.size(); ++i) {
        randPos[i] = i;
    }

    while (state.KeepRunning()) {
        for (int pos = 0; pos < randPos.size();) {
            REPEAT(*(pStart + randPos[pos++]) = fill;)
        }
    }
}

#define ARGS() ->RangeMultiplier(2)->Range(1024, 8*1024*1024)->UseRealTime();

// Register the function as a benchmark
BENCHMARK_TEMPLATE(BM_WriteRand, char) ARGS();
BENCHMARK_TEMPLATE(BM_WriteRand, int) ARGS();
BENCHMARK_TEMPLATE(BM_WriteRand, long) ARGS();
BENCHMARK_TEMPLATE(BM_WriteSeqIndex, char) ARGS();
BENCHMARK_TEMPLATE(BM_WriteSeqIndex, int) ARGS();
BENCHMARK_TEMPLATE(BM_WriteSeqIndex, long) ARGS();
