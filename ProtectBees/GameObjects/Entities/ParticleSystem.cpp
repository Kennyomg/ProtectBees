#include "../../stdafx.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int count)
	: _particles(count), _vertices(sf::Points, count), _lifetime(sf::seconds(3.0f)), _emitter(0.0f, 0.0f)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
	_emitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < _particles.size(); ++i)
	{
		// Update the particle lifetime
		Particle& p = _particles[i];
		p.lifetime -= elapsed;

		// If the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero) {
			resetParticle(i);
		}

		// Update the position of the corresponding vertex
		_vertices[i].position += p.velocity * elapsed.asSeconds();

		// Update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / _lifetime.asSeconds();
		_vertices[i].color.r = static_cast<sf::Uint8>(231);
		_vertices[i].color.g = static_cast<sf::Uint8>(133);
		_vertices[i].color.b = static_cast<sf::Uint8>(0);
		_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply the transform
	states.transform *= getTransform();

	// Our particles don't use a texture
	states.texture = NULL;

	// Draw the vertex array
	target.draw(_vertices, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
	// Give a random velocity and lifetime to the particle
	float angle = (std::rand() % 90) * 3.14f / 90.0f;
	float speed = (std::rand() % 30) + 1.0f;
	_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	_vertices[index].position = _emitter;
}