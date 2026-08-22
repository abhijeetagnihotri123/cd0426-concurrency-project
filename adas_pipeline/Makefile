CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
SRC_INC = include
OBJ_DIR = obj
BIN_DIR = build

TARGET = $(BIN_DIR)/ADAS_SIMULATOR

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

$(info all cpp files are : $(SRCS))
$(info all object files are : $(OBJS))

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)