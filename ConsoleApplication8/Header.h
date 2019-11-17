#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "Menu.h"
#include <string>
#include <ctime>

void defaultPos(Paddle& paddle1, Paddle& paddle2, Ball& ball); //đưa bảng đỡ, bóng về vị trí ban đầu
void drawToWindow(sf::RenderWindow& window, Paddle paddle1, Paddle paddle2, Ball ball, Wall wall, sf::Text Exit); //thao tác vẽ bảng, tường, bóng
void changeSpeed(sf::RenderWindow& window, sf::Event& event, sf::Text& Level, int& speed,Menu); //tăng giảm tốc độ
void changeSetting(sf::RenderWindow& window, sf::Event& event, sf::Text& Level, float& defaulSpeed, float& ballSpeed, float& padSpeed, int& speed, bool& AIMode, sf::Text & Mode); //thay đổi Mode, Speed
void changeMode(sf::RenderWindow& window, sf::Event& event, Menu optionScreen, bool& AImode, sf::Text &Mode); //đổi chế 1 player hoặc 2 player
void gamePlay(sf::RenderWindow& window, sf::Font font, float padSpeed, float ballSpeed, float defaultSpeed, bool& playing, bool AIMode); //Thực hiện các hoạt động của game
void result(int scoreLeft, int scoreRight, sf::Text& Result); //thống kê điểm
