cmake_minimum_required(VERSION 3.15)
project(SPO_lab1_5 C)

set(CMAKE_C_STANDARD 99)

include_directories(SYSTEM ../wjelement-master/include)

add_executable(SPO_lab1_5
        main.c
        sql_lexical_analyzer/lex.yy.h sql_lexical_analyzer/lex.yy.c
        sql_grammar/y.tab.c sql_grammar/y.tab.h
        json/json_serialization_module.c json/json_serialization_module.h json/json_deserialization_module.c json/json_deserialization_module.h
        server/server_linux.c server/server_linux.h
        client/client_linux.h client/client_linux.c
        table_storage/storage.c table_storage/storage.h
        common/utils.c common/utils.h)


target_link_libraries(SPO_lab1_5 "/cygdrive/c/Users/Alena/CLionProjects/wjelement-master/cmake-build-debug/src/wjelement/libwjelement.dll.a")
target_link_libraries(SPO_lab1_5 "/cygdrive/c/Users/Alena/CLionProjects/wjelement-master/cmake-build-debug/src/wjreader/libwjreader.dll.a")
target_link_libraries(SPO_lab1_5 "/cygdrive/c/Users/Alena/CLionProjects/wjelement-master/cmake-build-debug/src/wjwriter/libwjwriter.dll.a")
target_link_libraries(SPO_lab1_5 "/cygdrive/c/Users/Alena/CLionProjects/wjelement-master/cmake-build-debug/src/lib/libxpl.dll.a")
target_link_libraries(SPO_lab1_5 "/cygdrive/c/Users/Alena/CLionProjects/wjelement-master/cmake-build-debug/src/lib/libxpl.dll.a")
target_link_libraries(SPO_lab1_5 "/lib/libcygwin.a")

