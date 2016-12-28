tSQ: syn_queue.cc syn_queue.h tSQ.cc
	g++ -l pthread -c syn_queue.cc
	g++ -l pthread syn_queue.o tSQ.cc -o tSQ  
