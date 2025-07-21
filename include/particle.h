#ifndef INCLUDE_INCLUDE_PARTICLE_H_
#define INCLUDE_INCLUDE_PARTICLE_H_

#include "common.h"

class SPHParticle {
public:
  SPHParticle();
  SPHParticle(SPHParticle &&) = default;
  SPHParticle(const SPHParticle &) = default;
  SPHParticle &operator=(SPHParticle &&) = default;
  SPHParticle &operator=(const SPHParticle &) = default;
  ~SPHParticle();

private:
  Vec3 m_pos;
  Vec3 m_vel;
  Vec3 m_acc;

	double m_mass;
};

SPHParticle::SPHParticle() {}

SPHParticle::~SPHParticle() {}

#endif // INCLUDE_INCLUDE_PARTICLE_H_
