# Building FuryStudio

## Windows

### Environment
- Ensure you have either Visual Studio or the dotnet SDK installed
- Use a command prompt with the sdk tools configured.  Such as the Developer Command Prompt

### Get Source
- `git clone https://david-c14/FuryStudio`

### Build the utils
- `cd FuryStudio\Utils\build`
- `cmake .`
- `cmake --build .`

### Test the utils
- `vstest.console Debug\C_Tests.dll`
- `vstest.console Debug\Cpp_Tests.dll`
- `vstest.console Debug\Cli_Tests.dll`

### Test FuryStudio
- `cd ..\..\Core.Tests`
- `dotnet test`

### Build FuryStudio
- `cd ..\WinUI` or `cd ..\AvaloniaUI`
- `dotnet build`


### Run FuryStudio
- `dotnet run` or - `dotnet run --framework net6.0` (for avaloniaUI)