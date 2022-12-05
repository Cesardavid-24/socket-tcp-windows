# Socket-tcp-windows
## A example to TCP socket on windows WinSock2

this tcp socket send to client a simple message **"Hello from the server"**

and the client send to a simple message to server **"Hello from the client"**

## To compile server on windows
go to the directory where the file is,
to compile run this command on **powershell** , **cmd** or **gitbash**

```shell
g++ server.cpp -o server -lws2_32 -lwsock32 -L $MinGW\lib
```
then run the following command to run the program in **powershell** , **cmd** or **gitbash**
```
./server.exe
```

## To compile client on windows

```shell
g++ client.cpp -o client -lws2_32 -lwsock32 -L $MinGW\lib
```
next
```
./client.exe
```
