#pragma once

#include <SFML\Graphics.hpp>
#include "Ball.h"

class Paddle{
private:
	sf::RectangleShape paddle;
public:
	Paddle();
	~Paddle();
	void setSize(sf::Vector2f size); //cài đặt kích thước
	Paddle(sf::Vector2f size); //Khởi tạo kích thước
	void drawTo(sf::RenderWindow& window); //vẽ bảng đỡ
	void move(sf::Vector2f distance); //di chuyển theo vector
	void setPos(sf::Vector2f newPos); //cài đặt vị trí
	void setColor(int a, int b, int c, int d); //tô màu
	sf::Vector2f getPos(); //lấy vị trí
	bool isHitBall(Ball ball); //trả về true nếu bảng trúng bóng, ngược lại trả về false
};
