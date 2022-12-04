# LittleMarketHelperQt

## About
Small application with Qt interface used to recalibrate a portfolio given user specified weight for each product.

## Build
LittleMarketHelperQt can be compiled only with msvc compiler. In particular, it has been tested using msvc2019 64-bit with Qt Creator IDE.

- Download [Qt binaries](https://www.qt.io/download)
- Download the precompiled [OrTools](https://developers.google.com/optimization/install/cpp) library for Visual Studio 2019.
- Set the environment variable `OR_TOOLS` to ORTools path

Note: OrTools is a big library, with more than 10Gb of source code. They distribute only the `Release` binaries. While it is possible to download the source code and build the `Debug` .lib, right now the portfolio optimazion is available only
