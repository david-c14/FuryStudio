# Bin.ConversionType enum

The ConversionType enum indicates the required format for a [Bin](bin.md) game level conversion.

`carbon14.FuryStudio.Utils.Bin.ConversionType`

## values

- `Uncompressed` An uncompressed file can still be read by the game, but will take up more space.
- `Compressed` Normally the file will be compressed using an RLE compression scheme.
- `Yaml` A Yaml description of the game level.
