#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Interface.h"

using namespace std;

void InterfaceUI::SFMLInterface() {

    string fontPath = "../resources/Fonts/arial.ttf";

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 500}), "DIM Sort Algorithms", sf::Style::Titlebar | sf::Style::Close);
    //Set main banner
    sf::Font fontTitle;
    fontTitle.loadFromFile(fontPath);
    sf::Text textTitle; // a font is required to make a text object
    textTitle.setFont(fontTitle);
    textTitle.setString("Merge Sort vs Radix Sort");
    textTitle.setCharacterSize(30); // in pixels, not points!
    textTitle.setFillColor(sf::Color::Blue);
    textTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textTitle.setPosition((window.getSize().x / 2)- 190, 50);


    //Enter Value Label
    sf::Font fontLabel;
    fontLabel.loadFromFile(fontPath);
    sf::Text textLabel; // a font is required to make a text object
    textLabel.setFont(fontLabel);
    textLabel.setString("Enter Value: ");
    textLabel.setCharacterSize(20); // in pixels, not points!
    textLabel.setFillColor(sf::Color::Blue);
    textLabel.setStyle(sf::Text::Bold);
    textLabel.setPosition(150, 200);

    //Enter Value Text
    sf::Font fontInput;
    fontInput.loadFromFile(fontPath);
    sf::Text textInput; // a font is required to make a text object
    textInput.setFont(fontInput);
    textInput.setString("12");
    textInput.setCharacterSize(20); // in pixels, not points!
    textInput.setFillColor(sf::Color::Blue);
    textInput.setPosition(300, 200);

    //Result Label
    sf::Font fontResultLabel;
    fontResultLabel.loadFromFile(fontPath);
    sf::Text textResultLabel; // a font is required to make a text object
    textResultLabel.setFont(fontResultLabel);
    textResultLabel.setString("Result Value: ");
    textResultLabel.setCharacterSize(20); // in pixels, not points!
    textResultLabel.setFillColor(sf::Color::Black);
    textResultLabel.setStyle(sf::Text::Bold);
    textResultLabel.setPosition(100, 420);

    //Result Label
    sf::Font fontResultValue;
    fontResultValue.loadFromFile(fontPath);
    sf::Text textResultValue; // a font is required to make a text object
    textResultValue.setFont(fontResultValue);
    textResultValue.setCharacterSize(20); // in pixels, not points!
    textResultValue.setFillColor(sf::Color::Black);
    textResultValue.setStyle(sf::Text::Bold);
    textResultValue.setPosition(240, 420);


    //Radix Button
    sf::Texture radixTexture;
    radixTexture.loadFromFile("../resources/images/btnradixsort.png");
    sf::Sprite radixSprite(radixTexture);
    radixSprite.setPosition(sf::Vector2f(100,300));

    //Merge Button
    sf::Texture mergeTexture;
    mergeTexture.loadFromFile("../resources/images/btnmergesort.png");
    sf::Sprite mergeSprite(mergeTexture);
    mergeSprite.setPosition(sf::Vector2f(468,300));

    string input_text;
    string output_text;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if ((mousePos.x >= 100 ) && (mousePos.x <= 332 )
                        && (mousePos.y >= 300 ) && (mousePos.y <= 382 )) {
                        //output_text =RadixSort(stoi(input_text));
                        output_text = "using radix";
                        textResultValue.setString(output_text);
                        }
                    if ((mousePos.x >= 468 ) && (mousePos.x <= 700 )
                        && (mousePos.y >= 300 ) && (mousePos.y <= 382 )) {
                        //output_text =MergeSort(stoi(input_text));
                        output_text = "using merge " ;
                        textResultValue.setString(output_text);
                        }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (std::isprint(event.text.unicode))
                    input_text += event.text.unicode;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!input_text.empty())
                        input_text.pop_back();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    input_text += '\n';
                }
            }
        }

        static sf::Time text_effect_time;
        static bool show_cursor;

        text_effect_time += clock.restart();

        if (text_effect_time >= sf::seconds(0.5f))
        {
            show_cursor = !show_cursor;
            text_effect_time = sf::Time::Zero;
        }

        textInput.setString(input_text + (show_cursor ? '_' : ' '));

        // Clear screen
        window.clear();

        // Update the window
        window.clear(sf::Color::White);
        window.draw(textTitle);
        window.draw(textLabel);
        window.draw(textInput);
        window.draw(radixSprite);
        window.draw(mergeSprite);
        window.draw(textResultLabel);
        window.draw(textResultValue);
        window.display();
    }
}