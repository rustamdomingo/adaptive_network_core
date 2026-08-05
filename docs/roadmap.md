# Roadmap

This roadmap describes the planned development stages of the project.

The project is experimental, so individual stages may change as testing and
benchmarking provide new information.

## Phase 0 — Architecture

**Status: In progress**

- [x] Create project repository
- [x] Define initial architecture
- [x] Document architecture
- [x] Document initial design
- [ ] Review component boundaries
- [ ] Define initial interfaces

## Phase 1 — Core Prototype

**Status: Planned**

- [ ] Create core runtime
- [ ] Define component lifecycle
- [ ] Define configuration model
- [ ] Implement basic logging
- [ ] Implement basic error handling
- [ ] Create initial test framework

## Phase 2 — High-Speed Data Exchange

**Status: Planned**

- [ ] Design ring-buffer data structure
- [ ] Implement producer/consumer model
- [ ] Implement synchronization
- [ ] Define shared-memory interfaces
- [ ] Create correctness tests
- [ ] Create performance benchmarks
- [ ] Measure copying and synchronization overhead

## Phase 3 — Transport Layer

**Status: Planned**

- [ ] Define transport abstraction
- [ ] Implement first transport prototype
- [ ] Implement second experimental transport
- [ ] Create transport metrics
- [ ] Create transport integration tests

## Phase 4 — Telemetry

**Status: Planned**

- [ ] Implement latency measurements
- [ ] Implement throughput measurements
- [ ] Implement packet-loss measurements
- [ ] Implement jitter measurements
- [ ] Store historical measurements
- [ ] Create telemetry visualization

## Phase 5 — Adaptive Scheduling

**Status: Planned**

- [ ] Define scheduling interface
- [ ] Implement deterministic baseline algorithm
- [ ] Implement path scoring
- [ ] Test scheduling under simulated network conditions
- [ ] Compare different scheduling strategies
- [ ] Benchmark scheduling overhead

## Phase 6 — Machine Learning

**Status: Planned**

- [ ] Build experimental dataset
- [ ] Define feature set
- [ ] Implement baseline statistical model
- [ ] Train experimental ML model
- [ ] Compare ML decisions with baseline algorithm
- [ ] Measure prediction overhead
- [ ] Investigate federated-learning architecture

## Phase 7 — C / Python Integration

**Status: Planned**

- [ ] Define C/Python interface
- [ ] Implement telemetry exchange
- [ ] Connect experimental ML model
- [ ] Test process failure and restart behavior
- [ ] Measure communication overhead

## Phase 8 — eBPF / XDP Experiments

**Status: Planned**

- [ ] Create isolated eBPF/XDP experiments
- [ ] Measure packet-processing performance
- [ ] Investigate interaction with the transport layer
- [ ] Benchmark different processing paths
- [ ] Document limitations

## Phase 9 — Reliability

**Status: Planned**

- [ ] Add component health monitoring
- [ ] Implement graceful degradation
- [ ] Implement component restart mechanisms
- [ ] Add fault-injection tests
- [ ] Test recovery behavior

## Phase 10 — Cross-Platform Experiments

**Status: Planned**

- [ ] Test on x86
- [ ] Test on ARM
- [ ] Identify platform-specific components
- [ ] Separate hardware-dependent code
- [ ] Document portability limitations

## Phase 11 — Benchmarking

**Status: Planned**

- [ ] Create reproducible benchmark environment
- [ ] Measure throughput
- [ ] Measure latency
- [ ] Measure CPU utilization
- [ ] Measure memory usage
- [ ] Measure IPC overhead
- [ ] Publish benchmark results

## Phase 12 — Prototype Release

**Status: Future**

- [ ] Stabilize public interfaces
- [ ] Improve documentation
- [ ] Add examples
- [ ] Add automated tests
- [ ] Add CI
- [ ] Review security assumptions
- [ ] Publish experimental release

## Long-Term Research

Potential future research directions include:

- more advanced adaptive scheduling;
- distributed optimization;
- federated learning;
- hardware-assisted processing;
- additional transport implementations;
- more advanced telemetry;
- automated performance tuning.

These items are research directions rather than commitments to a specific
implementation.
