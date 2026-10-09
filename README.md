# Parallel and Distributed Computing

A collection of C programs exploring **parallel programming, concurrency, synchronization, workload scheduling, and performance scalability** using OpenMP and, eventually, OpenMPI.

This repository contains implementations and experiments developed as part of learning Parallel and Distributed Computing, with a focus on understanding how parallel execution affects performance and how different parallel programming constructs work in practice.

## Technologies

- **C** — Core programming language
- **OpenMP** — Shared-memory parallel programming
- **OpenMPI** — Distributed-memory parallel programming *(upcoming)*

## Repository Structure

### OpenMP Programs

The current collection covers OpenMP directives, data-sharing attributes, synchronization mechanisms, parallel workloads, and scalability experiments.

| Program | Description |
|---|---|
| [`OMP-Sections.c`](OMP-Sections.c) | Executing independent code sections in parallel |
| [`OMP-Critical.c`](OMP-Critical.c) | Protecting shared resources using critical regions |
| [`OMP-Barriers.c`](OMP-Barriers.c) | Synchronizing threads using barriers |
| [`OMP-Reduction.c`](OMP-Reduction.c) | Combining thread-local results using reduction operations |
| [`OMP-FirstPrivate.c`](OMP-FirstPrivate.c) | Initializing private variables using their original values |
| [`OMP-LastPrivate.c`](OMP-LastPrivate.c) | Propagating the value from the logically last iteration or section |
| [`OMP-ThreadPrivate.c`](OMP-ThreadPrivate.c) | Maintaining thread-specific copies of variables |
| [`OMP-Ordered-Pvt.c`](OMP-Ordered-Pvt.c) | Exploring ordered execution and private data |
| [`OMP-ImageBrightness.c`](OMP-ImageBrightness.c) | Parallel image brightness adjustment |
| [`OMP-GPU-Sim.c`](OMP-GPU-Sim.c) | Simulating GPU-like parallel execution using OpenMP threads |
| [`OMP-AVSensorScalability.c`](OMP-AVSensorScalability.c) | Exploring scalability using autonomous-vehicle sensor data |
| [`OMP-ParallelSensorFusion.c`](OMP-ParallelSensorFusion.c) | Parallel processing for sensor fusion |
| [`OMP-MatMulScalability.c`](OMP-MatMulScalability.c) | Investigating scalability in matrix multiplication |

### OpenMPI Programs

**Coming soon.**
