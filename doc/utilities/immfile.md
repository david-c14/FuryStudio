# FuryStudio immfile utility

immfile can convert imm images and pam palette files into windows bmp format files.

Fury of the Furries pam files are 6-bits per channel VGA palettes. If you wish to use
a full 8-bit palette, use the 8-bit variations listed at the bottom.

## Usage

### Convert imm to bmp

`immfile -ib [IMMFILE] [PAMFILE] [BMPFILE]`  
`immfile --imm-to-bmp [IMMFILE] [PAMFILE] [BMPFILE]`

Converts the supplied IMMFILE and PAMFILE into a windows bmp format bitmap file BMPFILE. 

### Convert bmp to imm

`immfile -bi [BMPFILE] [IMMFILE] [PAMFILE]`  
`immfile --bmp-to-imm [BMPFILE] [IMMFILE] [PAMFILE]`

Converts the supplied BMPFILE into separate image and palette files saving them as IMMFILE and PAMFILE respectively.

### Convert imm to lbm

`immfile -il [IMMFILE] [PAMFILE] [LBMFILE]`  
`immfile --imm-to-lbm [IMMFILE] [PAMFILE] [LBMFILE]`

Converts the supplied IMMFILE and PAMFILE into an lbm format bitmap file LBMFILE

### Convert lbm to imm

`immfile -li [LBMFILE] [IMMFILE] [PAMFILE]`  
`immfile --lbm-to-imm [LBMFILE] [IMMFILE] [PAMFILE]`

Converts the supplied LBMFILE into separate image and palette files saving them as IMMFILE and PAMFILE respectively.

### CONVERT bmp to lbm

`immfile -bl [BMPFILE] [LBMFILE]`  
`immfile --bmp-to-lbm [BMPFILE] [LBMFILE]`

Converts the supplied BMPFILE into an lbm format bitmap file LBMFILE

### CONVERT lbm to bmp

`immfile -lb [LBMFILE] [BMPFILE]`  
`immfile --lbm-to-bmp [LBMFILE] [BMPFILE]`

Converts the supplied LBMFILE into a windows bmp format bitmap file BMPFILE.

### Convert imm to bmp with 8-bit palette

`immfile -8b [IMMFILE] [PAMFILE] [BMPFILE]`  
`immfile --imm8-to-bmp [IMMFILE] [PAMFILE] [BMPFILE]`

Converts the supplied IMMFILE and PAMFILE into a windows bmp format bitmap file BMPFILE. 

### Convert bmp to imm with 8-bit palette

`immfile -b8 [BMPFILE] [IMMFILE] [PAMFILE]`  
`immfile --bmp-to-imm8 [BMPFILE] [IMMFILE] [PAMFILE]`

Converts the supplied BMPFILE into separate image and palette files saving them as IMMFILE and PAMFILE respectively.

### Convert imm to lbm with 8-bit palette;

`immfile -8l [IMMFILE] [PAMFILE] [LBMFILE]`  
`immfile --imm8-to-lbm [IMMFILE] [PAMFILE] [LBMFILE]`

Converts the supplied IMMFILE and PAMFILE into an lbm format bitmap file LBMFILE

### Convert lbm to imm with 8-bit palette

`immfile -l8 [LBMFILE] [IMMFILE] [PAMFILE]`  
`immfile --lbm-to-imm8 [LBMFILE] [IMMFILE] [PAMFILE]`

Converts the supplied LBMFILE into separate image and palette files saving them as IMMFILE and PAMFILE respectively.

