
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "gol.h"
using namespace std;
using namespace sf;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GOL_SIZE 700
#define GRID_SIZE 20

struct CustomState
{
    string state;
};

int main()
{
    GOL game(GRID_SIZE, GRID_SIZE);
    game.randomize();
    RenderWindow window(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Game of Life Grid");
    tgui::Gui gui(window);
    CustomState state = {"start_screen"}; // Ensure this matches the variable used in the main loop
    float cellWidth = static_cast<float>(GOL_SIZE) / GRID_SIZE;
    float cellHeight = static_cast<float>(GOL_SIZE) / GRID_SIZE;

    SoundBuffer buffer("born.wav");
    Sound sound(buffer);
    static bool buttonsInitialized = false;

    // Create a start screen button
    if (state.state == "start_screen")
    {
        static tgui::Label::Ptr titleLabel;
        static tgui::Button::Ptr startButton;
        static tgui::Button::Ptr exitButton;

        if (!buttonsInitialized)
        {
            titleLabel = tgui::Label::create("Game of Life");
            titleLabel->setTextSize(30);
            titleLabel->setPosition({"35%", "20%"});
            titleLabel->getRenderer()->setTextColor(tgui::Color::White);
            titleLabel->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            gui.add(titleLabel);

            startButton = tgui::Button::create("Start Game");
            startButton->setSize({"20%", "10%"});
            startButton->setPosition({"40%", "35%"});
            startButton->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            startButton->onPress([&]()
                     {
                     state.state = "init"; // Ensure this matches the logic in the main loop
                     gui.remove(titleLabel);
                     gui.remove(startButton);
                     gui.remove(exitButton);
                     });
            gui.add(startButton);

            exitButton = tgui::Button::create("Exit");
            exitButton->setSize({"20%", "10%"});
            exitButton->setPosition({"40%", "50%"});
            exitButton->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            exitButton->onPress([&]()
                     {
                     window.close(); // Close the application
                     });
            gui.add(exitButton);

            buttonsInitialized = true;
        }
    }

    if(state.state != "start_screen")
    {
        buttonsInitialized = false; // Reset button initialization for the next state
    }

    // // Set up a theme for the button to ensure it is styled properly
    // auto theme = tgui::Theme::create("Black.txt"); // Ensure you have a valid theme file
    // startButton->setRenderer(theme->getRenderer("Button"));

    // Calculate the size of each cell

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            gui.handleEvent(*event); // Pass events to TGUI
        }

        window.clear();

        if (state.state == "start_screen")
        {
            gui.draw(); // Draw the start screen
        }
        else if (state.state == "init" || state.state == "start")
        {
            // Handle custom state changes
            if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            {
                if (state.state == "init")
                {
                    state.state = "start";
                }
            }

            // Draw the grid
            for (int row = 0; row < GRID_SIZE; ++row)
            {
                for (int col = 0; col < GRID_SIZE; ++col)
                {
                    RectangleShape cell(Vector2f(cellWidth, cellHeight));
                    cell.setPosition(Vector2f(col * cellWidth, row * cellHeight));

                    // Set cell color based on the state in the GOL game
                    if (game.isAlive(row, col))
                        cell.setFillColor(Color::Green);
                    else
                        cell.setFillColor(Color::White);

                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(Color::Black);

                    window.draw(cell);
                }
            }

            if (state.state == "init")
            {
                // Handle mouse clicks to toggle cell state
                static Clock clickClock;
                if (clickClock.getElapsedTime().asMilliseconds() > 500 && Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    int row = mousePos.y / (GOL_SIZE / GRID_SIZE);
                    int col = mousePos.x / (GOL_SIZE / GRID_SIZE);

                    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE)
                    {
                        game.toggleBlock(row, col);
                    }
                    clickClock.restart();
                }
            }

            if (state.state == "start")
            {
                static Clock updateClock;
                if (updateClock.getElapsedTime().asMilliseconds() >= 100)
                {
                    game.update(sound);
                    updateClock.restart();
                }
            }
        }

        window.display();
    }
}