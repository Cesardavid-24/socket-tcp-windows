/** con este comando 
 * g++ server.cpp -o server -lws2_32 -lwsock32 -L $MinGW\lib
*/
#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<WinSock2.h>
#include <ws2tcpip.h>
#include<iostream>
#include <stdlib.h>
#include<cstring>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main(){
    cout<<"\t\t-----------TCP SERVER---------"<<endl;
    cout<<endl;
    //variables locales
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET TCPServerSocket;
    int iCloseSocket;

    struct sockaddr_in TCPServerAdd;
    struct sockaddr_in TCPClientAdd;
    int iTCPClientAdd = sizeof(TCPClientAdd);
    
    int iBind;
    int iListen;

    SOCKET sAcceptSocket;

    int iSend;
    char SendBuffer[1500] = "Hello from Server!";
    int iSenderBuffer = sizeof(SendBuffer);  

    int iRecv;
    char RecvBuffer[1500];
    int iRecvBuffer = sizeof(RecvBuffer) ; 
    //inicializar el archivo dll WS2_32.DLL (winsock2)
    iWsaStartup = WSAStartup(MAKEWORD(2,2), &Winsockdata);
    if(iWsaStartup != 0){
        cout<<"WSAStartUp Failed "<<endl;
    }
    cout<<"WSAStartUp Succes "<<endl; 
    //cargar llenar la estructura con la data
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);
    //creando el socket 
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(TCPServerSocket == INVALID_SOCKET){
        cout<<"TCP Server Socket Creation Failed"<<WSAGetLastError()<<endl;
    }
    cout<<"TCP Server Socket Creation Succes"<<endl;
    //enlazando el socket
    iBind = bind(TCPServerSocket,(SOCKADDR*)&TCPServerAdd,sizeof(TCPServerAdd)); 
    if(iBind == SOCKET_ERROR){
        cout<<"Binding Failed & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Binding Success"<<endl;
    //colocando el socket en escucha
    iListen = listen(TCPServerSocket, 2);
    if(iListen == SOCKET_ERROR){
        cout<<"Listen Failed & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Listen Success"<<endl;
    //aceptanto las conexiones que nos llegan
    sAcceptSocket = accept(TCPServerSocket,(SOCKADDR*)&TCPClientAdd, &iTCPClientAdd); 
    if(sAcceptSocket == INVALID_SOCKET){
        cout<<"Accept Failed & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Connection Accepted"<<endl;
    
    //Enviar datos al cliente
    iSend = send(sAcceptSocket, SendBuffer, iSenderBuffer, 0);
    if(iSend == SOCKET_ERROR){
        cout<<"Send Data Failed & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Data Sending Success"<<endl;

    //recibir datos del cliente
    iRecv = recv(sAcceptSocket,RecvBuffer,iRecvBuffer,0); 
    if(iRecv == SOCKET_ERROR){
        cout<<"Receive Data Failed & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Data Received -> "<<RecvBuffer<<endl;

    //cerracdo la conexion entre socket
    iCloseSocket = closesocket(TCPServerSocket);
    if(iCloseSocket == SOCKET_ERROR){
        cout<<"Closing Socket Failed & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Closing Socket Success"<<endl;

    //elimiar informacion en el archivo dll
    iWsaCleanup = WSACleanup();
     if(iWsaCleanup == SOCKET_ERROR){
        cout<<"CleanUp Failed & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"CleanUp Success"<<endl;

    system("pause");
    return EXIT_SUCCESS;
}


