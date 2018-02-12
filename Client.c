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
  int socket_fd;
  struct sockaddr_in  dest, get,from;
  struct hostent *hostptr;
  char msg[]="hello C how are u?";
  char get_msg[100];
  char send_msg[100];

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  memset((char *) &dest,0, sizeof(dest)); /* They say you must do this */
  memset((char *) &get,0, sizeof(get));

  hostptr = gethostbyname(argv[1]);

  dest.sin_family = (short) AF_INET;
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = 4444;

  get.sin_family = (short) AF_INET;
  get.sin_port = 3333;
  get.sin_addr.s_addr = htonl(INADDR_ANY);

bind(socket_fd, (struct sockaddr *)&get, sizeof(get));//listening on 3333

sendto(socket_fd,&msg,100,0,(struct sockaddr *)&dest,sizeof(dest));//send first msg to C via B
printf("I sent msg\n");

  while(1){
    socklen_t size=sizeof(from);
    recvfrom(socket_fd,&get_msg,100,0,(struct sockaddr *)&from,size);
    printf("I got msg\n\"%s\"\n",get_msg);
    printf("choose msg to send\n");

    scanf ("%[^\n]%*c", send_msg);    //get msg from user
    if(strcmp(send_msg,"exit")==0)
    exit(1);
    sendto(socket_fd,&send_msg,100,0,(struct sockaddr *)&dest,sizeof(dest));//sent to B
    printf("I sent msg\n");
  }
  return 0;
}
