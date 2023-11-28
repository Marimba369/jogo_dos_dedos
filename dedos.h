#ifndef DEDOS_H
#define DEDOS_H

int dividir_dedos(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada);
int jogador_ataque(int mao_jogadores[][2], int controlador, char *jogada, char **nome_jogadores);
void validar_jogada(char *jogada, int controlador, char **nome_jogadores, int mao_jogadores[][2]);
void receber_nome(int controlador, char **nome_jogadores, int mao_jogadore[][2], char *jogada);
int game_over(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada);
void warning(int pid_mensagem, int controlador, char **nome_jogadores, int mao_jogadores[][2], char *jogada);
void ataque_chico_esperto(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada);
void ataque_ao_calhas(int mao_jogadores[][2], int controlador, char **nome_jogadores, char *jogada);

#endif