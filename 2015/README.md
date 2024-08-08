# 2015

## Structure

## Evaluation

Evaluation of the efficiency of the solutions.    
Time is based on all variable instatiations and algorithms, **except** file access if possible.
(Currently, time is tracked in seconds, and sometimes C is able to compute in less than 1 microseconds (*us*).)

|  Day      |   Python      |     C         |
| -----     |   -----       |   -----       |
|   1       |  ~ 506 us     |  < 1 us       |
|   2       |  ~ 1 ms       |  < 1 us       |
|   3       |  ~ 14,026 ms  |   ~ 42 ms     |
|   4       | ~ 15418,17 ms |  X[^1]        |
|   5       | ~ 24,955 ms   |  ~ 1 ms       |
|   6       | ~ 4728,183 ms | ~ 61ms        |
|   7[^2]   | ~ 2,517 ms    |   ~ 1 ms      |
|   8       |   ~ 1,328 ms  |   ~ 1ms       |
|   9       |  ~ 121,151 ms |   X           |
|   10      | ~ 8,6407 s    |   X           |
|   11      | ~ 1,4997 s    |   X           |
|   12      | ~ 3,728 ms    |   X           |
|   13      | ~ 1,2026 s    |   X           |
|   14      | ~ 4,681 ms    |   X           |
|   15      | ~ 151,366 ms  |   X           |
|   16      | ~ 667,81 us   |   X           |
|   17      | ~ 236,499 ms  |   X           |


[^1]: Day 4 is missing a C implementation, as the MD5 library would have to be imported or self made. And I'm not good enough. Yet.
[^2]: Values may be due caching behavior. **WORSE** is the Heisenbug of C. 

## Issues
- Day 3: Most likely the worst written List in C, with ~300% the overhead of python.
- Day 7: C Program Heisenbug. Most likely due to missing ```free()```

## Changelog