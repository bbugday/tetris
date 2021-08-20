#include <State/EndState.h>

#include <ResourceHandling/ResourceHolder.h>
#include <Utility.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

EndState::EndState(StateStack& stack, Context context) 
	: State(stack, context)
	, mBackgroundSprite()
	, mEndText()
	, mBackMenuText()
{
	sf::Font& font = context.fonts->get(Fonts::Main);

	sf::Vector2f viewSize = context.window->getView().getSize();

	mEndText.setFont(font);
	mEndText.setString("Game Over!");
	mEndText.setCharacterSize(70);
	centerOrigin(mEndText);
	mEndText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mPlayAgainText.setFont(font);
	mPlayAgainText.setString("Press space to play again");
	centerOrigin(mPlayAgainText);
	mPlayAgainText.setPosition(0.5f * viewSize.x, 0.55f * viewSize.y);

	mBackMenuText.setFont(font);
	mBackMenuText.setString("(Press esc to return to the main menu)");
	centerOrigin(mBackMenuText);
	mBackMenuText.setPosition(0.5f * viewSize.x, 0.7f * viewSize.y);
}

void EndState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mEndText);
	window.draw(mBackMenuText);
	window.draw(mPlayAgainText);
}

bool EndState::update(sf::Time)
{
	return false;
}

bool EndState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
		requestStackPop();
		requestStackPush(States::Menu);
	}

	if (event.key.code == sf::Keyboard::Space)
	{
		requestStackPop();
		requestStackPop();
		requestStackPush(States::Game);
	}

	return false;
}