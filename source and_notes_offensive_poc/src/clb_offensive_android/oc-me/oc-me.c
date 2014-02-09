/*
 * m0nk's general Copywrite: 
 *      For fun: Open Source & Free
 *      For profit: pay me 
 * m0nk's extended Copywrite:
 *      For better human good: Open Source & Free
 *      For evil or nefarious use: Pay me
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

char *program_name;


static void print_usage(FILE *stream, int exit_code)
{
	fprintf(stream, "Usage: %s [OPTIONS...]\n", program_name);
	fprintf(stream, "   OPTIONS\n");
	fprintf(stream, "      -o, --overclock        percentage of cpu overclock requested (from 0 to 100) (required)\n");
	fprintf(stream, "\nReport bugs to m0nk.\n");
	exit(exit_code);
}

static void oc_the_proc (double overclock_percentage)
{
	printf("Casbah rocked\n");
}

int main(int argc, char **argv) {
    printf("Hello world, I want to Overclock things\n");

	//argument variables
	int overclock_ok = 0;		// Just a flag
	int user_oc = 0;			// What the user supplies

	//get program name
	char *p = (char*)memrchr(argv[0], (unsigned int)'/', strlen(argv[0]));
	program_name = p==NULL ? argv[0] : (p+1);

	//parse arguments
	int next_option;
    int option_index = 0;
	
	//A string listing valid short options letters
	const char* short_options = "+o:";
	
	//An array describing valid long options
	const struct option long_options[] = {
		{ "overclock",  required_argument, NULL, 'o' },
		{ 0,            0,                 0,     0  }
	};

	do {
		next_option = getopt_long(argc, argv, short_options,long_options, &option_index);
		switch(next_option) {
			case 'o':
				user_oc = atoi(optarg);
				overclock_ok = 1;
				break;
			case 'h':
				print_usage(stdout, 1);
				break;
			case '?':
				print_usage(stderr, 1);
				break;
			case -1:
				break;
			default:
				abort();
		}
	} while(next_option != -1);

	
	if (!overclock_ok) {
		fprintf(stderr,"Error: You must specify a cpu overclock percentage\n");
		print_usage(stderr, 1);
		exit(1);
	}
	double overclock = user_oc / 100.0;
	if (overclock<0.0 || overclock>1.0) {
		fprintf(stderr,"Error: overclock percentage must be in the range 0-100\n");
		print_usage(stderr, 1);
		exit(1);
	}

	printf("You requested to overclock the system by %d percent \n", user_oc);

	oc_the_proc(overclock);


    return 0;
}

