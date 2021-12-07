// /**
//  * Trabalho 02 - Estrutura de Dados III
//  *
//  * Integrantes do grupo:
//  *
//  * Leonardo Hannas de Carvalho Santos  NUSP: 11800480
//  * Lucas Carvalho Freiberger Stapf     NUSP: 11800559
//  */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// //#include "../headers/binmanager.h"
// #include "../headers/linkedlist.h"
// #include "../headers/constants.h"
// #include "../headers/commands.h"
// // #include "../headers/registers.h"
// // #include "../headers/display.h"

// /**
//  * @brief Funcao responsavel por ler e realizar um determinado comando passado no stdin.
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void cmdSelector() {

//   char inputstr[MAX_SIZE_STR];
//   char *str;

//   fgets(inputstr, MAX_SIZE_STR, stdin);

//   char filename[MAX_SIZE_STR], destinationfilename[MAX_SIZE_STR];
//   int cmd;
//   int number;

//   eraseCRLF(inputstr);

//   str = strtok(inputstr, " ");
//   cmd = atoi(str);
//   str = strtok(NULL, " ");
//   strncpy(filename, str, MAX_SIZE_STR);

//   switch(cmd) {

//   case create:
//     str = strtok(NULL, " ");
//     strncpy(destinationfilename, str, MAX_SIZE_STR);
//     createTable(filename, destinationfilename);
//     break;

//   case selectData:
//     selectDataTable(filename);
//     break;

//   case selectDataWhere:
//     str = strtok(NULL, " ");
//     number = atoi(str);
//     selectDataWhereTable(filename, number);
//     break;

//   case deleteData:
//     str = strtok(NULL, " ");
//     number = atoi(str);
//     deleteDataTable(filename, number);
//     break;

//   case insertData:
//     str = strtok(NULL, " ");
//     number = atoi(str);
//     insertDataTable(filename, number);
//     break;

//   case updateData:
//     str = strtok(NULL, " ");
//     number = atoi(str);
//     updateDataTable(filename, number);
//     break;

//   default:
//     break;
//   }
// }

// /**
//  * @brief Esta funcao simula o comando CREATE TABLE de um SQL.
//  * 
//  * @param inputfilename Nome do arquivo csv de leitura dos dados.
//  * @param outputfilename Nome do arquivo binario a ser gerado.
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void createTable(char *inputfilename, char *outputfilename) {
//   showMessage(createFileBIN(inputfilename, outputfilename));
//   binarioNaTela(outputfilename);
// }


// /**
//  * @brief Esta funcao simula o comando SELECT de um SQL.
//  * 
//  * @param inputfilename Nome do arquivo binario para leitura dos dados.
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void selectDataTable(char *inputfilename) {
//   showMessage(printFileBIN(inputfilename));
// }


// /**
//  * @brief Esta funcao simula o comando SELECT WHERE de um SQL.
//  * 
//  * @param inputfilename Nome do arquivo binario para leitura dos dados. 
//  * @param number Numero de campos utilizados para realizar a busca. 
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void selectDataWhereTable(char *inputfilename, int number) {

//   char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

//   DataRegister dr;
//   setEmptyDataRegister(&dr);

//   FILE *f = fopen(inputfilename, "rb");
//   if(f == NULL) {
//     showMessage(FILE_ERROR);
//     return;
//   }

//   for(int i = 0; i < number; i++) {

//     fgets(str, MAX_SIZE_STR, stdin);
//     eraseCRLF(str);

//     char *p = strtok_custom(str, ' ');
//     strcpy(fieldName, p);

//     p = strtok_custom(NULL, ' ');
//     strcpy(fieldValue, p);

//     fillFieldDataRegister(&dr, fieldName, fieldValue);
//   }

//   showMessage(findDataRegistersBIN(f, &dr));
//   fclose(f);
// }


// /**
//  * @brief Esta funcao simula o comando DELETE de um SQL.
//  * 
//  * @param inputfilename Nome do arquivo binario para leitura dos dados.
//  * @param number Numero de delecoes que serao realizadas.
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void deleteDataTable(char *inputfilename, int number) {

//   char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

//   DataRegister dr;
//   FILE *f = fopen(inputfilename, "rb+");
//   if(f == NULL) {
//     showMessage(FILE_ERROR);
//     return;
//   }

//   for(int i = 0; i < number; i++) {

//     setEmptyDataRegister(&dr);

//     fgets(str, MAX_SIZE_STR, stdin);
//     eraseCRLF(str);

//     int n; // numero de campos
//     char *p = strtok_custom(str, ' ');
//     n = atoi(p);

//     for(int j = 0; j < n; j++) {
      
//       p = strtok_custom(NULL, ' ');
//       strcpy(fieldName, p);

//       p = strtok_custom(NULL, ' ');
//       strcpy(fieldValue, p);

//       fillFieldDataRegister(&dr, fieldName, fieldValue);
//     }

//     if(showMessage(deleteDataRegisterBIN(f, &dr)) == FILE_NOT_CONSISTENT) break;
//   }

//   fclose(f);

//   binarioNaTela(inputfilename);
// }


// /**
//  * @brief Esta funcao simula o comando INSERT INTO de um SQL.
//  * 
//  * @param inputfilename Nome do arquivo binario para leitura dos dados.
//  * @param number Numero de insercoes que serao realizadas.
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void insertDataTable(char *inputfilename, int number) {

//   FILE *f = fopen(inputfilename, "rb+");

//   if(f == NULL) {
//     showMessage(FILE_ERROR);
//     return;
//   }

//   DataRegister dr;
//   char str[MAX_SIZE_STR];
//   char *p;

//   for(int i = 0; i < number; i++) {

//     fgets(str, MAX_SIZE_STR, stdin);
//     eraseCRLF(str);

//     p = strtok_custom(str, ' '); // codEstacao
//     fillFieldDataRegister(&dr, "codEstacao", p);

//     p = strtok_custom(NULL, ' '); // nomeEstacao
//     fillFieldDataRegister(&dr, "nomeEstacao", p);

//     p = strtok_custom(NULL, ' '); // codLinha
//     fillFieldDataRegister(&dr, "codLinha", p);

//     p = strtok_custom(NULL, ' '); // nomeLinha
//     fillFieldDataRegister(&dr, "nomeLinha", p);

//     p = strtok_custom(NULL, ' '); // codProxEstacao
//     fillFieldDataRegister(&dr, "codProxEstacao", p);

//     p = strtok_custom(NULL, ' '); // distProxEstacao
//     fillFieldDataRegister(&dr, "distProxEstacao", p);

//     p = strtok_custom(NULL, ' '); // codLinhaIntegra
//     fillFieldDataRegister(&dr, "codLinhaIntegra", p);

//     p = strtok_custom(NULL, ' '); // codEstIntegra
//     fillFieldDataRegister(&dr, "codEstIntegra", p);

//     dr.removido = '0';
//     dr.tamanhoRegistro = sizeOfRegister(dr);
//     dr.proxLista = NULL_FIELD_INTEGER;

//     if(showMessage(insertDataRegisterBIN(f, &dr)) == FILE_NOT_CONSISTENT) break;
//   }

//   fclose(f);

//   binarioNaTela(inputfilename);
// }


// /**
//  * @brief Esta funcao simula o comando UPDATE de um SQL.
//  * 
//  * @param inputfilename Nome do arquivo binario para leitura dos dados.
//  * @param number Numero de atualizacoes que serao realizadas.
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void updateDataTable(char *inputfilename, int number) {

//   char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

//   DataRegister dr_busca, dr_alteracao;
//   FILE *f = fopen(inputfilename, "rb+");
//   if (f == NULL) {
//     showMessage(FILE_ERROR);
//     return;
//   }

//   for(int i = 0; i < number; i++) {

//     setEmptyDataRegister(&dr_busca);
//     setEmptyDataRegister(&dr_alteracao);

//     fgets(str, MAX_SIZE_STR, stdin);
//     eraseCRLF(str);

//     int n; // numero de campos
//     char *p = strtok_custom(str, ' ');
//     n = atoi(p);

//     for(int j = 0; j < n; j++) {
      
//       p = strtok_custom(NULL, ' ');
//       strcpy(fieldName, p);

//       p = strtok_custom(NULL, ' ');
//       strcpy(fieldValue, p);

//       fillFieldDataRegister(&dr_busca, fieldName, fieldValue);
//     }

//     fgets(str, MAX_SIZE_STR, stdin);
//     eraseCRLF(str);

//     p = strtok_custom(str, ' ');
//     n = atoi(p);

//     for (int j = 0; j < n; j++) {
      
//       p = strtok_custom(NULL, ' ');
//       strcpy(fieldName, p);

//       p = strtok_custom(NULL, ' ');
//       strcpy(fieldValue, p);

//       fillFieldDataRegister(&dr_alteracao, fieldName, fieldValue);
//     }

//     if(showMessage(updateDataRegisterBIN(f, &dr_busca, &dr_alteracao)) == FILE_NOT_CONSISTENT) break;
//   }

//   fclose(f);

//   binarioNaTela(inputfilename);
// }


// /**
//  * @brief Funcao de comparacao no run.codes - Fornecida
//  * 
//  * @param nomeArquivoBinario Nome do arquivo binario.
//  */
// void binarioNaTela(char *nomeArquivoBinario) {

//   unsigned long i, cs;
//   unsigned char *mb;
//   size_t fl;
//   FILE *fs;
  
//   if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
//     fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
//     return;
//   }

//   fseek(fs, 0, SEEK_END);
//   fl = ftell(fs);
//   fseek(fs, 0, SEEK_SET);
//   mb = (unsigned char *)malloc(fl);
//   fread(mb, 1, fl, fs);

//   cs = 0;
//   for (i = 0; i < fl; i++) {
//     cs += (unsigned long)mb[i];
//   }
  
//   printf("%lf\n", (cs / (double)100));
//   free(mb);
//   fclose(fs);
// }

// /**
//  * @brief Esta funcao possui a mesma funcionalidade da funcao original stktok da string.h, 
//  * porem a string nao eh quebrada no delimitador se estiver entre aspas duplas, sendo 
//  * quebrado o bloco inteiro de caracteres dentro das aspas.
//  * 
//  * @param str string a ser quebrada.
//  * @param delimitador char, baseado no qual eh feita a quebra da string. 
//  * @return ponteiro para o inicio do token valido (pedaco da string).
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// char *strtok_custom(char *str, char delimitador) {

//   static char *pi, *pf;

//   if(str != NULL) pi = pf = str;
//   else pi = pf;

//   if(pi == NULL) return NULL;

//   int i = 0;

//   if(pf[i] == delimitador) {
//     for (; pf[i] == delimitador; i++);
//     pi = pf = &pf[i];
//   }

//   for(i = 0; pf[i] != delimitador && pf[i] != '"' && pf[i] != '\0'; i++);

//   if(pf[i] == delimitador) {
    
//     pf[i] = '\0';
//     pf = &pf[i + 1];
//     return pi;
  
//   } else if(pf[i] == '"') {

//     pi++;
//     pf++;
//     for (i = 0; pf[i] != '"'; i++);
//     pf[i] = '\0';
//     pf = &pf[i + 1];
//     return pi;

//   } else {

//     if (i == 0) return NULL;
//     else {
//       pf = NULL;
//       return pi;
//     }
//   }
// }

// /**
//  * @brief Remove os caracteres '\\r' (CR) e '\\n' (LF) da string.
//  * 
//  * @param str String de entrada.
//  * 
//  * @author Leonardo Hannas de Carvalho Santos
//  * @author Lucas Carvalho Freiberger Stapf
//  */
// void eraseCRLF(char *str) {
  
//   if(str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0'; // Tira o '\n' se houver.
//   if(str[strlen(str) - 1] == '\r') str[strlen(str) - 1] = '\0'; // Tira o '\r' se houver.
// }
