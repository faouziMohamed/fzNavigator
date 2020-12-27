# FzNavigator <img src="assets/fznavigator_icones/web.png" align="left" height="48" width="48" >  [![Build Status](https://travis-ci.org/faouziMohamed/fzNavigator.svg?branch=master)](https://travis-ci.org/faouziMohamed/fzNavigator)  
[![GitHub license](https://img.shields.io/github/license/faouziMohamed/fzNavigator)](https://github.com/faouziMohamed/fzNavigator/blob/master/LICENSE)  ![GitHub language count](https://img.shields.io/github/languages/count/faouzimohamed/fzNavigator)  ![GitHub top language](https://img.shields.io/github/languages/top/faouzimohamed/fznavigator)  [![Codacy Badge](https://api.codacy.com/project/badge/Grade/a76cf0b31db8478090be5bc2e708b55f)](https://app.codacy.com/manual/faouziMohamed/fzNavigator?utm_source=github.com&utm_medium=referral&utm_content=faouziMohamed/fzNavigator&utm_campaign=Badge_Grade_Dashboard)   
A simple web Navigator based on [Chromium](https://wiki.qt.io/QtWebEngine), written in c++ using [Qt(5.14.1)](https://download.qt.io/official_releases/qt/5.14/5.14.1/) framework  

## Sections of this documentation  
 - [Requirements](#requirements)  
 - [Download the binary File](#download-the-binary-file)  
 - [Download Microsoft Windows Sdk Tool](#download-microsoft-windows-sdk-tool)
 - [Build and run](#Build and run)
 - [QT 5](#QT 5)

## Requirements  

* C++11 or higher

 ### On Windows  

  - [_Qt5_](https://download.qt.io/official_releases/qt/) or higher  

  - MSVC2017 ([Microsoft windows sdk](https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk/))or higher (_The Web Engine compile only with Microsoft's compiler_), it doesn't compile with Mingw compiler.  

 ### On Linux (Ubuntu 18.04 LTS)

  - [_Qt5_](https://www.qt.io/download-open-source) or higher  
   
 - [_Qt Creator _Latest version_ (recommended)_](https://download.qt.io/official_releases/qtcreator/4.11/)
   
## Download the binary File  
- For windows  
 - Download the FzNavigator Installer(Wizard) [here](https://github.com/faouziMohamed/fzNavigator/releases/tag/V0.2-wizzared)  
## Download Microsoft Windows Sdk Tool  
 - For [Windows7](https://www.microsoft.com/en-us/download/details.aspx?id=8279)  
 - For [Windows8](https://support.microsoft.com/en-us/help/2780680/an-update-is-available-for-windows-sdk-for-windows-8)  
 - For [Windows10](https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk/)  


## Build and run
### Easiest way
 Use Qt Creator and open the `fzNavigator.pro` file the hit the run button<img src="assets/images/run_button.png" width=20 alt="run button" /> to build and run.

### The CMake way (Linux/Unix only)

##### Generate a Makefile

 - You'll need to set the `CMAKE_PREFIX_PATH` variable the value must be the path to the Qt compiler  
   here an example :  
   
   ```bash
   # For me QT is installed on /home/me/Qt5/ and I use the gcc_64 compiler
   # So The Cmake Prefix path will be /home/me/Qt5/[the qt version]/gcc_64
   # for me the qt version is 5.15.2, so we have :↓
   $ cmake -DCMAKE_PREFIX_PATH=/home/me/Qt5/5.15.2/gcc_64
   ```
 - In order to have a project directory clean, we recommend to use the `-B ` option to specify 
   where to generate the Makefile file.
   Example : 
   
   ```bash
   # Here _build is the path to generate the Makefile
   $ cmake -DCMAKE_PREFIX_PATH=/home/me/Qt5/gcc_64 -B _build
   ```

For more option : [Cmake doc](https://cmake.org/cmake/help/latest/manual/cmake.1.html)

Finally use this command to compile with CMake :  

```bash
cmake -DCMAKE_PREFIX_PATH=/home/me/Qt5/gcc_64 -B _build
```

#### Build and run

Assuming that the Makefile is generated into the `_build` folder 
```bash
$ cd _build
$ make
# Run the program with 
$ ./FzNavigator
```

### QT 5

 - Download [Qt5 Framwork](https://download.qt.io/official_releases/qt/)  
 - Qt [Documentation](https://doc.qt.io/)  
 #### How to Install MSVC (In Qt Creator) ?  
 Here a [thread](https://stackoverflow.com/questions/47773289/debugging-in-qtcreator-using-msvc2017-compiler#answers) on stackoverflow that show how to proceed  
