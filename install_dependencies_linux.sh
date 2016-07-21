echo "Installing dependencies..."
apt-get update
echo "Creating temp folder "
mkdir temp
cd temp
echo "Downloading Qt..."
sudo apt-get install libglu1-mesa-dev
echo "Downloading build essential..."
apt-get install build-essential
echo "Downloading cmake"
apt-get install cmake
echo "Downloading fftw..."
apt-get install libfftw3-dev
echo "Downloading portaudio..."
apt-get install portaudio19-dev 
echo "Download dependencies por essentia lib..."
apt-get install build-essential libyaml-dev libfftw3-dev libavcodec-dev libavformat-dev libavutil-dev libavresample-dev python-dev libsamplerate0-dev libtag1-dev
sudo apt-get install python-numpy-dev python-numpy python-yaml
echo "Download release..."
git clone https://github.com/MTG/essentia.git
cd ./essentia
echo "Installing release..."
./waf configure --mode=release --with-python --with-cpptests --with-examples --with-vamp 
./waf
./waf install
echo "Installing boost..."
sudo apt-get install libboost-all-dev
echo "Download aquila..."
cd ./../
git clone git://github.com/zsiciarz/aquila.git aquila-src
cd ./aquila-src 
cmake .
make
make install
echo "Downloading Qwt lib..."
cd ./../
wget http://liquidtelecom.dl.sourceforge.net/project/qwt/qwt/6.1.2/qwt-6.1.2.zip -P .
unzip qwt-6.1.2.zip -d .
cd qwt-6.1.2
/opt/Qt5.5.1/5.5/gcc_64/bin/qmake qwt.pro
make
make install

