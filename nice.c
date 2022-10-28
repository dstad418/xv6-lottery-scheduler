

#include "types.h"
#include "user.h"


int
main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf(1, "Incorrect arguement\n");
        exit();
    }

    //The command/program renice takes a new nice value as argv[1] and applies that to all the pids following on the command line. See the image below.
    renice(atoi(argv[1]), getpid());

    // It should first set its own nice value (using renice()) and then exec() the program on the command line, in argv[2].
    exec(argv[2], (&(argv[2])));
    
    exit();
}
