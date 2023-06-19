# FuryStudio immfile utility

immfile can convert imm images and pam palette files into windows bmp format files

## Usage

### Convert imm to bmp

`immfile -ib [IMMFILE] [PAMFILE] [BMPFILE]`  
`immfile --imm-to-bmp [IMMFILE] [PAMFILE] [BMPFILE]`

Converts the supplied IMMFILE and PAMFILE into a windows bmp format bitmap file BMPFILE. 

### Convert bmp to imm

`immfile -bi [BMPFILE] [IMMFILE] [PAMFILE]`  
`immfile --bmp-to-imm [BMPFILE] [IMMFILE] [PAMFILE]`

Converts the supplied [BMPFILE] into separate image and palette files saving them as IMMFILE and PAMFILE respectively.
