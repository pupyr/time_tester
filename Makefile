rep:=100

all: run pyth

sum: run_sum pyth

run:
	cls
	g++ main.cpp time_tester.cpp -o app.exe -O0 -DREPEAT_SIZE=${rep} -DAVERAGE
	./app.exe

run_sum:
	cls
	g++ main.cpp time_tester.cpp -o app.exe -O0 -DREPEAT_SIZE=${rep}
	./app.exe

run_only:
	cls
	g++ main.cpp time_tester.cpp -o app.exe -O0 -DREPEAT_SIZE=${rep} -DAVERAGE
	./app.exe

pyth:
	python graph.py res.csv