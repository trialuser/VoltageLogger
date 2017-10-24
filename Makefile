all:
	g++ main.cpp -o monitor -lnutclient
	
test:
	g++ test.cpp -o test -lnutclient
clean:
	rm monitor test
