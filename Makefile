CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -O3 -fPIC -shared

CXXX_INCS = -I$(INC_DIR) -I$(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)

SRC_DIR = ./src
INC_DIR = ./include

POINT_SRC = $(SRC_DIR)/Point.cpp
POINT_TARGET = ./_point$(PYTHON_SUF)

.PHONY: test test_point clean

test: $(POINT_TARGET)
	python3 -m pytest

$(POINT_TARGET): $(POINT_SRC)
	$(CXX) $(CXX_FLAGS) $(CXXX_INCS) -o $@ $<

clean:
	rm -f $(POINT_TARGET)