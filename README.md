CGProject - Image Studio
===

## Instruções de Compilação

### Dependências
- CMake 3.10 ou superior
- Compilador para C++ (com suporte a C++17)
- SDL 2.0.9 (http://libsdl.org)
- OpenMP
- Boost 1.70.0 (https://www.boost.org)


### Instruções
- Clone o repositório (ou faça o download to ZIP)
    ```bash
    git clone https://github.com/DCubix/CGProject
    ```
- Inicialize os submódulos do projeto (para clonar o repositório da GUI)
    ```bash
    cd CGProject
    git submodule update --init
    ```

- Compile o projeto
    ```bash
    mkdir build
    cd build
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    make -j4
    ```

- Para executar: `./imgstudio`