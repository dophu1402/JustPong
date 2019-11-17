#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class Ball{
private:
	sf::CircleShape ball;
public:
	Ball();
	~Ball();
	Ball(float size); // khởi tạo với kích thước cho trước
	void drawTo(sf::RenderWindow& window); //vẽ bóng
	void move(sf::Vector2f distance); //di chuyển theo hướng vector 
	void setPos(sf::Vector2f newPos); //cài đặt vị trí
	sf::Vector2f getPos(); //lấy vị trí hiện tại
	float getRad(); //lấy bán kính
};
