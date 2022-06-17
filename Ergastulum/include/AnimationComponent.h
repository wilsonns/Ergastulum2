#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <vector>
#include <unordered_map>
#include <map>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Glsl.hpp>

enum FrameRow
{
	IDLE = 0, //Standing character or item on the ground
	WAKLKING,
	DEAD
};

class Character;

class AnimationComponent
{
public:
	//Constructors & Destructors
	AnimationComponent(sf::Texture* texture, unsigned int spriteSize, float updateTime);
	~AnimationComponent();

	sf::Vector2u frames();
	float updateTime();
	void update(sf::Vector2f displayPos, unsigned int y, float elapsedTime);
	void render(sf::RenderTarget* window);
	void die();
	void merge(AnimationComponent* toMerge, unsigned int baseRow, unsigned int toMergeRow);
private:
	
protected:
	sf::Vector2u m_frames;
	sf::Vector2u m_maxFrames;
	float m_updateTime;
	float m_totalTime;
	int m_spriteSize;
	bool m_toUpdate;
	std::vector<std::vector<std::unique_ptr<sf::Sprite>>> m_sprites;
};

class ItemAnimationComponent : public AnimationComponent
{
public:
	//Constructors & Destructors
	using AnimationComponent::AnimationComponent;

	void syncWithCharacter(AnimationComponent* characterAnimation);
};



#endif
