write:shmwrite.c shm_me.h read del
	gcc -o write shmwrite.c

read:shmread.c shm_me.h
	gcc -o read shmread.c
	
del:shmdel.c shm_me.h 
	gcc -o del shmdel.c

clean:
	rm write read del

.PHONY:clean
