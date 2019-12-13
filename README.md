# Chat-ly


A multi-user chat system that is like a real-time instant message board system, much like IRC. The users can talk to one another and to everyone else. 

To compile the code, run make on the linux terminal.
>make

To start the server, you need to run ./server on 1 terminal. 
>./server

To make a client active, open a new terminal and type:
>" ./client clientname ".

Here clientname is the name of the client who will become active.

Simmilarly, multiple clients can be made active at a time.


The 2 keywords used to send messages are:

❏ **SEND client_number my_msg** : This sends a personal message to the specific client number.For instance: SEND 4 hey there

❏ **ALL my_msg** : This sends a broadcast message to everyone (i.e every client connected). For instance ALL hello



First connection is established between the server and client through **UNIX DOMAIN SOCKET**. The message which is sent through the client is appended with the client’s name. The message is received by the server and it is checked for the keywords(ALL/SEND)in our case, and different functions are called respectively which in turn sends the message to the respective client.

Personal messages and Global(i.e broadcasted) messages can also be differentiated from the receiving client side. When the message is received, the name of the sender is also shown explicitly to avoid confusion. 

The output message format is *“Global/personal message from name_of_sender: message ”*
