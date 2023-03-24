#pragma once
#include <fstream>

namespace Math {
	const double EPSYLON = 0.000001;
}

namespace FileHelper {
	const int BUFF_SIZE = 1024;
	size_t getFileSize(std::fstream& fstr);
}

namespace StringHelper {
	void stringCopy(char* destination, const char* resource);
}

class Game {
private:
	char* title;
	mutable bool isAvailable;
	double price;

public:
	Game();

	Game(const char* title, const double price);

	const char* getTitle() const;
	void setTitle(const char* title);

	double getPrice() const;
	void setPrice(const double price);

	bool isFree() const;

	void print() const;

	Game operator=(const Game& other);

	void saveToBinaryFile(std::fstream& fstr) const;

	void getFromBinaryFile(std::fstream& fstr);

	void saveToFile(std::ofstream& ofs) const;

	void getFromFile(std::ifstream& ifs);

	~Game();
};