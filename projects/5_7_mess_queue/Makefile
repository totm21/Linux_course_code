all:creat write read del

creat:msgcreat.c msg_me.h 
	gcc -o creat msgcreat.c

write:msgwrite.c msg_me.h
	gcc -o write msgwrite.c

read:msgread.c msg_me.h
	gcc -o read msgread.c
	
del:msgdel.c msg_me.h
	gcc -o del msgdel.c
	

clean:
	rm creat write read del

.PHONY:clean