# Building FuryStudio on Linux

### Environment 
- Ensure you have a suitable c++ compiler. I use g++
- Ensure you have the dotnet SDK installed (dotnet 6.0)

### Get Source
- `git clone --branch develop --recurse-submodules https://github.com/david-c14/FuryStudio`

### Build command line utilis and c++ library
- `cd FuryStudio/Utils/build`
- `cmake .`
- `cmake --build .`

### Test command line utils and c++ library
- `Debug/Cli_Tests`
- `Debug/C_Tests`
- `Debug/Cpp_Tests`
- `Debug/C_LibTests`
- `Debug/Cpp_LibTests`

### Build and Test GUI Application
- `cd ../..`
- `dotnet test`

### Run GUI application 
- `cd AvaloniaUI`
- `dotnet run --framework net6.0`
