# Building FuryStudio

## Windows

### Environment
- Ensure you have either Visual Studio or the dotnet SDK installed (dotnet 6.0)
- Use a command prompt with the sdk tools configured.  Such as the Developer Command Prompt

### Get Source
- `git clone --branch develop --recurse-submodules https://github.com/david-c14/FuryStudio`

### Build command line utilis and c++ library
- `cd FuryStudio\Utils\build`
- `cmake .`
- `cmake --build .`

### Test command line utils and c++ library
- `Debug\Cli_Tests`
- `Debug\C_Tests`
- `Debug\Cpp_Tests`

### Build and Test GUI Application
- `cd ..\..`
- `dotnet test Core.Tests`

### Run Guid application 
either
- `cd WinUI`
- `dotnet run --framework net6.0`
or
- `cd AvaloniaUI`
- `dotnet run --framework net6.0`

### Run FuryStudio
- `dotnet run` or - `dotnet run --framework net6.0` (for avaloniaUI)

### Linux

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

### Build and Test GUI Application
- `cd ../..`
- `dotnet test Core.Tests`

### Run GUI application 
- `cd AvaloniaUI`
- `dotnet run --framework net6.0`