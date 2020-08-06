#include "Board.h"
#include <vector>

Board::Board() 
{
	//access by images["name"}
	//change these paths before submission
	ifstream testboard1("boards/testboard1.brd");
	ifstream testboard2("boards/testboard2.brd");
	ifstream testboard3("boards/testboard3.brd");


	images["digits"].loadFromFile("images/digits.png");
	images["face_happy"].loadFromFile("images/face_happy.png");
	images["face_lose"].loadFromFile("images/face_lose.png");
	images["face_win"].loadFromFile("images/face_win.png");
	images["flag"].loadFromFile("images/flag.png");
	images["mine"].loadFromFile("images/mine.png");
	images["number_1"].loadFromFile("images/number_1.png");
	images["number_2"].loadFromFile("images/number_2.png");
	images["number_3"].loadFromFile("images/number_3.png");
	images["number_4"].loadFromFile("images/number_4.png");
	images["number_5"].loadFromFile("images/number_5.png");
	images["number_6"].loadFromFile("images/number_6.png");
	images["number_7"].loadFromFile("images/number_7.png");
	images["number_8"].loadFromFile("images/number_8.png");
	images["test_1"].loadFromFile("images/test_1.png");
	images["test_2"].loadFromFile("images/test_2.png");
	images["test_3"].loadFromFile("images/test_3.png");
	images["tile_hidden"].loadFromFile("images/tile_hidden.png");
	images["tile_revealed"].loadFromFile("images/tile_revealed.png");
	images["debug"].loadFromFile("images/debug.png");
	

	

	//Stores testboard data into array
	//Input data is shifted 48 for some reason?
	string line;
	if (testboard1.is_open()) {
		while (getline(testboard1, line)) {
			for (unsigned int i = 0; i < line.length(); i++) {
				t1.push_back((int)line[i] - 48);
			}
		}
	}
	if (testboard2.is_open()) {
		while (getline(testboard2, line)) {
			for (unsigned int i = 0; i < line.length(); i++) {
				t2.push_back((int)line[i] - 48);
			}
		}
	}
	if (testboard3.is_open()) {
		while (getline(testboard3, line)) {
			for (unsigned int i = 0; i < line.length(); i++) {
				t3.push_back((int)line[i] - 48);
			}
		}
	}
	testboard1.close();
	testboard2.close();
	testboard3.close();

	mineCount = 0;
	mineClicked = false;
	debugMode = false;
	numFlags = 0;
	revealedTiles = 0;

	square.setTexture(images["tile_hidden"]);
	tileHeight = square.getTextureRect().height;
	tileWidth = square.getTextureRect().width;

	debugPic.setTexture(images["debug"]);

	float debugPicW = (float)debugPic.getTextureRect().width;
	debugPic.setPosition(sf::Vector2f(500, 16 * tileHeight));
	test1.setTexture(images["test_1"]);
	float test1W = test1.getTextureRect().width;
	
	test1.setPosition(sf::Vector2f(500 + debugPicW, 16*tileHeight));
	test2.setTexture(images["test_2"]);
	test2.setPosition(sf::Vector2f(500 + test1W + debugPicW, 16 * tileHeight));
	float test2W = test2.getTextureRect().width;

	test3.setTexture(images["test_3"]);
	test3.setPosition(sf::Vector2f(500 + test2W + debugPicW + test1W, 16 * tileHeight));
	win.setTexture(images["face_win"]);
	win.setPosition(sf::Vector2f(350, 16 * tileHeight));
	happy.setTexture(images["face_happy"]);
	happy.setPosition(sf::Vector2f(350, 16 * tileHeight));
	lose.setTexture(images["face_lose"]);
	lose.setPosition(sf::Vector2f(350, 16 * tileHeight));

	digits.setTexture(images["digits"]);
	setRandomTile();
}
void Board::updateBoard(sf::RenderWindow& window)
{
	startBoard(window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i position = sf::Mouse::getPosition(window);
		//Code using position.x and position.y

		sf::FloatRect debugButton = debugPic.getGlobalBounds();
		sf::FloatRect test1Button = test1.getGlobalBounds();
		sf::FloatRect test2Button = test2.getGlobalBounds();
		sf::FloatRect test3Button = test3.getGlobalBounds();
		sf::FloatRect smileButton = win.getGlobalBounds();
		if (debugButton.contains(sf::Vector2f(position.x, position.y))) {
			debugMode = !debugMode;
			//cout << debugMode << endl;
		}
		else if (test1Button.contains(sf::Vector2f(position.x, position.y))) {
			//
			//cout << "test1 clicked" << endl;
			setUpBoard(1);
		}
		else if (test2Button.contains(sf::Vector2f(position.x, position.y))) {
			//
			//cout << "test2 clicked" << endl;
			setUpBoard(2);
		}
		else if (test3Button.contains(sf::Vector2f(position.x, position.y))) {
			//
			//cout << "test3 clicked" << endl;
			setUpBoard(3);
		}
		else if (smileButton.contains(sf::Vector2f(position.x, position.y))) {
			//
			//cout << "test3 clicked" << endl;
			setRandomTile();
			setUpBoard(0);
		}
		else if (mineClicked == false && (400 - revealedTiles) != mineCount) {
			{
				int posX = position.x / (int)tileWidth;
				int posY = position.y / (int)tileHeight;
				if (posX < 25 && posX>=0) {
					if (posY < 16 && posY>=0) {
						//cout << posX << " " << posY << endl;
						if (gameBoard[posX + 25 * posY].getFlag() == false) {
							mineClicked = gameBoard[posX + 25 * posY].revealTile();
						}
					}
				}
			}

		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mineClicked == false && (400-revealedTiles)!=mineCount) {
			sf::Vector2i position = sf::Mouse::getPosition(window);
			//Code using position.x and position.y to place flags
			int posX = position.x / (int)tileWidth;
			int posY = position.y / (int)tileHeight;
			if (posX < 25 && posX>=0) {
				if (posY < 16 && posY>=0) {
					//cout << posX << " " << posY << endl;
					if (gameBoard[posX + 25 * posY].getFlag() == true) {
						if (gameBoard[posX + 25 * posY].setFlag(window) == true) {
							numFlags++;
						}
					}
					else {
						if (gameBoard[posX + 25 * posY].setFlag(window) == true)
							numFlags--;
					}

				}
			}


	}

	if (mineClicked == true) {
			//cout << "You Lose" << endl;
			window.draw(lose);
	}
	else if ((400 - revealedTiles) == mineCount) {
			//cout << "You Won" << endl;
			window.draw(win);
	}

	
}

void Board::checkWin()
{
	revealedTiles = 0;
	for (unsigned int i = 0; i < gameBoard.size(); i++) {
		if (gameBoard[i].isReveal == true)
			revealedTiles++;
	}
}


void Board::startBoard(sf::RenderWindow& window)
{
	checkWin();
	if (mineClicked == false && (400-revealedTiles) != mineCount) {
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			gameBoard[i].drawTile(window);
		}

		if (debugMode == true) {
			drawMines(window);
		}
	}
	else if(mineClicked == true) {
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			gameBoard[i].showMine(window);
		}
	}
	else if ((400-revealedTiles) == mineCount) {
		for(unsigned int i = 0; i < gameBoard.size(); i++) {
			if (gameBoard[i].getFlag() == true) {
				bool t = gameBoard[i].setFlag(window);
			}
			if (gameBoard[i].isMine() == true) {
				bool t = gameBoard[i].setFlag(window);
			}
			numFlags = 0;
			gameBoard[i].drawTile(window);
		}
	}

	setDigits(window);
	window.draw(happy);
	window.draw(debugPic);
	window.draw(test1);
	window.draw(test2);
	window.draw(test3);
}

void Board::drawMines(sf::RenderWindow &window)
{
	for (unsigned int i = 0; i < gameBoard.size(); i++) {
		gameBoard[i].setDebug(window);
	}

}


void Board::setRandomTile()
{
	boardValues.clear();
	int counter = 0;
	bool tempFlag = false;
	vector<int> tempVector;
	while (counter < 50) {
		int temp = Random::Int(0, 399);
		tempFlag = false;
		for (unsigned int i = 0; i < tempVector.size(); i++) {
			if (temp == tempVector[i])
				tempFlag = true;
		}
		if (tempFlag == false) {
			tempVector.push_back(temp);
			counter++;
		}
	}
	for (unsigned int i = 0; i < 400; i++) {
		boardValues.push_back(0);
	}
	for (unsigned int i = 0; i < tempVector.size(); i++) {
		boardValues[tempVector[i]] = 1;
	}
	
}
void Board::setDigits(sf::RenderWindow &window)
{
	drawDigits(numFlags, window);

}
void Board::drawDigits(int d, sf::RenderWindow &window)
{
	
	if (d >= 0) {
		int hundDigit = (d / 10) / 10;
		int tensDigit = (d / 10 )% 10;
		int onesDigit = d % 10;
		
		digits.setPosition(sf::Vector2f(0, 16*tileHeight));
		digits.setTextureRect(sf::IntRect(21*hundDigit, 0, 21, 32));
		window.draw(digits);
		digits.setPosition(sf::Vector2f(21, 16 * tileHeight));
		digits.setTextureRect(sf::IntRect(21 * tensDigit, 0, 21, 32));
		window.draw(digits);
		digits.setPosition(sf::Vector2f(42, 16 * tileHeight));
		digits.setTextureRect(sf::IntRect(21 * onesDigit, 0, 21, 32));
		window.draw(digits);
	}
	else if (d < 0) {
		int hundDigit = (-d / 10) / 10;
		int tensDigit = (-d / 10) % 10;
		int onesDigit = -d % 10;
		digits.setPosition(sf::Vector2f(0, 16 * tileHeight));
		digits.setTextureRect(sf::IntRect(21 * 10 ,0, 21, 32));
		window.draw(digits);
		digits.setPosition(sf::Vector2f(21, 16 * tileHeight));
		digits.setTextureRect(sf::IntRect(21 * hundDigit, 0, 21, 32));
		window.draw(digits);
		digits.setPosition(sf::Vector2f(42, 16 * tileHeight));
		digits.setTextureRect(sf::IntRect(21 * tensDigit, 0, 21, 32));
		window.draw(digits);
		digits.setPosition(sf::Vector2f(63, 16 * tileHeight));
		digits.setTextureRect(sf::IntRect(21 * onesDigit, 0, 21, 32));
		window.draw(digits);
	}
}

void Board::initiatizeTiles() {
	gameBoard.clear();

	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 25; x++)
		{
			Tile n(images, false, x * tileWidth, y * tileHeight);
			gameBoard.push_back(n);
		}
	}
	
}
void Board::setUpBoard(int x)
{
	mineCount = 0;
	mineClicked = false;
	debugMode = false;

	if ( x == 0) {
		//random board
		initiatizeTiles();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			if (boardValues[i] == 0) 
				gameBoard[i].mine = false;
			else {
				gameBoard[i].mine = true;
				mineCount++;
			}
		}
		linkNeighbors();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			gameBoard[i].setItem(images);
		}


	}
	else if (x == 1) {
		//set up with test1 using t1[]
		initiatizeTiles();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			if (t1[i] == 0)
				gameBoard[i].mine = false;
			else {
				gameBoard[i].mine = true;
				mineCount++;
			}
		}
		linkNeighbors();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			gameBoard[i].setItem(images);
		}

	}
	else if (x == 2) {
		//set up with test 2 using t2[]
		initiatizeTiles();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			if (t2[i] == 0)
				gameBoard[i].mine = false;
			else {
				gameBoard[i].mine = true;
				mineCount++;
			}
		}
		linkNeighbors();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			gameBoard[i].setItem(images);
		}

	}
	else if (x == 3) {
		//set up with test 3 using t3[]
		initiatizeTiles();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			if (t3[i] == 0)
				gameBoard[i].mine = false;
			else {
				mineCount++;
				gameBoard[i].mine = true;
			}
		}
		linkNeighbors();
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			gameBoard[i].setItem(images);
		}

	}
	else {
		cout << "error" << endl;
		return;
	}

	numFlags = mineCount;
}

void Board::linkNeighbors() 
{
	if (gameBoard.size() != 400) {
		cout << "Error with initializing board" << endl;
	}
	else {
		for (unsigned int i = 0; i < gameBoard.size(); i++) {
			if (i == 0) { //top left corner
				gameBoard[0].tileNeighbor[3] = &gameBoard[1];
				gameBoard[0].tileNeighbor[4] = &gameBoard[26];
				gameBoard[0].tileNeighbor[5] = &gameBoard[25];
			}
			else if (i < 24) { //up to top right
				gameBoard[i].tileNeighbor[3] = &gameBoard[i + 1];
				gameBoard[i].tileNeighbor[7] = &gameBoard[i - 1];
				gameBoard[i].tileNeighbor[4] = &gameBoard[i + 26];
				gameBoard[i].tileNeighbor[5] = &gameBoard[i + 25];
				gameBoard[i].tileNeighbor[6] = &gameBoard[i + 24];
			}
			else if (i == 24) { //top right
				gameBoard[i].tileNeighbor[5] = &gameBoard[i + 25];
				gameBoard[i].tileNeighbor[6] = &gameBoard[i + 24];
				gameBoard[i].tileNeighbor[7] = &gameBoard[i - 1];
			}
			else if (i < 375) { //up till bottom left
				if (i % 25 == 0) { //left edge
					gameBoard[i].tileNeighbor[1] = &gameBoard[i - 25];
					gameBoard[i].tileNeighbor[2] = &gameBoard[i - 24];
					gameBoard[i].tileNeighbor[3] = &gameBoard[i + 1];
					gameBoard[i].tileNeighbor[4] = &gameBoard[i + 26];
					gameBoard[i].tileNeighbor[5] = &gameBoard[i + 25];
				}
				else if ((i+1) % 25 == 0) { //right edge
					gameBoard[i].tileNeighbor[0] = &gameBoard[i - 26];
					gameBoard[i].tileNeighbor[1] = &gameBoard[i - 25];
					gameBoard[i].tileNeighbor[7] = &gameBoard[i - 1];
					gameBoard[i].tileNeighbor[6] = &gameBoard[i + 24];
					gameBoard[i].tileNeighbor[5] = &gameBoard[i + 25];
				}
				else { //middle
					gameBoard[i].tileNeighbor[0] = &gameBoard[i-26];
					gameBoard[i].tileNeighbor[1] = &gameBoard[i-25];
					gameBoard[i].tileNeighbor[2] = &gameBoard[i-24];
					gameBoard[i].tileNeighbor[3] = &gameBoard[i+1];
					gameBoard[i].tileNeighbor[4] = &gameBoard[i+26];
					gameBoard[i].tileNeighbor[5] = &gameBoard[i+25];
					gameBoard[i].tileNeighbor[6] = &gameBoard[i+24];
					gameBoard[i].tileNeighbor[7] = &gameBoard[i-1];
				}
			}
			else if (i == 375) {
				gameBoard[i].tileNeighbor[1] = &gameBoard[i-25];
				gameBoard[i].tileNeighbor[2] = &gameBoard[i-24];
				gameBoard[i].tileNeighbor[3] = &gameBoard[i+1];
			}
			else if (i < 399) {
				gameBoard[i].tileNeighbor[7] = &gameBoard[i-1];
				gameBoard[i].tileNeighbor[0] = &gameBoard[i-26];
				gameBoard[i].tileNeighbor[1] = &gameBoard[i-25];
				gameBoard[i].tileNeighbor[2] = &gameBoard[i-24];
				gameBoard[i].tileNeighbor[3] = &gameBoard[i+1];
			}
			else if (i == 399) {
				gameBoard[i].tileNeighbor[7] = &gameBoard[i-1];
				gameBoard[i].tileNeighbor[0] = &gameBoard[i-26];
				gameBoard[i].tileNeighbor[1] = &gameBoard[i-25];
			}
			

		}
	}
}

