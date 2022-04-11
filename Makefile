#!bin/bash

GCC := gcc -Wall -Werror -Wextra -pedantic -std=gnu89
BETTY := ./scripts/betty

#
# Makefile
#

install:
	sudo apt install gcc -y
	git clone https://github.com/holbertonschool/Betty betty
	sudo sh ./betty/install.sh
	chmod u+x ./scripts/betty

linter:
	@$(BETTY) *.c
	@$(BETTY) *.h

tests:
	$(info Running the tests)

build:
	$(info Building the project...)
	$(GCC) *.c -o hsh
	$(info Build proccess terminated!)

clean:
	$(info Cleaning residuals files...)
	@rm *.o
	@rm hsh
	$(info Cleaning proccess terminated!)