# FuryStudio datfile utility

datfile can pack and unpack the files within a DAT archive

## Usage

### List contents

`datfile -l [ARCHIVEFILE]`  
`datfile --list [ARCHIVEFILE]`

lists the contents of ARCHIVEFILE, giving compressed and uncompressed sizes.

### Brief contents

`datfile -b [ARCHIVEFILE]`  
`datfile --list-brief [ARCHIVEFILE]`

lists the contents of ARCHIVEFILE, giving filenames only.

### Extract a single file from the archive

`datfile -x [ARCHIVEFILE] [ENTRYNAME]`  
`datfile --extract [ARCHIVEFILE] [ENTRYNAME]`

Extracts ENTRYNAME to a file called ENTRYNAME from ARCHIVEFILE. If ENTRYNAME is compressed in the archive it will be decompressed.

### Extract all files from the archive

`datfile -X [ARCHIVEFILE]`  
`datfile --extract-all [ARCHIVEFILE]`

Extracts all the files from within ARCHIVEFILE, decompressing any compressed files. 
The extracted files are saved in the current directory, using the names given in the archive.

### Pack files into an archive

`datfile -c [ARCHIVEFILE] [ENTYRNAME] [...]`  
`datfile --compress [ARCHIVEFILE] [ENTYRNAME] [...]`

Compresses one or more files given by ENTRYNAME and subsequent parameters and packs them into a new file ARCHIVEFILE. 
Individual entries are not compressed if that would take up more space than the uncompressed file.

### Pack files into an archive without compression

`datfile -u [ARCHIVEFILE] [ENTRYNAME] [...]`  
`datfile --pack [ARCHIVEFILE] [ENTRYNAME] [...]`

Packs one or more files given by ENTRYNAME and subsequent parameters into a new file ARCHIVEFILE.
