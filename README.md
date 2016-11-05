# lnglat2coord

Utility to convert between longitude/latitude and z/x/y coordinates.

## Building

Depends on [futile](https://github.com/rmarianski/futile) being built first. The makefile expects `pkg-config` to be able to find it.

    make

## Usage

### Converting from longitude latitude -> z/x/y coordinate

    lnglat2coord <longitude> <latitude> <zoom>

### Converting from z/x/y coordinate -> longitude latitude

    lnglat2coord z/x/y
