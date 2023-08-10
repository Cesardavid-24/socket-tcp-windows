/** con este comando 
 * g++ client.cpp -o client -lws2_32 -lwsock32 -L $MinGW\lib
*/
#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<WinSock2.h>
#include <ws2tcpip.h>
#include<iostream>
#include <stdlib.h>

#pragma comment (lib, "ws2_32.lib")
using namespace std;

int main(){
    cout<<"\t\t-----------TCP CLIENT---------"<<endl;
    cout<<endl;
    //variables locales
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET TCPClientSocket;
    int iCloseSocket;
    struct sockaddr_in TCPServerAdd;

    int iConnect;

    int iRecv;
    char RecvBuffer[1500];
    int iRecvBuffer = sizeof(RecvBuffer); 

    int iSend;
    char SendBuffer[1500] = "Hello from Client!";
    int iSenderBuffer = sizeof(SendBuffer);  

    //inicializar el archivo dll WS2_32.DLL (winsock2)
    iWsaStartup = WSAStartup(MAKEWORD(2,2), &Winsockdata);
    if(iWsaStartup != 0){
        cout<<"WSAStartUp Failed (CLIENT)"<<endl;
    }
    cout<<"WSAStartUp Succes "<<endl; 

    //creacion del Socket
    TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(TCPClientSocket == INVALID_SOCKET){
        cout<<"TCP Client Socket Creation Failed"<<WSAGetLastError()<<endl;
    }
    cout<<"TCP Client Socket Creation Succes"<<endl;

    //cargar llenar la estructura con la data
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //conectar socket
    iConnect = connect(TCPClientSocket,(SOCKADDR*)&TCPServerAdd , sizeof(TCPServerAdd));
    if(iConnect == SOCKET_ERROR){
        cout<<"Connection Failed  (CLIENT) & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Connection Success"<<endl;

    //recibir datos del servidor
    iRecv = recv(TCPClientSocket,RecvBuffer,iRecvBuffer,0); 
    if(iRecv == SOCKET_ERROR){
        cout<<"Receive Data Failed (CLIENT) & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Data Received -> "<<RecvBuffer<<endl;
    
    //Enviar datos al servidor
    iSend = send(TCPClientSocket, SendBuffer, iSenderBuffer, 0);
    if(iSend == SOCKET_ERROR){
        cout<<"Send Data Failed (CLIENT) & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Data Sending Success (CLIENT) "<<endl;
    //cerrando el socket
    iCloseSocket = closesocket(TCPClientSocket);
    if(iCloseSocket == SOCKET_ERROR){
        cout<<"Closing Socket Failed (CLIENT) & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"Closing Socket Success (CLIENT)"<<endl;
    //elimiar informacion en el archivo dll
    iWsaCleanup = WSACleanup();
    if(iWsaCleanup == SOCKET_ERROR){
        cout<<"CleanUp Failed (CLIENT) & Error No-> "<<WSAGetLastError()<<endl;
    }
    cout<<"CleanUp Success (CLIENT)"<<endl;

    system("pause");
    return EXIT_SUCCESS;
}
//ALFA Network AWUS036AC Adaptador