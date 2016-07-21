/**
 *
 * @author Akash Rajendra Ventekar
 * Class: CS-590
 * Date: 6/24/2016
 * C program to	copy files using the file I/O routines on Linux.
 */

//Header files
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFSIZE 4096

int main(int argc, char* argv[])
{
	//Declaration section
	int i, n, fd, fd1;	
	char choice;
	char buf[BUFFSIZE];
	char path[BUFFSIZE];
	
	//Exception handling for arguments less than 3. Show usage
	if(argc < 3)
	{
		printf("Error: Usage: ./mycp <source-file> <Target-file-or-dir> OR <source-files> <Target-dir>\n");
		return 1;
	}
	
	//We can also use Macro: S_ISDIR()
	/*if (lstat(argv[argc-1], &buf) < 0) {
                        err_ret("lstat error");
                        continue;
                }
                if (S_ISDIR(buf.st_mode))
                        ptr = "directory";
	*/
	//Requirement 1:  Copy one file(sourceFile) to another(targetFile)
	if(open(argv[argc - 1],O_DIRECTORY) < 0 && argc == 3)	//If the last argument is not a directory and arguments are 3
	{
		//Exception handling 1.3: Compare if the filenames are the same
		if(strcmp(argv[1],argv[2]) == 0)
		{
			printf("Error: Source file and target file are the same\n");
			return 1;
		}
		
		fd = open(argv[1],O_RDONLY);	//Open first file in read only mode
		
		//We can also use F_OK to check if file exists. Check if file exists
                if(fd < 0){		//Exception handling 1.1: If the file does not exist
                       printf("Error: Source file \"%s\" does not exist\n", argv[1]);
                       return 1;
                }
                
		fd1=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRWXU | S_IRGRP | S_IROTH);	//Exception handling 1.2: Check if the file already exists using O_EXCL
                if(fd1 < 0 )		//If file exists then warn the user for overwriting
                {
                	printf("The file %s already exists.Do you want to overwrite the file (y or n?)\n", argv[2]);
                        fflush(stdin);
                        scanf("%c", &choice);
                        getchar();
                        if(choice == 'y')
                        {
                        	fd1=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , S_IRWXU | S_IRGRP | S_IROTH);	//Truncate the file and create the file
                        }
                        else
                        	return 0;
                        }
			//Read from source file and write to the destination file
                        while ((n = read(fd, buf, BUFFSIZE)) > 0) {	
                                if (write(fd1, buf, n) != n)
                                	printf("Error: Write error\n");
                        }
                        if (n < 0)
                                printf("Error: Read error\n");
                        printf("Copied %s to %s\n", argv[1], argv[2]);

	}
	//Exception handling 2.2: If directory does not exist, throw an error
	else if(open(argv[argc - 1],O_DIRECTORY) < 0)
        {
                printf("Error: Target directory does not exist\n");
		return 1;
        }
	//Copy multiple files (file1,	file2,	...) to the target directory(targetDir)
	else
	{
		//Exception handling 1.4 and 2.3: Check	to see if the user has permissions to write to the target directory.Check write and execute access on the directory
		if (access(argv[argc - 1],W_OK) < 0 || access(argv[argc - 1],X_OK) < 0 ){
                        printf("Do not have permissions to copy into the directory: %s. Permission denied!\n", argv[argc-1]);
                        return 1;
                }
		for(i = 1;i < argc - 1; i++)
		{
			//Create the full  path
			strcpy(path, argv[argc - 1]);
			strcat(path,"/");
			strcat(path,argv[i]);
			
			fd = open(argv[i],O_RDONLY) ;	//Open first file in read only mode
	                //We can also use F_OK to check if file exists. 
			if(fd < 0){	//Exception handling 2.1: If the file does not exist
				printf("Error: Source file %s does not exist\n", argv[i]);
				continue;
			}
			fd1=open(path, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRWXU | S_IRGRP | S_IROTH);		//Check if the file already exists using O_EXCL
			if(fd1 < 0 )	//If file exists then warn the user for overwriting
			{
				printf("The file %s already exists.Do you want to overwrite the file (y or n?)\n", argv[i]);
				fflush(stdin);
				scanf("%c", &choice);
				getchar();
				if(choice == 'y')
				{
					 fd1=open(path, O_WRONLY | O_CREAT | O_TRUNC , S_IRWXU | S_IRGRP | S_IROTH);	//Truncate the file and create the file
				}
				else
					continue;
			}
			//Read from source file and write to the destination file
			while ((n = read(fd, buf, BUFFSIZE)) > 0) {
				if (write(fd1, buf, n) != n)
					printf("Error: Write error\n");
			}
			if (n < 0)
				printf("Error: Read error\n");
			printf("Copied %s to %s\n", argv[i], path);
			memset(&path[0], 0, sizeof(path));	//Clear the character array
			close(fd);	//Close source file
			close(fd1);	//Close destination file
		}
	}	
	return 0;
}
