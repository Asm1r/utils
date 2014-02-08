/*
 * =====================================================================================
 *
 *       Filename:  brset.c
 *
 *    Description:  Small util to manipulate screen brightness on ASUS eeepc X101CH.
 *
 *        Version:  1.0
 *        Created:  05/06/2013 05:37:47 PM
 *       Revision:  none
 *       Compiler:  musl-gcc
 *
 *         Author:  Asmir Abdulahovic 
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>
#include	<errno.h>
#include	<string.h>

#define		FILE_NAME "/sys/class/backlight/psb-bl/brightness"	
#define		INCREMENT 5

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_help
 *  Description:  if an error is occured user stderr for stream, otherwise use stdout
 * =====================================================================================
 */
void
print_help ( FILE *stream )
{
    fprintf(stream, "Usage brset:\n\
	    \t -d <value>\tDecrement by value.\n\
	    \t -i <value>\tIncrement by value.\n\
	    \t <value>\tSet value.\n\
	    \t -h\t\tPrint help.\n");
}		/* -----  end of function print_help  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int
main ( int argc, char *argv[] )
{
    int value, new_value, increment=0;
    FILE	*fp;					/* input/output-file pointer */
    char	*fp_file_name = FILE_NAME;		/* input/output-file name    */

    if(argc > 2){
	print_help(stderr);
	return EXIT_FAILURE;
    }

    if(argv[1][0]=='-'){
	switch ( argv[1][1] ) {
	    case 'd':	
		increment=INCREMENT*(-1);
		break;

	    case 'i':	
		increment=INCREMENT;
		break;

	    case 'h':	
		print_help(stdout);
		return EXIT_SUCCESS;
		break;

	    default:	
		print_help(stderr);
		return EXIT_SUCCESS;
		break;
	}				/* -----  end switch  ----- */
    }

    if(argc==2){
	new_value=atoi(argv[1]);
    }
    
    fp	= fopen( fp_file_name, "r+" );
    if ( fp == NULL ) {
	fprintf ( stderr, "couldn't open file '%s'; %s\n",
		fp_file_name, strerror(errno) );
	exit (EXIT_FAILURE);
    }

    if(increment){
	fscanf(fp,"%d", &value);
	new_value = value+increment;
    }

    fprintf(fp, "%d", new_value);
   
    if( fclose(fp) == EOF ) {			/* close input file   */
	fprintf ( stderr, "couldn't close file '%s'; %s\n",
		fp_file_name, strerror(errno) );
	exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
