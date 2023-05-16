# *__Advanced Programming Assignment__*

## Table of Contents
* [Project Description](#project-description)
* [How To Compile](#how-to-compile)
* [How To Run](#how-to-run)
* [Implementation](#implementation)
* [Authors](#authors)

### Project Description
In this assignment our server will have to handle several clients at the same time.   
That is, at a given moment, the server can speak with several clients at the same time.  
We would like our server to have a CLI (Command Line Interface). That is, when a client connects, he will see  
textual menus that the server sent and through which the interaction between the server and the client will take place.  
Further explanations regarding the server and the client, below.

### How To Compile
In order to compile the code, use the command: `make`

### How To Run
The program should run as follows:  
first, we run the server with the command `./server.out port`
- port is the port number, chosen by the user, and can be a number between 0 and 65535

After the server is running, it's waiting for a connection from the client.

Next, we run the client with the command `./client.out ip port`
- ip is the ipv4 address of the server so that a connection can be made with the server
- port is the same port used by the server

Finally, after the connection has been made, the client prints to the screen options received from the server.    
Each option works as described on the assignment page, and in the description of the functions in the code.  

### Implementation
We will use a design pattern called `Command`, where each command in our software has its own class of type Command.  
The Command class can define anything relevant to all commands in our system,
and in particular an abstract execute command for activation.  
In our code, the CLI object holds a vector that contains all the commands, and a `DefaultIO` object.  
 


The client runs in an infinite loop, and receives from the user an input as described above.  
The client sends the information received from the user to the server.  
The server is classified accordingly, and sends the classification to the client.  
The client prints the received answer to the screen, on a separate line, and receives the next input from the user.  
If the user enters several inputs, the client must send these inputs over the same connection to the server,  
and not on separate connections.  
If the user enters the input -1, the client must close the connection to the server and close the program.  
The server, in this case, continues to the next connection (the server does not close).  
In any case of invalid input, the customer must print invalid input, and continue to receive the next input.  
In any case that the server receives an invalid input from the client,
the server must return only invalid input to the client and continue receiving
the following information from that customer.

### Authors
- Roy Amit
- Yoav Shragay