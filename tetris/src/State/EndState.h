#pragma once

#include <State/State.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class EndState : public State
{
public:
	EndState(StateStack& stack, Context context);
	
	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mEndText;
	sf::Text			mBackMenuText;
	sf::Text			mPlayAgainText;
};