#include <Application.h>
#include <Utility.h>
#include <State/State.h>
#include <State/StateIdentifiers.h>
#include <State/MenuState.h>
#include <State/GameState.h>
#include <State/EndState.h>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::VideoMode(800, 600), "States", sf::Style::Close)
	, mTextures()
	, mFonts()
	, mStateStack(State::Context(mWindow, mTextures, mFonts))

{
	mWindow.setKeyRepeatEnabled(true);

	mFonts.load(Fonts::Main, "res/fonts/Sansation.ttf");
	mTextures.load(Textures::MenuScreen, "res/textures/background.jpg");

	registerStates();
	mStateStack.pushState(States::Menu);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();

			update(TimePerFrame);

			if (mStateStack.isEmpty())
				mWindow.close();
		}
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<EndState>(States::End);
}
