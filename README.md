# Chat-ly


A multi-user chat system that is like a real-time instant message board system, much like IRC. The users can talk to one another and to everyone else. 

To compile the code, run `make` on the linux terminal.

To start the server, you need to run `./server` on 1 terminal. 

To make a client active, open a new terminal and type:
`./client clientname`

Here clientname is the name of the client who will become active. Simmilarly, multiple clients can be made active at a time.


The 2 keywords used to send messages are:

1. `**SEND client_number my_msg**` : This sends a personal message to the specific client number. For instance: SEND 4 hey there. client_number is the number assigned to a particular client by the server. The 1st client is assigned the client_number=1.

2.` **ALL my_msg**` : This sends a broadcast message to everyone (i.e every client connected to the server at a given instance). For instance ALL hello


Personal messages and Global(i.e broadcasted) messages can also be differentiated from the receiving client side. When the message is received, the name of the sender is also shown explicitly to avoid confusion. 

The output message format is **“Global/personal message from name_of_sender: message ”**


**Errors handled:**

*Server side:*
- Binding error
- Listening error
- Accepting error
- Socket error
- Sending and receiving error

*Client side:*
- Connection failure 
- Sending and receiving error
- Trying to send messages to self
- Trying to send messages to an undefined client
- Input format other than SEND/ALL will throw an error
message.
- Missing argument in case of SEND command(eg. If client_number is inputted as a string )


