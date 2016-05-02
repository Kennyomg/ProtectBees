#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	ParticleSystem(unsigned int count);
	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void resetParticle(std::size_t index);

	std::vector<Particle> _particles;
	sf::VertexArray _vertices;
	sf::Time _lifetime;
	sf::Vector2f _emitter;
};