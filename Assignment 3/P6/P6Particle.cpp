#include "P6Particle.h"

using namespace P6;

void P6Particle::UpdatePosition(float time)
{
	this->Position = this->Position + (this->Velocity * time) + ((1.0f / 2.0f) * (this->Acceleration * time * time));
}

void P6Particle::UpdateVelocity(float time)
{
	this->Velocity = this->Velocity + (this->Acceleration * time);
}

void P6Particle::Update(float time)
{
	UpdatePosition(time);
	UpdateVelocity(time);
}
