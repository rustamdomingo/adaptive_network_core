# Ring Buffer Benchmarks

## Power-of-two indexing

The baseline implementation calculated the physical ring-buffer
position using modulo:

    position % capacity

The optimized implementation requires the capacity to be a power
of two and calculates the position using a bitwise mask:

    position & (capacity - 1)

## Test configuration

- Compiler: GCC
- Optimization: `-O2`
- Capacity: 1024 elements
- Element size: 4 bytes
- Operations: 10,000,000 push + 10,000,000 pop

## Results

| Implementation | Index calculation | Time/op | Operations/sec |
|---|---|---:|---:|
| Baseline | `position % capacity` | 15.62 ns | 64.03 M |
| Power-of-two V2 | `position & (capacity - 1)` | 6.36 ns | 157.12 M |

## Result

Under the tested configuration, the power-of-two implementation
reduced measured operation time from 15.62 ns to 6.36 ns.

Measured throughput increased from 64.03 M operations/sec to
157.12 M operations/sec.

This corresponds to approximately a 2.45× increase in measured
throughput.

The benchmark was executed using the same test program, compiler
optimization level, buffer capacity, element size, and operation
count for both implementations.

## Validation

The optimized implementation was also tested with:

- basic ring-buffer operations;
- full-buffer handling;
- wraparound behavior;
- 1,000,000-operation stress test;
- power-of-two capacities from 1 through 1024.

The stress test completed successfully with a capacity of 1024
and 1,000,000 operations.

## Notes

Benchmark results are environment-dependent. The measurements above
were obtained in a Google Colab environment and should be treated as
experimental measurements rather than universal performance figures.

Additional repeated benchmark runs will be used to reduce measurement
variance and establish a more representative median result.
