cmdcalc: main.o calc.o
	gcc main.o calc.o -o cmdcalc
main.o: main.c
	gcc -c main.c -o main.o
calc.o: calc.c
	gcc -c calc.c -o calc.o
clean:
	rm -f *.o main
run: cmdcalc
	@echo "Type an arguments for programm:"
	@read -p"Arguments: " args; \
	sh -c "./cmdcalc $$args"

