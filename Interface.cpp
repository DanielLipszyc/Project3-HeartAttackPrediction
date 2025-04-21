#include <string>
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "RadixSort.h"
#include "MergeSort.h"
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;

void InterfaceUI::ExtractBMIsFromFile() {
    this->patients.clear();
    ifstream file("../heart_attack_dataset.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file 'ONE'." << endl;
        return;
    }
    string line;
    getline(file, line); // skip header
    int count = 0;
    while (getline(file, line)) {
        size_t start = 0;
        size_t end = 0;
        int index = 0;
        float bmi = 0;
        int stressLevel = 0;
        int outcome = 0;
        string token;

        while (end != string::npos && index <= 31) {
            end = line.find(',', start);
            token = line.substr(start, end - start);

            if (index == 5) {
                bmi = stof(token);
            }

            else if(index == 13){
                stressLevel = stoi(token);
            }

            else if (index == 31) {
                outcome = (token == "Heart Attack") ? 1 : 0;
                break;
            }

            start = end + 1;
            ++index;
        }

        Patient* P = new Patient(bmi, outcome, stressLevel);
        patients.push_back(P);

        ++index;
        count++;
    }
    file.close();
}


double InterfaceUI::GetAverageScore(int filter) {
    int targetBMI = filter;
    int positive = 0;
    int total = 0;
    vector<Patient*> BMI_Group = {};
    for(int i = 0; i < this->patients.size(); i++){
        if(this->patients[i]->BMI < targetBMI){
            i++;
        }
        else if(this->patients[i]->BMI == targetBMI){
            BMI_Group.push_back(this->patients[i]);
            i++;
        }
        else{
            break;
        }
    }

    for(Patient* P : BMI_Group){
        if(P->HAO == 1){
            positive++;
        }
        total++;
    }

    double average = (positive*1.0) / total;
    return average * 100;
}

pair<string, string> InterfaceUI::MergeSortMethod( int filterValue) {
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(this->patients, 0, this->patients.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double result = GetAverageScore(filterValue);
    stringstream ss;
    ss << fixed << setprecision(2) << result;
    string resultStr = ss.str();
    return make_pair(resultStr + "%", to_string(duration.count()) + " microseconds.");
}

pair<string, string> InterfaceUI::RadixSortMethod( int filterValue) {
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(this->patients);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double result = GetAverageScore(filterValue);
    stringstream ss;
    ss << fixed << setprecision(2) << result;
    string resultStr = ss.str();
    return make_pair(resultStr + "%", to_string(duration.count()) + " microseconds.");
}


void InterfaceUI::SFMLInterface() {

    string fontPath = "../resources/Fonts/arial.ttf";

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 500}), "DIM Team - Sort Algorithms", sf::Style::Titlebar | sf::Style::Close);
    //Set main banner
    sf::Font fontTitle;
    fontTitle.loadFromFile(fontPath);
    sf::Text textTitle; // a font is required to make a text object
    textTitle.setFont(fontTitle);
    textTitle.setString("Merge Sort vs Radix Sort");
    textTitle.setCharacterSize(36); // in pixels, not points!
    textTitle.setFillColor(sf::Color::Blue);
    textTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textTitle.setPosition((window.getSize().x / 2)- 220, 50);


    //Enter Value Label
    sf::Font fontLabel;
    fontLabel.loadFromFile(fontPath);
    sf::Text textLabel; // a font is required to make a text object
    textLabel.setFont(fontLabel);
    textLabel.setString("Enter Value Between 18 to 40: ");
    textLabel.setCharacterSize(20); // in pixels, not points!
    textLabel.setFillColor(sf::Color::Blue);
    textLabel.setStyle(sf::Text::Bold);
    textLabel.setPosition(150, 150);

    //Enter Value Text
    sf::Font fontInput;
    fontInput.loadFromFile(fontPath);
    sf::Text textInput; // a font is required to make a text object
    textInput.setFont(fontInput);
    textInput.setString("00");
    textInput.setCharacterSize(20); // in pixels, not points!
    textInput.setFillColor(sf::Color::Blue);
    textInput.setPosition(470, 150);

    //Result Label Average
    sf::Font fontResultLabel;
    fontResultLabel.loadFromFile(fontPath);
    sf::Text textResultLabel; // a font is required to make a text object
    textResultLabel.setFont(fontResultLabel);
    textResultLabel.setString("Your chances of a heart attack is: ");
    textResultLabel.setCharacterSize(20); // in pixels, not points!
    textResultLabel.setFillColor(sf::Color::Black);
    textResultLabel.setStyle(sf::Text::Bold);
    textResultLabel.setPosition(100, 370);

    //Result Value Average
    sf::Font fontResultValue;
    fontResultValue.loadFromFile(fontPath);
    sf::Text textResultValue; // a font is required to make a text object
    textResultValue.setFont(fontResultValue);
    textResultValue.setCharacterSize(20); // in pixels, not points!
    textResultValue.setFillColor(sf::Color::Black);
    textResultValue.setStyle(sf::Text::Bold);
    textResultValue.setPosition(450, 370);

    //Result Label Sort Elapsed Time
    sf::Font fontElapsedTimeLabel;
    fontElapsedTimeLabel.loadFromFile(fontPath);
    sf::Text textElapsedTimeLabel; // a font is required to make a text object
    textElapsedTimeLabel.setFont(fontElapsedTimeLabel);
    textElapsedTimeLabel.setString("Sort - Elapsed Time : ");
    textElapsedTimeLabel.setCharacterSize(20); // in pixels, not points!
    textElapsedTimeLabel.setFillColor(sf::Color::Black);
    textElapsedTimeLabel.setStyle(sf::Text::Bold);
    textElapsedTimeLabel.setPosition(100, 420);

    //Result Value Average
    sf::Font fontElapsedTimeValue;
    fontElapsedTimeValue.loadFromFile(fontPath);
    sf::Text textElapsedTimeValue; // a font is required to make a text object
    textElapsedTimeValue.setFont(fontElapsedTimeValue);
    textElapsedTimeValue.setCharacterSize(20); // in pixels, not points!
    textElapsedTimeValue.setFillColor(sf::Color::Black);
    textElapsedTimeValue.setStyle(sf::Text::Bold);
    textElapsedTimeValue.setPosition(350, 420);

    //Radix Button
    sf::Texture radixTexture;
    radixTexture.loadFromFile("../resources/images/btnradixsort.png");
    sf::Sprite radixSprite(radixTexture);
    radixSprite.setPosition(sf::Vector2f(100,250));

    //Merge Button
    sf::Texture mergeTexture;
    mergeTexture.loadFromFile("../resources/images/btnmergesort.png");
    sf::Sprite mergeSprite(mergeTexture);
    mergeSprite.setPosition(sf::Vector2f(468,250));

    //Warning
    sf::Font fontWarningLabel;
    fontWarningLabel.loadFromFile(fontPath);
    sf::Text textWarningLabel; // a font is required to make a text object
    textWarningLabel.setFont(fontWarningLabel);
    textWarningLabel.setString("* The number entered is not valid!!");
    textWarningLabel.setCharacterSize(15); // in pixels, not points!
    textWarningLabel.setFillColor(sf::Color::Red);
    textWarningLabel.setStyle(sf::Text::Italic);
    textWarningLabel.setPosition(150, 175);

    //Warning
    sf::Font fontTeamLabel;
    fontTeamLabel.loadFromFile(fontPath);
    sf::Text textTeamLabel; // a font is required to make a text object
    textTeamLabel.setFont(fontTeamLabel);
    textTeamLabel.setString("D(aniel) I(vana) M(arian) Team");
    textTeamLabel.setCharacterSize(15); // in pixels, not points!
    textTeamLabel.setFillColor(sf::Color::Black);
    textTeamLabel.setStyle(sf::Text::Bold);
    textTeamLabel.setPosition(530, 480);

    string input_text = "";
    pair<string, string> output_text;

    sf::Clock clock;

    bool validNumber = true;

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
                        && (mousePos.y >= 250 ) && (mousePos.y <= 332 )) {
                            if (stoi(input_text) >=18 && stoi(input_text) <=40) {
                                output_text =RadixSortMethod(stoi(input_text));
                                textResultValue.setString(output_text.first);
                                textElapsedTimeValue.setString(output_text.second);
                                ExtractBMIsFromFile();
                            } else { validNumber = false; }
                        }
                    if ((mousePos.x >= 468 ) && (mousePos.x <= 700 )
                        && (mousePos.y >= 250 ) && (mousePos.y <= 332 )) {
                            if (stoi(input_text) >=18 && stoi(input_text) <=40) {
                                output_text =MergeSortMethod(stoi(input_text));
                                textResultValue.setString(output_text.first);
                                textElapsedTimeValue.setString(output_text.second);
                                ExtractBMIsFromFile();
                            } else { validNumber = false; }
                        }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode > 47 && event.text.unicode < 58) {
                    validNumber = true;
                    if (std::isprint(event.text.unicode))
                        input_text += event.text.unicode;
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    validNumber = true;
                    if (!input_text.empty())
                        input_text.pop_back();
                }
                //if (event.key.code == sf::Keyboard::Return) {
                //    input_text += '\n';
                //}
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
        if (!validNumber) {
            window.draw(textWarningLabel);
            radixTexture.loadFromFile("../resources/images/disbtnradixsort.png");
            mergeTexture.loadFromFile("../resources/images/disbtnmergesort.png");
        }
        else {
            radixTexture.loadFromFile("../resources/images/btnradixsort.png");
            mergeTexture.loadFromFile("../resources/images/btnmergesort.png");
        }
        window.draw(textTitle);
        window.draw(textLabel);
        window.draw(textInput);
        window.draw(radixSprite);
        window.draw(mergeSprite);
        window.draw(textResultLabel);
        window.draw(textResultValue);
        window.draw(textElapsedTimeLabel);
        window.draw(textElapsedTimeValue);
        window.draw(textTeamLabel);

        window.display();
    }
}