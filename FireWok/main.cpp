#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Engine.hpp>

using namespace sf;

class AECEWrapper {
    std::map<std::string, std::unique_ptr<sf::Music>> _songs;
    std::unique_ptr<AECE::Engine> _engine;
public:
    AECEWrapper() {
        std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
        music->openFromFile("Songs/Alan_Walker_Fade.ogg");

        auto song = AECE::SongWithAef("Songs/Alan_Walker_Fade.ogg", "Songs/Alan_Walker_Fade.aef", "Fade",
                                      music->getDuration().asMicroseconds());
        std::vector<AECE::SongWithAef> songsWithAef;
        songsWithAef.push_back(song);

        _songs["Fade"] = std::move(music);
        _engine = std::make_unique<AECE::Engine>(songsWithAef,
                                                 [=](std::string song) { _songs[song]->play(); },
                                                 [=](std::string song) { return _songs[song]->getPlayingOffset().asMicroseconds(); }
        );
    }

    void Play(std::string song) {
        _engine->StartPlaying(song);
    }

    std::vector<AECE::AudioEvent> QueryEvents() {
        return _engine->QueryEvents();
    }
};

int main()
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    AECEWrapper engine;

    engine.Play("Fade");

    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        Event event;
        if (shape.getFillColor() == Color::Red)
            shape.setFillColor(Color::Green);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::EventType::KeyPressed){
                if (event.key.code == sf::Keyboard::Key::Up)
                    shape.setFillColor(Color::Red);
            }
        }

        for (auto &event : engine.QueryEvents()) {

            shape.setFillColor(Color::Red);
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}