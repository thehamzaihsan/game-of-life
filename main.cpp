#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "gol.h"
using namespace std;
using namespace sf;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GRID_SIZE 50



//g++ main.cpp -o sfml-app -L/usr/lib64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

struct CustomState {
    string state;
};
int main()
{
    GOL game(GRID_SIZE, GRID_SIZE);
    game.randomize();
    // game.drawInfiniteSpaceship();
    RenderWindow window(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Game of Life Grid");

    // Calculate the size of each cell
    float cellWidth = static_cast<float>(WINDOW_WIDTH) / GRID_SIZE;
    float cellHeight = static_cast<float>(WINDOW_HEIGHT) / GRID_SIZE;
    CustomState state = {"init"};
      SoundBuffer buffer("born.wav");          
      Sound sound(buffer);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear();


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



        if(state.state == "init"){
            // Handle mouse clicks to toggle cell state
            static Clock clickClock;
            if (clickClock.getElapsedTime().asMilliseconds() > 500 && Mouse::isButtonPressed(Mouse::Button::Left))
            {
                Vector2i mousePos = Mouse::getPosition(window);
                int row = mousePos.y / (WINDOW_HEIGHT / GRID_SIZE);
                int col = mousePos.x / (WINDOW_WIDTH / GRID_SIZE);

                if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE)
                {
                    game.toggleBlock(row, col);
                }
                clickClock.restart();
            }
        }

        if(state.state == "start"){
            static Clock updateClock;
            if (updateClock.getElapsedTime().asMilliseconds() >= 100)
            {
              
               
                game.update(sound);
                updateClock.restart();
            }
        }

        window.display();
    }
}