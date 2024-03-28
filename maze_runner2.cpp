#include <stdio.h>
#include <stack>
#include <iostream>
#include <stdlib.h>

// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento:

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos:
//    valid_positions.size();
//
// Retornar o elemento no topo:
//  valid_positions.top();
//
// Remover o primeiro elemento do vetor:
//    valid_positions.pop();


// Função que le o labirinto de um arquivo texto, carrega em
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	char c;
	int k, l;
	// Abre o arquivo para leitura (fopen)
    FILE *arq;
    arq = fopen(file_name,"r");
	// Le o numero de linhas e colunas (fscanf)
	// e salva em num_rows e num_cols
    fscanf(arq, "%d %d", &num_rows, &num_cols);

	// Aloca a matriz maze (malloc)
	maze = (char**)malloc(num_rows*sizeof(char*));
    for (int i = 0; i < num_rows; i++){
		maze[i] = (char*)malloc((num_cols+1)*sizeof(char));
    }
		// Aloca cada linha da matriz

	for (int k = 0; k < num_rows; ++k) {
		for (int l = 0; l < num_cols+1; ++l) {
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			 fscanf(arq, "%c", &maze[k][l]);
			// Se o valor for 'e' salvar o valor em initial_pos
			 if(maze[k][l]=='e'){
                initial_pos.i = k;
	            initial_pos.j = l-1;
			}
		}
		 //fscanf(arq, "%c", &c);

	}

	return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
    //printf("\nLinhas Colunas\n%d %d \n", num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols+1; ++j) {
			printf("%c", maze[i][j]);
		}
		   printf("\n");
	}
}


// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
static int contador_position = 0;
static int contador_saida = 0;
static int contador_hashtag = 0;
char aux, aux2, aux3;
char c='.';
char c2='.';
char c3='.';
bool walk(pos_t pos) {
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'

    if((contador_saida==1)||(contador_hashtag>=2)){
            if((contador_hashtag>=2)){
                printf("\nSAIDA NAO ENCONTRADA.\n");
            }
            if(contador_saida==1){
                printf("\nPARABENS!\nSAIDA ENCONTRADA\n");
            }
            return true;
    }else{
		// Limpa a tela
		// Imprime o labirinto
		        printf("\nLABIRINTO ATUALIZADO:\n");
		//print_maze();
		      for (int i = 0; i < num_rows; ++i) {
		         for (int j = 0; j < num_cols+1; ++j) {
                     if((i==pos.i) && (j==pos.j+1)){
                          if(maze[i][j]=='e'){
                            aux = maze[i][j];
                            maze[i][j] = c;
                            c = aux;
                            c='.';
                          }
                          if(maze[i][j]=='x'){
                            aux2 = maze[i][j];
                            maze[i][j] = c2;
                            c2 = aux2;
                            c2='.';

                          }
                          if(maze[i][j]=='s'){
                            aux3 = maze[i][j];
                            maze[i][j] = c3;
                            c3 = aux3;
                            c3='.';
                            contador_saida++;
                          }
                          if(maze[i][j]=='#'){
                            contador_hashtag++;
                            printf("\n#\n");
                          }
                     }
			         printf("%c", maze[i][j]);
		         }
		         printf("\n");
	          }
            system("pause");
            system("cls");

		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j

		 	Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	 	*/
                  if(contador_position==0){

                      contador_hashtag = 0;
	 	            /*Nas condições abaixo é possível prosseguir em 4 direções*/
                      if((pos.i>0) && (pos.i<num_rows-1)&&(pos.j>0) && (pos.j< num_cols-1)){
                         pos.j = pos.j+1;
                         valid_positions.push(pos);
                         pos.j = pos.j-2;
                         valid_positions.push(pos);
                         pos.i = pos.i+1;
                         pos.j = pos.j+1;
                         valid_positions.push(pos);
                         pos.i = pos.i-2;
                         valid_positions.push(pos);
                         contador_position=4;
                      }else
                           if((pos.i==0)&&(pos.j==0)){  /*Nas condições abaixo, só é possível proseguir em 2 direções*/
                                                     //Quando estiver na posição (0,0)
                               pos.i = pos.i+1;
                               valid_positions.push(pos);
                               pos.i = pos.i-1;
                               pos.j = pos.j+1;
                               valid_positions.push(pos);
                               contador_position=2;
                       }else
                            if((pos.i==num_rows-1)&&(pos.j==0)){     //Quando estiver na posição (num_row-1,0)
                                 pos.j = pos.j+1;
                                 valid_positions.push(pos);
                                 pos.i = pos.i-1;
                                 pos.j = pos.j-1;
                                 valid_positions.push(pos);
                                 contador_position=2;
                       }else
                            if((pos.i==0)&&(pos.j==num_cols-1)){    //Quando estiver na posição (0,num_col-1)
                               pos.i = pos.i+1;
                               valid_positions.push(pos);
                               pos.i = pos.i-1;
                               pos.j = pos.j-1;
                               valid_positions.push(pos);
                               contador_position=2;
                       }else
                            if((pos.i==num_rows-1)&&(pos.j==num_cols-1)){      //Quando estiver na posição (num_rows-1,num_col-1)
                                pos.i = pos.i-1;
                                valid_positions.push(pos);
                                pos.i = pos.i+1;
                                pos.j = pos.j-1;
                                valid_positions.push(pos);
                                contador_position=2;
                       }else
                            if((pos.i==0)&&(pos.j>0)&&(pos.j<num_cols-1)){     /*Nas condições abaixo só é possível prosseguir em 3 direções*/
                                                                              //Quando está localizado na primeira linha
                                pos.j = pos.j+1;
                                valid_positions.push(pos);
                                pos.j = pos.j - 2;
                                valid_positions.push(pos);
                                pos.j = pos.j+1;
                                pos.i = pos.i+1;
                                valid_positions.push(pos);
                                contador_position=3;
                      }else
                           if((pos.i==num_rows-1)&&(pos.j>0)&&(pos.j<num_cols-1)){        //Quando está localizado na última linha
                               pos.j = pos.j+1;
                               valid_positions.push(pos);
                               pos.j = pos.j - 2;
                               valid_positions.push(pos);
                               pos.j = pos.j+1;
                               pos.i = pos.i-1;
                               valid_positions.push(pos);
                               contador_position=3;
                      }else
                           if((pos.i>0)&&(pos.i<num_rows-1)&&(pos.j==0)){         //Quando está localizado na primeira coluna
                               pos.i = pos.i+1;
                               valid_positions.push(pos);
                               pos.i = pos.i - 2;
                               valid_positions.push(pos);
                               pos.j = pos.j+1;
                               pos.i = pos.i+1;
                               valid_positions.push(pos);
                               contador_position=3;
                      }else
                           if((pos.i>0)&&(pos.i<num_rows-1)&&(pos.j==num_cols-1)){            //Quando está localizado na última coluna
                               pos.i = pos.i+1;
                               valid_positions.push(pos);
                               pos.i = pos.i - 2;
                               valid_positions.push(pos);
                               pos.j = pos.j-1;
                               pos.i = pos.i+1;
                               valid_positions.push(pos);
                               contador_position=3;
                     }
                  }


		          // Verifica se a pilha de posições nao esta vazia
                 //Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
		        // Caso contrario, retornar falso
		      //while( true ){
		         if (!valid_positions.empty()) {
			        pos_t next_position = valid_positions.top();
			        valid_positions.pop();
                    printf("\nPROXIMA POSICAO: %d,%d\n", next_position.i, next_position.j);
                    printf("\nContador_hashtag: %d", contador_hashtag);
                    printf("\nContador_position: %d\n", contador_position);
                    contador_position--;
                    system("pause");
			        walk(next_position);
                 }else{
                        printf("A pilha está vazia!\n");
                        //break;
                 }

	           return false;
   }
}

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze("maze.txt");
	print_maze();
	system("pause");
	system("cls");
	printf("POSICAO INICIAL: %d,%d", initial_pos.i, initial_pos.j);

	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
    if(!exit_found){
       printf("\nFIM.\n");
       system("pause");

   }
	//Tratar o retorno (imprimir mensagem)

	return 0;
}
