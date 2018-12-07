1. Unzip project folder

2. Use command 'make' to compile and create the executable

3. Run the program by typing "./plagiarismCatcher path/to/your/files <chunkNumber> <minimum collisions>
	>>> where path/to/your/files is the path to the directory of files you would like to use,
	>>> <chunkNumber> is the number of words considered in each chunk, and
	>>> <minimum collisions> is the minimum number of collisions for plagiarism to be flagged

Notes:
	<chunkNumber> should be greater than 0. (> 5 is prefered)
	<minimum collisions> is recommended to be greater than 100