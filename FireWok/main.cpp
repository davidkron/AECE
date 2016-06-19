#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    sf::Music music;
    if (!music.openFromFile("Songs/Alan_Walker_Fade.ogg"))
        return -1; // error
    music.play();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::EventType::KeyPressed){

                // Up and down to control volume
                if (event.key.code == sf::Keyboard::Key::Down)
                    music.setPitch(music.getPitch() + 0.1f);
                if (event.key.code == sf::Keyboard::Key::Up)
                    music.setPitch(music.getPitch() - 0.1f);


                // Left and right to control tracking position
                if (event.key.code == sf::Keyboard::Key::Right){
                    auto newPos = music.getPlayingOffset() + sf::seconds(5);
                    music.setPlayingOffset(sf::Time(newPos));
                }

                if (event.key.code == sf::Keyboard::Key::Left){
                    auto newPos = music.getPlayingOffset() - sf::seconds(5);
                    if (newPos.asSeconds() <= 0.0f) newPos = sf::seconds(0);
                    music.setPlayingOffset(sf::Time(newPos));
                }

                std::cout << "Current volume is :" << music.getVolume() << " position is: "
                << music.getPlayingOffset().asSeconds() << std::endl;
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}