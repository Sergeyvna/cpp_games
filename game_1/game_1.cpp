#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE};
side branchPos[NUM_BRANCHES];

// This is where our game starts from
int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::None);

	// adding background
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);


	// adding tree
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, -100);

	// adding ant
	Texture textureAnt;
	textureAnt.loadFromFile("graphics/bee.png");
	Sprite spriteAnt;
	spriteAnt.setTexture(textureAnt);
	spriteAnt.setPosition(0, 800);

	bool antMove = false;
	float antSpeed = 0.0f;


	// adding clouds
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	Sprite sCloud1, sCloud2, sCloud3;
	Sprite clouds[3]{ sCloud1, sCloud2, sCloud3 };
	float pos[3]{ 0,110,250 };

	for (int i = 0; i < 3; i++)
	{
		clouds[i].setTexture(textureCloud);
		clouds[i].setPosition(0, pos[i]);

	}

	bool cloudMove = false;
	float cloudSpeed[3];


	// time control
	Clock clock;

	RectangleShape timeBar;
	float timeBarW = 400;
	float timeBarH = 80;
	timeBar.setSize(Vector2f(timeBarW, timeBarH));
	timeBar.setFillColor(Color::White);
	timeBar.setPosition((1920 / 2) - timeBarW / 2, 980);

	Time total;
	float timeRemain = 6.0f;
	float timeBarShrink = timeBarW / timeRemain;

	bool pause = true;

	// text
	int score = 0;

	Text txt;
	Text scoreTxt;

	Font font;
	font.loadFromFile("fonts/8bit.ttf");
	txt.setFont(font);
	scoreTxt.setFont(font);

	txt.setString("Press enter to start!");
	scoreTxt.setString("0");

	txt.setCharacterSize(80);
	scoreTxt.setCharacterSize(100);

	txt.setFillColor(Color::White);
	scoreTxt.setFillColor(Color::White);

	FloatRect textRect = txt.getLocalBounds();
	RectangleShape background;
	background.setFillColor(Color(37,52,47));

	txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	txt.setPosition(1920 / 2.0f, 1000);

	scoreTxt.setPosition(20, 20);

	// branches
	Texture textureBranches;
	textureBranches.loadFromFile("graphics/branch.png");

	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranches);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	// player
	Texture playerTexture;
	playerTexture.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(playerTexture);
	spritePlayer.setPosition(580, 600);
	spritePlayer.setScale(1.3f, 1.3f);
	side playerSide = side::LEFT;

	// player dead
	Texture deadTexture;
	deadTexture.loadFromFile("graphics/rip.png");
	Sprite spriteDead;
	spriteDead.setTexture(deadTexture);
	spriteDead.setPosition(600, 870);

	// player axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(730, 790);

	const float AXE_LEFT = 730;
	const float AXE_RIGHT = 1075;

	// log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	bool acceptInput = false;

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/hit.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/lose.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/time.wav");
	Sound oot;
	oot.setBuffer(ootBuffer);



	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !pause)
			{
				acceptInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			pause = false;
			score = 0;
			timeRemain = 6;

			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPos[i] = side::NONE;
			}

			spriteDead.setPosition(675, 2000);
			//spritePlayer.setPosition(580, 720);

			acceptInput = true;
		}

		if (acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				playerSide = side::RIGHT;
				score++;
				timeRemain += (2 / score) + .15;
				spriteAxe.setPosition(AXE_RIGHT, spriteAxe.getPosition().y);

				spritePlayer.setPosition(1100, 600);
				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				playerSide = side::LEFT;
				score++;
				timeRemain += (2 / score) + .15;
				spriteAxe.setPosition(AXE_LEFT, spriteAxe.getPosition().y);

				spritePlayer.setPosition(580, 600);
				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}
		}



		window.clear();
		window.draw(spriteBackground);
		
		for (int i = 0; i < 3; i++)
		{
			window.draw(clouds[i]);
		}

		window.draw(spriteTree);

		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}

		window.draw(spritePlayer);
		window.draw(spriteLog);
		window.draw(spriteAxe);
		
		window.draw(spriteDead);

		window.draw(spriteAnt);

		window.draw(scoreTxt);

		window.draw(timeBar);

		if (pause)
		{
			background.setSize(Vector2f(txt.getLocalBounds().width + 20, txt.getLocalBounds().height + 50));
			window.draw(background, txt.getTransform());
			window.draw(txt);
		}


		if (!pause)
		{
			Time dt = clock.restart();

			timeRemain -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarShrink * timeRemain, timeBarH));

			
			if (timeRemain <= 0.0f)
			{
				pause = true;
				txt.setString("Game Over!!");
				FloatRect textRect = txt.getLocalBounds();

				txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				txt.setPosition(1920 / 2.0f, 1000);

				oot.play();

			}
			


			// ant movement
			if (!antMove)
			{
				srand((int)time(0));
				antSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() & 500) + 500;
				spriteAnt.setPosition(2000, height);
				antMove = true;
			}
			else
			{
				spriteAnt.setPosition(spriteAnt.getPosition().x - (antSpeed * dt.asSeconds()), spriteAnt.getPosition().y);

				if (spriteAnt.getPosition().x < -100)
				{
					antMove = false;
				}
			}

			// cloud movement
			if (!cloudMove)
			{
				srand((int)time(0));
			
				for (int i = 0; i < 3; i++)
				{
					srand((int)time(0) * 10 * i);
					cloudSpeed[i] = (rand() % 100);
					clouds[i].setPosition(-300, clouds[i].getPosition().y);
				}
				
				cloudMove = true;
			}
			else
			{
				int counter = 0;
				for (int i = 0; i < 3; i++)
				{
					clouds[i].setPosition(clouds[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()), clouds[i].getPosition().y);
					if (clouds[i].getPosition().x > 1920)
						counter++;
				}
				
				if (counter == 3)
					cloudMove = false;
			}

			// update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreTxt.setString(ss.str());

			// set branch
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 120;
				if (branchPos[i] == side::LEFT)
				{
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPos[i] == side::RIGHT)
				{
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else
				{
					branches[i].setPosition(3000, height);
				}
			}

			if (logActive)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			if (branchPos[5] == playerSide)
			{
				pause = true;
				acceptInput = false;

				spriteDead.setPosition(spritePlayer.getPosition().x, 760);
				spritePlayer.setPosition(2000, 660);
				txt.setString("YOU DIED");

				death.play();

			}
		}

		
		
		
		window.display();

	}
	return 0;
}

void updateBranches(int seed)
{
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPos[j] = branchPos[j - 1];
	}

	srand((int)time(0) + seed);
	int r = (rand() % 5);

	// set random position for first branch
	switch (r)
	{
	case 0:
		branchPos[0] = side::LEFT;
		break;
	case 1:
		branchPos[0] = side::RIGHT;
		break;
	default:
		branchPos[0] = side::NONE;
		break;
	}
}