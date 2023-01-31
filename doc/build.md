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

### Build FuryStudio
- `cd ..\..\WinUI`
- `dotnet build WinUI.csproj`

### Run FuryStudio
- `dotnet run WinUI.csproj`