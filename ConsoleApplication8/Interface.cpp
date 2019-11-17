#include "Header.h"

//Vị trí mặc định
void defaultPos(Paddle &paddle1, Paddle& paddle2, Ball& ball){
	paddle1.setPos({ 50, 460 });
	paddle2.setPos({ 840, 460 });
	ball.setPos({ 450, 500 });
}
//vẽ các chi tiết
void drawToWindow(sf::RenderWindow& window, Paddle paddle1, Paddle paddle2, Ball ball, Wall wall, sf::Text Exit){
	window.clear(sf::Color(40, 40, 40));
	window.draw(Exit);
	paddle1.drawTo(window);
	paddle2.drawTo(window);
	wall.drawTo(window);
	ball.drawTo(window);
}
//đổi speed
void changeSpeed(sf::RenderWindow& window, sf::Event& event, sf::Text& Level, int& speed, Menu optionScreen) {
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		// Up, Down để thoát khỏi chế độ chọn
		case sf::Keyboard::Up:
			break;
		case sf::Keyboard::Down:
			break;
		//Left, Right để thay đổi tốc độ
		case sf::Keyboard::Right:
			speed++;//tăng speed lên, nếu > 10 thì trở về 1
			if (speed == 11) {
				speed = 1;
			}
			break;
		case sf::Keyboard::Left:
			speed--;//giảm speed lại, nếu < 1 thì trở thành 10
			if (speed == 0) {
				speed = 10;
			}
			break;
		}
		break;
	}
	Level.setString("Level: " + std::to_string(speed));//cập nhật thông báo level
}
//đổi Mode
void changeMode(sf::RenderWindow& window, sf::Event& event, Menu optionScreen, bool& AIMode, sf::Text& Mode) {
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		exit(0);
	case sf::Event::KeyReleased:
		// Up, Down để thoát khỏi chế độ chọn
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			break;
		case sf::Keyboard::Down:
			break;
		//Left hoặc Right để thay đổi chế độ
		case sf::Keyboard::Right:
			AIMode = !AIMode;
			break;
		case sf::Keyboard::Left:
			AIMode = !AIMode;
			break;
		}
		break;
	}
	//cập nhật thông báo Mode
	if (AIMode == true) {
		Mode.setString("Human VS Computer");
	}
	else {
		Mode.setString("Human VS Human");
	}
}
//menu thay đổi speed, level cho game
void changeSetting(sf::RenderWindow &window, sf::Event &event, sf::Text &Level,float &defaultSpeed, float &ballSpeed, float &padSpeed, int &speed, bool &AIMode, sf::Text &Mode){
	//optionmenu
	std::string optionMenu[3];
	optionMenu[0] = "Select Mode";
	optionMenu[1] = "Speed Level";
	optionMenu[2] = "Return";
	Menu optionScreen(900, 900, optionMenu, 3);//tạo 3 dòng giá trị
	bool exitOption = false;
	while (exitOption == false) {
		//event loop
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				//di chuyển lên xuống = up/down
				case sf::Keyboard::Up:
					optionScreen.moveUp();
					break;
				case sf::Keyboard::Down:
					optionScreen.moveDown();
					break;
				case sf::Keyboard::BackSpace:
					exitOption = true;//Thoat khoi option menu
					break;
				case sf::Keyboard::Enter:
					if (optionScreen.getPressedItem() == 2) {
						Level.setFillColor(sf::Color::Color(185, 175, 120));
						Mode.setFillColor(sf::Color::Color(185, 175, 120));
						exitOption = true;
						optionScreen.resetPressedItem();
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				exit(0);
				break;
			}
			//giá trị 1 tương ứng speed level
			if (optionScreen.getPressedItem() == 1)
			{
				Level.setFillColor(sf::Color::Yellow);
				Mode.setFillColor(sf::Color::Color(185, 175, 120));
				changeSpeed(window, event, Level, speed, optionScreen);

				defaultSpeed = (0.36 + 1.0 * speed / 20);
				padSpeed = defaultSpeed - 0.02;
				ballSpeed = defaultSpeed;
				break;
			}
			//giá trị 0 tương ứng Mode
			if (optionScreen.getPressedItem() == 0)
			{
				Level.setFillColor(sf::Color::Color(185, 175, 120));
				Mode.setFillColor(sf::Color::Yellow);
				changeMode(window, event, optionScreen, AIMode, Mode);
			}
			Level.setFillColor(sf::Color::Color(185, 175, 120));
			break;
		}
		window.clear();
		window.draw(Level);
		window.draw(Mode);
		optionScreen.drawTo(window);
		window.display();//hiện thị cập nhật ra màn hình
	}
}

void result(int scoreLeft, int scoreRight, sf::Text &Result) {
	//thông báo lợi thế của người chơi
	if (scoreLeft > scoreRight) {
		Result.setFillColor({ 255, 85, 45, 255 });
		Result.setString("Red is leading");
	}
	if (scoreLeft < scoreRight) {
		Result.setFillColor({ 0, 105, 255, 255 });
		Result.setString("Blue is leading");
	}
	if (scoreLeft == scoreRight) {
		Result.setFillColor(sf::Color::Yellow);
		Result.setString("       Tie");
	}
}
