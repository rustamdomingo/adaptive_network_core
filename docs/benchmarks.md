# Ring Buffer Benchmarks

## Power-of-two indexing

The baseline implementation calculates the physical ring-buffer
position using modulo:

    position % capacity

The optimized implementation requires the capacity to be a power
of two and calculates the position using a bitwise mask:

    position & (capacity - 1)

This optimization removes the modulo operation from the hot path
when the buffer capacity is a power of two.

## Test configuration

- Compiler: GCC
- Optimization: `-O2`
- Capacity: 1024 elements
- Element size: 4 bytes
- Operations per run: 10,000,000 push + 10,000,000 pop
- Runs per implementation: 5

## Results

### Baseline

| Run | Time/op | Operations/sec |
|---:|---:|---:|
| 1 | 14.79 ns | 67.60 M |
| 2 | 14.60 ns | 68.50 M |
| 3 | 14.87 ns | 67.26 M |
| 4 | 14.27 ns | 70.08 M |
| 5 | 14.42 ns | 69.33 M |

Median:

- Time/op: **14.60 ns**
- Throughput: **68.50 M operations/sec**

### Power-of-two V2

| Run | Time/op | Operations/sec |
|---:|---:|---:|
| 1 | 6.29 ns | 158.96 M |
| 2 | 7.00 ns | 142.81 M |
| 3 | 6.23 ns | 160.57 M |
| 4 | 6.33 ns | 157.95 M |
| 5 | 6.33 ns | 158.09 M |

Median:

- Time/op: **6.33 ns**
- Throughput: **158.09 M operations/sec**

## Performance comparison

Using the median results:

| Metric | Baseline | Power-of-two V2 | Improvement |
|---|---:|---:|---:|
| Time/op | 14.60 ns | 6.33 ns | 56.6% lower |
| Throughput | 68.50 M ops/s | 158.09 M ops/s | 2.31× |

The optimized implementation achieved approximately **2.31× higher
measured throughput** than the baseline implementation under the
tested configuration.

Measured operation time decreased by approximately **56.6%**.

## Validation

The optimized implementation was also tested with:

- basic ring-buffer operations;
- full-buffer handling;
- wraparound behavior;
- 1,000,000-operation stress test;
- power-of-two capacities from 1 through 1024.

The functional test suite completed successfully.

The stress test completed successfully with:

- 1,000,000 operations;
- capacity of 1024 elements.

The power-of-two validation completed successfully for all tested
capacities from 1 through 1024.

## Notes

Benchmark results are environment-dependent. The measurements above
were obtained in a Google Colab environment and should be treated as
experimental measurements rather than universal performance figures.

Five runs were performed for each implementation. Median values are
reported as the primary comparison metric to reduce the influence of
individual runtime fluctuations.

The benchmark compares the same ring-buffer workload and compiler
optimization level for both implementations.

The power-of-two optimization is applicable only when the configured
ring-buffer capacity satisfies the required power-of-two constraint.
