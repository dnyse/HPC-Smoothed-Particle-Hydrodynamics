#ifndef INCLUDE_INCLUDE_PARTICLE_H_
#define INCLUDE_INCLUDE_PARTICLE_H_

#include "common.h"
#include <vector>

class ParticleSystem {
private:
  // Separate contiguous arrays for each property
  std::vector<double> m_pos_x, m_pos_y, m_pos_z; // Positions
  std::vector<double> m_vel_x, m_vel_y, m_vel_z; // Velocities
  std::vector<double> m_mass;                    // Masses
  std::vector<double> m_density;                 // Densities
  std::vector<double> m_pressure;                // Pressures
  std::vector<double> m_smoothing_h;             // Smoothing lengths

  size_t particle_count;

public:
  Vec3 get_position(unsigned int idx) const;
  void set_position(unsigned int idx, const Vec3 &pos);
  double get_mass(unsigned int idx) const;
  double get_density(unsigned int idx) const;
  size_t size() const { return particle_count; }
};

#endif // INCLUDE_INCLUDE_PARTICLE_H_
