# FuryStudio binfile utility

binfile can convert game level data BIN files into other formats

## Usage

### View summary of file

`binfile -i [BINFILE]`  
`binfile --info [BINFILE]`

Gives a small sample of the content of the file.

### Convert to YAML

`binfile -y [INPUTFILE] [OUTPUTFILE]`  
`binfile --yaml [INPUTFILE] [OUTPUTFILE]`

Converts the file from any of the supported formats to YAML

### Convert to BIN

`binfile -b [INPUTFILE] [OUTPUTFILE]`  
`binfile --bin [INPUTFILE] [OUTPUTFILE]`

Converts the file from any of the supported formats to BIN format (The format expected by the game)

### Convert to Uncompressed BIN

`binfile -u [INPUTFILE] [OUTPUTFILE]`  
`binfile --uncompressed [INPUTFILE] [OUTPUTFILE]`

Converts the file from any of the supported formats to an BIN format with no compression. This format can be read by the game, but takes up more space.

