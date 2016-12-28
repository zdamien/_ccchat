tSQ: syn_queue.h tSQ.cc
	g++ -l pthread tSQ.cc -o tSQ  

clean:
	rm a.out tSQ ccchat
