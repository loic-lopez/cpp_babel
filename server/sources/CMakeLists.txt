FILE (GLOB SRC_DATABASE Database/*.cpp ../include/Database/*.hpp)

FILE (GLOB SRC_NETWORK Network/*.cpp ../include/Network/*.hpp)

FILE (GLOB SRC_SERVER Server/*.cpp ../include/Server/*.hpp)

FILE (GLOB SRC_PROTOCOL ../include/Protocol/*.hpp ../include/Plugin/*.hpp)

target_sources(${TARGET_BABEL_NAME} PUBLIC ${SRC_DATABASE} ${SRC_NETWORK} ${SRC_SERVER} ${SRC_PROTOCOL})