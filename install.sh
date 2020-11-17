sudo apt-get update && sudo apt-get -y install build-essential
sudo apt -y install cmake

## build
mkdir out

cd Program2
cmake .
make 
ctest -V
cp ./src/Program2 ../out

cd ../Program1
cmake .
make
cp Program1 ../out

cd ../out
cp ../cmd.txt .

adduser testusr --disabled-password --no-create-home -gecos ""
passwd -d testusr
