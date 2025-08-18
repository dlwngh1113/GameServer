# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++20 -g -Wall

# 프로젝트 경로 설정
SERVER_SRC_DIR = ./Server
SERVER_BUILD_DIR = ./build/Server
COMMONLIB_SRC_DIR = ./CommonLib
COMMONLIB_BUILD_DIR = ./build/CommonLib
COMMON_INC_DIR = ./Common
BOOST_LIB_DIR = ../extlib/libx64/boost
BOOST_INC_DIR = ../extlib/include

# 공통 라이브러리 (CommonLib) 경로 및 이름
# DLL은 동적 링크 (예: Windows .dll, Linux .so)
COMMONLIB_NAME = CommonLib
COMMONLIB_LIB_PATH = $(COMMONLIB_BUILD_DIR)
COMMONLIB_LIB = -L$(COMMONLIB_LIB_PATH) -l$(COMMONLIB_NAME)

# 서버 프로젝트 소스 파일 목록
SERVER_SRCS = $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJS = $(patsubst $(SERVER_SRC_DIR)/%.cpp, $(SERVER_BUILD_DIR)/%.o, $(SERVER_SRCS))

# 공통 라이브러리 소스 파일 목록
COMMONLIB_SRCS = $(wildcard $(COMMONLIB_SRC_DIR)/*.cpp)
COMMONLIB_OBJS = $(patsubst $(COMMONLIB_SRC_DIR)/%.cpp, $(COMMONLIB_BUILD_DIR)/%.o, $(COMMONLIB_SRCS))

# 최종 실행 파일 이름
SERVER_TARGET = $(SERVER_BUILD_DIR)/Server
COMMONLIB_TARGET = $(COMMONLIB_BUILD_DIR)/lib$(COMMONLIB_NAME).dll

# 필요한 헤더 경로 설정 (Common과 CommonLib의 헤더 포함)
INCLUDES = -I$(SERVER_SRC_DIR) -I$(COMMON_INC_DIR) -I$(COMMONLIB_SRC_DIR) -I$(BOOST_INC_DIR)

# 링커 옵션 (Boost 라이브러리와 CommonLib 동적 링크)
LDFLAGS = -lboost_system -lboost_thread -lboost_chrono -lboost_date_time $(COMMONLIB_LIB) $(BOOST_LIB_DIR)

.PHONY: all clean

all: $(SERVER_TARGET)

# Server 프로젝트 빌드 규칙
$(SERVER_TARGET): $(SERVER_OBJS) $(COMMONLIB_TARGET)
	@mkdir -p $(@D)
	$(CXX) $(SERVER_OBJS) -o $@ $(LDFLAGS)

$(SERVER_BUILD_DIR)/%.o: $(SERVER_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# CommonLib 프로젝트 빌드 규칙 (DLL 생성)
$(COMMONLIB_TARGET): $(COMMONLIB_OBJS)
	@mkdir -p $(@D)
	$(CXX) -shared $(COMMONLIB_OBJS) -o $@

$(COMMONLIB_BUILD_DIR)/%.o: $(COMMONLIB_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -c $< -o $@

clean:
	rm -rf $(SERVER_BUILD_DIR) $(COMMONLIB_BUILD_DIR)