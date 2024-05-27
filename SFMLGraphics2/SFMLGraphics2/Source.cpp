#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

using namespace sf;


int main() {
    RenderWindow window(VideoMode(800, 600), L"Танчики");

    Texture playerTexture;
    if (!playerTexture.loadFromFile("player.png")) {
        return EXIT_FAILURE;
    }
    Texture wallTexture;
    if (!wallTexture.loadFromFile("brick_wall.png")) {
        return EXIT_FAILURE;
    }
    
    

    Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(2.f, 2.f);
    playerSprite.setPosition(400.f, 300.f);
    
    float playerSpeed = 0.05f;
    

    RectangleShape wall1(Vector2f(120, 100));
    wall1.setTexture(&wallTexture);
    wall1.setPosition(400, 200);

    RectangleShape wall2(Vector2f(20, 100));
    wall2.setTexture(&wallTexture);
    wall2.setPosition(400, 400);

    RectangleShape wall3(Vector2f(20, 100));
    wall3.setTexture(&wallTexture);
    wall3.setPosition(200, 200);
 
    RectangleShape wall4(Vector2f(120, 20));
    wall4.setTexture(&wallTexture);
    wall4.setPosition(200, 400);
    RectangleShape wall5(Vector2f(800, 30));
    wall5.setTexture(&wallTexture);
    wall5.setPosition(0, 0);
    RectangleShape wall6(Vector2f(800, 30));
    wall6.setTexture(&wallTexture);
    wall6.setPosition(0, 570);

    SoundBuffer moveBuffer;
    if (!moveBuffer.loadFromFile("tracks.ogg")) {
        return EXIT_FAILURE;
    }
    Sound moveSound;
    moveSound.setBuffer(moveBuffer);
    moveSound.setVolume(40);
    moveSound.setLoop(true);
    SoundBuffer loopBuffer;
    if (!loopBuffer.loadFromFile("engine.ogg")) {
        return EXIT_FAILURE;
    }
    Sound loopSound;
    loopSound.setBuffer(loopBuffer);
    loopSound.setLoop(true);
    loopSound.setVolume(80);

    bool isMooving = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                isMooving = true;
                moveSound.play();
            }
            else if (event.type == Event::KeyReleased) {
                moveSound.stop();
            }
        }
        if (!isMooving && !loopSound.getStatus() == Sound::Playing) {
            loopSound.play();
        }
        Vector2f prevPosition = playerSprite.getPosition();
        float angle = 0.0f;
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            playerSprite.move(-playerSpeed, 0.f);
            angle = 0.0f;
            
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            playerSprite.move(playerSpeed, 0.f);
            angle = 180.0f;
            
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            playerSprite.move( 0.f ,-playerSpeed);
            angle = 90.0f;
            
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            playerSprite.move(0.f ,playerSpeed);
            angle = -90.0f;
            
        }
        if (playerSprite.getGlobalBounds().intersects(wall1.getGlobalBounds())||
            playerSprite.getGlobalBounds().intersects(wall2.getGlobalBounds()) ||
            playerSprite.getGlobalBounds().intersects(wall3.getGlobalBounds()) ||
            playerSprite.getGlobalBounds().intersects(wall4.getGlobalBounds())){
            playerSprite.setPosition(prevPosition);
        }
        playerSprite.setRotation(angle);

        window.clear();
        
        window.draw(playerSprite);
        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);
        window.draw(wall4);
        window.draw(wall5);
        window.draw(wall6);
        
        window.display();
       
    }
    
    return 0;


        
    }

    
