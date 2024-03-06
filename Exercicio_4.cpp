#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
//Criacao de struct com dados
typedef struct{
    char nome[50];
    int idade;
    int cpf;
    float score;
}Aluno;
//Criacao de ponteiro apontador do tipo Dados
typedef struct Celula_str * Apontador;
//Criacao de struct com dados
typedef struct Celula_str{
    Aluno DadosAluno;
    Apontador Proximo;
}Dado;
//Criacao de struct com dados
typedef struct{
    Apontador primeiro, ultimo;
}Lista;
//Incio das funcoes
void ListarAlunos (Lista * Informacoes){ 
    Apontador apoio;
    int cpf, cont = 1;
    apoio = Informacoes -> primeiro;
		printf("Informe o CPF do aluno a ser consultado \n");
			scanf("%i", &cpf);
		 
	    while(apoio != NULL){//Verifica se o apoio é diferente de NULL
	    	if(cpf == apoio->DadosAluno.cpf){ // se encontrar algum cpf igual ele mostra os dados do aluno
	        printf("-Aluno: %s -Score: %.2f  -Posicao: %i \n", apoio->DadosAluno.nome, apoio->DadosAluno.score, cont);
	        break; // e sai do while
	    	}
	    	cont = cont + 1; // aqui sera contado para mostrar a posicao do aluno
	        apoio = apoio->Proximo;// receber o endereço de memoria do proximo valor da lista
	    }
    system("pause");
}

void Ordena(Lista *Informacoes){
    Apontador Atual, Prox, Aux1, Aux2, Ant;
    int Troca=0;
    Atual=Informacoes->primeiro; // recebe o primeiro
    Prox=Informacoes->primeiro;// recebe o primeiro
    Ant= Informacoes->primeiro;// recebe o primeiro
    while(Troca==0){ // while troca for igual a 0
        Troca=1; // seta 1 em troca
        Atual=Informacoes->primeiro;
        Prox=Informacoes->primeiro->Proximo; // prox recebera o proximo de primeiro
        Ant = Informacoes->primeiro;
            if(Atual==NULL){ // se atual for null entao a lista esta vazia
                printf("Não há itens suficientes para serem ordenados");
            }
            else {
                for(int x=0; Prox!=NULL; x++){ 
                    if(Atual->DadosAluno.score < Prox->DadosAluno.score){ // compara se score de atual for menor que prox
                            
                            if(Informacoes->primeiro == Atual){ // se primeiro da lista for igual a atual
                                Informacoes->primeiro = Prox; // primeiro recebe prox
                            }
                            if(Informacoes->ultimo == Prox){ // compara ultimo da lista com o prox
                                Informacoes->ultimo = Atual; // ultimo recebe atual
                            }
                            Troca=0;
                            Aux1 = Prox; //recebe prox
                            Aux2= Prox->Proximo; //recebe o proximo de prox
                            Prox=Atual; // prox recebe atual
                            Prox->Proximo = Aux2; // proximo de prox recebe aux2
                            Atual=Aux1; // atual recebe aux1
                            Atual->Proximo= Prox; // proximo de atual recebe prox
                                if(x!=0){   //se x for diferente de 0
                                Ant->Proximo=Atual; // prox de ant recebe atual
                                }
                            
                    }
                    Ant=Atual; // anterior recebe atual
                    Atual=Prox; // atual passa para o proximo
                    Prox=Prox->Proximo; //prox recebe o seu proximo
                }           
            }   
    }
}

void LancarNotas (Lista *Informacoes){
    int chave;
    float nota;
    Apontador aux = Informacoes->primeiro;
    printf("Digite o CPF de um aluno para atualizar seu score: \n"); // procura o cpf de um aluno
            scanf("%i", &chave);
        aux = Informacoes->primeiro;
        while(aux != NULL){
            if(aux->DadosAluno.cpf == chave){ //se encontrar o cpf 
                printf("Digite a nota do aluno: \n");
                    scanf("%f", &nota);
                    aux->DadosAluno.score = aux->DadosAluno.score + nota; // soma a nota no cadastro do aluno e sai do while
                    break;              
            }
            aux = aux->Proximo;
        }
}

void FuncaoPreencher(Aluno * info){
    float score = 0.0; //declaraçao de variavel, garante que o score esta zerado ate receber as notas
    printf("Informe o nome do aluno: \n");
    fflush(stdin);
        scanf("%[^\n]s", info->nome); 
    printf("Informe a idade do aluno: \n");
        scanf("%i", &info->idade);
    printf("Informe o CPF do aluno: \n");
        scanf("%i", &info->cpf);
}

void NovaInsercao(Aluno * info, Lista * Informacoes){  
    if(Informacoes->primeiro->DadosAluno.score < info->score){ // verifica se o score do primeiro e maior do que o que esta chegando em info
        Apontador NovoCad = (Apontador) malloc(sizeof(Dado)); //Sera alocado memoria para a variavel NovoCad
        NovoCad -> DadosAluno = *info; // novo cadastro recebera os dados de info
        NovoCad -> Proximo = Informacoes -> primeiro; //o proximo de novocad recebera o primeiro 
        Informacoes ->primeiro = NovoCad; // agora o primeiro recebe o novocad
    }
    else{
        Apontador itemAnterior = Informacoes->primeiro; // itemnterior recebe o primeiro
        while(itemAnterior != NULL){//Condicao para ver se o itemAnterior é diferente de NULL
            if(itemAnterior->Proximo != NULL && itemAnterior->Proximo->DadosAluno.score< info->score){//Condicao para saber se o score de itemanterior é menor que o que esta vindo e o proximo é NULL
                break;
            }
            itemAnterior = itemAnterior->Proximo; 
        }
        if(itemAnterior == NULL){ // se for null
            Informacoes->ultimo-> Proximo = (Apontador)malloc(sizeof(Dado)); // aloca memoria para o ultimo
            Informacoes->ultimo = Informacoes->ultimo->Proximo; // ultimo recebe o proximo de ultimo
            Informacoes->ultimo-> DadosAluno = *info; //ultimo recebe os dados de info
            Informacoes->ultimo-> Proximo = NULL; // proximo de ultimo recebe null
        }
        else{
            Apontador novo = (Apontador)malloc(sizeof(Dado));
            novo->DadosAluno = *info;
            novo->Proximo = itemAnterior->Proximo;
            itemAnterior->Proximo = novo;
        }
    }
}

void CadastrarAluno(Aluno * info ,Lista * Informacoes){  
    if(Informacoes -> primeiro == NULL){//Se o primeiro dado for NULL aloca uma posicao
        Informacoes->ultimo = (Apontador) malloc(sizeof(Dado)); // alocando memoria para o ultimo
        Informacoes->ultimo->DadosAluno = *info; // o ultimo recebera os dddos de info
        Informacoes->ultimo->Proximo = NULL; // ultimo aponta para null
        Informacoes->primeiro = Informacoes->ultimo; // iguala o primeiro ao ultimo
    }
    else{   
        NovaInsercao(info, Informacoes);
    }
}

void SalaVazia(Lista * Informacoes){ 
    Informacoes -> primeiro = NULL;//Define a posicao como NULL
    Informacoes -> ultimo = NULL;//Define a posicao como NULL
}

int ConfirmaVazia(Lista * Informacoes){
    return(Informacoes -> primeiro == NULL && Informacoes -> ultimo == NULL); // retorna se a lista realmente está vazia
}

void RemoverAluno(Lista * Informacoes){
    int chave;
    printf("Informe o cpf do aluno que sera removido: \n"); // procura um aluno para ser 
        scanf("%i", &chave);
    if(ConfirmaVazia(Informacoes) || Informacoes->primeiro == NULL){ // se a lista estiver vazia sera informado
        printf("Nao ha cadastros a serem retirados \n");
        system("pause");
        return;
    }
    else{
        if(Informacoes->primeiro->DadosAluno.cpf == chave){ // se o primeiro for o cpf selecionado
            Apontador excluir = Informacoes->primeiro; //excluir  recebe os dados de primeiro
            Informacoes->primeiro = Informacoes->primeiro->Proximo; // e o primeiro recebe o seu proximo
            printf("Aluno: %s excluido com sucesso \n", excluir->DadosAluno.nome); // mostra o nome do aluno excluido
            system("pause");
            free(excluir); // libera a memoria de excluir
        }
        else{
            Apontador ItemAnterior = Informacoes->primeiro; // itemanterior recebe o primeiro
            while(ItemAnterior != NULL){ //aqui sera buscado a o cpf do aluno e setado em itemanterior
                if(ItemAnterior->Proximo != NULL && ItemAnterior->Proximo->DadosAluno.cpf == chave){
                    break;
                }
                ItemAnterior = ItemAnterior -> Proximo;
            }
            if(ItemAnterior == NULL){ // se for igual a null ele informara
                printf("CPF inexistente! \n");
                system("pause");
            }
            else{ //se nao
                Apontador excluir = ItemAnterior->Proximo; // excluir recebe o proximo
                ItemAnterior->Proximo = ItemAnterior->Proximo->Proximo; //itemanterior recebe o seu proximo
                printf("Aluno: %s excluido com sucesso \n", excluir->DadosAluno.nome); //mostra o excluido
                system("pause");
                free(excluir); // libera a memoria de excluir
            }
        }
    }
}

void SalvarArquivo(Lista * Informacoes){
    Apontador aux;
    aux = Informacoes -> primeiro;  
    FILE * arq; // cria-se o arquivo
    arq = fopen("Alunos.txt", "w");// abre o arquivo
    if(arq != NULL){
        while(aux != NULL){ // esta opcao ira percorrer a lista e salvar os dados dos Alunos
            int resu = fprintf(arq, "%i|%i|%f|%s\n", aux->DadosAluno.idade, aux->DadosAluno.cpf, aux->DadosAluno.score, aux->DadosAluno.nome);
            if(resu == EOF){
                printf("Não foi possível ler o arquivo \n");
            }
            aux = aux->Proximo;
        }
    }
    else{
        printf("Arquivo não encontrado \n");
        system("pause");
    }
    fclose(arq);// fecha o arquivo para ser lido posteriormente
}

int LerArquivo(Lista * Informacoes, Aluno * info){   
    char nome[50]; 
    int idade = 0, cpf = 0;
    float score = 0; 
    Apontador aux; 
    aux=Informacoes -> primeiro; 
    FILE *arq; // cria o arquivo
    arq = fopen("Alunos.txt", "rt"); // abre o arquivo
    if(arq == NULL){ // se arq for igual a NULL
        printf("Houve um problema em ler o arquivo \n");// mostra mensagem na tela
    }
    else{
        while(fscanf(arq, "%i|%i|%f|%[^\n]s", &idade, &cpf, &score, &nome)!=EOF){ // aqui sera lido os dados no arquivo e jogados em info
                fgetc(arq); 
                strcpy(info->nome, nome);
                info->idade = idade;
                info->cpf = cpf;
                info->score = score;
                CadastrarAluno(info ,Informacoes); // apos ler uma linha e info ser preenchido, a funçao cadastrarAluno sera chamada para que a lista seja ordenada durante o carregamento do arquivo
    }
    fclose(arq);// fecha o arquivo
    }
}

//Criacao do main
int main(){
int op;
Aluno info;
Lista Informacoes; 
SalaVazia(&Informacoes); 
LerArquivo(&Informacoes, &info);
    do{
        system("cls");
        printf("*********************************\n");
        printf("Digite 1 para Cadastrar um aluno \n");
        printf("Digite 2 para remover um aluno \n");
        printf("Digite 3 para atualizar o score de um aluno \n");
        printf("Digite 4 para Mostrar a posicao de um aluno\n");
        printf("Digite 5 para sair \n");
        printf("*********************************\n");
            scanf("%i", &op);//Recebe um inteiro 
        switch(op){//Switch para a opcao desejada
            case 1:
                FuncaoPreencher(&info); 
                CadastrarAluno(&info ,&Informacoes);
                system("pause");
                system("cls");
                break;
            case 2: 
                RemoverAluno(&Informacoes);
                break;
            case 3:
                LancarNotas(&Informacoes);
                Ordena(&Informacoes);
                break;     
            case 4:
                ListarAlunos(&Informacoes);
                break;
            default:{
                if(op == 5){
                    printf("Encerrando... \n");
                }
                else{
                    printf("Opção desconhecida \n");
                    system("pause");
                }
                break;
            }
        }
    }while(op != 5);
SalvarArquivo(&Informacoes);
system("pause");
return 0;
}
