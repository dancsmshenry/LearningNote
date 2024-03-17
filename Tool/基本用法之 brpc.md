```shell
# brpc 的编译
sudo apt-get install protobuf-compiler
sudo apt install libleveldb-dev
sudo apt-get install -y git g++ make libssl-dev libgflags-dev libprotobuf-dev libprotoc-dev
sudo apt-get install -y libsnappy-dev

cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

