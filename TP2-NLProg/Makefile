all: clean main1 runmain1 main2 runmain2


# COMPILAÇÃO DAS MAINS #
main1: objetos/main1.o objetos/palavras.o objetos/documentos.o objetos/dados.o objetos/idx.o objetos/arquivos.o
	gcc -o main1 objetos/main1.o objetos/palavras.o objetos/documentos.o objetos/dados.o objetos/idx.o objetos/arquivos.o -lm
	@echo
	@echo Programa 1 compilado! Nome do arquivo executavel: main1
	@echo

main2: objetos/main2.o objetos/palavras.o objetos/documentos.o objetos/dados.o objetos/classes.o objetos/idx.o objetos/arquivos.o objetos/menu.o
	gcc -o main2 objetos/main2.o objetos/palavras.o objetos/documentos.o objetos/dados.o objetos/classes.o objetos/idx.o objetos/arquivos.o objetos/menu.o -lm
	@echo
	@echo Programa 2 compilado! Nome do arquivo executavel: main2
	@echo

main3: objetos/main3.o objetos/palavras.o objetos/documentos.o objetos/dados.o objetos/classes.o objetos/idx.o objetos/arquivos.o objetos/menu.o
	gcc -o main3 objetos/main3.o objetos/palavras.o objetos/documentos.o objetos/dados.o objetos/classes.o objetos/idx.o objetos/arquivos.o objetos/menu.o -lm
	@echo
	@echo Programa 3 compilado! Nome do arquivo executavel: main3
	@echo

# COMPILAÇÃO DOS ARQUIVOS .o #
objetos/main1.o: P1_main.c headers/palavras.h headers/documentos.h headers/dados.h headers/idx.h headers/arquivos.h
	gcc -o objetos/main1.o P1_main.c -c -Wall

objetos/main2.o: P2_main.c headers/palavras.h headers/documentos.h headers/dados.h headers/classes.h headers/idx.h headers/arquivos.h headers/menu.h
	gcc -o objetos/main2.o P2_main.c -c -Wall

objetos/main3.o: P3_main.c headers/palavras.h headers/documentos.h headers/dados.h headers/classes.h headers/idx.h headers/arquivos.h headers/menu.h
	gcc -o objetos/main3.o P3_main.c -c -Wall

objetos/palavras.o: sources/palavras.c headers/palavras.h
	gcc -o objetos/palavras.o sources/palavras.c -c -Wall

objetos/documentos.o: sources/documentos.c headers/documentos.h
	gcc -o objetos/documentos.o sources/documentos.c -c -Wall

objetos/dados.o: sources/dados.c headers/dados.h
	gcc -o objetos/dados.o sources/dados.c -c -Wall

objetos/classes.o: sources/classes.c headers/classes.h
	gcc -o objetos/classes.o sources/classes.c -c -Wall

objetos/idx.o: sources/idx.c headers/idx.h
	gcc -o objetos/idx.o sources/idx.c -c -Wall

objetos/arquivos.o: sources/arquivos.c headers/arquivos.h
	gcc -o objetos/arquivos.o sources/arquivos.c -c -Wall

objetos/menu.o: sources/menu.c headers/menu.h
	gcc -o objetos/menu.o sources/menu.c -c -Wall


# RODANDO CADA MAIN
runmain1: main1
	./main1 datasets/medium-small/train.txt haha.bin
	@echo Resposta pronta!
	@echo

runmain2: main2
	./main2 haha.bin 5
	@echo Resposta pronta!
	@echo


# VALGRIND PARA MAIN 2 #
val: main2
	valgrind ./main2 haha.bin 5 >resp.txt

valplus: main2
	valgrind --leak-check=full --show-leak-kinds=all ./main2 haha.bin 5 >resp.txt

valerror: main2
	valgrind -s ./main2 haha.bin 5 >resp.txt


# CODIGOS TOPS #
org: clean
	mkdir sources
	mkdir headers
	mkdir objetos

	mv *.c sources/
	mv *.h headers/
	mv sources/P1_main.c sources/..
	mv sources/P2_main.c sources/..

	@echo Organizado!
	@echo

clean:
	rm -rf objetos/*.o *~ main1 main2
