A real time audio signal processing tool for speech human analysis. Features:

* Echo analysis.
* Equalization.
* Filtering.
* Pitch Estimation.
* PSD.
* Energy
* Avarage Zero Crossing Rate
* Fundamental Frequency Estimation with different algorithms.
* FFT Spectrogram.
* LPC Spectrum.
* Cepstrum.

#COMPILATION

On Linux, download the repository and exec install_dependencies_linux.sh  to download all required libraries.

To compile use Qt Version > 5.0. Compatible with MinGW (Windows), Clang (MAC OS) ang GCC (Linux). 

How to install Aquila?

- Install CMake
- git clone git://github.com/zsiciarz/aquila.git aquila-src
- mkdir build
- cd build
- cmake ..\aquila-src -G "MinGW Makefiles"
- mingw32-make
- mingw32-make install
- Go to: C:\Program Files (x86)\Aquila

How to install Portaudio?
	
- Download Mingw
- Install Msys
- Add directory to system path
- msys (open Msys terminal)
- cd directory
- ./configure
- make

Info: https://www.assembla.com/wiki/show/portaudio/Notes_about_building_PortAudio_with_MinGW

How to install Qwt on Mac?
Go: http://stackoverflow.com/questions/18588418/install-and-use-qwt-under-mac-os-x

How to install PortAudio on mac x64? Download precompiled binaries.
https://github.com/spatialaudio/portaudio-binaries
Copy framework:
cp -R  qwt.framework /System/Library/
cp -R  qwt.framework /Library/Frameworks/
