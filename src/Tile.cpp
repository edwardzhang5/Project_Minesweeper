#include "Tile.h"


Tile::Tile(map<string, sf::Texture>& images, bool mine, float xcor, float ycor)
{
	this->xcor = xcor;
	this->ycor = ycor;
	this->mine = mine;
	this->debugMode = false;
	this->isFlagged = false;
	this->isReveal = false;
	this->hasItem = false;
	this->numAdjMine = 0;

		
	back.setPosition(sf::Vector2f(xcor, ycor));
	back.setTexture(images["tile_revealed"]);
	front.setPosition(sf::Vector2f(xcor, ycor));
	front.setTexture(images["tile_hidden"]);
	flag.setPosition(sf::Vector2f(xcor, ycor));
	flag.setTexture(images["flag"]);
	item.setPosition(sf::Vector2f(xcor, ycor));
	
	for (int i = 0; i < 8; i++) {
		tileNeighbor.push_back(nullptr);
	}

}


bool Tile::isMine()
{
	return mine;
}
void Tile::setDebug(sf::RenderWindow& window)
{
	//debugMode = !debugMode;
	if (mine==true) {
		window.draw(front);
		window.draw(item);
	}
	else if(isReveal==false && isFlagged==false){
		window.draw(front);
	}
	else if (isReveal == false && isFlagged == true) {
		window.draw(front);
		window.draw(flag);
	}
}
bool Tile::setFlag(sf::RenderWindow& window)
{
	if (isReveal == true)
		return false;
	if (isFlagged == true) {
		isFlagged = false;
		window.draw(front);
	}
	else {
		isFlagged = true;
		window.draw(flag);
	}
	return true;
}
bool Tile::getFlag()
{
	return isFlagged;
}
bool Tile::revealTile()
{
	if (isFlagged == true || isReveal==true) {
		return false;
	}
	if (isMine() == true)
		return true;
	else {
		isReveal = true;
		//window.draw(back);
		if (hasItem == true) {
			//window.draw(item);
			return false;
		}
		else {
			for (unsigned int i = 0; i < tileNeighbor.size(); i++) {
				if (tileNeighbor[i] != nullptr && tileNeighbor[i]->isMine() == false) {
					tileNeighbor[i]->revealTile(); //recursively reveals tiles
				}

			}
		}


		
	}
	
	return false;

}
void Tile::showMine(sf::RenderWindow &window) { //Shows all mines after losing
	drawTile(window);
	if (mine == true) {
		window.draw(back);
		window.draw(item);
	}
	

}
void Tile::drawTile(sf::RenderWindow& window)
{
	if(isReveal==false)
		window.draw(front);
	if (isFlagged == true) {
		//window.draw(front);
		window.draw(flag);
	}
	else if (isReveal == true) {
		window.draw(back);
		window.draw(item);
	}

	//for testing
	//window.draw(item);

}

void Tile::countNeighborMine() 
{
	numAdjMine = 0;
	for (unsigned int i = 0; i < tileNeighbor.size(); i++) {
		if (tileNeighbor[i] != nullptr && tileNeighbor[i]->isMine() == true)
			numAdjMine++;
	}
}

void Tile::setItem(map<string, sf::Texture>& images)
{
	countNeighborMine();
	//cout << numAdjMine << endl;

	if (mine == true) {
		item.setTexture(images["mine"]);
		hasItem = true;
		
	}
	else {
		if (numAdjMine == 0) {
			hasItem = false;
			return;
		}
		if (numAdjMine == 1) {
			item.setTexture(images["number_1"]);
			hasItem = true;
		}
		else if (numAdjMine == 2) {
			item.setTexture(images["number_2"]);
			hasItem = true;
		}
		else if (numAdjMine == 3) {
			item.setTexture(images["number_3"]);
			hasItem = true;
		}
		else if (numAdjMine == 4) {
			item.setTexture(images["number_4"]);
			hasItem = true;
		}
		else if (numAdjMine == 5) {
			item.setTexture(images["number_1"]);
			hasItem = true;
		}
		else if (numAdjMine == 6) {
			item.setTexture(images["number_6"]);
			hasItem = true;
		}
		else if (numAdjMine == 7) {
			item.setTexture(images["number_7"]);
			hasItem = true;
		}
		else if (numAdjMine == 8) {
			item.setTexture(images["number_8"]);
			hasItem = true;
		}
		else {
			item.setTexture(images["tile_revealed"]);
			hasItem = false;
		}

	}
	

}
