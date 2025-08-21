# 컴파일러 설정
# C++ 컴파일러 및 플래그 설정
CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -fPIC

# 프로젝트 경로 설정
# 소스, 빌드 및 라이브러리 경로
SERVER_SRC_DIR = ./Server
SERVER_BUILD_DIR = ./build/Server
COMMONLIB_SRC_DIR = ./CommonLib
COMMONLIB_BUILD_DIR = ./build/CommonLib
COMMON_INC_DIR = ./Common
BOOST_LIB_DIR = ../extlib/libx64
BOOST_INC_DIR = ../extlib/include

# 공통 라이브러리 (CommonLib) 경로 및 이름
# 동적 라이브러리(.so) 경로와 이름
COMMONLIB_NAME = CommonLib
COMMONLIB_LIB = -L$(COMMONLIB_BUILD_DIR) -l$(COMMONLIB_NAME)

# 소스 파일 및 객체 파일 목록
# 소스 파일과 빌드될 객체 파일 목록 생성
SERVER_SRCS = $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJS = $(patsubst $(SERVER_SRC_DIR)/%.cpp, $(SERVER_BUILD_DIR)/%.o, $(SERVER_SRCS))
COMMONLIB_SRCS = $(wildcard $(COMMONLIB_SRC_DIR)/*.cpp)
COMMONLIB_OBJS = $(patsubst $(COMMONLIB_SRC_DIR)/%.cpp, $(COMMONLIB_BUILD_DIR)/%.o, $(COMMONLIB_SRCS))

# 최종 실행 파일 이름
# 서버 실행 파일 및 공통 라이브러리 이름
SERVER_TARGET = $(SERVER_BUILD_DIR)/Server
COMMONLIB_TARGET = $(COMMONLIB_BUILD_DIR)/lib$(COMMONLIB_NAME).so

# 필요한 헤더 경로 설정
# 헤더 파일 경로 목록
INCLUDES = -I$(SERVER_SRC_DIR) -I$(COMMON_INC_DIR) -I$(COMMONLIB_SRC_DIR) -I$(BOOST_INC_DIR)

# 링커 옵션
# Boost 라이브러리 링크 및 공통 라이브러리 링크
LDFLAGS = -L$(BOOST_LIB_DIR) -lmysqlcppconn -lpthread $(COMMONLIB_LIB)

# 설치 경로 설정 (예: /usr/local/lib)
INSTALL_LIB_DIR = /usr/local/lib

.PHONY: all clean install

all: $(SERVER_TARGET)

# Server 프로젝트 빌드 규칙
# 서버 실행 파일 빌드
$(SERVER_TARGET): $(SERVER_OBJS) $(COMMONLIB_TARGET)
	@mkdir -p $(@D)
	$(CXX) $(SERVER_OBJS) -o $@ $(LDFLAGS)

$(SERVER_BUILD_DIR)/%.o: $(SERVER_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# CommonLib 프로젝트 빌드 규칙 (공유 라이브러리 생성)
# 공유 라이브러리(.so) 빌드
$(COMMONLIB_TARGET): $(COMMONLIB_OBJS)
	@mkdir -p $(@D)
	$(CXX) -shared $(COMMONLIB_OBJS) -o $@

$(COMMONLIB_BUILD_DIR)/%.o: $(COMMONLIB_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -DCOMMON_LIB_EXPORTS $(CXXFLAGS) $(INCLUDES) -c $< -o $@

	# 설치 규칙
# 빌드된 공유 라이브러리를 지정된 경로에 복사
install: $(COMMONLIB_TARGET)
	@mkdir -p $(INSTALL_LIB_DIR)
	@cp $< $(INSTALL_LIB_DIR)/
	@echo "Copied $< to $(INSTALL_LIB_DIR)/"

# 모든 빌드 파일 삭제
clean:
	@rm -rf $(SERVER_BUILD_DIR)
	@rm -rf $(COMMONLIB_BUILD_DIR)

