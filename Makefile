rep:=10
metr:=AVERAGE
def:=
ifeq ($(metr), AVERAGE)
	def += -DAVERAGE
endif

all: run_silent pyth

sum: run_sum pyth

run:
	cls
	g++ main.cpp time_tester.cpp -o app.exe -O0 -DREPEAT_SIZE=${rep} ${def}
	./app.exe

run_only:
	cls
	g++ main.cpp time_tester.cpp -o app.exe -O0 -DREPEAT_SIZE=${rep} ${def}
	./app.exe

run_silent:
	g++ main.cpp time_tester.cpp -o app.exe -O0 -DREPEAT_SIZE=${rep} ${def} -DSILENT
	./app.exe
	
pyth:
	python graph.py res.csv

