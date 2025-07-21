# HPC Smoothed Particle Hydrodynamics

A learning-oriented implementation of Smoothed Particle Hydrodynamics (SPH) for high-performance computing applications.

## About This Project

This repository represents my journey into understanding and implementing SPH methods for scientific computing as part of my computational science studies with a focus on high-performance computing. Coming from a computer science background with solid knowledge of numerical methods but limited physics experience, this project serves as both a learning exercise and an evolving implementation of SPH techniques optimized for HPC environments.

As a computational science student, this work bridges the gap between theoretical understanding and practical implementation, emphasizing the computational challenges and optimization opportunities that arise when applying SPH methods to real-world scientific problems at scale.

## Learning Philosophy

Rather than starting with a fully-featured SPH solver, this repository follows an incremental approach:

- **Foundation First**: Begin with basic SPH formulations to understand the underlying physics and mathematics
- **Implementation Focus**: Emphasize clean, readable C++ code that can be understood and modified
- **Performance Evolution**: Gradually introduce HPC optimizations (vectorization, parallelization, GPU acceleration)
- **Scientific Rigor**: Validate each implementation stage against established benchmarks
- **Documentation**: Maintain detailed explanations of both theory and implementation choices

## Theoretical Background

## Neighbor Search: Compact Hashing

**The Critical Performance Bottleneck**: Every SPH particle must find all neighbors within its kernel support radius every timestep to compute density, forces, and other physical quantities. For N particles, naive approaches require O(N²) distance calculations, making large simulations computationally intractable.

### Core Problem
```cpp
// Naive O(N²) approach - becomes prohibitive for large N
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
        if (distance(particles[i], particles[j]) < support_radius) {
            neighbors[i].push_back(j);
        }
    }
}
// 1M particles = 1 trillion distance calculations per timestep!
```

### Compact Hashing Solution

This implementation employs **compact hashing**, providing O(N) complexity with superior cache performance.

#### Spatial Grid Foundation
```cpp
// Divide space into uniform grid cells
double cell_size = kernel_support_radius;  // Key insight!
int grid_x = static_cast<int>(particle.x / cell_size);
int grid_y = static_cast<int>(particle.y / cell_size);
int grid_z = static_cast<int>(particle.z / cell_size);

// Hash 3D coordinates to 1D index
uint64_t hash = (73856093 * grid_x) ^ (19349663 * grid_y) ^ (83492791 * grid_z);
```

#### Key Innovations

1. **Memory Efficiency**: Scales with particle count O(N), not domain size O(domain³)
2. **Hash Table + Secondary Array**: Sparse hash table maps to compact contiguous storage
3. **Z-Order Optimization**: Morton curve sorting for cache-friendly spatial locality
4. **Parallel Construction**: Lock-free algorithms for multi-threaded performance

## Implementation
