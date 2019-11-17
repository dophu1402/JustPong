#pragma once
7
#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

class Wall {
public:
	Paddle Left, Right, Top, Bottom; //có thể truy xuất 4 cạnh ra ngoài vì bóng tác động lên mỗi cạnh sẽ có hiệu ứng khác nhau
	Wall(); //khởi tạo kích thước
	~Wall();
	void drawTo(sf::RenderWindow& window); //vẽ ra màn hình
};
