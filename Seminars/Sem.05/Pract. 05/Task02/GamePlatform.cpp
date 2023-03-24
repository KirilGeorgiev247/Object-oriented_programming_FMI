#include <iostream>
#include <cstring>
#include <fstream>
#include "GamePlatform.h"
#include "Game.h"

const int BUFF_SIZE = 1024;
const char* FILE_FIRST_LINE = "Title,Price,Availability";

GamePlatform::GamePlatform() {
	count = 0;
}

void GamePlatform::sortGamesByPrice(const bool isDescending)
{
	if (isDescending)
	{
		for (size_t i = 0; i < count - 1; ++i)
		{
			size_t indexOfMaxElement = i;
			for (size_t j = i + 1; j < count; ++j)
			{
				if ((games[indexOfMaxElement].getPrice() - games[j].getPrice()) > Math::EPSYLON)
				{
					indexOfMaxElement = j;
				}
			}

			std::swap(games[i], games[indexOfMaxElement]);
		}
	}
	else
	{
		for (size_t i = 0; i < count - 1; ++i)
		{
			size_t indexOfMaxElement = i;
			for (size_t j = i + 1; j < count; ++j)
			{
				if ((games[indexOfMaxElement].getPrice() - games[j].getPrice()) < Math::EPSYLON)
				{
					indexOfMaxElement = j;
				}
			}

			std::swap(games[i], games[indexOfMaxElement]);
		}
	}
}

bool GamePlatform::gameExists(const Game& game) const {
	for (size_t i = 0; i < count; ++i)
	{
		if (strcmp(game.getTitle(), games[i].getTitle()))
			return true;
	}
	return false;
}

void GamePlatform::addGame(const Game& game)
{
	if (!gameExists(game))
	{
		games[count++] = game;
	}

	// error
}

void GamePlatform::printGameByIndex(const int index) const {
	if (index < count)
	{
		games[index].print();
	}

	// error
}

void GamePlatform::printGames() const {
	for (size_t i = 0; i < count; ++i)
	{
		games[i].print();
		std::cout << std::endl;
	}
}

void GamePlatform::printCheapestGame() const {
	int indexOfCheapestGame = 0;
	for (size_t i = 0; i < count; ++i)
	{
		if ((games[indexOfCheapestGame].getPrice() - games[i].getPrice()) > Math::EPSYLON)
		{
			indexOfCheapestGame = i;
		}
	}

	games[indexOfCheapestGame].print();
}

void GamePlatform::printMostExpensiveGame() const {
	int indexOfTheMostExpensiveGame = 0;
	for (size_t i = 0; i < count; ++i)
	{
		if ((games[indexOfTheMostExpensiveGame].getPrice() - games[i].getPrice()) < Math::EPSYLON)
		{
			indexOfTheMostExpensiveGame = i;
		}
	}

	games[indexOfTheMostExpensiveGame].print();
}

void GamePlatform::printAllFreeGames() const {
	for (size_t i = 0; i < count; ++i)
	{
		if (games[i].getPrice() < Math::EPSYLON)
		{
			games[i].print();
			std::cout << std::endl;
		}
	}

}

int GamePlatform::getIndexOfGame(const Game& game) const {
	for (size_t i = 0; i < count; ++i)
	{
		if (strcmp(game.getTitle(), games[i].getTitle()))
			return i;
	}
	return -1;
}

bool GamePlatform::removeGame(const Game& game) {
	int indexOfGame = getIndexOfGame(game);
	if (indexOfGame == -1)
	{
		return false;
	}

	games[indexOfGame] = games[count - 1];
	games[count - 1] = Game();
	count--;
	return true;
}

bool GamePlatform::saveGamesInBinaryFile(const char* fileName) const {
	std::fstream fstr(fileName, std::ios::out | std::ios::binary);

	if (!fstr.is_open())
	{
		return false;
	}

	fstr.write((const char*)count, sizeof(count));

	for (size_t i = 0; i < count; i++)
	{
		games[i].saveToBinaryFile(fstr);
	}

	fstr.close();
	return true;
}

bool GamePlatform::getGamesFromBinaryFile(const char* fileName) {
	std::fstream fstr(fileName, std::ios::out | std::ios::binary);

	if (!fstr.is_open())
	{
		return false;
	}

	fstr.read((char*)&count, sizeof(count));

	for (size_t i = 0; i < count; i++)
	{
		Game currGame;
		currGame.getFromBinaryFile(fstr);
		games[i] = currGame;
	}

	fstr.close();
	return true;
}

bool GamePlatform::saveGamesInFile(const char* fileName) const {
	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		return false;
	}

	ofs << FILE_FIRST_LINE << std::endl;

	for (size_t i = 0; i < count; i++)
	{
		games[i].saveToFile(ofs);
	}

	ofs.close();
	return true;
}

bool GamePlatform::getGamesFromFile(const char* fileName) {
	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{
		return false;
	}

	char buff[FileHelper::BUFF_SIZE];
	ifs.getline(buff, BUFF_SIZE, '\n');

	for (size_t i = 0; i < count; i++)
	{
		games[i].getFromFile(ifs);
	}

	ifs.close();
	return true;
}