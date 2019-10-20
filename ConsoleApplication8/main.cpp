#include "Header.h"

int main() {
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);//Lấy vị trí giữa màn hình
	window.create(sf::VideoMode(900, 900), "Pong Pong Pong Pong", sf::Style::Titlebar | sf::Style::Close);//create window: size, title
	window.setPosition(centerWindow);//đặt vị trí mở lên = centerWindow

	window.setFramerateLimit(480);//limit framerate
	
	bool AIMode = false;
	//Set Text
	sf::Font font;
	if (!font.loadFromFile("INVASION2000.ttf")){
		// error...
	}
	
	//Start Screen
	//Option
	float defaultSpeed = 0.61;
	float padSpeed = defaultSpeed - 0.01;
	float ballSpeed = defaultSpeed;
	int speed = 5;

	//Thông báo level
	sf::Text Level;
	Level.setFont(font);
	Level.setFillColor(sf::Color::Color(185, 175, 120));
	Level.setPosition({ 250,480 });
	Level.setCharacterSize(50);
	Level.setString("Level: 5"); //mặc định lv5

	//thông báo Mode
	sf::Text Mode;
	Mode.setFont(font);
	Mode.setFillColor(sf::Color::Yellow);
	Mode.setPosition({ 250, 250 });
	Mode.setCharacterSize(50);
	Mode.setString("Human VS Human"); //mặc định 2 player

	//Menu
	//Mainmenu
	std::string mainMenu[3];
	mainMenu[0] = "Play";
	mainMenu[1] = "Option";
	mainMenu[2] = "Exit";
	Menu mainScreen(900, 900, mainMenu, 3); //truyền vào 3 lựa chọn

	while (window.isOpen()) {
		bool playing = false;
		sf::Event event;
		//Menu screen
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				//chọn bằng nút Up/Down
				case sf::Keyboard::Up:
					mainScreen.moveUp();
					break;
				case sf::Keyboard::Down:
					mainScreen.moveDown();
					break;

				case sf::Keyboard::Return:
					switch (mainScreen.getPressedItem())//lấy giá trị đang chọn
					{
					case 0:
						playing = true;
						break;
					case 1:
						changeSetting(window, event, Level, defaultSpeed, ballSpeed, padSpeed, speed, AIMode, Mode);
						//cập nhật giá trị speed, mode
						break;
					case 2:
						window.close();
						exit(0);
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				exit(0);
				break;
			}
		}
		//truyền vào speed, mode để chơi game
		gamePlay(window, font, padSpeed, ballSpeed, defaultSpeed, playing, AIMode);

		window.clear();
		mainScreen.drawTo(window);
		window.display();//hiện thị ra màn hình menu
	}
}