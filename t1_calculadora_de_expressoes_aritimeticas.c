#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAXV 1001

typedef struct _fstack{//definicao de pilha estatica
	float data[MAXV];
	int end;
}Fstack;

typedef struct _fqueue{//definicao de fila estatica
	float data[MAXV];
	int bgn, end;
}Fqueue;

void clearvector(float *v){//limpa vetores de tamanho MAXV
	int i = 0;
	for(; i < MAXV; i++){
		v[i] = 0;
	}
}

void Screate(Fstack *a){//inicializacao de pilha
	clearvector(a->data);
	a->end = 0;
}

float Spop(Fstack *a){//tirar um valor do final da pilha
	if(!(a->end)){//se o fim nao for zero (vazia)
		return -1;//pilha vazia
	}
	return a->data[--(a->end)];
}

int Spush(Fstack *a, float value){//colocar na pilha
	if(a->end != MAXV - 1){//se nao estiver cheia
		a->data[(a->end)++] = value;
		return 1;
	}
	return 0;
}

void Sprint(Fstack *a){//imprime pilha
	if(!a->end){//se nao estiver vazia
		int i = 0;
		for(; i < a->end; i++){
			printf("%.1f ", a->data[i]);
		}
	}
	printf("\n");
}

void Qcreate(Fqueue *a){//inicializa fila
	clearvector(a->data);
	a->bgn = 0;
	a->end = 0;
}

float Qpop(Fqueue *a){//tira um valor do comeco da fila
	if(!(a->end - a->bgn)){//se nao estiver vazia
		return -1;//fila vazia
	}
	return a->data[(a->bgn)++];
}

int Qpush(Fqueue *a, float value){//coloca um valor no fim da fila
	if(a->end != MAXV - 1){//se nao estiver cheia
		a->data[(a->end)++] = value;
		return 1;
	}
	return 0;
}

void Qprint(Fqueue *a){//imprime pilha
	if(a->end - a->bgn){//se nao estiver vazia
		int i = a->bgn;
		for(; i < a->end; i++){
			printf("%.1f ", a->data[i]);
		}
	}
	printf("\n");
}

int Qbye(Fqueue *a, int i, int j){//remove um valor da fila puxando seus sucessores
	for(; i < j; i++){
		a->data[i] = a->data[i+1];
	}
	j--;
	(a->end)--;//decrece a quantidade de elementos na fila
	return j;
}

int str2flt(char *l, float *out, int lim){//conversao de string para float
	int i = 0, j = 0;//declaracoes
	Fqueue per, temp;
	Qcreate(&per);//limpando as filas
	Qcreate(&temp);
	for(i = 0; i < lim; i++){
		if((l[i] >= '0' && l[i] <= '9') || (l[i] == '.')){//se for numero ou ponto
			Qpush(&temp, l[i]);//coloca na fila pemporaria
		}
		else if(l[i] > 39 && l[i] < 58){//se for sinal
			if(temp.end-temp.bgn){//se a fila temporaria nao estiver vazia
				char *conv = (char *)malloc(sizeof(char)*(temp.end-temp.bgn+1));//cria uma "sub"string do tamanho da fila temp
				for(j = 0; temp.end - temp.bgn; j++){
					conv[j] = Qpop(&temp);//a string recebe os elementos da fila
				}
				Qpush(&per, atof(conv));//coloca na fila 'per' o float retornado pela substring
				Qcreate(&temp);//zera a fila temporaria
				free(conv);//libera a alcacao da substring
			}
			Qpush(&per, -l[i]);//depois de checar se a fila temporaria esta vazia coloca o operador na fila 'per'
		}
		if(i + 1 == lim){//se for a ultima operacao a ser realizada
			if(temp.end-temp.bgn){//ja descrito antes 12 linhas acima
				char *conv = (char *)malloc(sizeof(char)*(temp.end-temp.bgn+1));
				for(j = 0; temp.end - temp.bgn; j++){
					conv[j] = Qpop(&temp);
				}
				Qpush(&per, atof(conv));
				Qcreate(&temp);
				free(conv);
			}
		}
	}
	lim = per.end - per.bgn;//o limite recebe o tamanho da fila per
	for(i = 0; per.end - per.bgn; i++){
		out[i] = Qpop(&per);//o vetor out recebe os elentos da fila per
	}
	return lim;
}

int main(){
	int i = 0, j = 0, flagEOF = 1, k = 0, divzero = 0;//declaracoes
	char c, l[MAXV], op;
	float out[MAXV], sol = 0;
	Fstack sings;
	Fqueue numbs;
	clearvector(out);
	while((c = getchar()) && flagEOF){//enquanto for pegando chars e o arquivo nao tiver acabado
		if(c > 39 && c < 58 && c != 44){//verifique a tabela ASCII
			l[j] = c;//so entrara no vetor os caracteres definidos no pfd, qualquer outro sera lido e ignorado
			j++;
		}
		else if(c == ';' || c == ','){//autoexplicativo
			j = str2flt(l, out, j);//j recebe a qualtidade de elementos tratada e alterada na funcao descrita acima
			for(i = 0; i < j; i++){
				if(out[i] >= 0){//se for positivo (numero) (defini os simbolos como negativos)
					Qpush(&numbs, out[i]);//coloca na fila numbs
				}
				else{//se for simbolo
					if(-(int)out[i] == '+' || -(int)out[i] == '-'){//se for + ou -
						while(-(int)sings.data[sings.end-1] != '(' && sings.end){//enquanto o topo da pilha sings for diferente de ( e ainda tiver elentos na pilha (por causa da questao de precedencia)
							Qpush(&numbs, Spop(&sings));//tira os elementos da pilha sings e coloca na fila numbs
						}
						Spush(&sings, out[i]);//apos isso coloca o caracter do vetor sendo tratado na pilha sinais
					}
					else if(-(int)out[i] == '*' || -(int)out[i] == '/'){//se for * ou / 
						while(-(int)sings.data[sings.end-1] != '+' && -(int)sings.data[sings.end-1] != '-' && -(int)sings.data[sings.end-1] != '(' && sings.end){//enquanto o topo da pilha for diferente de + ou - ou (
							Qpush(&numbs, Spop(&sings));//tira os elementos da pilha e coloca na fila
						}
						Spush(&sings, out[i]);//apos isso coloca o caracter do vetor na pilha sings
					}
					else if(-(int)out[i] == '('){//se for (
						Spush(&sings, out[i]);//coloca na pilha sings
					}
					else if(-(int)out[i] == ')'){//se for )
						while(-(int)sings.data[sings.end-1] != '(' && sings.end){//enquanto o topo da pilha nao for ( 
							Qpush(&numbs, Spop(&sings));//tira os elemntos da pilha e coloca na fila numbs
						}
						if(-(int)sings.data[sings.end-1] == '('){//se o topo da pilha sings for (
							Spop(&sings);//tira o (
						}
					}
				}
				if(i == j - 1 && sings.end){//se for o ultimo passo e ainda tirar elemntos na pilha
					while(sings.end){//enquanto tiver elementos 
						Qpush(&numbs, Spop(&sings));//tira da pulha e coloca na fila
					}
				}
				for(k = 0; k < j; k++){
					if(numbs.data[k] == -(float)'('){//se apos tratar tudo isso e ainda tiver um ( aberto 
						printf("Expressao incorreta\n");
						break;
					}
				}
			}
			for(i = 0; i < j && !divzero; i++){//enquanto i estiver dentro da quantidade de elementos da fila e a flag de divisao por zero estiver abaixada
				if(numbs.data[i] < 0){//se ler um simbolo
					op = -(char)numbs.data[i];//operador recebe o simbolo
					switch (op){
						case '+':
							numbs.data[i-2] = numbs.data[i-2] + numbs.data[i-1];//o primeiro elemento recebe a soma dos dois anteriores ao simbolo lindo
							j = Qbye(&numbs, i-1, j);//tira os elementos antes do simbolo
							j = Qbye(&numbs, i-1, j);
							break;
						case '-':
							numbs.data[i-2] = numbs.data[i-2] - numbs.data[i-1];//mesmo para +
							j = Qbye(&numbs, i-1, j);
							j = Qbye(&numbs, i-1, j);
							break;
						case '*':
							numbs.data[i-2] = numbs.data[i-2] * numbs.data[i-1];//mesmo para +
							j = Qbye(&numbs, i-1, j);
							j = Qbye(&numbs, i-1, j);
							break;
						case '/':
							numbs.data[i-2] = numbs.data[i-2] / numbs.data[i-1];//mesmo para +
							if(!numbs.data[i-1]){//se o denominador for zero
								printf("Expressao incorreta\n");
								divzero = 1;//sobe a flag de divisao por zero
							}
							j = Qbye(&numbs, i-1, j);
							j = Qbye(&numbs, i-1, j);
							break;
						default:
							break;
					}
					i = 0;//vai para o inicio do vetor para procurar os proximos simbolos
				}
			}
			if(!divzero){//se nao for divisao por zero
				sol = Qpop(&numbs);//sol recebe o unico elemento da fila numbs
				printf("%.2f\n", sol);
			}
			j = 0;//recomeca j para continar lendo as proximas linhas
			Screate(&sings);//zera a pilha
			Qcreate(&numbs);//e a fila
			if(c == ',')//se for ,
				flagEOF = 0;//sobe a flag de fim de programa
		}
		divzero = 0;//abaixa a flag de divisao por zero
	}
	return 0;
}
