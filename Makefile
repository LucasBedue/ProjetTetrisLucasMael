all : exec

main.o : main.c header.h
	gcc -c main.c -o main.o

fonctions.o : fonctions.c header.h
	gcc -c fonctions.c -o fonctions.o

tetristour.o : tetristour.c header.h
	gcc -c tetristour.c -o tetristour.o

exec : main.o fonctions.o tetristour.o
	gcc $^ -o $@