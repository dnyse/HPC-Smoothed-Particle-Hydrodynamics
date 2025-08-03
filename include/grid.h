#ifndef INCLUDE_INCLUDE_GRID_H_
#define INCLUDE_INCLUDE_GRID_H_
#include "common.h"
#include "particle.h"

struct Cell {
  Vec3 center;          // Cell center position
  int start_index;      // Start index in particle_indices array
  int count;            // Number of particles in this cell
  uint32_t morton_code; // For Z-order sorting (cache optimization)
};

class CompactHashGrid {
public:
  CompactHashGrid();
  ~CompactHashGrid();
  void build(const ParticleSystem &particles);
// TODO:
	void clear(); 
	uint64_t compute_hash_key();
	void build_compact_storage();

private:
  std::vector<Cell> cells; // Cell metadata
  std::vector<int>
      particle_indices; // Flattened: [p1,p2,p3, p4,p5, p6,p7,p8,p9, ...]
  std::vector<int> cell_starts; // Offsets:   [0,      3,    5,          9, ...]
  //                                                ↑       ↑     ↑           ↑
  //                                              cell0   cell1  cell2 cell3
};

#endif // INCLUDE_INCLUDE_GRID_H_
