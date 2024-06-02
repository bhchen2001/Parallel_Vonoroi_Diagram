CXX = g++
CXX_FLAGS = -std=c++11 -Wall -Wextra -Werror -O3 -fPIC -shared

CXXX_INCS = -I$(INC_DIR) -I$(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)

SRC_DIR = ./src
INC_DIR = ./include

POINT_SRC = $(SRC_DIR)/Point.cpp
POINT_TARGET = ./_point$(PYTHON_SUF)

KDNODE_SRC = $(SRC_DIR)/KDNode.cpp
KDNODE_TARGET = ./_kdnode$(PYTHON_SUF)

RECT_SRC = $(SRC_DIR)/Rectangle.cpp
RECT_TARGET = ./_rectangle$(PYTHON_SUF)

KDTREE_SRC = $(SRC_DIR)/KDTree.cpp
KDTREE_TARGET = ./_kdtree$(PYTHON_SUF)

.PHONY: all test clean

all: $(POINT_TARGET) $(KDNODE_TARGET) $(RECT_TARGET) $(KDTREE_TARGET)

test: $(POINT_TARGET) $(KDNODE_TARGET) $(RECT_TARGET) $(KDTREE_TARGET)
	python3 -m pytest -vv

$(POINT_TARGET): $(POINT_SRC)
	$(CXX) $(CXX_FLAGS) $(CXXX_INCS) -o $@ $<

$(KDNODE_TARGET): $(KDNODE_SRC)
	$(CXX) $(CXX_FLAGS) $(CXXX_INCS) -o $@ $<

$(RECT_TARGET): $(RECT_SRC)
	$(CXX) $(CXX_FLAGS) $(CXXX_INCS) -o $@ $<

$(KDTREE_TARGET): $(KDTREE_SRC)
	$(CXX) $(CXX_FLAGS) $(CXXX_INCS) -o $@ $<

clean:
	rm -f $(POINT_TARGET) $(KDNODE_TARGET) $(RECT_TARGET) $(KDTREE_TARGET)