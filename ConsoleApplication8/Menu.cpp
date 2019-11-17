#include "Menu.h"
7
Menu::Menu(float width, float height, std::string selectLine[], int amount){
	amountOfItems = amount;
	menu = new sf::Text[amount];
	if (!font.loadFromFile("INVASION2000.ttf")){
		//error...
	}
	for (int i = 0; i < amountOfItems; i++) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(70);
		menu[i].setString(selectLine[i]);
		menu[i].setPosition(sf::Vector2f(250, height / (amountOfItems + 1) * (i+1) - 50));
		if (i == 0) {
			menu[i].setFillColor(sf::Color::White); //dòng đang chọn trắng tinh
		}
		else {
			menu[i].setFillColor(sf::Color::Color(128, 128, 128)); // các dòng không được chọn nhạt hơn
		}
	}
	selectedItemIndex = 0;
}


Menu::~Menu(){
}

void Menu::drawTo(sf::RenderWindow& window){
	for (int i = 0; i < amountOfItems; i++)	{
		window.draw(menu[i]);//vẽ menu
	}
}
//di chuyển lên
void Menu::moveUp(){
	if (selectedItemIndex - 1 >= 0){
		menu[selectedItemIndex].setFillColor(sf::Color::Color(128, 128, 128));
		selectedItemIndex--; //cập nhập vị trí sau khi di chuyển chọn
		menu[selectedItemIndex].setFillColor(sf::Color::White); //đổi màu dòng đang chọn
	}
}
//di chuyển xuống
void Menu::moveDown(){
	if (selectedItemIndex + 1 < amountOfItems)	{
		menu[selectedItemIndex].setFillColor(sf::Color::Color(128, 128, 128));
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::White);
	}
}
//trả về vị trí đang chọn
int Menu::getPressedItem(){
	return selectedItemIndex;
}
//trả về 0 khi thoát menu
void Menu::resetPressedItem() {
	selectedItemIndex = 0;
}
//số lượng dòng
int Menu::setAmount(int amount) {
	menu = new sf::Text[amount];
	amountOfItems = amount;
	return amount;
}
