# Environment
download libtorch at [libtorch](https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-2.3.1%2Bcpu.zip)
and unzip at ```UGRP_apply_NN_to_Robot/```

You have to change file path in ```read.cpp```
```
int main() {
    
    torch::jit::script::Module module;
    module = torch::jit::load("/home/dohyeon/UGRP_apply_NN_to_Robot/model/model_dataset4.pt"); // you have to change path to fit your environment
...
...
```

# build
```
cd build
cmake ..
make
```
