//servidor tcp/ip em C.
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>//biblioteca para poder acessar a função "socket()".
#include <netinet/in.h>//usar o protocolo TCP/IP.
#include <string.h>//biblioteca para manipular strings.
#include <unistd.h>//biblioteca para se comunicar com o Sistema Operacional, POSIX;

#define porta 2020

int main ()
{
    int socket_server = socket(AF_INET, SOCK_STREAM, 0);//iniciar conexão com a internet.
    //verificar se o servidor foi iniciado.
    printf("Iniciando Servidor... \n");
    if (socket_server == -1)
    {
        printf("Servidor não foi criado.\n");
        return 1;
    }
    printf("Servidor criado.\n");

    struct sockaddr_in endereco_server;
    endereco_server.sin_family = AF_INET;//utiliza o IPv4.
    endereco_server.sin_port = htons(porta);//define a porta da rede.
    endereco_server.sin_addr.s_addr = INADDR_ANY;//poder conversar com qualquer computador.
    memset(endereco_server.sin_zero, 0, sizeof(endereco_server.sin_zero));//setar a o "sin_zero" para 0, não ocorrer falhas.
    //associar o socket ao endereço de rede com "bind()".
    if (bind(socket_server, (struct sockaddr*)&endereco_server, sizeof(endereco_server) == -1))
    {
        printf("Porta não criada.\n");
        return 1;
    }
    printf("Porta criada: %d\n", porta);
    //esperar conexões.
    if (listen(socket_server, 5) == -1)//até 5 conexões na fila.
    {  
        printf("Falha na espera.\n");
        return 1;
    }
    printf("Esperando conexões...\n");
    //aceitar conexões.
    struct sockaddr_in endereco_client;//criou endereço do cliente.
    socklen_t tam_endereco = sizeof(endereco_client);//definir o tamanho da estrutura do endereço.
    int socket_client = accept(socket_server, (struct sockaddr*)&endereco_client, &tam_endereco);
    if (socket_client == -1)
    {
        printf("Conexão falhada.");
        return 1;
    }
    printf("Conexão estabelecida.");
    //aviso para o cliente.
    char *aviso = "Conexão confirmada.\n";
    send(socket_client, aviso, strlen(aviso), 0);

    close(socket_client);
    close(socket_server);

    return 0;
}