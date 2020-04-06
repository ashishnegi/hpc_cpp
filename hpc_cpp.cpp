// hpc_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// tried separating benchmark in different executables.
// will use
// x64\Release\hpc_cpp.exe --benchmark_filter=.*Add.*
// cl /Zi /EHsc /I google\x64-Release\include\ hpc_cpp.cpp  benchmark.lib benchmark_main.lib /link /Machine:X64 /libpath:".\google\x64-Debug\lib" /out:hpc_cpp.exe

#include <benchmark/benchmark.h>
#include "synchronization.h"

// Register the function as a benchmark
BENCHMARK(BM_Add);
BENCHMARK(BM_MutexAdd);
BENCHMARK(BM_AtomicAdd);

// Run the benchmark
BENCHMARK_MAIN();

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
