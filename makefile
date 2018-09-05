init : init.c
		gcc -c init init.c

getty : getty.c
		gcc -c getty getty.c 
sh : sh
		gcc -c sh sh.c 


clean :
	rm    init getty sh