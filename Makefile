CXX		  := gcc
CXX_FLAGS := -Wall -Wextra -std=c17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
TEST    := test

LIBRARIES	:= -ljansson -lm
EXECUTABLE	:= range
TEST_EXECUTABLE := test_range

JANSSON_VERSION := 2.13.1
JANSSON_DIR := jansson-$(JANSSON_VERSION)
JANSSON_TAR := $(JANSSON_DIR).tar.gz
JANSSON_URL := https://github.com/akheron/jansson/releases/download/v$(JANSSON_VERSION)/$(JANSSON_TAR)

all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

dependencies:
	@echo "Baixando Jansson $(JANSSON_VERSION)..."
	@wget $(JANSSON_URL)
	@tar -xvf $(JANSSON_TAR)
	@rm $(JANSSON_TAR)
	@cd $(JANSSON_DIR) && ./configure && make && make check && sudo make install
	@echo "Jansson $(JANSSON_VERSION) instalado com sucesso!"
	@rm -rf $(JANSSON_DIR)

test: $(BIN)/$(TEST_EXECUTABLE)
	./$(BIN)/$(TEST_EXECUTABLE)

$(BIN)/$(TEST_EXECUTABLE): $(filter-out $(SRC)/main.c, $(wildcard $(SRC)/*.c)) $(wildcard $(TEST)/*.c)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)
	-mkdir $(BIN)