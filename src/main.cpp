#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "Board.h"
#include "Random.h"


using namespace std;

//Change image directory before submission
//Change board directory too
int main()
{
   

    //Code for clicking on something
    //sf::FloatRect rectangle = sprite_name.getGlobalBounds();
    //if(rectangle.contains(sf::Vector2f(position.x,position.y){}

    cout << "Game started." << endl;
    //int test = Random::Int(0, 399);
    //cout << test << endl;


    //map<string, sf::Texture> textureMap;
    Board n;
    n.initiatizeTiles();
    n.setUpBoard(0);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                cout << "Thank you for playing :)" << endl;
                window.close();
            }
           
        
            window.clear(sf::Color(255, 255, 255, 255));
            //Insert sprite drawings here
            //window.draw(sprite);
            //n.startBoard(window);
            n.updateBoard(window);

            window.display();
        }
        
        
    }
  


    return 0;
}