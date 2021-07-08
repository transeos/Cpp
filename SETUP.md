# How to Setup #

# prerequisites
sudo apt-get install cmake
sudo apt-get install clang
sudo apt install libtbb-dev
sudo apt install g++-10

# copy hook
cp hook/pre-commit .git/hooks

# go inside cpp directories
mkdir build
cd build
cmake ..
make

# Now you'll have cpp unit tests
