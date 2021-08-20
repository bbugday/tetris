#include <Game.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Utility.h>

const int Game::tetromino[TypeCount][16] = {
		{
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0
		},
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		}
};

const sf::Color Game::colors[TypeCount] = {
	sf::Color::Color(0, 185, 208), sf::Color::Color(175, 0, 213),			 
	sf::Color::Color(228, 209, 0), sf::Color::Color(213, 0, 0),
	sf::Color::Color(0, 221, 84) , sf::Color::Color(208, 148, 0), 
	sf::Color::Color(0, 122, 195) 
};

Game::Game(sf::RenderWindow& window) : mWindow(window), mPiece(3, 0), timePerDrop(0.5f), score(0)
{
	loadTextures();
	loadFonts();
    mBoard.fill({});
}

void Game::update(sf::Time dt)
{
    if (mDropClock.getElapsedTime() > sf::seconds(timePerDrop))
    {
		if (DoesFit(mPiece.type, mPiece.x, mPiece.y + 1, mPiece.rotation))
			mPiece.y++;
		else
		{
			lockPiece();
			removeLines();

			Piece newPiece(3, 0);

			if (DoesFit(newPiece.type, 3, 0, newPiece.rotation))
				mPiece = std::move(newPiece);
			else
			{
				//end game
			}
		}
        mDropClock.restart();
    }
}

void Game::removeLines()
{
	for (int py = 0; py < 4; py++)
		if (mPiece.y + py < HEIGHT)
		{
			bool clear = true;

			int firstIndexOfLine = (mPiece.y + py) * WIDTH;

			for (int i = 0; i < WIDTH; i++)
				if (mBoard[firstIndexOfLine + i] == 0)
					clear = false;

			if (clear)
			{
				score++;
				for (int i = 0; i < WIDTH; i++)
					mBoard[firstIndexOfLine + i] = 0;

				for (int i = mPiece.y + py; i > 0; i--)
					for (int j = 0; j < WIDTH; j++)
						mBoard[i * WIDTH + j] = mBoard[(i - 1) * WIDTH + j];
			}
		}
}

void Game::lockPiece()
{
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
			if (tetromino[mPiece.type][rotate(px, py, mPiece.rotation)] != 0)
				mBoard[(mPiece.y + py) * WIDTH + (mPiece.x + px)] = mPiece.type + 1;
}

int Game::rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: 			
		pi = py * 4 + px;			
		break;												
	case 1:
		pi = 12 + py - (px * 4);	
		break;										
	case 2:
		pi = 15 - (py * 4) - px;	
		break;
	case 3: 
		pi = 3 - py + (px * 4);		
		break;						
	}								

	return pi;
}

bool Game::DoesFit(int type, int nPosX, int nPosY, int nRotation)
{
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			int pi = rotate(px, py, nRotation);

			if (tetromino[type][pi] == 0)
				continue;

			int fi = (nPosY + py) * WIDTH + (nPosX + px);

			if (nPosX + px >= WIDTH || fi > (WIDTH * HEIGHT - 1) || mBoard[fi] != 0)
				return false;
		}
	return true;
}

void Game::draw()
{
	sf::Sprite background(mTextures.get(Textures::Background));
	mWindow.draw(background);

	drawBoard();
	drawScore();
}

void Game::drawBoard()
{
	sf::RectangleShape area(sf::Vector2f(261.f, 521.f));
	area.setPosition(270.f, 40.f);
	area.setFillColor(sf::Color::Black);
	mWindow.draw(area);

	//draw horizontal lines
	for (int i = 0; i < WIDTH + 1; i++)
	{
		sf::RectangleShape line(sf::Vector2f(1.f, 521.f));
		line.setPosition(270.f + i * 26.f, 40.f);
		line.setFillColor(sf::Color::Color(35, 35, 35));
		mWindow.draw(line);
	}

	//draw vertical lines
	for (int i = 0; i < HEIGHT + 1; i++)
	{
		sf::RectangleShape line(sf::Vector2f(261.f, 1.f));
		line.setPosition(270.f, 40.f + i * 26.f);
		line.setFillColor(sf::Color::Color(35, 35, 35));
		mWindow.draw(line);
	}

	//draw current piece
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
			if (tetromino[mPiece.type][rotate(px, py, mPiece.rotation)] != 0)
			{
				sf::RectangleShape square(sf::Vector2f(25.f, 25.f));
				square.setPosition(271.f + 26 * (px + mPiece.x), 41.f + 26 * (mPiece.y + py));
				square.setFillColor(colors[mPiece.type]);
				mWindow.draw(square);
			}

	//draw locked pieces
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if (mBoard[i * WIDTH + j] != 0)
			{
				sf::RectangleShape square(sf::Vector2f(25.f, 25.f));
				square.setPosition(271.f + 26 * j, 41.f + 26 * i);
				square.setFillColor(colors[mBoard[i * WIDTH + j] - 1]);
				mWindow.draw(square);
			}
		}

	//draw shadow
	int maxDrop = 0;
	while (DoesFit(mPiece.type, mPiece.x, mPiece.y + maxDrop + 1, mPiece.rotation))
		maxDrop++;

	if (maxDrop != 0)
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[mPiece.type][rotate(px, py, mPiece.rotation)] != 0)
				{
					sf::RectangleShape square(sf::Vector2f(25.f, 25.f));
					square.setOutlineColor(colors[mPiece.type]);
					square.setOutlineThickness(1.f);
					square.setPosition(271.f + 26 * (px + mPiece.x), (41.f) + 26 * (mPiece.y + py + maxDrop));
					square.setFillColor(sf::Color::Transparent);
					mWindow.draw(square);
				}
}

void Game::drawScore()
{
	sf::RectangleShape area(sf::Vector2f(150.f, 85.f));
	area.setPosition(80.f, 80.f);
	area.setFillColor(sf::Color::Black);
	mWindow.draw(area);

	sf::Font& font = mFonts.get(Fonts::Main);
	sf::Text ScoreLabel;
	ScoreLabel.setFont(font);
	ScoreLabel.setString("Score");
	centerOrigin(ScoreLabel);
	ScoreLabel.setPosition(area.getGlobalBounds().left + area.getLocalBounds().width / 2.f, 55.f);
	mWindow.draw(ScoreLabel);

	sf::Text ScoreText;
	ScoreText.setFont(font);
	ScoreText.setString(std::to_string(score));
	centerOrigin(ScoreText);
	ScoreText.setPosition(area.getGlobalBounds().left + area.getLocalBounds().width / 2.f, 
		area.getGlobalBounds().top + area.getLocalBounds().height / 2.f);
	mWindow.draw(ScoreText);
}


void Game::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
		switch (event.key.code)
		{
		case sf::Keyboard::Right:
			if (DoesFit(mPiece.type, mPiece.x + 1, mPiece.y, mPiece.rotation))
				mPiece.x++;
			break;
		case sf::Keyboard::Left:
			if (DoesFit(mPiece.type, mPiece.x - 1, mPiece.y, mPiece.rotation))
				mPiece.x--;
			break;
		case sf::Keyboard::Up:
			if (DoesFit(mPiece.type, mPiece.x, mPiece.y, mPiece.rotation + 1))
				mPiece.rotation++;
			break;
		case sf::Keyboard::Down:
			if (DoesFit(mPiece.type, mPiece.x, mPiece.y + 1, mPiece.rotation))
				mPiece.y++;
			break;
		case sf::Keyboard::Space:
			int maxDrop = 0;
			while (DoesFit(mPiece.type, mPiece.x, mPiece.y + maxDrop + 1, mPiece.rotation))
				maxDrop++;
			mPiece.y += maxDrop;
			break;
		}
}

void Game::loadTextures()
{
	mTextures.load(Textures::Background, "res/textures/background.jpg");
}

void Game::loadFonts()
{
	mFonts.load(Fonts::Main, "res/fonts/Sansation.ttf");
}