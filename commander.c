/*
** commander.c -- a stream socket commander for motor simulator
** jalomann.fi 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "9034" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

struct command {
  char device[24];
  int  devnum;
  char command[24];
  int  value;
};

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int setupconnection(char ip[INET6_ADDRSTRLEN]){
    int sockfd, numbytes;  

    struct addrinfo hints, *servinfo, *p;
    int rv;
    //char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

        if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) 
	{
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            ip, sizeof ip);
    printf("client: connecting to %s\n", ip);

    freeaddrinfo(servinfo); // all done with this structure
    return sockfd;

}
static char *nnumtocommandstring(int device){
    char ret[24] = "ruutu";
    printf("[ ] 71\n");
    printf("[ ] 72\n");
#if 0
    switch (device){
      case 1:
	printf("[ ] 1\n");
	strcpy(ret,"rokur");
	break;
      case 2:
	printf("[ ] 1\n");
	strcpy(ret,"mokur");
	break;
      default:
	printf("[ ] default\n");
	strcpy(ret,"xxx");
	break;
    }
#endif
    //return ret;
	  
}

numtocommandstring(int device, char **com){
    char ret[24];
    printf("[ ] 71\n");
    printf("[ ] 72\n");
    switch (device){
      case 1:
	printf("[ ] 1\n");
	*com="mokur";
	break;
      case 2:
	printf("[ ] 1\n");
	*com="nokur";
	break;
      default:
	printf("[ ] default\n");
	strcpy(ret,"xxx");
	break;
    }
	  
}

static char *givedevice(int num){
	char *res;
	int command;
	printf("1 ... Motor\n");
	printf("2 ... Valve\n");
	scanf("%d", &command);
	
	if ( command == 1 ){
		res = malloc(sizeof (char) * 10);
		if (!res)
			return (char *)res;
		sprintf(res, "motor");
	}
	if ( command == 2 ){
		res = malloc(sizeof (char) * 10);
		if (!res)
			return (char *)res;
		sprintf(res, "valve");
	}

	return res;
}

static int givedevicenum(int num){
	int devicenum;
	printf("Enter device num :\n");
	scanf("%d", &devicenum);
	return devicenum;
}


static char *givecommand(int num){
	char *res;
	int command;
	printf("1 ... Start\n");
	printf("2 ... Stop\n");
	printf("3 ... Setpoint\n");
	printf("4 ... Inc\n");
	printf("5 ... Dec\n");

	scanf("%d", &command);
	
	if ( command == 1 ){
		res = malloc(sizeof (char) * 10);
		if (!res)
			return (char *)res;
		sprintf(res, "start");
	}
	if ( command == 2 ){
		res = malloc(sizeof (char) * 10);
		if (!res)
			return (char *)res;
		sprintf(res, "stop");
	}
	if ( command == 3 ){
		res = malloc(sizeof (char) * 10);
		if (!res)
			return (char *)res;
		sprintf(res, "setpoint");
	}
	if ( command == 4 ){
		res = malloc(sizeof (char) * 10);
		if (!res)
			return (char *)res;
		sprintf(res, "inc");
	}
	if ( command == 5 ){
		res = malloc(sizeof (char) * 10);
		if (!res)
			return (char *)res;
		sprintf(res, "dec");
	}

	return res;
}

static int givesetpoint(int num){
	int setpoint=0;
	printf("Enter setpoint :\n");
	scanf("%d", &setpoint);
	return setpoint;
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes, sentbytes;
    char buf[MAXDATASIZE];

    //printf("[ ] 01\n");
    
    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    //printf("[ ] 02\n");

    sockfd = setupconnection(argv[1]);
    //printf("[ ] 03\n");

    int mainloop =0;
    struct command motor1;
    int commandmenu = 0;
    char commandmenudevice[24];
    char *device;
    int   devicenum;
    char *command;
    int   setpoint;

    for (mainloop = 0; mainloop < 2 ; mainloop++ ){
	  // prepare command package
          //printf("[ ] 11\n");
	  //printf("[ ] 12 ask user command\n");
	  // scanf("%d", &commandmenu);
	  //numtocommandstring(commandmenu, &commandmenudevice);
	  //strcpy (commandmenudevice, nnumtocommandstring(commandmenu));
          //printf("[ ] got from function ... %s\n", commandmenudevice);
	  device = givedevice(1);
	  devicenum = givedevicenum(1);
	  command = givecommand(1);
	  setpoint = givesetpoint(1);

  	  printf ("O: %s\n", device);
  	  printf ("O: %d\n", devicenum);
  	  printf ("O: %s\n", command);
  	  printf ("O: %d\n", setpoint);

	  strcpy(commandmenudevice, device);
	  strcpy(motor1.device, commandmenudevice);
	  motor1.devnum = devicenum;
	  strcpy(motor1.command , command);
	  motor1.value = setpoint;

	  printf("[ ] 21\n");

	  buf[0]='\0';
	  strcat(buf, motor1.device);
	  strcat(buf, ";");
	  char numtoasc[2];
	  sprintf(numtoasc, "%d", motor1.devnum);
	  strcat(buf, numtoasc);
	  strcat(buf, ";");
	  strcat(buf, motor1.command);
	  strcat(buf, ";");
	  sprintf(numtoasc, "%d", motor1.value);
	  strcat(buf, numtoasc);
	  strcat(buf, ";");

	  // printf("[ ] 31\n");
	  printf("commander sent: '%s'\n",buf);

	  if ( sentbytes =(send(sockfd, buf, strlen(buf), 0)) == -1) {
	    perror("send");
	  }
  	  printf ("buf: %d\n", sentbytes);
	
	  if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	      perror("recv");
	      exit(1);
	  }

	  buf[numbytes] = '\0';

	  printf("simulator sent: %d bytes\n",numbytes);
	  printf("simulator sent: '%s'\n",buf);

    }

    close(sockfd);

    return 0;
}