mkdir utils
copy ..\build\Debug\DatFile.exe utils
copy ..\build\Debug\ImmFile.exe utils
copy ..\..\LICENSE utils
copy ..\..\doc\utilities\datfile.md utils
copy ..\..\doc\utilities\immfile.md utils
Compress-Archive -Path ".\utils\*" -DestinationPath "Utils-win-x64-${{ github.event.release.name }}.zip"