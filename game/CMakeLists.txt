# Create cluedo game library for cluedo-specific obects/methods
add_library(game
    src/tCard.cpp
    src/tDeck.cpp
    src/tGame.cpp
    )

target_include_directories(game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")