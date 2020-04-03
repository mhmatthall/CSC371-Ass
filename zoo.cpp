/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 961500
 * @date March, 2020
 */
#include "zoo.h"

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider()
{
    Grid g(3);

    g(0, 2) = Cell::ALIVE;
    g(1, 0) = Cell::ALIVE;
    g(1, 2) = Cell::ALIVE;
    g(2, 1) = Cell::ALIVE;
    g(2, 2) = Cell::ALIVE;

    return g;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino()
{
    Grid g(3);

    g(0, 1) = Cell::ALIVE;
    g(1, 0) = Cell::ALIVE;
    g(1, 1) = Cell::ALIVE;
    g(1, 2) = Cell::ALIVE;
    g(2, 0) = Cell::ALIVE;

    return g;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship()
{
    Grid g(5, 4);

    g(0, 1) = Cell::ALIVE;
    g(0, 2) = Cell::ALIVE;
    g(0, 3) = Cell::ALIVE;
    g(1, 0) = Cell::ALIVE;
    g(1, 3) = Cell::ALIVE;
    g(2, 3) = Cell::ALIVE;
    g(3, 3) = Cell::ALIVE;
    g(4, 0) = Cell::ALIVE;
    g(4, 2) = Cell::ALIVE;

    return g;
}

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(const std::string path)
{
    std::ifstream in(path);

    // File exists check
    if (!in.is_open())
    {
        throw std::runtime_error("ERROR: File '" + path + "' not found.");
    }

    // Load height and width
    int width = 0;
    in >> width;

    int height = 0;
    in >> height;

    // Width/height bounds check
    if (width < 0 || height < 0)
    {
        in.close();
        throw std::range_error("ERROR: Invalid grid shape in file '" + path + "'.");
    }
    
    // Assemble grid and fill cells
    Grid new_grid(width, height);

    in.get();   // Ignore first newline character

    char current_char = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            current_char = in.get();

            if (current_char == '#')
            {
                new_grid(x, y) = Cell::ALIVE;
            }
            else if (current_char == ' ')
            {
                new_grid(x, y) = Cell::DEAD;
            }
            else
            {
                in.close();
                throw std::runtime_error("ERROR: File '" + path + "' is invalid.");
            }
        }

        // Check that newline is present
        if (in.get() != '\n')
        {
            in.close();
            throw std::runtime_error("ERROR: File '" + path + "' is invalid.");
        }
    }

    in.close();

    return new_grid;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(const std::string path, const Grid grid)
{
    std::ofstream out(path);

    // Check file created successfully
    if (!out.is_open())
    {
        throw std::runtime_error("ERROR: Cannot write to file '" + path + "'.");
    }

    // Write height/width into first line
    out << grid.get_width() << " " << grid.get_height() << "\n";

    // Write grid state
    for (int y = 0; y < grid.get_height(); y++)
    {
        for (int x = 0; x < grid.get_width(); x++)
        {
            out.put(
                grid(x, y) == Cell::ALIVE ? '#' : ' '
            );
        }

        out.put('\n');
    }

    out.close();
}
/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(const std::string path)
{
    std::ifstream in(path, std::ios::binary);

    // Check file exists
    if (!in.is_open())
    {
        throw std::runtime_error("ERROR: File '" + path + "' not found.");
    }

    // Read width and height
    int width = 0;
    in.read((char *)&width, sizeof(int));

    int height = 0;
    in.read((char *)&height, sizeof(int));

    // Check width/height within bounds
    if (width < 0 || height < 0)
    {
        in.close();
        throw std::range_error("ERROR: Invalid grid shape in file '" + path + "'.");
    }

    // Read x bytes of cell data into buffer
    int read_size = floor((width * height) / 8); // Number of bytes to read (inc. padding)
    char buffer[read_size];

    in.read(buffer, read_size + 1);

    // Check if file ended unexpectedly
    if (in.fail())
    {
        in.close();
        throw std::runtime_error("ERROR: File '" + path + "' is invalid.");
    }

    in.close(); // End of file reading

    // Assemble and fill grid
    Grid new_grid(width, height);
    int c_index = 0;
    bool current_bit = false;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Get absolute position of the cell in the grid: [0, w * h)
            c_index = x + (y * width);

            // Retrieve jth bit from the ith byte in the buffer
            current_bit = (buffer[c_index / 8] >> c_index % 8) & 1U;

            // Set cell as appropriate
            new_grid(x, y) = current_bit == true ? Cell::ALIVE : Cell::DEAD;
        }
    }

    return new_grid;
}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

