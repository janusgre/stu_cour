export LD_LIBRARY_PATH=`pwd`/lib:$LD_LIBRARY_PATH
make clean
make
touch ms.log
make clean
