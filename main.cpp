
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "gol.h"
using namespace std;
using namespace sf;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 900
#define GOL_SIZE 800
#define GRID_SIZE 20
#define DEMO_SIZE 50

struct CustomState
{
    string state; // "init" , "start" , "start_screen"
    string mode;  // "levels", "randomize", "Creative"
};

int main()
{
    GOL game(GRID_SIZE, GRID_SIZE);
    GOL startscreendemo(DEMO_SIZE, DEMO_SIZE);
    float ScellWidth = static_cast<float>(WINDOW_WIDTH) / DEMO_SIZE;
    float ScellHeight = static_cast<float>(WINDOW_HEIGHT) / DEMO_SIZE;
    RenderWindow window(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Game of Life Grid");
    tgui::Gui gui(window);
    CustomState state = {
        "start_screen", // Initial state is the start screen
        ""              // Initial mode is levels
    }; // Ensure this matches the variable used in the main loop
    float cellWidth = static_cast<float>(GOL_SIZE) / GRID_SIZE;
    float cellHeight = static_cast<float>(GOL_SIZE) / GRID_SIZE;
    int level = 1;
    int st = true;
    int random = true;

    SoundBuffer buffer("born.wav");
    Sound sound(buffer);

    static bool buttonsInitialized = false;
    // Create a start screen button
    if (state.state == "start_screen")
    {
        static tgui::Label::Ptr titleLabel;
        static tgui::Button::Ptr startButton;
        static tgui::Button::Ptr randomizeButton;
        static tgui::Button::Ptr creativeButton;
        static tgui::Button::Ptr exitButton;

        if (!buttonsInitialized)
        {
            titleLabel = tgui::Label::create("Game of Life");
            titleLabel->setTextSize(40);
            titleLabel->setPosition({"29%", "20%"});
            titleLabel->getRenderer()->setTextColor(tgui::Color::White);
            titleLabel->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            gui.add(titleLabel);

            startButton = tgui::Button::create("Levels");
            startButton->setSize({"20%", "5%"});
            startButton->setPosition({"40%", "38%"});
            startButton->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            startButton->onPress([&]()
                                 {
                            state.state = "init"; 
                            state.mode =  "levels"; // Set the mode to levels
                            gui.remove(titleLabel);
                            gui.remove(startButton);
                            gui.remove(randomizeButton);
                            gui.remove(creativeButton);
                            gui.remove(exitButton); });
            gui.add(startButton);

            randomizeButton = tgui::Button::create("Randomize Mode");
            randomizeButton->setSize({"20%", "5%"});
            randomizeButton->setPosition({"40%", "45%"});
            randomizeButton->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            randomizeButton->onPress([&]()
                                     {
                            game.randomize(); // Call a function to randomize the grid
                            state.state = "init";
                            state.mode = "randomize"; // Set the mode to randomize
                            gui.remove(titleLabel);
                            gui.remove(startButton);
                            gui.remove(randomizeButton);
                            gui.remove(creativeButton);
                            gui.remove(exitButton); });
            gui.add(randomizeButton);

            creativeButton = tgui::Button::create("Creative Mode");
            creativeButton->setSize({"20%", "5%"});
            creativeButton->setPosition({"40%", "52%"});
            creativeButton->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            creativeButton->onPress([&]()
                                    {
                            state.state = "init"; // Enter creative mode
                            state.mode = "Creative"; // Set the mode to creative
                            gui.remove(titleLabel);
                            gui.remove(startButton);
                            gui.remove(randomizeButton);
                            gui.remove(creativeButton);
                            gui.remove(exitButton); });
            gui.add(creativeButton);

            exitButton = tgui::Button::create("Exit");
            exitButton->setSize({"20%", "5%"});
            exitButton->setPosition({"40%", "59%"});
            exitButton->getRenderer()->setFont("gigantic.ttf"); // Set custom font
            exitButton->onPress([&]()
                                {
                                    window.close(); // Close the application
                                });
            gui.add(exitButton);

            buttonsInitialized = true;
        }
    }

    if (state.state != "start_screen")
    {
        buttonsInitialized = false; // Reset button initialization for the next state
    }

    while (window.isOpen())
    {
        cout << "Current State: " << state.state << ", Mode: " << state.mode << endl;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            gui.handleEvent(*event); // Pass events to TGUI
        }

        window.clear();

        if (state.state == "start_screen")
        {
            // Draw the start screen

            if (st)
            {
                startscreendemo.randomize();
                st = false;
            }
            static Clock randomizeClock;
            if (randomizeClock.getElapsedTime().asSeconds() >= 5.0f)
            {
                startscreendemo.randomize();
                randomizeClock.restart();
            }
            static Clock updateClock1;
            if (updateClock1.getElapsedTime().asMilliseconds() >= 100)
            {
                startscreendemo.update();
                updateClock1.restart();
            }

            // Draw the grid
            for (int row = 0; row < DEMO_SIZE; ++row)
            {
                for (int col = 0; col < DEMO_SIZE; ++col)
                {
                    RectangleShape cell(Vector2f(ScellWidth, ScellHeight));
                    cell.setPosition(Vector2f(col * ScellWidth, row * ScellHeight));

                    // Set cell color based on the state in the GOL game
                    if (startscreendemo.isAlive(row, col))
                        cell.setFillColor(Color::Green);
                    else
                        cell.setFillColor(Color::Black);

                    window.draw(cell);
                }
            }
            gui.draw();
        }
        else if (state.mode == "levels")
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

            // Display game stats
            static tgui::Label::Ptr statsLabel;
            if (!statsLabel)
            {
                statsLabel = tgui::Label::create();
                statsLabel->setTextSize(11);
                statsLabel->getRenderer()->setFont("gigantic.ttf"); // Set custom font
                statsLabel->setPosition({"2%", "90%"});
                statsLabel->getRenderer()->setTextColor(tgui::Color::White);
                gui.add(statsLabel);
            }

            // Update stats
            std::stringstream statsStream;
            statsStream << "Level: " << level << "\n"
                        << "Alive Cells: " << game.getAlive() << "\n";
            statsLabel->setText(statsStream.str());

            // Display a message to press Space to start
            static tgui::Label::Ptr spaceLabel;
            if (state.state != "start")
            {
                spaceLabel = tgui::Label::create("Press Space to start");
                spaceLabel->setTextSize(15);
                spaceLabel->getRenderer()->setFont("gigantic.ttf"); // Set custom font
                spaceLabel->setPosition({"2%", "95%"});
                spaceLabel->getRenderer()->setTextColor(tgui::Color::White);
                gui.add(spaceLabel);
            }

            // Remove the label once the game starts
            if (state.state == "start" && spaceLabel)
            {
                gui.remove(spaceLabel);
                spaceLabel = nullptr;
            }

            // Draw the GUI elements
            gui.draw();
        }
        else if (state.mode == "randomize")
        {
            if (random)
            {
                game.randomize();
                random = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            {
                if (state.state == "init")
                {
                    state.state = "start";
                }
            }

            static tgui::Label::Ptr spaceLabel;
            if (state.state == "init")
            {
                if (!spaceLabel) // Ensure the label is only created once
                {
                    spaceLabel = tgui::Label::create("Press Space to start");
                    spaceLabel->setTextSize(15);
                    spaceLabel->getRenderer()->setFont("gigantic.ttf"); // Set custom font
                    spaceLabel->setPosition({"2%", "95%"});
                    spaceLabel->getRenderer()->setTextColor(tgui::Color::White);
                    gui.add(spaceLabel);
                }
            }

            // Remove the label once the game starts
            if (state.state == "start" && spaceLabel)
            {
                gui.remove(spaceLabel);
                spaceLabel = nullptr;
            }

            // Display game stats
            static tgui::Label::Ptr statsLabel;
            if (!statsLabel)
            {
                statsLabel = tgui::Label::create();
                statsLabel->setTextSize(11);
                statsLabel->getRenderer()->setFont("gigantic.ttf"); // Set custom font
                statsLabel->setPosition({"2%", "90%"});
                statsLabel->getRenderer()->setTextColor(tgui::Color::White);
                gui.add(statsLabel);
            }

            // Update stats
            std::stringstream statsStream;
            statsStream << "Random Mode\n"
                << "Alive Cells: " << game.getAlive() << "\n";
            statsLabel->setText(statsStream.str());

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

            if (state.state == "start")
            {
                static Clock updateClock;
                if (updateClock.getElapsedTime().asMilliseconds() >= 100)
                {
                    game.update();
                    updateClock.restart();
                }
            }

            gui.draw();
        }

        window.display();
    }
}