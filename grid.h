/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 961500
 * @date April, 2020
 */
#pragma once

#include <sstream>
#include <vector>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char
{
    DEAD = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid
{
    private:
        int width;
        int height;
        std::vector<Cell> cells; // 1D cell array

        int get_index(int x, int y) const;

        Grid x_flip(const Grid &old_grid) const;
        Grid y_flip(const Grid &old_grid) const;
        Grid swap_coordinates(const Grid &old_grid) const;

    public:
        Grid();
        explicit Grid(int square_size);
        Grid(int width, int height);

        int get_width() const;
        int get_height() const;
        int get_total_cells() const;
        int get_alive_cells() const;
        int get_dead_cells() const;

        void resize(int square_size);
        void resize(int new_width, int new_height);

        Cell &operator()(int x, int y);
        const Cell &operator()(int x, int y) const;

        Cell get(int x, int y) const;
        void set(int x, int y, const Cell value);

        Grid crop(int x0, int y0, int x1, int y1) const;
        void merge(const Grid &other, int x0, int y0, bool alive_only = false);
        Grid rotate(int rotation) const;

        friend std::ostream &operator<<(std::ostream &output_stream, const Grid &grid);
};