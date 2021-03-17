all:
	gcc main.c -l lexbor-html \
		   -l curl \
		   -o alternativeto
