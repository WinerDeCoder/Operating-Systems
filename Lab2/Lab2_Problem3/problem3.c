#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
static int pipefd1[2] , pipefd2[2] ;

void INIT(void){
   if (pipe(pipefd1)<0 || pipe(pipefd2)<0){
       perror("pipe" ) ;
       exit (EXIT_FAILURE) ;
  }
}
void WRITE_TO_PARENT(void){
    /* send parent a message through pipe*/
    // TO DO
    char *message = "message from child";
    write(pipefd1[0], message, strlen(message)+1);
    close(pipefd1[0]);
    printf("Child send message to parent !\n" ) ;
}
void READ_FROM_PARENT(void){
    /* read message sent by parent from pipe*/
    // TO DO
    char message[100];
    read(pipefd1[1], message, 100);
    printf("Child read message from parent: %s\n", message);
    close(pipefd1[1]);

    printf("Child receive message from parent !\n" ) ;
}
void WRITE_TO_CHILD(void) {
    /* send child a message through pipe*/
    // TO DO
    char *message = "message from parent";
    write(pipefd2[1], message, strlen(message)+1);
    close(pipefd2[1]);
    printf("Parent send message to child !\n" ) ;
}
void READ_FROM_CHILD(void){
    /* read the message sen t by c h il d from p ipe */
    // TO DO
    char message[100];
    read(pipefd2[0], message, 100);
    close(pipefd2[0]);
    printf("Parent␣ receive ␣message␣from␣ child !\n" ) ;
}

int main(int argc , char* argv[] ) {
    INIT() ;
    pid_t pid ;
    pid = fork() ;
    // set a timer , process will end after 1 second .
    alarm(10);
    if( pid==0){
        while(1){
            sleep(rand()%2+1);
            WRITE_TO_CHILD() ;
            READ_FROM_CHILD() ;
        }
    }
    else{
        while(1){
            sleep( rand()%2+1);
            READ_FROM_PARENT() ;
            WRITE_TO_PARENT() ;
        }
    }
    return 0;
 }
