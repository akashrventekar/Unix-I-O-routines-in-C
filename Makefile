#Create Object file
mycp: mycp.o
	gcc -o mycp mycp.o
#Create executable file
mycp.o: mycp.c
	gcc -c mycp.c
#Not enough arguments
run1: 
	./mycp
#Not enough arguments
run2:
	./mycp asd
#Source file does not exist
run3:
	./mycp creation J.txt
#Copy creation.txt to J.txt
run4: 
	./mycp creation.txt J.txt
#Overwrite J.txt
run5:
	./mycp printf.txt J.txt
#Source file and target file are the same
run6:
	./mycp creation.txt creation.txt
#Target directory does not exist
run7:
	./mycp creation.txt J.txt assdf
#Multiple file copy
run8:
	./mycp creation.txt J.txt J Creation a
#Permission denied
run9:
	./mycp creation.txt J.txt J Creation /usr
clean:
	rm *.o
