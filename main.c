#define LSH_RL_BUFSIZE = 1024;
#include <stdio.h>;

void lsh_loop(void);
char *lsh_read_line(void);
int main(int argc, char **argv)
{
    // Load config files, if any

    // Run command loop
    lsh_loop();

    return EXIT_SUCCESS; 
}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do {
        printf("> ")
        line = lsh_read_line();             // Read
        args = lsh_split_line(line);        // Parse
        status = lsh_execute(args);         // Execute

        free(line);
        free(args);
    } while(status);

}

char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    int buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer){
        fprintf(stderr, "lsh: allocation error:\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        c = getchar();

        if (c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }

        else{
            buffer[position] = c;
        }
        position += 1;

        if (position >= bufsize){
            bufsize += LSH_RL_BUFSIZE;
            
            if(!buffer){
                fprintf(stderr, "lsh: allocation error:\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
}