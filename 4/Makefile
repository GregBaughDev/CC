compile:
	@echo "compile"
	@gcc 4.c functions.c -o 4

clean:
	@echo "clean"
	@${RM} ./4

run:
	@echo "run"
	@./4 -f$(field) $(if $(delim), -d$(delim)) $(file)