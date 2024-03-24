# Airport Simulator

Welcome to the Airport Simulator project! This program simulates the operations of an airport, including managing incoming and outgoing flights, runway activities, and more.

## Getting Started

### Prerequisites

To compile and run the Airport Simulator, you'll need:

- **Compiler**:
    - For Linux and macOS: GNU Compiler Collection (g++) or Clang (clang++)
    - For Windows: MinGW or Microsoft Visual C++
- **C++ Standard Library**: Make sure your compiler supports C++17.

### Download

Clone the repository to your local machine using the following command:

    ```bash
    git clone https://github.com/LeoSuzu/AirportSimulationCpp.git
    ```

### Project Structure

The project directory contains the following files:

- **Airport.cpp/h**: Implementation and definition of the Airport class.
- **Plane.cpp/h**: Implementation and definition of the Plane class.
- **Runway.cpp/h**: Implementation and definition of the Runway class.
- **Queue.cpp/h**: Implementation and definition of the Queue class.
- **Random.cpp/h**: Implementation and definition of the Random class.
- **Utility.cpp/h**: Implementation and definition of utility functions.
- **main.cpp**: Entry point of the program.
- **CMakeLists.txt**: Configuration file for CMake.
- **LICENSE**: License information for the project.
- **README.md**: This file.

### Compilation

To compile the project, navigate to the project directory and run the following command:
    
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
    ```bash
    g++ -std=c++17 *.cpp -o airport_simulator
    ```

Replace `airport_simulator` with your preferred name for the executable program.

### Usage Examples

**Run program**:

    ```bash
    ./airport_simulator
    ```