#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"dedos.h"

//PID
#define OK 1
#define ERROR -1
#define INVALID_NAME -3
#define INVALID_PLAY -6
#define GAME_OVER -9
#define JOGADA 7
#define GIVEUP -10
#define STATUS 10
#define INVALID_PLAY2 -5
#define IGUALAR 369

//Marimba

 //-------------------------------vvvvvvvvvvvvvvv------------------Módulo de Operações----------------------vvvvvvvvvvvvvvvvvvvvvvvvvv---------------------------------------
 /*
    Objectivo: Dividir os dedos pelas mãos
    Retorna: Ok caso tenha dividido e ERROR caso não seja possivel dividir os dedos
------------------------------------------------------------------------------------------------------------------------------- */
int dividir_dedos(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada)
{
    if( mao_jogadores[controlador - 1][0] == 0 && mao_jogadores[controlador - 1][1] % 2 == 0 )
    {
        warning(IGUALAR, mao_jogadores[controlador - 1][1], nome_jogadores, mao_jogadores, jogada); //Antes de divir os dedos, imprimir a mensagem reperesentando a jogada
        mao_jogadores[controlador - 1][1] /= 2;
        mao_jogadores[controlador - 1][0] = mao_jogadores[controlador - 1][1];
        return OK;
    }
    else if( mao_jogadores[controlador - 1][1] == 0 && mao_jogadores[controlador - 1][0] % 2 == 0 )
        {   
            warning(IGUALAR, mao_jogadores[controlador - 1][0], nome_jogadores, mao_jogadores, jogada);
            mao_jogadores[controlador - 1][0] /= 2;
            mao_jogadores[controlador - 1][1] = mao_jogadores[controlador - 1][0];
            return OK;
        } 
    return ERROR;
}
 /*------------------------------------------------------------------------------------------------------------------------------------------------
    Objectivo: Ataque generico, esta função é chamada por todos os jogadores
    Retorna: OK caso o ataque seja realizado, e INVALID_PLAY caso o jogador tente atacar com uma mão zerada ou a uma mão zerada
 ------------------------------------------------------------------------------------------------------------------------------------------------*/
int jogador_ataque(int mao_jogadores[][2], int controlador, char *jogada, char **nome_jogadores)
{
    if( jogada[0] == '.' )
        return GAME_OVER;
    if( jogada[0] == '=' )
    {
        if( dividir_dedos(mao_jogadores, controlador, nome_jogadores, jogada) == ERROR )
        {
            warning(INVALID_PLAY, controlador, nome_jogadores, mao_jogadores, jogada); 
            return INVALID_PLAY;
        }
    }
    else if( mao_jogadores[(controlador == 1) ? 1 : 0][(jogada[1] == 'e') ? 0 : 1] != 0 && mao_jogadores[controlador - 1][(jogada[0] == 'e') ? 0 : 1] != 0 )
        {
            mao_jogadores[(controlador == 1) ? 1 : 0][(jogada[1] == 'e') ? 0 : 1] = ( mao_jogadores[(controlador == 1) ? 1 : 0][(jogada[1] == 'e') ? 0 : 1] + mao_jogadores[controlador - 1][(jogada[0] == 'e') ? 0 : 1] ) % 5; 
            printf("\n%d ", mao_jogadores[controlador - 1][(jogada[0] == 'e') ? 0 : 1] );
            warning(JOGADA, mao_jogadores[(controlador == 1) ? 1 : 0][(jogada[1] == 'e') ? 0 : 1], nome_jogadores, mao_jogadores, jogada);
        }
        else
        {
            warning(INVALID_PLAY2, controlador, nome_jogadores, mao_jogadores, jogada);
            return INVALID_PLAY;
        }
    return OK;
}
 /*---------------------------------------------------------------------------------------------------------------
    Objectivo: Realizar o ataque do Chico_esperto
    Devolve: A Mão actualizada, com os valores da mão atacada actualizados 
 -----------------------------------------------------------------------------------------------------------------*/
void ataque_chico_esperto(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada)
{
    if ( mao_jogadores[controlador - 1][0] != 0 && mao_jogadores[controlador - 1][1] != 0 )
    {
        jogada[0] = ( mao_jogadores[controlador - 1][0] >= mao_jogadores[controlador - 1][1] ) ? 'e' : 'd';
    }
    else
    {
        if( mao_jogadores[controlador - 1][0] == 0 )
            jogada[0] = 'd'; 
        else    
            jogada[0] = 'e';
    }
    if ( mao_jogadores[( controlador == 2 ) ? 0 : 1][0] != 0 && mao_jogadores[( controlador == 2 ) ? 0 : 1][1] != 0 )
    {
        jogada[1] = ( mao_jogadores[( controlador == 2 ) ? 0 : 1][0] <= mao_jogadores[( controlador == 2 ) ? 0 : 1][1] ? 'e' : 'd');
    }
    else
    {
        if ( mao_jogadores[( controlador == 2 )? 0 : 1][0] == 0 )
            jogada[1] = 'd';
        else    
            jogada[1] = 'e';
    }
    printf("%s\n",jogada); //imprimir a jogada escolhida
    jogador_ataque(mao_jogadores, controlador, jogada, nome_jogadores);
}
 /*-----------------------------------------------------------------------------------------------------------
    Objectivo: Preencher o vector jogadas com as jogadas válidas para AO-Calhas
    Retorna: Retorna a quantidade de Jogadas válidas
 -----------------------------------------------------------------------------------------------------------*/
int jogadas_possiveis( int mao_jogadores[][2], int controlador, char jogadas[][2], char **nome_jogadores )
{
    int i=0;
    if ( mao_jogadores[controlador - 1][0] > 0 )
    {
        if ( mao_jogadores[ (controlador == 2) ? 0 : 1 ][0] > 0 ) 
        {
            jogadas[i][0] = 'e';
            jogadas[i][1] = 'e';
            i++;
        }
        if ( mao_jogadores[ (controlador == 2) ? 0 : 1 ][1] > 0 )
        {
            jogadas[i][0] = 'e';
            jogadas[i][1] = 'd';
            i++;
        }
    }
    if ( mao_jogadores[controlador - 1][1] > 0)
    {
        if ( mao_jogadores[ (controlador == 2) ? 0 : 1 ][0] > 0 )
        {
            jogadas[i][0] = 'd';
            jogadas[i][1] = 'e';
            i++;
        }
        if ( mao_jogadores[ (controlador == 2) ? 0 : 1 ][1] > 0 )
        {
            jogadas[i][0] = 'd';
            jogadas[i][1] = 'd';
            i++;
        }
    }
    if( mao_jogadores[controlador - 1][0] == 0 && mao_jogadores[controlador - 1][1] % 2 == 0 )
    {
        jogadas[i][0] = '=';
        i++;
    }
    if( mao_jogadores[controlador - 1][1] == 0 && mao_jogadores[controlador - 1][0] % 2 == 0 )
    {
        jogadas[i][0] = '=';
        i++;
    }
    /*jogadas[i][0] = '.';  //Quanto ativo permite que a função Ao-calhas termina o jogo também
    i++;*/
    jogadas[i][0] = '\0'; //colocar o delimitador na última posição, tivemos alguns erros sem colocar tal delimitador, imprimia posições a mais(lixo)
    return i; //retorna a quantidade de jogadas válidas
}
 /*
    Objectivo: Realizar o ataque Ao-Calhas
    Devolve: A mão actualizada, com o ataque da Ao-calhas realizado 
 */
void ataque_ao_calhas(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada)
{
    char jogadas[6][2];
    int index_ataque;

    int quantidade_jogadas = jogadas_possiveis(mao_jogadores, controlador, jogadas, nome_jogadores);
    srand((int)time(NULL)); //semear, para poder receber valores aleatórios sempre que executamos o programa
    
    index_ataque = (int)(((int)rand()) % quantidade_jogadas); //Receber uma posição aleatória
 
    jogada[0] = jogadas[index_ataque][0];
    jogada[1] = jogadas[index_ataque][1];

    if ( jogada[0] == '=' )
        jogada[1] = '\0';

    printf("%c%c\n",jogada[0],jogada[1]); //imprimir a jogada escolhida
    jogador_ataque( mao_jogadores, controlador, jogada, nome_jogadores );
}

//--------------------------^^^^^^^^^^^^^^^^^^^^^^---------------------Fim do Módulos das Operações----------------------^^^^^^^^^^^^^^^^^^^^^--------------------------
//-------------------------------------------------------------------------Mudança de Módulo--------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------Módulos das Validações e Warnings-----------------------------------------------------------------------------
 /*
    Objectivo: Imprimir as mensagens que permitem a interação com o usuário
    Recebe: Esta função recebe um inteiro PID que diz qual mensagem imprimir
    Devolve: Mensagem de alerta 
 -----------------------------------------------------------------------------------------------------------*/
void warning(int pid_mensagem, int controlador, char **nome_jogadores, int mao_jogadores[][2], char *jogada)
{
    switch ( pid_mensagem )
    {
        case INVALID_NAME:
            printf("\tJogada do jogador %d inválida!!!! , name valid is: <humano>, <ao-calhas>, <chico-esperto> \n", controlador);
        break;
        case INVALID_PLAY:
            printf("\tJogada inválida!\n");21
        break;
        case GAME_OVER:
            printf("\t%13s1: %d , %d",nome_jogadores[1], mao_jogadores[0][0], mao_jogadores[0][1]);
            printf("\n");
            printf("\t%13s2: %d , %d",nome_jogadores[2], mao_jogadores[1][0], mao_jogadores[1][1]);
            printf("\n");
            printf("\tVitória do %s %d!!!\n",nome_jogadores[(controlador == 2) ? 1 : 2],(controlador == 2) ? 1 : 2);
        break;
        case GIVEUP:
            printf("\tDesistência: Vitoria do %s %d !!\n",nome_jogadores[controlador], controlador);
            break;
        case JOGADA:
            printf("dedo da %s ataca dedo da %s, ficam %d dedos\n",(jogada[0]=='e')?"esquerda":"direita",(jogada[1]=='e')?"esquerda":"direita",controlador);
            break;
        case STATUS:
            printf("\t%13s1: %d , %d",nome_jogadores[1], mao_jogadores[0][0], mao_jogadores[0][1]);
            printf("\n");
            printf("\t%13s2: %d , %d",nome_jogadores[2], mao_jogadores[1][0], mao_jogadores[1][1]);
            printf("\n");
            break;
        case INVALID_PLAY2:
            printf("\n\tA quantidade de dedos atacada ou atacante deve ser superior a 0\n");
            break;
        case IGUALAR:
            printf("\n\tDivide os %d dedos pelas duas mãos\n", controlador);
            break;  
        default:
        break;
    }
}
 /*---------------------------------------------------------------------------------------------------------------------
    Objectivo: Verificar se a jogada inserida faz parte das jogadas válidas
    Devolve: Devolve ooo vector Jogadas  com o valor correto
 ----------------------------------------------------------------------------------------------------------------------*/
void validar_jogada(char *jogada, int controlador, char **nome_jogadores, int mao_jogadores[][2])
{
    while( strcmp(jogada, "ee") && strcmp(jogada, "ed") && strcmp(jogada, "de") && strcmp(jogada, "dd") && strcmp(jogada, ".") && strcmp(jogada, "=") )
    {
        warning(INVALID_PLAY, controlador, nome_jogadores, mao_jogadores, jogada);
        printf("\nVez do %s %d: ",nome_jogadores[controlador], controlador);
        scanf("%s",jogada);
    }
}
 /*----------------------------------------------------------------------------------------------------------------
    Objectivo: Validar e ou actualizar o nome inserido pelo usuario 
    Devolve: Um nome válido para o jogador
 ----------------------------------------------------------------------------------------------------------------*/
void receber_nome(int controlador, char **nome_jogadores, int mao_jogadore[][2], char *jogada)
{
    while(strcmp(nome_jogadores[controlador], "humano") && strcmp(nome_jogadores[controlador], "chico-esperto") && strcmp(nome_jogadores[controlador], "ao-calhas"))
    {
        warning(INVALID_NAME, controlador, nome_jogadores, mao_jogadore, jogada);
        scanf("%s",nome_jogadores[controlador]);
    }
}
 /*---------------------------------------------------------------------------------------------------------
    Objectivo: verificar se um dos jogadores ganhou
    Retorna: Ok caso nenhum dos jogador ganhor e GAME_OVER caso um deles ganhou
 ----------------------------------------------------------------------------------------------------------*/
int game_over(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada)
{
    if( ( mao_jogadores[controlador-1][controlador-1] == 0 && mao_jogadores[controlador-1][(controlador == 2) ? 0 : 1] == 0 ) || !strcmp(jogada, ".") )
    {
        warning( (!(strcmp(jogada, ".")) ? GIVEUP : GAME_OVER ), controlador, nome_jogadores, mao_jogadores, jogada);
        return GAME_OVER;
    } 
    return OK;
}
//-----------------------------------------------------------------------------------------Fim dos Módulos-----------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    int mao_jogadores[2][2] = {{1,1} , {1,1}};
    char jogada[2];
    int controlador=1, flag=0;

    receber_nome(1, argv, mao_jogadores, jogada);
    receber_nome(2, argv, mao_jogadores, jogada);

    system("clear");
    printf("\t-------------------------------------------------------INICIO DO JOGO------------------------------------------------------------------------------\t");
    printf("\n\t\t            Jogo dos dedos - %s vs %s \n",argv[1], argv[2]);

     while(flag != GAME_OVER)
    {
        warning(STATUS, controlador, argv, mao_jogadores, jogada);

        printf("Vez do %s %d: ",argv[controlador], controlador);
        if( !strcmp(argv[controlador], "humano") )
        {
            //ataque humano
            scanf("%s",jogada);
            validar_jogada(jogada, controlador, argv, mao_jogadores);
            if ( jogador_ataque(mao_jogadores, controlador, jogada, argv) == INVALID_PLAY )
                controlador = (controlador == 1) ? 2 : 1;
        }
        else if( !strcmp(argv[controlador], "ao-calhas") )
            {
                //ataque ao-calhas
                system("sleep 2");
                ataque_ao_calhas(mao_jogadores, controlador, argv, jogada);
                printf("\n");
            }
            else if( !strcmp(argv[controlador], "chico-esperto") )
                {
                    //ataque chico-esperto
                    system("sleep 2"); // wait 2 seconds
                    ataque_chico_esperto(mao_jogadores, controlador, argv, jogada);
                    printf("\n");
                }
        controlador = (controlador == 1) ? 2 : 1;
        flag = game_over(mao_jogadores,controlador, argv, jogada);
    }

    return 0;
}
