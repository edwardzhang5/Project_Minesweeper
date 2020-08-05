#pragma once
#include "Tile.h"
#include "Random.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
using namespace std;

class Board
{
public:
	//git
	Board();          //If board is created without test data - random numbers
	
	void startBoard(sf::RenderWindow& window);
	void drawMines(sf::RenderWindow& window);
	void updateBoard(sf::RenderWindow &window);
	
	void setRandomTile();
	void setDigits(sf::RenderWindow &window); //use flagCount
	void setUpBoard(int x);
	void initiatizeTiles();
	void linkNeighbors();
	void drawDigits(int d, sf::RenderWindow &window);
	void checkWin();
	
private:

	map<string, sf::Texture> images;
	vector<Tile> gameBoard;
	
	vector<int> boardValues;

	vector<int> t1;
	vector<int> t2;
	vector<int> t3;
	bool mineClicked;
	bool debugMode;
	int mineCount;
	int numFlags; //number of flags at start, usually 50
	int revealedTiles; //max of 400
	
	int tileHeight;
	int tileWidth;

	sf::Sprite square;
	sf::Sprite debugPic;
	sf::Sprite digits;
	//sf::Texture completeDigits;
	sf::Sprite happy;
	sf::Sprite win;
	sf::Sprite lose;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;

	sf::Sprite digit1;
	sf::Sprite digit2;
	sf::Sprite digit3;
};