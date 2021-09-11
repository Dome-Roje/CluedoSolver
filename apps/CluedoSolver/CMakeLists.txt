add_executable(CluedoSolver
    main.cpp)
target_compile_features(CluedoSolver PRIVATE cxx_std_17)

target_link_libraries(CluedoSolver LINK_PUBLIC game)