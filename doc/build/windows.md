# Building FuryStudio on 64-bit Windows

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
- `Debug\C_LibTests`
- `Debug\Cpp_LibTests`

### Build and Test GUI Application
- `cd ..\..`
- `dotnet test`

### Run GUI application 
either
- `cd WinUI`
- `dotnet run --framework net6.0`
or
- `cd AvaloniaUI`
- `dotnet run --framework net6.0`

### Run FuryStudio
- `dotnet run` or - `dotnet run --framework net6.0` (for avaloniaUI)
