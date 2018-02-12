#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int socket_fd, fsize;
  struct sockaddr_in  dest, get,from;
  struct hostent *hostptr;
  char get_msg[100];
  char send_msg[100];

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  memset((char *) &dest,0, sizeof(dest)); /* They say you must do this */
  memset((char *) &get,0, sizeof(get));


  dest.sin_family = (short) AF_INET;
  dest.sin_addr.s_addr = htonl(INADDR_ANY);
  dest.sin_port = 4444;                         //sending on port 4444

  get.sin_family = (short) AF_INET;
  get.sin_port = 5555;
  get.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(socket_fd, (struct sockaddr *)&get, sizeof(get));//listening on 3333

  while(1){
    fsize = sizeof(from);
    recvfrom(socket_fd,&get_msg,100,0,(struct sockaddr *)&from,&fsize);
    printf("I am server: I got msg\n\"%s\"\n",get_msg);
    printf("choose msg to send back\n");

    scanf ("%[^\n]%*c", send_msg);    //get msg from user
      if(strcmp(send_msg,"exit")==0)
      exit(1);
    sendto(socket_fd,&send_msg,100,0,(struct sockaddr *)&dest,sizeof(dest));
    printf("I sent msg");
  }
  return 0;
}
