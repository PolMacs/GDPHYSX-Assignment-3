#include "P6Particle.h"

using namespace P6;

void P6Particle::UpdatePosition(float time) {
	//p2 = p1 + v t
	//Position = Position + Velocity * time;

	//p2 = p1 Vt+ [(At^2)/2]

	this->Position = this->Position + (this->Velocity * time) + ((1.0f / 2.0f) * (this->Acceleration * time * time));
}

void P6Particle::UpdateVelocity(float time) {
	//Vf = Vi A t
	this->Velocity = this->Velocity + (this->Acceleration * time);
}

void P6Particle::update(float time) {

	//update position first
	this->UpdatePosition(time);

	//update velocity next
	this->UpdateVelocity(time);

}