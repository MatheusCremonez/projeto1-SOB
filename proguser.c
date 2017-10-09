#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256              
static char receive[BUFFER_LENGTH];    //buffer para guardar a reposta recebida

int main(){
   int ret, fd,i=0;
   char decifrar[20];
   char stringToSend[BUFFER_LENGTH]; //a msg que sera enviada
 
   fd = open("/dev/ebbchar", O_RDWR);             // Open the device with read/write access
   if (fd < 0){
      perror("Failed to open the device...");
      return errno;
   }
   printf("Digite o comando para cifrar tal como:\n");
   printf("c + <string a ser cifrada>\n");
   printf("d + <string a ser decifrada>\n");
   printf("h + <string para exibição do resumo criptográfico hash>\n");
	char escolha;   
	scanf("%c", &escolha);   //o primeiro caracter é recebido de forma separada
   	char vetaux[200];
	vetaux[0] = escolha;
	vetaux[1]='\0';
	if(escolha == 'c') //caso ele queira cifrar algo
	{

		 scanf("%[^\n]%*c", stringToSend); //recebe a palavra como string
		 strcat(vetaux,stringToSend); //concatena c com o resto da string
	}
	if(escolha == 'd') //caso ele queira decifrar algo
	{

		for(i=0;i<16;i++)
		{
			scanf("%02x", &decifrar[i]); //recebe 16 caracteres em hexadecimal
		}
	
 		
		strcat(vetaux," ");
		strcat(vetaux,decifrar); //concatena os valores com o resto do comando
 		
		
	}
	if(escolha == 'h'){
		//em breve....
	}

	write(fd, vetaux, strlen(vetaux));  //escreve no device


 	printf("Pressione enter para efetuar leitura do device...\n");
   	getchar(); //solicita um enter para realizar a leitura do device

	printf("\nLendo do device...\n\n");
	ret = read(fd, receive, BUFFER_LENGTH);        // Recebe a resposta do device
   
	if (ret < 0){ //caso ocorra algum erro
    	  perror("Falha ao ler mensagem do device.");
          return errno;
  	 }
  

 	printf("Mensagem recebida: %s\n", receive); //mensagem em string

	printf("Valor recebido em Hexa:\n");
	for(i=0;i<16;i++) //mensagem em hexa
	{
		printf("%02x ",(unsigned char) (receive[i]));
	}
 	printf("\n\n");
	

	
   return 0;
}
