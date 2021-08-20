#include <State/GameState.h>

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mGame(*context.window)
{
}

void GameState::draw()
{
	mGame.draw();
}

bool GameState::update(sf::Time dt)
{
	mGame.update(dt);

	if (mGame.didEnd())
		requestStackPush(States::End);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	mGame.handleEvent(event);
	return true;
}