include_directories(include)

add_executable(Kipp
        BitInputStream.cpp
        BitOutputStream.cpp
        HuffTree.cpp
        main.cpp
        Chr.cpp
        Compression.cpp
        ${PROJECT_SOURCE_DIR}/include/BitInputStream.h
        ${PROJECT_SOURCE_DIR}/include/BitOutputStream.h
        ${PROJECT_SOURCE_DIR}/include/Chr.h
        ${PROJECT_SOURCE_DIR}/include/common.h
        ${PROJECT_SOURCE_DIR}/include/Compression.h
        ${PROJECT_SOURCE_DIR}/include/HuffTree.h
 )
