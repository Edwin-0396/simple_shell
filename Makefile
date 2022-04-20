#!bin/bash

GCC := gcc -Wall -Werror -Wextra -pedantic -std=gnu89
BETTY := ./scripts/betty
OUTPUT := hsh

#
# Makefile
#

valgrind:
	@echo "Compilling for valgrind..."
	@gcc -g -O0 *.c -o hsh
	@echo "Compiled!"
	
	@echo "Running valgrind..."
	@valgrind --leak-check=full --track-origins=yes --tool=memcheck ./$(OUTPUT)

install:
	@echo "Installing gcc and valgrind..."
	@sudo apt install gcc valgrind -y
	@echo "gcc and valgrind installed!"

	@echo "Cloning and installing Betty..."
	@git clone https://github.com/holbertonschool/Betty betty
	@sudo sh ./betty/install.sh
	@chmod u+x ./scripts/betty
	@echo "Betty installed!"

linter:
	@echo "Executing linter..."
	@$(BETTY) *.c
	@$(BETTY) *.h
	@echo "Linter finished!"

build:
	@echo "Building the project..."
	@$(GCC) *.c -o hsh
	@echo "Build proccess terminated!"

clean:
	@echo "Cleaning residuals files..."
	@rm *.o
	@rm $(OUTPUT)
	@echo "Cleaning proccess terminated!"