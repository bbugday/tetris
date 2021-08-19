#pragma once

#include <ctime>

enum PieceType{ I, T, O, Z, S, L, J, TypeCount };

struct Piece
{
	Piece(int type, int x, int y, int r) : type(type), x(x), y(y), rotation(r) {}
	Piece(int x, int y) : x(x), y(y)
	{
		srand(time(NULL));
		type = rand() % TypeCount;
		rotation = rand() % 4;
	}
	int type;
	int x;
	int y;
	int rotation;
};