/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 961500
 * @date March, 2020
 */
#pragma once

#include "grid.h"

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World
{
    private:
        Grid current_state;
        Grid next_state;

    public:
        World();
        World(int width, int height);
        explicit World(int square_size);
        explicit World(Grid &initial_state);

        int get_width() const;
        int get_height() const;
        int get_total_cells() const;
        int get_alive_cells() const;
        int get_dead_cells() const;
        const Grid &get_state() const;

        void resize(int square_size);
        void resize(int new_width, int new_height);
};