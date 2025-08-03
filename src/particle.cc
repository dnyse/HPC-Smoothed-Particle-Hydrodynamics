#include "../include/particle.h"

Vec3 ParticleSystem::get_position(unsigned int idx) const {
  return Vec3(m_pos_x[idx], m_pos_y[idx], m_pos_z[idx]);
}

void ParticleSystem::set_position(unsigned int idx, const Vec3 &pos) {
  m_pos_x[idx] = pos.x();
  m_pos_y[idx] = pos.y();
  m_pos_z[idx] = pos.z();
}

double ParticleSystem::get_mass(unsigned int idx) const { return m_mass[idx]; }
double ParticleSystem::get_density(unsigned int idx) const {
  return m_density[idx];
}
