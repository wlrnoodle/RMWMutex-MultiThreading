Mutexes vs. RMW

C++ implementations and benchmarks of mutexes, a reader-writer lock, and concurrent stacks, written for CSE113 Parallel Programming (UC Santa Cruz).

The project compares locks built from plain loads and stores (Filter, Bakery) and locks built on hardware read-modify-write operations (std::mutex, std::shared_mutex), looking at throughput and fairness as thread counts grow.

**Report (design, results, and analysis):** 

I included my report and analysis on C++ implementations and bechmarks of these mutexes, with comparison with atomic RMW mutexes.
<p align="center">
  <a href="Mutex-and-RMW-Concurrent-Methods.pdf">
    <img src="https://img.shields.io/badge/Read_the_Report-PDF-red?style=for-the-badge&logo=adobeacrobatreader&logoColor=white" alt="Read the Report"/>
  </a>
</p>
Each of part1/, part2/, and part3/ has its own Makefile:

bash
cd part1 && make

bash
./part -threadcount

Tested on an Ubuntu VM with 4 cores. Performance may vary with different numbers of cores and architectures. Check your core count and architecture before comparing against the analysis, since the results are most accurate for 4 cores.