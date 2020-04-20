/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 961500
 * @date April, 2020
 */
#include <cmath>
#include <stdexcept>

#include "grid.h"

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid() : Grid::Grid(0) {}

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(int square_size) : Grid::Grid(square_size, square_size) {}

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
Grid::Grid(int width, int height) : width(width), height(height), cells(width * height, Cell::DEAD) {}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
int Grid::get_width() const
{
    return width;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
int Grid::get_height() const
{
    return height;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
int Grid::get_total_cells() const
{
    return width * height;
}

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
int Grid::get_alive_cells() const
{
    int count = 0;

    for (int i = 0; i < get_total_cells(); i++)
    {
        if (cells[i] == Cell::ALIVE)
        {
            count++;
        }
    }

    return count;
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
int Grid::get_dead_cells() const
{
    int count = 0;

    for (int i = 0; i < get_total_cells(); i++)
    {
        if (cells[i] == Cell::DEAD)
        {
            count++;
        }
    }

    return count;
}

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void Grid::resize(int square_size)
{
    Grid::resize(square_size, square_size);
}

/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void Grid::resize(int new_width, int new_height)
{
    // Sanity check; skip everything if no values change
    if (new_width != width || new_height != height)
    {
        if (get_total_cells() == 0) // If grid is only default constructed
        {
            cells.resize(new_width * new_height, Cell::DEAD);
        }
        else if (new_width > width && new_height > height) // When adding both rows and columns
        {
            std::vector<Cell> new_cells(new_width * new_height, Cell::DEAD);

            int y, new_index = 0;

            // For all cells in old grid
            for (int i = 0; i < get_total_cells(); i++)
            {
                // Derive old grid's y coordinate
                y = floor(i / width);

                // Calculate new index value
                new_index = i + y * (new_width - width);

                // Transfer cell to new grid
                new_cells[new_index] = cells[i];
            }

            cells = new_cells;
        }
        else
        {
            // When changing rows
            if (new_height != height)
            {
                cells.resize(new_width * new_height, Cell::DEAD);
            }

            // When adding columns
            if (new_width > width)
            {
                // Create replacement cell vector
                std::vector<Cell> new_cells(new_width * new_height, Cell::DEAD);

                int y = 0;

                // For all cells in new grid
                for (int i = 0; i < (new_width * new_height); i++)
                {
                    // Derive old grid's y coordinate
                    y = floor(i / new_width);

                    // Transfer cell to new grid
                    new_cells[i] = cells[i - y];
                }

                cells = new_cells;
            }

            // When removing columns
            if (new_width < width)
            {
                // Create replacement cell vector
                std::vector<Cell> new_cells(new_width * new_height, Cell::DEAD);

                int y = 0;

                // For all cells in new grid
                for (int i = 0; i < (new_width * new_height); i++)
                {
                    // Derive old grid's y-coordinate
                    y = floor(i / new_width);

                    // Transfer cell to new grid
                    new_cells[i] = cells[i - y * (new_width - width)];
                }

                cells = new_cells;
            }
        }

        width = new_width;
        height = new_height;
    }
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */
int Grid::get_index(int x, int y) const
{
    return x + (y * width);
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell Grid::get(int x, int y) const
{
    // Check x/y within bounds
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        throw std::out_of_range("ERROR: Requested cell coordinate is out of bounds.");
    }
    else
    {
        return operator()(x, y);
    }
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(int x, int y, Cell value)
{
    // Check x/y within bounds
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        throw std::out_of_range("ERROR: Requested cell coordinate is out of bounds.");
    }
    else
    {
        // Dereference cell and apply value
        Cell &current_cell = operator()(x, y);
        current_cell = value;
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell &Grid::operator()(int x, int y)
{
    // Check x/y within bounds
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        throw std::out_of_range("ERROR: Requested cell coordinate is out of bounds.");
    }
    else
    {
        return cells[get_index(x, y)];
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
const Cell &Grid::operator()(int x, int y) const
{
    // Check x/y within bounds
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        throw std::out_of_range("ERROR: Requested cell coordinate is out of bounds.");
    }
    else
    {
        return cells[get_index(x, y)];
    }
}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
Grid Grid::crop(int x0, int y0, int x1, int y1) const
{
    // Check x0, y0 within bounds and x1, y1 not negative
    if (x0 >= width || x0 < 0 || y0 >= height || y0 < 0 || x1 < 0 || y1 < 0)
    {
        throw std::out_of_range("ERROR: Attempted resize is out of bounds.");
    }
    else
    {
        // Construct new grid of size dx * dy
        Grid new_grid(x1 - x0, y1 - y0);

        // Iterate through new grid and fill values
        for (int y = 0; y < new_grid.get_height(); y++)
        {
            for (int x = 0; x < new_grid.get_width(); x++)
            {
                new_grid.set(x, y, get(x + x0, y + y0));
            }
        }
    }

        return new_grid;
    }
}

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge region to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
void Grid::merge(Grid &other, int x0, int y0, bool alive_only)
{
    if (width < x0 + other.get_width() || height < y0 + other.get_height())
    {
        throw std::invalid_argument("ERROR: Merging grid too large.");
    }
    else
    {
        // Iterate through new grid
        for (int y = 0; y < other.get_height(); y++)
        {
            for (int x = 0; x < other.get_width(); x++)
            {
                // Check merge condition
                if (!alive_only)
                {
                    // Transfer cell unconditionally
                    set(x + x0, y + y0, other.get(x, y));
                }
                else
                {
                    if (get(x + x0, y + y0) == Cell::DEAD)
                    {
                        // Transfer cell only if dead
                        set(x + x0, y + y0, other.get(x, y));
                    }
                }
            }
        }
    }
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
Grid Grid::rotate(int _rotation) const
{
    // Normalise rotation amount to range [0, 3]
    int rotation = _rotation % 4;

    // Correct negative results to fix C++'s silly modulus
    if (rotation < 0)
    {
        rotation += 4;
    }

    // Copy the current grid
    Grid new_grid(*this);

    if (rotation == 1)
    {
        // 90 degree rotation:
        //   Equivalent to a coordinate swap and vertical flip
        return x_flip(swap_coordinates(new_grid));
    }
    else if (rotation == 2)
    {
        // 180 degree rotation:
        //   Equivalent to a vertical and horizontal flip
        return x_flip(y_flip(new_grid));
    }
    else if (rotation == 3)
    {
        // 270 degree rotation:
        //   Equivalent to a coordinate swap and horizontal flip
        return y_flip(swap_coordinates(new_grid));
    }
    else
    {
        // 0 degree rotation:
        //   Equivalent to the grid as-is
        return new_grid;
    }
}

/**
 * Grid::x_flip(old_grid)
 *
 * Private helper function which returns a copy of the grid flipped along the
 * x-axis (vertical reflection).
 *
 * @param old_grid
 *      The grid to be transformed.
 *
 * @return
 *      A copy of the grid reflected along the x-axis.
 */
Grid Grid::x_flip(const Grid &old_grid) const
{
    if (old_grid.get_width() == 1)
    {
        // Do nothing if only one column
        return old_grid;
    }
    else
    {
        int height = old_grid.get_height();
        int width = old_grid.get_width();

        Grid new_grid(width, height);

        // For all cells
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                // Reverse the ordering of rows in the grid, to flip
                new_grid(x, y) = old_grid((width - 1 - x), y);
            }
        }

        return new_grid;
    }
}

/**
 * Grid::y_flip(old_grid)
 *
 * Private helper function which returns a copy of the grid flipped along the
 * y-axis (horizontal reflection).
 *
 * @param old_grid
 *      The grid to be transformed.
 *
 * @return
 *      A copy of the grid reflected along the y-axis.
 */
Grid Grid::y_flip(const Grid &old_grid) const
{
    if (old_grid.get_height() == 1)
    {
        // Do nothing if only one row
        return old_grid;
    }
    else
    {
        int height = old_grid.get_height();
        int width = old_grid.get_width();

        Grid new_grid(width, height);

        // For all cells
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                // Reverse the ordering of rows in the grid, to flip
                new_grid(x, y) = old_grid(x, (height - 1 - y));
            }
        }

        return new_grid;
    }
}

/**
 * Grid::swap_coordinates(old_grid)
 *
 * Private helper function which returns a copy of the grid flipped along the
 * main diagonal, by switching the position of each cell's coordinates (diagonal
 * reflection).
 *
 * @param old_grid
 *      The grid to be transformed.
 *
 * @return
 *      A copy of the grid reflected along the main diagonal.
 */
Grid Grid::swap_coordinates(const Grid &old_grid) const
{
    Grid new_grid;

    //Invert grid dimensions
    new_grid.resize(old_grid.get_height(), old_grid.get_width());

    // For all cells
    for (int y = 0; y < new_grid.get_height(); y++)
    {
        for (int x = 0; x < new_grid.get_width(); x++)
        {
            new_grid(x, y) = old_grid(y, x);
        }
    }

    return new_grid;
}

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */
std::ostream &operator<<(std::ostream &output_stream, const Grid &grid)
{
    // Create (identical) top & bottom borders
    std::string border;

    border += "+";

    for (int i = 0; i < grid.get_width(); i++)
    {
        border += "-";
    }

    border += "+\n";

    // Print top border
    output_stream << border;

    // Print grid contents
    for (int y = 0; y < grid.get_height(); y++)
    {
        output_stream << "|";

        for (int x = 0; x < grid.get_width(); x++)
        {
            if (grid(x, y) == Cell::ALIVE)
            {
                output_stream << "#";
            }
            else
            {
                output_stream << " ";
            }
        }

        output_stream << "|\n";
    }

    // Print bottom border
    output_stream << border;

    return output_stream;
}