# Linux dir command- dirx

This project is a modified implementation of linux dir command in C.

Installation:

```sh
 # Clone this repository to a folder and navigate there
 make
 chmod -rwx ./dirx
 sudo mv ./dirx /bin/

```

Running the command:

```sh
# Show contents of the pwd
dirx

# Sorted file display
dirx -s name
dirx -s size
dirx -s date

# Reverse sorted
dirx -s name -r
dirx -s size -r
dirx -s date -r

# Recursive display: Shows the contents of the subfolder
dirx -R <further options>

# Display the contents as a tree (Recursive by default)
dirx -t <Sorting options>

# Display only particular filetypes (txt, c, pdf)
dirx <Options> -f __filetype__

```

This command uses the dirent.h file to get the directories and filenames.
The names are stored in a tree structure implemented using linked lists with a
next and a branch pointer.  
The files in any subfolder are stored in a branch from the main parent folder
tree.
