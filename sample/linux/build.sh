#!/bin/bash

function clean() {
    echo "clean project"
    rm -rf build
}

function build() {
    echo "build project"
    cmake -B build -G "Unix Makefiles"
    make -C build -j 20

    awk '
    function convert_size(size) {
        if (size >= 1073741824) {
            return sprintf("%.2f GB", size / 1073741824);
        } else if (size >= 1048576) {
            return sprintf("%.2f MB", size / 1048576);
        } else if (size >= 1024) {
            return sprintf("%.2f KB", size / 1024);
        } else {
            return sprintf("%d bytes", size);
        }
    }

    {
        # 将十六进制的大小转换为十进制
        size = strtonum($3)

        # 累加 .text 和 .rodata 段到 Flash
        if ($1 == ".text" && !seen[".text"]++) {
            flash_size += size;
            printf "%s\t Address: %s\t Size: %s (%s)\n", $1, $2, $3, convert_size(size);
        }
        if ($1 == ".rodata" && !seen[".rodata"]++) {
            flash_size += size;
            printf "%s\t Address: %s\t Size: %s (%s)\n", $1, $2, $3, convert_size(size);
        }

        # .data 段既占用 Flash(用于存储初始值),又占用 RAM
        if ($1 == ".data" && !seen[".data"]++) {
            flash_size += size;
            ram_size += size;
            printf "%s\t Address: %s\t Size: %s (%s)\n", $1, $2, $3, convert_size(size);
        }

        # 累加 .bss 段到 RAM
        if ($1 == ".bss" && !seen[".bss"]++) {
            ram_size += size;
            printf "%s\t Address: %s\t Size: %s (%s)\n", $1, $2, $3, convert_size(size);
        }

    }
    END {
        # 使用 convert_size 函数将字节数转换为合适的单位
        printf "Flash\t usage: %s\n", convert_size(flash_size);
        printf "RAM\t usage: %s\n", convert_size(ram_size);
    }' "./build/output.map"
}

function buildcpp() {
    echo "build project"
    cmake -B build -G "Unix Makefiles" -DUSE_MAKE=cpp
    make -C build -j 20
}

function exe() {
    ./build/output/lilos_sample
}

if [[ "$1" == "-all" ]]; then
    clean
    if [[ "$2" == "-cpp" ]]; then
        buildcpp
    else
        build
    fi

elif [[ "$1" == "-clean" ]]; then
    clean

elif [[ "$1" == "-exe" ]]; then
    if [[ "$2" == "-cpp" ]]; then
        buildcpp
    else
        build
    fi
    exe
    
elif [[ "$1" == "-cpp" ]]; then
    buildcpp
    if [[ "$2" == "-exe" ]]; then
        exe
    fi
else
    build
fi
