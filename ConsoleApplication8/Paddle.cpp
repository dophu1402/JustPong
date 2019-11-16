#include "Paddle.h"

Paddle::Paddle() {
	paddle.setSize({ 0,0 });//khởi tạo size mặc định = 0
}

void Paddle::setSize(sf::Vector2f size) {
	paddle.setSize(size);//cài size
}

Paddle::~Paddle() {

}

Paddle::Paddle(sf::Vector2f size) {
	paddle.setSize(size);//khởi tạo với size cho trước
}

void Paddle::drawTo(sf::RenderWindow& window) {
	window.draw(paddle);//vẽ thanh trượt (hình chữ nhật)
}

void Paddle::move(sf::Vector2f distance) {
	paddle.move(distance);//di chuyển theo hướng vector
}

void Paddle::setPos(sf::Vector2f newPos) {
	paddle.setPosition(newPos);//cài đặt vị trí
}

void Paddle::setColor(int a, int b, int c, int d) {
	paddle.setFillColor(sf::Color(a, b, c, d));//đổi màu
}

sf::Vector2f Paddle::getPos() {
	return paddle.getPosition(); // lấy vị trí
}

bool Paddle::isHitBall(Ball ball) {
	//nếu bóng chạm thanh trượt thì trả về true
	if (ball.getPos().y + ball.getRad() * 2 > paddle.getPosition().y && ball.getPos().y < paddle.getPosition().y + paddle.getSize().y) {
		if (ball.getPos().x + ball.getRad() * 2 > paddle.getPosition().x && ball.getPos().x < paddle.getPosition().x + paddle.getSize().x) {
			return true;
		}
	}
	return false;
}