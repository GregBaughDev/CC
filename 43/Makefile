compile:
	@echo "Compile"
	@eval cc main.c $(pkg-config --libs --cflags raylib) -o tetris

clean:
	@echo "Clean"
	@${RM} ./tetris

run:
	@echo "Run"
	@./tetris