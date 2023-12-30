# Sniper: Pattern Scanner with Regex Support

## Overview
Sniper is a pattern scanning tool designed to analyze and identify specific patterns within binary files. Featuring regex support.

## Features
- **Regex Support**: Leverage the power of regular expressions for advanced pattern matching capabilities.
- **Binary File Analysis**: Efficiently scan binary files for predefined patterns or opcodes.

 
## Installation
To install Sniper, follow these instructions:
```sh
git clone https://github.com/zeropio/Sniper
cd Sniper
make
```

## Usage
To use Sniper, run the executable with the required parameters:
```sh
./Sniper [path to binary file] [pattern or regex]
./Sniper example.bin "^\\x90\\x90\\x90.*"
```

## Contributing
Contributions to Sniper are welcome! If you have suggestions for improvements or bug fixes, please open an issue or submit a pull request.

## License
Sniper is distributed under the GNU license. See the LICENSE file for more details.
