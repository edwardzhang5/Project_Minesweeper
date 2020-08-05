#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Tile
{
public:
	Tile(map<string, sf::Texture> &images, bool isBomb, float xcor, float ycor);  //default constructor, takes in image map, yes/no for bomb, and coordinates
	void countNeighborMine();                 //number of mines around tile
	bool isMine();                          //returns true if tile is a mine
	void setDebug(sf::RenderWindow& window); //reveals mines, should restore flags after revealing hopefully
	bool setFlag(sf::RenderWindow& window); //returns true if successful in toggeling flag
	bool getFlag();                        //returns true if flagged, false otherwise
	bool revealTile(); //Returns true if bomb, should recursively call neighboring tiles too
	void showMine(sf::RenderWindow &window); //if game is over, show all tiles with bombs
	void drawTile(sf::RenderWindow& window); //Draws front cover of tile (unrevealed tile)
	void setItem(map<string, sf::Texture>& images);  //sets item sprite to bomb or number 1-8, sets item to revealed tile if no item 
	vector<Tile*> tileNeighbor;   //tile pointers to neighbor, size should be 8
	bool mine;   //true or false depending if square is mine

	bool isReveal;  //is the tile revealed already
private:
	sf::Sprite back; //revealed tile
	sf::Sprite front; //nonrevealed tile
	sf::Sprite flag;  // flag duh
	sf::Sprite item;  //the item, could be bomb or number or revelaed tile
	
	float xcor; //coordinates
	float ycor;
	
	bool isFlagged; //is the tile flagged
	
	bool hasItem;  //does the tile have an item (bomb or number)
	bool debugMode; //is the tile in debug mode
	int numAdjMine; //counter holding number of mines surronding the tile
	

};