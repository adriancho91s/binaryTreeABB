# Dictionary Program

This is a simple dictionary program implemented in C. It uses a binary search tree to store words along with their meanings, grammatical categories, and synonyms.

## Features

- Add a word to the dictionary with its meaning, grammatical category, and synonyms.
- Modify the properties of a word, including its meaning, grammatical category, and synonyms.
- Delete a word from the dictionary.
- Show the properties of a word, including its meaning, grammatical category, and synonyms.
- List words by grammatical category.
- List words by the first letter.
- List all words in the dictionary in alphabetical order.

## How to Run

You can compile and run this program using gcc or CMake.

### Using gcc

To compile the program with gcc, use the following command:

```bash
gcc -o main main.c
```

Then, you can run the program with:

```bash
./main
```

### Using CMake

If you prefer to use CMake, you can follow these steps:

First, create a build directory and navigate into it:

```bash
mkdir build
cd build
```

Then, generate the build system with CMake:

```bash
cmake ..
```

Finally, build and run the program:

```bash
cmake --build .
./main
```

## Contributing

Contributions are welcome. Feel free to suggest improvements or report bugs.

## License

Licensed under the MIT License. See [LICENSE](LICENSE) for details.
