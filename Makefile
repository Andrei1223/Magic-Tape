NUME:="banda"
NUMEFIS:="tema1"

build:
	touch $(NUMEFIS).out
	gcc -o $(NUMEFIS) -Wall $(NUME).c
	
run:
	./$(NUMEFIS)

clean:
	rm $(NUMEFIS)