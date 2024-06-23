# 2015

## Structure

## Evaluation

Evaluation of the efficiency of the solutions.    
Time is based on all variable instatiations and algorithms, **except** file access if possible.
(Currently, time is tracked in seconds, and sometimes C is able to compute in less than 1 microseconds (*us*).)

|  Day  |   Python      |     C         |
| ----- |   -----       |   -----       |
|   1   |  ~ 506 us     |  < 1 us       |
|   2   |  ~ 1 ms       |  < 1 us       |
|   3   |  ~ 14,026 ms  |   ~ 42 ms     |
|   4   | ~ 15418,17 ms |  X[^1]        |
|   5   | ~ 24,955 ms   |  ~ 1 ms       |
|   6   | ~ 4728,183 ms | ?             |


[^1]: Day 4 is missing a C implementation, as the MD5 library would have to be imported or self made. And I'm not good enough. Yet.

## Changelog