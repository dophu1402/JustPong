#pragma once
#include "SFML/Graphics.hpp"
#include <string>
1
#define MAX_NUMBER_OF_ITEMS 3
#define const sf::Time Game::TimePerFrame  sf::seconds(1.f / 60.f)

class Menu
{
private:
	int selectedItemIndex;//Phần tử đang được chọn
	int amountOfItems;//số lượng phần  tử trong menu
	sf::Font font;    //font trong Menu
	sf::Text *menu;   //Menu có thể gồm nhiều dòng khác nhau
public:
	Menu(float width, float height, std::string lineOption[], int amount); //khởi tạo Menu, vị trí dòng dựa trên kích thước màn hình, truyền vào số lượng dòng và nội dung menu
	~Menu();
	void drawTo(sf::RenderWindow& window);//vẽ ra màn hình
	void moveUp();    //di chuyển xuống
	void moveDown();  //di chuyển lên
	int getPressedItem();     //lấy số thứ tự phần tử đang được chọn
	void resetPressedItem();  //trả về 0 khi rời menu
	int setAmount(int amount);  //truyền số dòng trong menu
};
