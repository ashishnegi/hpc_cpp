#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>
#include <algorithm>
#include <random>

#define REPEAT2(x) x x
#define REPEAT8(x) REPEAT2(x) REPEAT2(x) REPEAT2(x) REPEAT2(x)
#define REPEAT32(x) REPEAT8(x) REPEAT8(x) REPEAT8(x) REPEAT8(x)
#define REPEAT64(x) REPEAT32(x) REPEAT32(x)
#define REPEAT(x) REPEAT64(x) REPEAT64(x)

template <class Word>
static void BM_WriteRandThreaded(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    Word* const pStart = static_cast<Word*>(start);
    Word fill(0);

    size_t size = vec1.size() / sizeof(Word);
    std::vector<int> randPos(size);
    for (int i = 0; i < randPos.size(); ++i) {
        randPos[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(randPos.begin(), randPos.end(), g);

    while (state.KeepRunning()) {
        for (int pos = 0; pos < randPos.size();) {
            REPEAT(*(pStart + randPos[pos++]) = fill;)
        }
    }
}

template <class Word>
static void BM_WriteSeqIndexThreaded(benchmark::State& state) {
    std::vector<char> vec1(state.range(0));
    void* const start = vec1.data();
    Word* const pStart = static_cast<Word*>(start);
    Word fill(0);

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

#define ARGS(N) ->RangeMultiplier(2)->Range(1024, 8*1024*1024)->Threads(N)->UseRealTime();

// Register the function as a benchmark
BENCHMARK_TEMPLATE(BM_WriteRandThreaded, long) ARGS(1);
BENCHMARK_TEMPLATE(BM_WriteRandThreaded, long) ARGS(2);
BENCHMARK_TEMPLATE(BM_WriteRandThreaded, long) ARGS(4);
BENCHMARK_TEMPLATE(BM_WriteSeqIndexThreaded, long) ARGS(1);
BENCHMARK_TEMPLATE(BM_WriteSeqIndexThreaded, long) ARGS(2);
BENCHMARK_TEMPLATE(BM_WriteSeqIndexThreaded, long) ARGS(4);