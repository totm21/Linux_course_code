scoure:lib1.o lib2.o lib3.o scoure.o
	gcc lib1.o lib2.o lib3.o scoure.o -o scoure	
lib1.o:lib1.c lib.h
	gcc -c lib1.c -o lib1.o
lib2.o:lib2.c lib.h
	gcc -c lib2.c -o lib2.o
lib3.o:lib3.c lib.h
	gcc -c lib3.c -o lib3.o
scoure.o:scoure.c lib.h
	gcc -c scoure.c -o scoure.o
clean_o:
	rm *.o
clean_r:
	rm *.o scoure
clean:
	rm *.o scoure
.PHONY:clean_o clean clean_r