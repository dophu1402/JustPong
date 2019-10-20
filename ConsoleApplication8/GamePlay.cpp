#include "Header.h"

void gamePlay(sf::RenderWindow& window, sf::Font font, float padSpeed, float ballSpeed, float defaultSpeed, bool& playing, bool AIMode) {
	
	sf::Text Start;//cài đặt thông báo dừng màn hình
	Start.setFont(font);
	Start.setString("Press Space/Enter To Start");
	Start.setFillColor(sf::Color::Yellow);

	sf::Text Guide;//hướng dẫn phím
	Guide.setFont(font);
	Guide.setFillColor(sf::Color::Yellow);
	Guide.setString("Pause: P\t\t\t\t\t Menu: Tab\nResume: Space/Enter\tExit: ESC");
	Guide.setPosition(10, 820);
	
	sf::Text Result;
	Result.setFont(font);
	Result.setCharacterSize(60);
	Result.setPosition(220, 450);

	//điểm (ban đầu cả 2 bằng 0)
	int scoreLeft = 0;
	int scoreRight = 0;

	//tạo paddle với kích thước và màu
	Paddle paddle1({ 10, 100 });
	Paddle paddle2({ 10, 100 });
	paddle1.setColor(255, 85, 45, 255);
	paddle2.setColor(0, 105, 255, 255);
	//tạo 4 bức tường
	Wall wall;

	//tạo trái bóng:
	Ball ball({ 10 });
	//cài đặt vị trí ban đầu
	defaultPos(paddle1, paddle2, ball);

	//khởi tạo event
	sf::Event event;
	//tạo clock để do thời gian các vòng chạy
	sf::Clock clock;
	while (playing == true) {
		float timeElapse = clock.restart().asSeconds() * 1000;//do thời gian mỗi lần thực hiện vòng lặp để kết hợp tốc độ di chuyển để giảm không thuộc vào tốc độ cpu
		if (timeElapse > 3) {
			timeElapse = 3; //giới hạn tốc độ, tránh trường hợp bóng di chuyển nhảy vọt nhiều pixel khi máy bị giật, lag
		}
		//Hướng di chuyển của bóng, mặc định ban đầu về bên trái, giá trị thay đổi liên tục
		static bool goingUp = false;
		static bool goingDown = false;
		static bool goingLeft = true;
		static bool goingRight = false;

		//Hướng di chuyển của máy
		//sau mỗi vòng lặp hướng tự trả về mặc định
		bool AIgoingUp = false;
		bool AIgoingDown = false;
		bool AIgoingLeft = false;
		bool AIgoingRight = false;

		//Player1 Movement:
		//sử dụng các nút W A S D để di chuyển
		//giới giạn không gian di chuyển
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.getPos().y > 210) {
			paddle1.move({ 0, -padSpeed * timeElapse });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && paddle1.getPos().x < 100) {
			paddle1.move({ padSpeed / 3 * 2 * timeElapse, 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.getPos().y < 700) {
			paddle1.move({ 0, padSpeed * timeElapse });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && paddle1.getPos().x > 30) {
			paddle1.move({ -padSpeed / 3 * 2 * timeElapse, 0 });
		}

		//Player2 Movement
		//sử dụng các nút mũi tên để di chuyển
		//giới giạn không gian di chuyển
		if (AIMode == false) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.getPos().y > 210) {
				paddle2.move({ 0, -padSpeed * timeElapse });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle2.getPos().x < 860) {
				paddle2.move({ padSpeed / 3 * 2 * timeElapse, 0 });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.getPos().y < 700) {
				paddle2.move({ 0, padSpeed * timeElapse });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle2.getPos().x > 790) {
				paddle2.move({ -padSpeed / 3 * 2 * timeElapse, 0 });
			}
		}
		//Computer Movement
		//giới hạn không gian di chuyển
		else {
			//di chuyển theo hướng quả bóng
			if (ball.getPos().y >= paddle2.getPos().y + 41 && paddle2.getPos().y < 700) {
				paddle2.move({ 0,padSpeed * timeElapse });
			}
			if (ball.getPos().y < paddle2.getPos().y + 41 && paddle2.getPos().y > 210) {
				paddle2.move({ 0, -padSpeed * timeElapse });
			}
			//điều chỉnh hướng đánh lên hay xuống
			if (goingUp == false && goingDown == false) {
				if (ball.getPos().y >= paddle1.getPos().y + 41) {
					AIgoingDown = true;
				}
				if (ball.getPos().y < paddle1.getPos().y + 41) {
					AIgoingUp = true;
				}
			}
			//Đánh về phía trước nếu đối phương xa hướng đối diện
			if ((ball.getPos().y > paddle1.getPos().y + 230 || ball.getPos().y < paddle1.getPos().y - 230) && ball.getPos().x > 760) {
				if (paddle2.getPos().x > 790) {
					paddle2.move({ -padSpeed * timeElapse, 0 });
				}
				AIgoingLeft = true;
				AIgoingUp = AIgoingDown = false;
			}
			//lui về khi đến đỡ
			else if (paddle2.getPos().x < 860) {
				paddle2.move({ padSpeed / 3 * 2 * timeElapse, 0 });
				AIgoingLeft = false;
			}
		}

		//Vòng lặp đợi lệnh
		//Nếu không có lệnh nào đang thực thi thì trả về giá trị false
		//nếu có lệnh thì thực hiện
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: //click nút tắt bằng chuột
				window.close();
				exit(0);
			case sf::Event::KeyReleased:
				switch (event.key.code) //Nhận lệnh từ phím
				{
				case sf::Keyboard::Escape:
					window.close();
					exit(0);
				case sf::Keyboard::Tab:
					playing = goingUp = goingDown = goingRight = false;//reset bóng & trở về menu
					goingLeft = true;
					ballSpeed = defaultSpeed;// reset speed
					defaultPos(paddle1, paddle2, ball);//reset position
					break;
				case sf::Keyboard::P://pause game, hiện thông báo
					window.draw(Start);
					window.display();
					//dừng màn hình
					while (window.waitEvent(event)) {
						switch (event.type) {
						case sf::Event::Closed:
							window.close();
							exit(0);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
							window.close();
							exit(0);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
							clock.restart(); //bỏ thời gian vòng lặp khi pause
							break;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
							clock.restart(); //bỏ thời gian vòng lặp khi pause
							break;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
							goingLeft = true;
							goingDown = goingUp = goingRight = false;
							playing = false;//trở về main menu
							break;
						}
					}
				}
			}
		}

		//speed
		//faster, đỡ + đẩy bóng đi thì tốc độ tăng lên
		if (paddle1.isHitBall(ball) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && ballSpeed < defaultSpeed + 2) {
			ballSpeed += defaultSpeed / 5;
			goingUp = false;
			goingDown = false;
		}
		if (paddle2.isHitBall(ball) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || AIgoingLeft == true) && ballSpeed < defaultSpeed + 2) {
			ballSpeed += defaultSpeed / 5;
			AIgoingUp = AIgoingDown = false;

			goingUp = false;
			goingDown = false;
		}

		//speed
		//slower, đỡ lùi thì giảm tốc
		if (paddle1.isHitBall(ball) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && ballSpeed >= defaultSpeed) {
			ballSpeed -= defaultSpeed / 5;
			goingUp = false;
			goingDown = false;
		}
		if (paddle2.isHitBall(ball) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ballSpeed >= defaultSpeed) {
			ballSpeed -= defaultSpeed / 5;
			goingUp = false;
			goingDown = false;
		}

		//Hướng đánh bóng
		//va chạm khi đang di chuyển lên, quả bóng sẽ hướng lên
		if (paddle1.isHitBall(ball) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			goingUp = true;
			goingDown = false;
		}
		if (paddle2.isHitBall(ball) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || AIgoingUp == true)) {
			goingUp = true;
			goingDown = false;
		}

		//va chạm khi đang di chuyển xuống, quả bóng sẽ hướng xuống
		if (paddle1.isHitBall(ball) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			goingDown = true;
			goingUp = false;
		}
		if (paddle2.isHitBall(ball) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || AIgoingDown == true)) {
			goingDown = true;
			goingUp = false;
		}

		//Hit pad, di chuyển cho đến khi va chạm thì đổi hướng
		if (goingLeft == true && paddle1.isHitBall(ball) == false) {
			if (goingUp == true) {
				ball.move({ 0, -ballSpeed * timeElapse / 3 });
			}
			if (goingDown == true) {
				ball.move({ 0, ballSpeed * timeElapse / 3 });
			}
			ball.move({ -ballSpeed * timeElapse, 0 });
		}
		else if (goingLeft == true && paddle1.isHitBall(ball) == true) {
			if (ballSpeed < 3)

				ballSpeed += ballSpeed / 10; //tăng tốc 10% khi chạm
			//đổi hướng
			goingRight = true;
			goingLeft = false;
		}

		if (goingRight == true && paddle2.isHitBall(ball) == false) {
			if (goingUp == true) {
				ball.move({ 0, -ballSpeed / 3 * timeElapse });
			}
			if (goingDown == true) {
				ball.move({ 0, ballSpeed / 3 * timeElapse });
			}
			ball.move({ ballSpeed * timeElapse, 0 });
		}
		else if (goingRight == true && paddle2.isHitBall(ball) == true) {
			if (ballSpeed < 3)
				ballSpeed += ballSpeed / 10; //tăng tốc 10% khi chạm
			//đổi hướng
			goingRight = false;
			goingLeft = true;
		}

		//đổi hướng khi chạm trên và dưới
		if (wall.Top.isHitBall(ball) == true) {
			ball.move({ 0, ballSpeed / 3 * timeElapse });
			goingUp = false;
			goingDown = true;
		}
		if (wall.Bottom.isHitBall(ball) == true) {
			ball.move({ 0, -ballSpeed / 3 * timeElapse });
			goingUp = true;
			goingDown = false;
		}

		//score board
		sf::Text Score;
		Score.setString(std::to_string(scoreLeft) + ":" + std::to_string(scoreRight));//chuyển int thành string và set giá trị cho text
		Score.setFont(font);
		Score.setCharacterSize(78);
		Score.setFillColor(sf::Color::Color(100, 255, 35));
		Score.setPosition(390, 110);

		//Player score
		if (wall.Left.isHitBall(ball) == true) {
			scoreRight++;
			Score.setString(std::to_string(scoreLeft) + ":" + std::to_string(scoreRight));
			//vẽ các chi tiết
			drawToWindow(window, paddle1, paddle2, ball, wall, Guide);
			window.draw(Score);
			window.draw(Start);
			result(scoreLeft, scoreRight, Result);
			window.draw(Result);
			window.display(); //hiển thị ra màn hình

			//reset game
			ballSpeed = defaultSpeed;
			defaultPos(paddle1, paddle2, ball);
			goingDown = goingUp = false;
			//tạm dừng đợi người chơi sẵn sàng
			while (window.waitEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					exit(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();//Thoat Game
					exit(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					clock.restart();//chơi tiếp
					break;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
					playing = false;//về main menu
					break;
				}
			}
		}

		//Player score
		if (wall.Right.isHitBall(ball) == true) {
			scoreLeft++;
			Score.setString(std::to_string(scoreLeft) + ":" + std::to_string(scoreRight));
			//vẽ chi tiết
			drawToWindow(window, paddle1, paddle2, ball, wall, Guide);
			window.draw(Score);
			window.draw(Start);
			result(scoreLeft, scoreRight, Result);
			window.draw(Result);
			window.display();//hiển thị
			//reset game
			defaultPos(paddle1, paddle2, ball);
			ballSpeed = defaultSpeed;
			goingDown = goingUp = false;

			while (window.waitEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					exit(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();//Thoat Game
					exit(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					clock.restart(); //chơi tiếp
					break;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
					playing = false; //về menu
					break;
				}
			}
		}
		//vẽ các chi tiết
		drawToWindow(window, paddle1, paddle2, ball, wall, Guide);
		window.draw(Score);

		window.display();//hiện thị ra màn hình
	}
}