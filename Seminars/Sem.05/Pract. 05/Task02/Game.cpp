#include <iostream>
#include <cstring>
#include <sstream>
#include "Game.h"

size_t FileHelper::getFileSize(std::fstream& fstr)
{
	size_t currentPos = fstr.tellg();
	fstr.seekg(0, std::ios::end);
	size_t fileSize = fstr.tellg();
	fstr.seekg(currentPos);
	return fileSize;
}

void StringHelper::stringCopy(char* destination, const char* resource) {
	while (resource[0] != '\0')
	{
		destination[0] = resource[0];
		destination++;
		resource++;
	}

	destination[0] = '\0';
}

Game::Game() {
	title = nullptr;
	isAvailable = false;
	price = -1.0;
}

Game::Game(const char* title, const double price)
{
	this->isAvailable = true;
	this->title = new char[strlen(title) + 1];
	StringHelper::stringCopy(this->title, title);
	this->price = price;
}

Game::~Game()
{
	delete[] title;
}

const char* Game::getTitle() const {

	return title;
}

void Game::setTitle(const char* title) {
	delete[] this->title;
	this->title = new char[strlen(title) + 1];
	StringHelper::stringCopy(this->title, title);
}

double Game::getPrice() const {
	return price;
};

void Game::setPrice(const double price) {
	if (price > Math::EPSYLON)
	{
		this->price = price;
	}
}

bool Game::isFree() const {
	return Math::EPSYLON > price;
}

void Game::print() const {
	std::cout << "Game: " << title << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << isAvailable ? "Available" : "Not available";
}

void Game::saveToBinaryFile(std::fstream& fstr) const {
	int titleLen = strlen(title);
	fstr.write((const char*)&titleLen, sizeof(titleLen));
	fstr.write(title, titleLen);
	fstr.write((const char*)&price, sizeof(price));
	fstr.write((const char*)&isAvailable, sizeof(isAvailable));
}

void Game::getFromBinaryFile(std::fstream& fstr) {
	int titleLen;
	fstr.read((char*)&titleLen, sizeof(titleLen));
	title = new char[titleLen + 1];
	fstr.read((char*)title, titleLen);
	title[titleLen] = '\0';
	fstr.read((char*)&price, sizeof(price));
	fstr.read((char*)&isAvailable, sizeof(isAvailable));
}

void Game::saveToFile(std::ofstream& ofs) const {
	ofs << title << "," << price << "," << isAvailable << std::endl;
}

void Game::getFromFile(std::ifstream& ifs) {

	char buff[FileHelper::BUFF_SIZE];
	ifs.getline(buff, FileHelper::BUFF_SIZE, '\n');
	std::stringstream ss(buff);

	ss.getline(buff, FileHelper::BUFF_SIZE, ',');
	int titleLen = strlen(buff);
	title = new char[titleLen + 1];
	StringHelper::stringCopy(title, buff);

	ss.getline(buff, FileHelper::BUFF_SIZE, ',');
	price = std::stod(buff);

	ss.getline(buff, FileHelper::BUFF_SIZE, '\n');
	if (buff == "1" || buff == "true")
	{
		isAvailable = true;
	}
	else if (buff == "0" || buff == "false")
	{
		isAvailable = false;
	}
}

Game Game::operator=(const Game& other) {
	if (!strcmp(this->title, other.title))
	{
		delete[] this->title;
		this->title = new char[strlen(other.title) + 1];
		StringHelper::stringCopy(this->title, other.title);
		this->isAvailable = other.isAvailable;
		this->price = other.price;
		return *this;
	}
}