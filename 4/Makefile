ifeq ($(strip $(delim)), )
	delim = 't'
endif

compile:
	@echo "compile"
	@gcc 4.c -o 4

clean:
	@echo "clean"
	@${RM} ./4

run:
	@echo "run"
	@./4 -f$(field) -d$(delim) $(file)