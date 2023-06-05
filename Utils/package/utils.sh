mkdir utils
cp ../build/Debug/DatFile utils
cp ../build/Debug/ImmFile utils
chmod 775 utils/*
cp ../../LICENSE utils
cp ../../doc/utilities/datfile.md utils
cp ../../doc/utilities/immfile.md utils
tar -cvzf "Utils-linux-x64-${{ github.event.release.name }}.tgz" utils