#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

void setspeed(float &xspeed, float &yspeed) // Assigns random values to speed
{
    xspeed = (rand() % 300 + 1) /100 + 0.50;
    yspeed = (rand() % 300 + 1) /100 + 0.50;
}

void resetbirdpositions(sf::RectangleShape bird[10])
{
    bird[0].setPosition(3200, 500);
    bird[1].setPosition(1200, 350);
    bird[2].setPosition(1400, 250);
    bird[3].setPosition(1600, 450);
    bird[4].setPosition(2000, 300);
    bird[5].setPosition(2400, 600);
    bird[6].setPosition(2600, 400);
    bird[7].setPosition(2800, 200);
    bird[8].setPosition(3000, 550);
    bird[9].setPosition(2500, 150);
}

int flowerpos() // returns which location the flowers will be in
{
    int decision = (rand() % 3) + 1;
    return (decision * 120);

}

void flowerreset(sf::RectangleShape flower[3], sf::Clock &flowertimer, bool finished, sf::Sound flowerscoming)
{
    int yflower; // flower y spawn location from function
    if (flowertimer.getElapsedTime().asSeconds() > 10.0f || finished){
        yflower = flowerpos();
        for (int i = 0; i < 3; i++){
            flower[i].setPosition(852 * 1.5 + (i * 100), yflower); // Prevents flowers from spawning over the edge of the screen
            flowerscoming.play();
        }
        flowertimer.restart();
    }
    std::cout << flowertimer.getElapsedTime().asSeconds() << std:: endl;
}


int main()
{

    // Clocks (animation and main stopwatch)
    sf::Clock butterflyanimation;
    sf::Clock birdanimation[10];
    sf::Clock stopwatch;
    sf::Clock flowertimer;

    // Variables
    float mouseXPos;
    float mouseYPos;
    int framebutterfly = 0; //Butterfly animation tracker
    int framebird[10];
    int points = 0;
    int addtopoints = 0; // Added from flowers (100 each)
    int highestscore = 0;

    float xspeed = 1.0;
    float yspeed = 1.0;
    float movingXSpeed, movingYSpeed;
    int controller = 0; // Gamestate controller. (Turns values to 0, their own value, or multiplies it)
    bool nomusic = true; //Music plays once
    bool onetime = true; //Allows for code to run once when player loses (finished = true)


    //Gamestate
    bool welcomepage = true; // Intro screen
    bool tutorial = false;
    bool gaming = false;
    bool finished = false;


    // Create the main window
    sf::RenderWindow app(sf::VideoMode(1152, 648), "Fly Away!"); //(1920*0.6, 1080*0.6)
    app.setFramerateLimit(300); // Reduces the amount of speed changes

// Creation of objects, shapes and more

    // Background
    sf::Texture backgroundtexture1;
    backgroundtexture1.loadFromFile("background1.png");
    sf::RectangleShape background1(sf::Vector2f(1152, 648));
    background1.setTexture(&backgroundtexture1);


    sf::Texture backgroundtexture2;
    backgroundtexture2.loadFromFile("background2.png");
    sf::RectangleShape background2(sf::Vector2f(1152, 648));
    background2.setTexture(&backgroundtexture2);
    background2.setPosition(1152, 0);


    // Butterfly
    sf::RectangleShape butterfly(sf::Vector2f(75, 75));
    butterfly.setOrigin(75/2, 75/2);
    butterfly.setPosition(1152/2, 648/2);

    // Butterfly animation creation
    sf::Texture butterflytexture1;
    butterflytexture1.loadFromFile("butterfly1.png");
    sf::Texture butterflytexture2;
    butterflytexture2.loadFromFile("butterfly2.png");
    sf::Texture butterflytexture3;
    butterflytexture3.loadFromFile("butterfly3.png");
    sf::Texture butterflytexture4;
    butterflytexture4.loadFromFile("butterfly4.png");
    sf::Texture butterflytexture5;
    butterflytexture5.loadFromFile("butterfly5.png");
    sf::Texture butterflytexture6;
    butterflytexture6.loadFromFile("butterfly6.png");
    sf::Texture butterflytexture7;
    butterflytexture7.loadFromFile("butterfly7.png");
    sf::Texture butterflytexture8;
    butterflytexture8.loadFromFile("butterfly8.png");
    sf::Texture butterflytexture9;
    butterflytexture9.loadFromFile("butterfly9.png");
    sf::Texture butterflytexture10;
    butterflytexture10.loadFromFile("butterfly10.png");

    butterfly.setTexture(&butterflytexture1);


    // Bird
    sf::RectangleShape bird[10];

    // Bird animation creation
    sf::Texture birdtexture1;
    birdtexture1.loadFromFile("bird1.png");
    sf::Texture birdtexture2;
    birdtexture2.loadFromFile("bird2.png");
    sf::Texture birdtexture3;
    birdtexture3.loadFromFile("bird3.png");
    sf::Texture birdtexture4;
    birdtexture4.loadFromFile("bird4.png");
    sf::Texture birdtexture5;
    birdtexture5.loadFromFile("bird5.png");
    sf::Texture birdtexture6;
    birdtexture6.loadFromFile("bird6.png");
    sf::Texture birdtexture7;
    birdtexture7.loadFromFile("bird7.png");
    sf::Texture birdtexture8;
    birdtexture8.loadFromFile("bird8.png");
    sf::Texture birdtexture9;
    birdtexture9.loadFromFile("bird9.png");
    sf::Texture birdtexture10;
    birdtexture10.loadFromFile("bird10.png");



    for (int i = 0; i < 10; i++){
        bird[i].setSize(sf::Vector2f(50, 50));
        bird[i].setOrigin(50/2, 50/2);
        bird[i].setTexture(&birdtexture1);
        framebird[i] = i; // Bird animation frames
    }


    // Flowers
    sf::RectangleShape flower[3];
    sf::Texture flowertexture;
    flowertexture.loadFromFile("Flower.png");

    for (int i = 0; i < 3; i++){
        flower[i].setSize(sf::Vector2f(50, 50));
        flower[i].setOrigin(50/2, 50/2);
        flower[i].setTexture(&flowertexture);
    }



    // Loading Font
    sf::Font mogena;
    mogena.loadFromFile("mogena.ttf");

    // Welcome Screen
    sf::RectangleShape startbutton;
    startbutton.setSize(sf::Vector2f(210, 40));
    startbutton.setPosition(470, 400);
    startbutton.setFillColor(sf::Color::Blue);
    startbutton.setOutlineColor(sf::Color::White);
    startbutton.setOutlineThickness(1);


    // Welcome to Fly Away Text
    sf::Text Welcome;
    Welcome.setFont(mogena);
    Welcome.setCharacterSize(36);
    Welcome.setPosition(400, 350);
    Welcome.setString("Welcome to Fly Away");

    // Press to Start Text
    sf::Text PtS;
    PtS.setFont(mogena);
    PtS.setCharacterSize(28);
    PtS.setPosition(480, 400);
    PtS.setString("Press to Start");


    //A Bird Got You Text
    sf::Text youlost;
    youlost.setFont(mogena);
    youlost.setCharacterSize(28);
    youlost.setPosition(425, 350);
    youlost.setString("Oh no,  a Bird Got You");


    //Tutorial items

    sf::RectangleShape tutorialbg(sf::Vector2f(350, 500)); //Background for tutorial text
    tutorialbg.setOrigin(350/2, 500/2);
    tutorialbg.setPosition(1152/2, 648/2);
    tutorialbg.setFillColor(sf::Color::Blue);
    tutorialbg.setOutlineColor(sf::Color::White);
    tutorialbg.setOutlineThickness(1);

    sf::Text tutorialtext1;
    tutorialtext1.setFont(mogena);
    tutorialtext1.setCharacterSize(32);
    tutorialtext1.setPosition(410, 100);
    tutorialtext1.setString("Welcome to Fly Away");

    sf::Text tutorialtext2;
    tutorialtext2.setFont(mogena);
    tutorialtext2.setCharacterSize(20);
    tutorialtext2.setPosition(410, 150);
    tutorialtext2.setString("  Your objective is to get as many \n  points as possible, by surviving \n  collecting as many flowers as \n\t\t\t\t  possible");

    sf::Text tutorialtext3;
    tutorialtext3.setFont(mogena);
    tutorialtext3.setCharacterSize(20);
    tutorialtext3.setPosition(410, 250);
    tutorialtext3.setString("You gain points by surviving and \n\t\t   collecting flowers");

    sf::Text tutorialtext4;
    tutorialtext4.setFont(mogena);
    tutorialtext4.setCharacterSize(20);
    tutorialtext4.setPosition(425, 300);
    tutorialtext4.setString("However, beware of your speed\n  Every time you stop,  start or \n change direction,  your speed \n\t\t\t\tchanges");

    sf::Text tutorialtext5;
    tutorialtext5.setFont(mogena);
    tutorialtext5.setCharacterSize(20);
    tutorialtext5.setPosition(425, 400);
    tutorialtext5.setString("Use the arrow keys to move up,  \n\t   down,  left,  and right");

    sf::Text tutorialtext6;
    tutorialtext6.setFont(mogena);
    tutorialtext6.setCharacterSize(20);
    tutorialtext6.setPosition(425, 450);
    tutorialtext6.setString("   Now go save the butterfly, \n\t\t\tand have fun");

    sf::RectangleShape tutorialbutton; //Click to open tutorial
    tutorialbutton.setSize(sf::Vector2f(210, 40));
    tutorialbutton.setPosition(470, 450);
    tutorialbutton.setFillColor(sf::Color::Blue);
    tutorialbutton.setOutlineColor(sf::Color::White);
    tutorialbutton.setOutlineThickness(1);

    sf::Text tutorialbuttontext;
    tutorialbuttontext.setFont(mogena);
    tutorialbuttontext.setCharacterSize(28);
    tutorialbuttontext.setPosition(520, 450);
    tutorialbuttontext.setString("Tutorial");

    sf::Texture XTexture;
    XTexture.loadFromFile("X.png");
    sf::RectangleShape XButton (sf::Vector2f(20, 20));
    XButton.setTexture(&XTexture);
    XButton.setPosition(405, 78);


    // Score and Highscore

    // Score
    sf::Text score;
    score.setFont(mogena);
    score.setCharacterSize(48);
    score.setPosition(550, 10);
    score.setString(std::to_string(points));
    score.setFillColor(sf::Color::Black);

    // Score bottom
    sf::Text scorebot;
    scorebot.setFont(mogena);
    scorebot.setCharacterSize(48);
    scorebot.setPosition(650, 435);
    scorebot.setString(std::to_string(points));
    scorebot.setFillColor(sf::Color::White);

    // Score (words)
    sf::Text scoreText;
    scoreText.setFont(mogena);
    scoreText.setString("Score");
    scoreText.setCharacterSize(28);
    scoreText.setPosition(475, 450);
    scoreText.setColor(sf::Color::Black);

    // Highscore
    sf::Text highscore;
    highscore.setFont(mogena);
    highscore.setCharacterSize(48);
    highscore.setPosition(650, 485);
    highscore.setColor(sf::Color::White);
    highscore.setString(std::to_string(highestscore));

    // Highscore (words)
    sf::Text highscoreText;
    highscoreText.setFont(mogena);
    highscoreText.setString("Highscore");
    highscoreText.setCharacterSize(28);
    highscoreText.setPosition(475, 500);
    highscoreText.setColor(sf::Color::Black);


    // MUSIC and AUDIO

    sf::SoundBuffer bgmusicloading;
    bgmusicloading.loadFromFile("bgmusic.wav");
    sf::Sound bgmusic;
    bgmusic.setBuffer(bgmusicloading);

    sf::SoundBuffer flowercollectedLoading;
    flowercollectedLoading.loadFromFile("flowercollected.wav");
    sf::Sound flowercollectedSound;
    flowercollectedSound.setBuffer(flowercollectedLoading);

    sf::SoundBuffer flowerscomingLoading;
    flowerscomingLoading.loadFromFile("flowerscoming.wav");
    sf::Sound flowerscomingSound;
    flowerscomingSound.setBuffer(flowerscomingLoading);


	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //  ====================================================== Start of game loop ======================================================

        // Adding flowers to the screen
        flowerreset(flower, flowertimer, finished, flowerscomingSound);

        //Mouse x y Positions
        mouseXPos = sf::Mouse::getPosition(app).x;
        mouseYPos = sf::Mouse::getPosition(app).y;

        //sf::Time elapsedtime = stopwatch.getElapsedTime().asSeconds();
        //std::cout << elapsed2.asSeconds() << std::endl;


        points = addtopoints + (stopwatch.getElapsedTime().asSeconds() * 2);
        score.setString(std::to_string(points));



        if (finished && onetime){
            scorebot.setString(std::to_string(points));
            onetime = false;

            if (points > highestscore) {
                highestscore = points;
                highscore.setString(std::to_string(highestscore));
            }
        }
        else if (gaming)
            onetime = true;

        if (nomusic) {//Prevents music from playing the first second over and over
            bgmusic.play();
            bgmusic.setLoop(true);
            nomusic = false;
        }


        // Animation
        if (butterflyanimation.getElapsedTime().asSeconds() > .1f) {
            framebutterfly ++;
            if (framebutterfly == 11) {
                framebutterfly = 1;
            }
            if (framebutterfly==1) {
                butterfly.setTexture(&butterflytexture1);
            } else if (framebutterfly==2) {
                butterfly.setTexture(&butterflytexture2);
            } else if (framebutterfly==3) {
                butterfly.setTexture(&butterflytexture3);
            } else if (framebutterfly==4) {
                butterfly.setTexture(&butterflytexture4);
            } else if (framebutterfly==5) {
                butterfly.setTexture(&butterflytexture5);
            } else if (framebutterfly==6) {
                butterfly.setTexture(&butterflytexture6);
            } else if (framebutterfly==7) {
                butterfly.setTexture(&butterflytexture7);
            } else if (framebutterfly==8) {
                butterfly.setTexture(&butterflytexture8);
            } else if (framebutterfly==9) {
                butterfly.setTexture(&butterflytexture9);
            } else if (framebutterfly==10) {
                butterfly.setTexture(&butterflytexture10);
            }
            butterflyanimation.restart();
        }

        // Bird Animation
        for (int i = 0; i < 10; i++){
            if (birdanimation[i].getElapsedTime().asSeconds()> 0.25f) {
                framebird[i]++;
                if (framebird[i] == 11) {
                    framebird[i] = 1;
                }
                if (framebird[i]==1) {
                    bird[i].setTexture(&birdtexture1);
                } else if (framebird[i]==2) {
                    bird[i].setTexture(&birdtexture2);
                } else if (framebird[i]==3) {
                    bird[i].setTexture(&birdtexture3);
                } else if (framebird[i]==4) {
                    bird[i].setTexture(&birdtexture4);
                } else if (framebird[i]==5) {
                    bird[i].setTexture(&birdtexture5);
                } else if (framebird[i]==6) {
                    bird[i].setTexture(&birdtexture6);
                } else if (framebird[i]==7) {
                    bird[i].setTexture(&birdtexture7);
                } else if (framebird[i]==8) {
                    bird[i].setTexture(&birdtexture8);
                } else if (framebird[i]==9) {
                    bird[i].setTexture(&birdtexture9);
                } else if (framebird[i]==10) {
                    bird[i].setTexture(&birdtexture10);
                }
                birdanimation[i].restart();
            }
        }



        //Press to start button
        if(welcomepage||finished){
            if(startbutton.getPosition().x <= mouseXPos && mouseXPos <= (startbutton.getPosition().x + startbutton.getGlobalBounds().width)) {
                if(startbutton.getPosition().y <= mouseYPos && mouseYPos <= (startbutton.getPosition().y + startbutton.getGlobalBounds().height)) {
                    startbutton.setOutlineThickness(3);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        welcomepage = false;
                        gaming = true;
                        finished = false;
                        controller = 1;
                        resetbirdpositions(bird);
                        stopwatch.restart();
                        addtopoints = 0;
                    }
                } else {
                    startbutton.setOutlineThickness(1);
                }
            } else {
                startbutton.setOutlineThickness(1);
            }

            // tutorial button
            if(tutorialbutton.getPosition().x <= mouseXPos && mouseXPos <= (tutorialbutton.getPosition().x + tutorialbutton.getGlobalBounds().width)&& welcomepage) {
                if(tutorialbutton.getPosition().y <= mouseYPos && mouseYPos <= (tutorialbutton.getPosition().y + tutorialbutton.getGlobalBounds().height)) {
                    tutorialbutton.setOutlineThickness(3);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        tutorial = true;
                        welcomepage = false;
                    }
                } else {
                    tutorialbutton.setOutlineThickness(1);
                }
            } else {
                tutorialbutton.setOutlineThickness(1);
            }

        }


        // MOVEMENT
        for (int i = 0; i < 3; i++){
            flower[i].move(-1*controller, 0);
            flower[i].rotate(1);
        }

        for (int i = 0; i < 10; i ++){
            bird[i].move(-2*controller, 0);

            // Collision Check
            if (butterfly.getGlobalBounds().intersects(bird[i].getGlobalBounds())){
            gaming = false;
            finished = true;
            }

            for (int j = 0; j < 10; j++){
                /*if (bird[i].getGlobalBounds().intersects(bird[j].getGlobalBounds())){
                    bird[j].setPosition(bird[j].getPosition().x - 100, bird[j].getPosition().y - 50);
                }*/

            // Prevents the birds from going under the screen
            if (bird[i].getPosition().y > 650){
                bird[i].setPosition(bird[i].getPosition().x, bird[i].getPosition().y-500);
                }
            }

            if (bird[i].getPosition().x < -100){
                bird[i].setPosition(2000, (rand() % 652) + 1);
            }
        }

        butterfly.move(movingXSpeed*controller, movingYSpeed*controller);
        background1.move(-1*controller, 0);
        background2.move(-1*controller, 0);


        // Butterfly Movement X
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            movingXSpeed = -xspeed;
            setspeed(xspeed, yspeed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            movingXSpeed = xspeed;
            setspeed(xspeed, yspeed);
        }
        else {
            movingXSpeed = 0;
        }

        // Butterfly Movement Y
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            movingYSpeed = -yspeed;
            setspeed(xspeed, yspeed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            movingYSpeed = yspeed;
            setspeed(xspeed, yspeed);
        }
        else {
            movingYSpeed = 0;
        }

        if (butterfly.getPosition().x >= 1152 - (75/2)){
            butterfly.setPosition(1152 - (75/2), butterfly.getPosition().y);
        } else if (butterfly.getPosition().x <= (75/2)){
            butterfly.setPosition((75/2), butterfly.getPosition().y);
        }

        if (butterfly.getPosition().y >= 648 - (75/2)){
            butterfly.setPosition(butterfly.getPosition().x, 648 - (75/2));
        } else if (butterfly.getPosition().y <= (75/2)){
            butterfly.setPosition(butterfly.getPosition().x, (75/2));
        }


        //Butterfly collide with flower
        for (int i = 0; i < 3; i++){
            if(butterfly.getGlobalBounds().intersects(flower[i].getGlobalBounds())){
                flowercollectedSound.play();
                flower[i].setPosition(-1000, 0);
                addtopoints += 10;
            }
        }


        // Continuous Background (moves one as soon as it's off the screen
        if (background1.getPosition().x < -1152){
            background1.setPosition(1151, 0);
        } else if (background2.getPosition().x < -1152){
            background2.setPosition(1151, 0);
        }


        if(finished){ // Lost the round/game
            controller = 0;
            butterfly.setPosition(1152/2, 648/2);
            for(int i = 3; i < 3; i++){
                flower[i].setPosition(-1000, 0);
            }
        }



        //Tutorial exit button
        if(XButton.getPosition().x <= mouseXPos && mouseXPos <= (XButton.getPosition().x + XButton.getGlobalBounds().width)) {
                if(XButton.getPosition().y <= mouseYPos && mouseYPos <= (XButton.getPosition().y + XButton.getGlobalBounds().height)) {
                    XButton.setOutlineThickness(3);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        tutorial = false;
                        welcomepage = true;
                    }
                } else {
                    XButton.setOutlineThickness(1);
                }
            } else {
                XButton.setOutlineThickness(1);
            }


        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(background1); // Regular
        app.draw(background2); // Flipped
        app.draw(butterfly);



        if(welcomepage){
            app.draw(startbutton);
            app.draw(Welcome);
            app.draw(PtS);
            app.draw(tutorialbutton);
            app.draw(tutorialbuttontext);
            //app.draw(Tutorial);
        }

        if(tutorial){
            app.draw(tutorialbg);
            app.draw(tutorialtext1);
            app.draw(tutorialtext2);
            app.draw(tutorialtext3);
            app.draw(tutorialtext4);
            app.draw(tutorialtext5);
            app.draw(tutorialtext6);
            app.draw(XButton);

        }

        if(gaming){
            for (int i = 0; i < 10; i++)
                app.draw(bird[i]);
            for (int i = 0; i < 3; i++)
                app.draw(flower[i]);

            app.draw(score);
        }

        if(finished){
            app.draw(youlost);
            app.draw(startbutton);
            app.draw(PtS);
            app.draw(scorebot);
            app.draw(scoreText);
            app.draw(highscore);
            app.draw(highscoreText);

        }

        // Update the window
        app.display();

    }
    return EXIT_SUCCESS;
}



//What, why, impact

/*
We used -------- to -----------
we integrated ------------ with ------------ to -------------
our project is hosted on --------- because ----------
We trained a machine learning model to -------------------. (it does with --% accuracy)


Include your how section in your live demo


Show off what you have, mention challenges, explain next steps
*/
