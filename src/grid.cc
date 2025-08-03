#include "../include/grid.h"
CompactHashGrid::CompactHashGrid() {}

void CompactHashGrid::build(const ParticleSystem& particles) {
    this->clear();
    
    // Temporary storage during construction
    std::unordered_map<uint64_t, std::vector<int>> temp_cells;
    
    // Insert each particle into appropriate cell
    for (int i = 0; i < particles.size(); ++i) {
        Vector3 pos = particles.get_position(i);
        uint64_t hash_key = computeHashKey(pos);
        temp_cells[hash_key].push_back(i);
    }
    
    // Convert to compact representation
    buildCompactStorage(temp_cells);
}

uint64_t CompactHashGrid::spatial_hash(int x, int y, int z) {
    const uint64_t p1 = 73856093;
    const uint64_t p2 = 19349663; 
    const uint64_t p3 = 83492791;
    return (p1 * x) ^ (p2 * y) ^ (p3 * z);
}

CompactHashGrid::~CompactHashGrid() {}
