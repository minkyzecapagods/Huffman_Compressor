# Compiler and flags
CXX := g++
LDFLAGS :=
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Frequency Counter settings
FC_TARGET := frequency_counter
FC_SRC_DIR = Frequency_Counter/src
FC_BUILD_DIR = Frequency_Counter/build

FC_SRCS := $(shell find $(FC_SRC_DIR) -name '*.cpp')
FC_OBJS := $(patsubst $(FC_SRC_DIR)/%.cpp,$(FC_BUILD_DIR)/%.o,$(FC_SRCS))
FC_DEPS := $(FC_OBJS:.o=.d)

# Compressor Decompressor settings
CD_TARGET := compressor_decompressor
CD_SRC_DIR = Compressor_Decompressor/src
CD_BUILD_DIR = Compressor_Decompressor/build

CD_SRCS := $(shell find $(CD_SRC_DIR) -name '*.cpp')
CD_OBJS := $(patsubst $(CD_SRC_DIR)/%.cpp,$(CD_BUILD_DIR)/%.o,$(CD_SRCS))
CD_DEPS := $(CD_OBJS:.o=.d)

# Default target (build both)
all: $(FC_TARGET) $(CD_TARGET)

# Build Frequency Counter
$(FC_TARGET): $(FC_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(FC_BUILD_DIR)/%.o: $(FC_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(FC_DEPS)

# Build Compressor Decompressor
$(CD_TARGET): $(CD_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CD_BUILD_DIR)/%.o: $(CD_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(CD_DEPS)

clean: 
	rm -rf $(FC_BUILD_DIR) $(FC_TARGET) $(CD_BUILD_DIR) $(CD_TARGET)

.PHONY: all clean run