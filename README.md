# EncNotes
*Extremely basic text editor with 128 bit AES encryption*

### Objective

To provide a quick, simple and cross-platform solution to store sensitive text based information with encryption.

### Features

1. QT/C++ based. Works on Mac OS, Windows and Linux.
2. 128 bit AES Encryption

### Build Requirements

1. OpenSSL libraries
   * Unix based operating systems: libcrypto
   * Windows:
       - Visual Studio 2008 Redistributables (see: [http://slproweb.com/products/Win32OpenSSL.html](http://slproweb.com/products/Win32OpenSSL.html))
       - OpenSSL library (see: [http://slproweb.com/products/Win32OpenSSL.html](http://slproweb.com/products/Win32OpenSSL.html))
2. Qt Library ([http://qt-project.org/downloads](http://qt-project.org/downloads))

### Build Instructions
Modify EncNotes.pro depending on the location of your libraries, architecture etc. Then either use Qt Creator or run

    qmake
    make
