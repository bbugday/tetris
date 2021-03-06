#pragma once

#include <ResourceHandling/ResourceHolder.h>
#include <ResourceHandling/ResourceIdentifiers.h>
#include <Piece.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include <array>

namespace sf
{
	class RenderWindow;
	class Time;
}

class Game : private sf::NonCopyable
{
public:
	explicit Game(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	bool didEnd();
private:
	void loadTextures();
	void loadFonts();

	int rotate(int px, int py, int r);
	bool DoesFit(int type, int nPosX, int nPosY, int nRotation);
	void lockPiece();
	void removeLines();
	void generateNext();
	void drawBoard();
	void drawScore();
	void drawNext();
private:
	static constexpr unsigned int WIDTH = 10;
	static constexpr unsigned int HEIGHT = 20;
	static const int tetromino[TypeCount][16];
	static const sf::Color colors[TypeCount];

	std::array<int, WIDTH * HEIGHT> mBoard;
	Piece mPiece;
	float timePerDrop;
	int score;
	bool end;
	int nextType;
	int nextRotation;

	sf::RenderWindow& mWindow;
	TextureHolder mTextures;
	FontHolder mFonts;
	sf::Clock mDropClock;
};