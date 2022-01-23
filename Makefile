dircmd: main.o dir_entry.o linked_list.o
	gcc -g main.o dir_entry.o linked_list.o -o dircmd

main.o: main.c
	gcc -c -g main.c

dir_entry.o: dir_entry.c
	gcc -c -g dir_entry.c

linked_list.o: linked_list.c
	gcc -c -g linked_list.c


clean:
	-rm *.o
	-rm dircmd
