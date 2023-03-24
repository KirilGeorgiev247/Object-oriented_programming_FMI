#pragma once
#include "Game.h"

class GamePlatform {
private:
	Game games[1024];
	int count;

public:

	void sortGamesByPrice(const bool isDescending);
	bool gameExists(const Game& game) const;
	GamePlatform();
	void addGame(const Game& game);
	void printGameByIndex(const int index) const;
	void printGames() const;
	void printCheapestGame() const;
	void printMostExpensiveGame() const;
	void printAllFreeGames() const;
	int getIndexOfGame(const Game& game) const;
	bool removeGame(const Game& game);
	bool saveGamesInBinaryFile(const char* fileName) const;
	bool getGamesFromBinaryFile(const char* fileName);
	bool saveGamesInFile(const char* fileName) const;
	bool getGamesFromFile(const char* fileName);
};