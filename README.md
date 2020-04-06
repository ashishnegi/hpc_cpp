# hpc_cpp
benchmarking in cpp


# building google benchmark lib

```
# Check out the library.
$ git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest

Install VS 2019
Open the benchmark folder.
Right click on "CMakeLists.txt", select "Build" and "Run Tests"
```

In Developer command prompt for X64, interactive developer command prompt:

```
> type nul >> hpc_cpp.cpp
> msbuild -p:Configuration=Release
> x64\Release\hpc_cpp.exe --benchmark_filter=.*Add.*
```

```
04/05/20 22:12:26
Running x64\Release\hpc_cpp.exe
Run on (8 X 2808 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB (x1)

> Without DoNotOptimize

-------------------------------------------------------
Benchmark             Time             CPU   Iterations
-------------------------------------------------------
BM_Add            0.300 ns        0.297 ns   1000000000
BM_MutexAdd        23.6 ns         23.5 ns     29866667
BM_AtomicAdd       5.65 ns         5.75 ns     89600000
-------------------------------------------------------

> With DoNotOptimize

Benchmark             Time             CPU   Iterations
-------------------------------------------------------
BM_Add             1.27 ns         1.22 ns    497777778
BM_MutexAdd        23.8 ns         24.0 ns     34461538
BM_AtomicAdd       8.18 ns         8.16 ns     74666667

D:\gitrepos\hpc_benchmark\hpc_cpp\hpc_cpp>x64\Release\hpc_cpp.exe
04/06/20 00:34:29
Running x64\Release\hpc_cpp.exe
Run on (8 X 2808 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB (x1)
---------------------------------------------------------------------------------------------
Benchmark                                                   Time             CPU   Iterations
---------------------------------------------------------------------------------------------
BM_noLockAdd                                             1.64 ns         1.64 ns    448000000
BM_MultiThreadedMutexAdd/real_time/threads:1             23.6 ns         24.0 ns     27389563
BM_MultiThreadedMutexAdd/real_time/threads:2             34.3 ns         67.7 ns     15225302
BM_MultiThreadedMutexAdd/real_time/threads:4             36.8 ns          146 ns     17160792
BM_MultiThreadedMutexAdd/real_time/threads:8             41.3 ns          325 ns     16747440
BM_MultiThreadedMutexAdd/real_time/threads:12            40.2 ns          328 ns     18110520
BM_MultiThreadedMutexAdd/real_time/threads:16            39.8 ns          326 ns     16000000
BM_MultiThreadedMutexAdd/real_time/threads:32            37.5 ns          324 ns     21492640
BM_MultiThreadedMutexBaseline/real_time/threads:1        48.7 ns         49.4 ns     12974376
BM_MultiThreadedMutexBaseline/real_time/threads:2        30.0 ns         59.5 ns     20470380
BM_MultiThreadedMutexBaseline/real_time/threads:4        33.8 ns          130 ns     19163332
BM_MultiThreadedMutexBaseline/real_time/threads:8        39.4 ns          308 ns     17966552
BM_MultiThreadedMutexBaseline/real_time/threads:12       36.6 ns          304 ns     18119268
BM_MultiThreadedMutexBaseline/real_time/threads:16       38.1 ns          308 ns     20118864
BM_MultiThreadedMutexBaseline/real_time/threads:32       36.5 ns          309 ns     42667744
BM_MultiThreadedAtomicAdd/real_time/threads:1            7.76 ns         7.87 ns     91371049
BM_MultiThreadedAtomicAdd/real_time/threads:2            14.3 ns         28.8 ns     47166488
BM_MultiThreadedAtomicAdd/real_time/threads:4            20.1 ns         79.8 ns     35235528
BM_MultiThreadedAtomicAdd/real_time/threads:8            21.4 ns          166 ns     33263624
BM_MultiThreadedAtomicAdd/real_time/threads:12           21.0 ns          175 ns     34309692
BM_MultiThreadedAtomicAdd/real_time/threads:16           21.0 ns          175 ns     36787696
BM_MultiThreadedAtomicAdd/real_time/threads:32           19.6 ns          172 ns     32000000
BM_FalseSharingMutexAddBefore/real_time/threads:1        25.4 ns         25.3 ns     28371140
BM_FalseSharingMutexAddBefore/real_time/threads:2        29.8 ns         60.0 ns     24752782
BM_FalseSharingMutexAddBefore/real_time/threads:4        33.5 ns          134 ns     20400328
BM_FalseSharingMutexAddBefore/real_time/threads:8        37.5 ns          293 ns     18610168
BM_FalseSharingMutexAddBefore/real_time/threads:12       39.7 ns          323 ns     19371936
BM_FalseSharingMutexAddAfter/real_time/threads:1         24.4 ns         24.1 ns     29128084
BM_FalseSharingMutexAddAfter/real_time/threads:2         26.9 ns         53.9 ns     25789266
BM_FalseSharingMutexAddAfter/real_time/threads:4         33.3 ns          131 ns     21199444
BM_FalseSharingMutexAddAfter/real_time/threads:8         37.5 ns          288 ns     18301656
BM_FalseSharingMutexAddAfter/real_time/threads:12        38.9 ns          320 ns     19180848
BM_FalseSharingMutexAddFar/real_time/threads:1           49.9 ns         50.2 ns     28607953
BM_FalseSharingMutexAddFar/real_time/threads:2           26.2 ns         51.2 ns     25029526
BM_FalseSharingMutexAddFar/real_time/threads:4           34.8 ns          138 ns     21451872
BM_FalseSharingMutexAddFar/real_time/threads:8           40.1 ns          319 ns     17197144
BM_FalseSharingMutexAddFar/real_time/threads:12          39.3 ns          318 ns     18298692
```