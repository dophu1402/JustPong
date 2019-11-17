#include "Ball.h"
7
Ball::Ball() {
	ball.setRadius(0); // kích thước mặc định = 0
}
Ball::~Ball() {

}

Ball::Ball(float size) {
	ball.setRadius(size); //truyền bán kính
}

void Ball::drawTo(sf::RenderWindow& window) {
	window.draw(ball); //vẽ quả bóng
}

void Ball::move(sf::Vector2f distance) {
	ball.move(distance); // di chuyển
}

void Ball::setPos(sf::Vector2f newPos) {
	ball.setPosition(newPos); //cài đặt vị trí
}

sf::Vector2f Ball::getPos() {
	return ball.getPosition(); //lấy vị trí
}

float Ball::getRad() {
	return ball.getRadius(); //lấy bán kính
}
