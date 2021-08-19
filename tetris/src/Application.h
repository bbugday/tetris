#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <ResourceHandling/ResourceHolder.h>
#include <ResourceHandling/ResourceIdentifiers.h>
#include <State/StateStack.h>

class Application
{
public:
	Application();
	void					run();
private:
	void					processInput();
	void					update(sf::Time dt);
	void					render();

	void					registerStates();


private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	TextureHolder			mTextures;
	FontHolder				mFonts;

	StateStack				mStateStack;
};