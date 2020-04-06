# hpc_cpp
benchmarking in cpp


## building google benchmark lib

```
# Check out the library.
$ git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest

Install VS 2019
Open the benchmark folder.
Right click on "CMakeLists.txt", select "Build" and "Run Tests"
```

## Running benchmark
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

>x64\Release\hpc_cpp.exe --benchmark_filter=.*BM_.*Seq.*
04/06/20 01:13:38
Running x64\Release\hpc_cpp.exe
Run on (8 X 2808 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB (x1)
------------------------------------------------------------------------------
Benchmark                                    Time             CPU   Iterations
------------------------------------------------------------------------------
BM_WriteSeq<char>/1024/real_time          2109 ns         2113 ns       480632
BM_WriteSeq<char>/2048/real_time          3056 ns         3030 ns       216577
BM_WriteSeq<char>/4096/real_time          7304 ns         7404 ns       120284
BM_WriteSeq<char>/8192/real_time         13924 ns        13710 ns        71802
BM_WriteSeq<char>/16384/real_time        22507 ns        22819 ns        29444
BM_WriteSeq<char>/32768/real_time        43160 ns        42398 ns        12530
BM_WriteSeq<char>/65536/real_time        88566 ns        89448 ns         7162
BM_WriteSeq<char>/131072/real_time      202095 ns       196331 ns         4218
BM_WriteSeq<char>/262144/real_time      382236 ns       378024 ns         1984
BM_WriteSeq<char>/524288/real_time      874412 ns       869436 ns          629
BM_WriteSeq<char>/1048576/real_time    1717068 ns      1696016 ns          433
BM_WriteSeq<char>/2097152/real_time    3164236 ns      3102022 ns          272
BM_WriteSeq<int>/1024/real_time            638 ns          645 ns      1429568
BM_WriteSeq<int>/2048/real_time           1288 ns         1287 ns       704300
BM_WriteSeq<int>/4096/real_time           2570 ns         2550 ns       428857
BM_WriteSeq<int>/8192/real_time           5948 ns         5919 ns       150481
BM_WriteSeq<int>/16384/real_time         12137 ns        12352 ns        50600
BM_WriteSeq<int>/32768/real_time         18359 ns        17558 ns        40935
BM_WriteSeq<int>/65536/real_time         49087 ns        45775 ns        16726
BM_WriteSeq<int>/131072/real_time        68667 ns        63930 ns         7821
BM_WriteSeq<int>/262144/real_time       146850 ns       146121 ns         4705
BM_WriteSeq<int>/524288/real_time       371172 ns       359583 ns         2781
BM_WriteSeq<int>/1048576/real_time      795483 ns       777715 ns         1105
BM_WriteSeq<int>/2097152/real_time     1343478 ns      1342236 ns          454
BM_WriteSeq<long>/1024/real_time           716 ns          705 ns      1130117
BM_WriteSeq<long>/2048/real_time          1328 ns         1307 ns       502088
BM_WriteSeq<long>/4096/real_time          2988 ns         2933 ns       234402
BM_WriteSeq<long>/8192/real_time          6181 ns         6125 ns       119893
BM_WriteSeq<long>/16384/real_time        11312 ns        11182 ns        65672
BM_WriteSeq<long>/32768/real_time        23213 ns        23157 ns        28339
BM_WriteSeq<long>/65536/real_time        43210 ns        43461 ns        11864
BM_WriteSeq<long>/131072/real_time       91471 ns        89866 ns         7998
BM_WriteSeq<long>/262144/real_time      178704 ns       178100 ns         3597
BM_WriteSeq<long>/524288/real_time      365593 ns       357143 ns         2100
BM_WriteSeq<long>/1048576/real_time     803280 ns       777633 ns          864
BM_WriteSeq<long>/2097152/real_time    1489450 ns      1451503 ns          549
BM_ReadSeq<char>/1024/real_time           2265 ns         2266 ns       337864
BM_ReadSeq<char>/2048/real_time           4479 ns         4453 ns       122819
BM_ReadSeq<char>/4096/real_time           9359 ns         9238 ns        65963
BM_ReadSeq<char>/8192/real_time          18571 ns        18453 ns        33870
BM_ReadSeq<char>/16384/real_time         36387 ns        35746 ns        16173
BM_ReadSeq<char>/32768/real_time         76064 ns        76802 ns         7324
BM_ReadSeq<char>/65536/real_time        143883 ns       140501 ns         4782
BM_ReadSeq<char>/131072/real_time       244641 ns       238423 ns         2818
BM_ReadSeq<char>/262144/real_time       602944 ns       574226 ns         1034
BM_ReadSeq<char>/524288/real_time      1449056 ns      1443273 ns          498
BM_ReadSeq<char>/1048576/real_time     2308422 ns      2332090 ns          335
BM_ReadSeq<char>/2097152/real_time     5479398 ns      5531832 ns          161
BM_ReadSeq<int>/1024/real_time             683 ns          681 ns       871777
BM_ReadSeq<int>/2048/real_time            1635 ns         1580 ns       583310
BM_ReadSeq<int>/4096/real_time            2195 ns         2166 ns       259666
BM_ReadSeq<int>/8192/real_time            3754 ns         3719 ns       193277
BM_ReadSeq<int>/16384/real_time           6776 ns         6747 ns       108852
BM_ReadSeq<int>/32768/real_time          13497 ns        13681 ns        37690
BM_ReadSeq<int>/65536/real_time          26702 ns        26628 ns        24058
BM_ReadSeq<int>/131072/real_time         61816 ns        62138 ns        13830
BM_ReadSeq<int>/262144/real_time        109191 ns       108759 ns         6465
BM_ReadSeq<int>/524288/real_time        242060 ns       241831 ns         3489
BM_ReadSeq<int>/1048576/real_time       421791 ns       422026 ns         1555
BM_ReadSeq<int>/2097152/real_time       859269 ns       859175 ns          782
BM_ReadSeq<long>/1024/real_time            443 ns          410 ns      1599556
BM_ReadSeq<long>/2048/real_time            813 ns          812 ns       904367
BM_ReadSeq<long>/4096/real_time           1783 ns         1793 ns       331162
BM_ReadSeq<long>/8192/real_time           3189 ns         3197 ns       166185
BM_ReadSeq<long>/16384/real_time          6806 ns         6816 ns        98568
BM_ReadSeq<long>/32768/real_time         13282 ns        12530 ns        56115
BM_ReadSeq<long>/65536/real_time         25787 ns        25617 ns        28057
BM_ReadSeq<long>/131072/real_time        52109 ns        52747 ns        13034
BM_ReadSeq<long>/262144/real_time       142264 ns       140728 ns         3775
BM_ReadSeq<long>/524288/real_time       195236 ns       198805 ns         2908
BM_ReadSeq<long>/1048576/real_time      461469 ns       464015 ns         1650
BM_ReadSeq<long>/2097152/real_time      810768 ns       774212 ns          888

```