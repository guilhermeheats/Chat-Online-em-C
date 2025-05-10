//servidor tcp/ip em C;
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>//biblioteca para poder acessar a função "socket()";

int main ()
{
    int tcp_server = socket(AF_INET, SOCK_STREAM, 0);

    printf("Iniciando Servidor: ");
    if (tcp_server == -1)
    {
        printf("Servidor não foi criado.");
        return 1;
    }
    else
    {
        printf("Servidor criado.");
    }

    return 0;
}