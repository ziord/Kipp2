# Kipp2

A lightweight text based file compressor and decompressor  written in C++ (17) based on the Huffman coding algorithm. Kipp2 is an extension of [Kipp](https://github.com/ziord/Kipp) and supports multiple file compression.

## Usage
- Build the project.
- For single file compression: </br>
   &nbsp; Run `Kipp -c name_of_file_to_be_compressed.ext`
- For decompression/uncompression of single `Kipp`ed files: </br>
    &nbsp; Run `Kipp -uc name_of_file_to_be_uncompressed.kipp` `name_of_output_file.ext`
- For multiple file compression:
    &nbsp; Run `Kipp -cm file1 file2 ...filen`
- For decompression/uncompression of multiple `Kipp`ed files: </br>
     &nbsp; Run `Kipp -um name_of_file_to_be_uncompressed.kipp`  `folder_name`

### Note
`Kipp2` only works for text based files (.txt, .py, .C, etc.).

    
