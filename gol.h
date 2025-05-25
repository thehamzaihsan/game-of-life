#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
struct Block {
    bool isAlive;

    Block() : isAlive(false) {}
};

class GOL {
public:
    GOL(int rows, int cols) : grid(rows, std::vector<Block>(cols)) {}

    void addBlock(bool life, int x, int y) {
        if (isValid(x, y)) {
            grid[x][y].isAlive = life;
        }
    }

    void removeBlock(int x, int y) {
        if (isValid(x, y)) {
            grid[x][y].isAlive = false;
        }
    }

    void toggleBlock(int x, int y) {
        if (isValid(x, y)) {
            grid[x][y].isAlive = !grid[x][y].isAlive;
        }
    }

    void clear() {
        for (auto& row : grid) {
            for (auto& block : row) {
                block.isAlive = false;
            }
        }
    }

    void printGrid() const {
        for (const auto& row : grid) {
            for (const auto& block : row) {
                std::cout << (block.isAlive ? "O" : ".") << " ";
            }
            std::cout << "\n";
        }
    }
    
    int getAlive() const {
        int count = 0;
        for (const auto& row : grid) {
            for (const auto& block : row) {
                if (block.isAlive) {
                    ++count;
                }
            }
        }
        return count;
    }


    bool isAlive(int x, int y) const {
        return isValid(x, y) ? grid[x][y].isAlive : false;
    }

    int countAliveNeighbors(int x, int y) const {
        static const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        static const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int count = 0;

        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny) && grid[nx][ny].isAlive) {
                ++count;
            }
        }

        return count;
    }


    void update() {
        std::vector<std::vector<Block>> newGrid = grid;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                int aliveNeighbors = countAliveNeighbors(i, j);
                if (grid[i][j].isAlive) {
                    // Death by underpopulation or overcrowding
                    if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                        newGrid[i][j].isAlive = false;
                    } else {
                        // Survival
                        newGrid[i][j].isAlive = true;
                    }
                } else {
                    // Birth
                    if (aliveNeighbors == 3) {
                        // alive.play();
                        newGrid[i][j].isAlive = true;
                    }
                }
            }
        }

        grid = newGrid;
    }
   



    void randomize() {
        for (auto& row : grid) {
            for (auto& block : row) {
                block.isAlive = (rand() % 2 == 0);
            }
        }
    }

    void setAllAlive(){
        for (auto& row : grid) {
            for (auto& block : row) {
                block.isAlive = true;
            }
        }
    }

    void drawSpaceship() {
        // Clear the grid first
        clear();

        // Define a simple spaceship pattern (Glider)
        // The pattern is:
        // . O .
        // . . O
        // O O O

        int startX = 1; // Starting x-coordinate
        int startY = 1; // Starting y-coordinate

        addBlock(true, startX, startY + 1);
        addBlock(true, startX + 1, startY + 2);
        addBlock(true, startX + 2, startY);
        addBlock(true, startX + 2, startY + 1);
        addBlock(true, startX + 2, startY + 2);
    }
    void drawSpaceshipInMiddle() {
        // Clear the grid first
        clear();

        // Define a simple spaceship pattern (Glider)
        // The pattern is:
        // . O .
        // . . O
        // O O O

        int midX = grid.size() / 2; // Middle x-coordinate
        int midY = grid[0].size() / 2; // Middle y-coordinate

        addBlock(true, midX - 1, midY);
        addBlock(true, midX, midY + 1);
        addBlock(true, midX + 1, midY - 1);
        addBlock(true, midX + 1, midY);
        addBlock(true, midX + 1, midY + 1);
    }

    void drawInfiniteSpaceship() {
        // Clear the grid first
        clear();

        // Define a Gosper Glider Gun pattern
        // This is a well-known pattern that produces an infinite stream of spaceships
        // The pattern is too large to describe in comments, but it is well-documented online

        int startX = 1; // Starting x-coordinate
        int startY = 1; // Starting y-coordinate

        // Left square
        addBlock(true, startX + 4, startY + 0);
        addBlock(true, startX + 4, startY + 1);
        addBlock(true, startX + 5, startY + 0);
        addBlock(true, startX + 5, startY + 1);

        // Left "arrow"
        addBlock(true, startX + 4, startY + 10);
        addBlock(true, startX + 5, startY + 10);
        addBlock(true, startX + 6, startY + 10);
        addBlock(true, startX + 3, startY + 11);
        addBlock(true, startX + 7, startY + 11);
        addBlock(true, startX + 2, startY + 12);
        addBlock(true, startX + 8, startY + 12);
        addBlock(true, startX + 2, startY + 13);
        addBlock(true, startX + 8, startY + 13);
        addBlock(true, startX + 5, startY + 14);
        addBlock(true, startX + 3, startY + 15);
        addBlock(true, startX + 7, startY + 15);
        addBlock(true, startX + 4, startY + 16);
        addBlock(true, startX + 5, startY + 16);
        addBlock(true, startX + 6, startY + 16);
        addBlock(true, startX + 5, startY + 17);

        // Right "arrow"
        addBlock(true, startX + 2, startY + 20);
        addBlock(true, startX + 3, startY + 20);
        addBlock(true, startX + 4, startY + 20);
        addBlock(true, startX + 2, startY + 21);
        addBlock(true, startX + 3, startY + 21);
        addBlock(true, startX + 4, startY + 21);
        addBlock(true, startX + 1, startY + 22);
        addBlock(true, startX + 5, startY + 22);
        addBlock(true, startX + 0, startY + 24);
        addBlock(true, startX + 1, startY + 24);
        addBlock(true, startX + 5, startY + 24);
        addBlock(true, startX + 6, startY + 24);

        // Right square
        addBlock(true, startX + 2, startY + 34);
        addBlock(true, startX + 3, startY + 34);
        addBlock(true, startX + 2, startY + 35);
        addBlock(true, startX + 3, startY + 35);
    }

private:
    std::vector<std::vector<Block>> grid;

    bool isValid(int x, int y) const {
        return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
    }
};
