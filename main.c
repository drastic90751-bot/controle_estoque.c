//Inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definição de constante
#define MAX 50

//Estrutura de dados
typedef struct {
	int id;
	char nome[20];
	char categoria[20];
	float preco;
	int quantidade;
	char fornecedor[20];
} Produto;

//Variáveis globais
Produto lista[MAX];
int n = 4;
int proximoID = 5;

//Declaração de funções
void inicializar();
void listar();
void inserir();
void alterar();
void excluir();
void buscar();
void ordenarNome();
void ordenarPreco();
void ordenarNomeDesc();
void ordenarPrecoDesc();
void salvarProdutosEmArquivo();
void carregarProdutosDeArquivo();

//Função inicializar -> adiciona produtos iniciais
void inicializar() {
	lista[0] = (Produto){1,"Camiseta Basica","Vestuario",49.90,30,"Moda Brasil"};
	lista[1] = (Produto){2,"Mouse Optico USB","Informatica",59.99,15,"TecnoShop"};
	lista[2] = (Produto){3,"Shampoo 300ml","Higiene Pessoal",22.50,40,"Beleza Pura"};
	lista[3] = (Produto){4,"Cafe 500g","Alimentos",18.00,25,"Graos do Sul"};
}

//Função listar -> exibe produtos na tela
void listar() {
	printf("ID | Produto             | Categoria       | Preco  | Qtde | Fornecedor\n");
	printf("---------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
		printf("%2d | %-18s | %-15s | %6.2f | %4d | %-15s\n",
		       lista[i].id,lista[i].nome,lista[i].categoria,
		       lista[i].preco,lista[i].quantidade,lista[i].fornecedor);
}

//Função inserir -> adiciona novo produto
void inserir() {
	if(n>=MAX){printf("Lista cheia!\n");return;}
	Produto p;
	p.id=proximoID++;
	printf("Nome: ");scanf(" %[^\n]",p.nome);
	for(int i=0;i<n;i++){if(strcmp(lista[i].nome,p.nome)==0){printf("Produto ja cadastrado!\n");return;}}
	printf("Categoria: ");scanf(" %[^\n]",p.categoria);
	printf("Preco: ");scanf("%f",&p.preco);
	printf("Quantidade: ");scanf("%d",&p.quantidade);
	printf("Fornecedor: ");scanf(" %[^\n]",p.fornecedor);
	lista[n++]=p;
	printf("Produto inserido!\n");
}

//Função alterar -> edita dados de um produto existente
void alterar() {
	int id,achou=0;
	printf("Digite ID do produto: ");
	scanf("%d",&id);
	for(int i=0;i<n;i++){
		if(lista[i].id==id){
			achou=1;
			printf("Novo nome: ");scanf(" %[^\n]",lista[i].nome);
			printf("Nova categoria: ");scanf(" %[^\n]",lista[i].categoria);
			printf("Novo preco: ");scanf("%f",&lista[i].preco);
			printf("Nova quantidade: ");scanf("%d",&lista[i].quantidade);
			printf("Novo fornecedor: ");scanf(" %[^\n]",lista[i].fornecedor);
			printf("Produto alterado!\n");
			break;
		}
	}
	if(!achou)printf("ID nao encontrado!\n");
}

//Função excluir -> remove produto da lista
void excluir() {
	int id,achou=0;
	printf("Digite ID do produto: ");
	scanf("%d",&id);
	for(int i=0;i<n;i++){
		if(lista[i].id==id){
			achou=1;
			for(int j=i;j<n-1;j++)lista[j]=lista[j+1];
			n--;
			printf("Produto excluido!\n");
			break;
		}
	}
	if(!achou)printf("ID nao encontrado!\n");
}

//Função buscar -> pesquisa por nome ou categoria
void buscar() {
	char termo[50];
	int opc;
	printf("Buscar por: 1-Nome 2-Categoria: ");
	scanf("%d",&opc);
	printf("Digite o termo: ");
	scanf(" %[^\n]",termo);
	printf("Resultados:\n");
	printf("ID | Produto             | Categoria       | Preco  | Qtde | Fornecedor\n");
	printf("---------------------------------------------------------------------\n");
	for(int i=0;i<n;i++){
		if((opc==1&&strcmp(lista[i].nome,termo)==0)||(opc==2&&strcmp(lista[i].categoria,termo)==0)){
			printf("%2d | %-18s | %-15s | %6.2f | %4d | %-15s\n",
			       lista[i].id,lista[i].nome,lista[i].categoria,
			       lista[i].preco,lista[i].quantidade,lista[i].fornecedor);
		}
	}
}

//Função ordenarNome -> ordena A–Z
void ordenarNome() {
	Produto temp;
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-1-i;j++)
			if(strcmp(lista[j].nome,lista[j+1].nome)>0){
				temp=lista[j];
				lista[j]=lista[j+1];
				lista[j+1]=temp;
			}
}

//Função ordenarPreco -> ordena por preço (menor→maior)
void ordenarPreco() {
	Produto temp;
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-1-i;j++)
			if(lista[j].preco>lista[j+1].preco){
				temp=lista[j];
				lista[j]=lista[j+1];
				lista[j+1]=temp;
			}
}

//Função ordenarNomeDesc -> ordena nome Z–A
void ordenarNomeDesc() {
	Produto temp;
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-1-i;j++)
			if(strcmp(lista[j].nome,lista[j+1].nome)<0){
				temp=lista[j];
				lista[j]=lista[j+1];
				lista[j+1]=temp;
			}
}

//Função ordenarPrecoDesc -> ordena preço (maior→menor)
void ordenarPrecoDesc() {
	Produto temp;
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-1-i;j++)
			if(lista[j].preco<lista[j+1].preco){
				temp=lista[j];
				lista[j]=lista[j+1];
				lista[j+1]=temp;
			}
}

//Função auxiliar -> remove aspas e quebras de linha
static void trim_quotes(char *s){
	size_t len;
	if(!s)return;
	len=strlen(s);
	while(len>0&&(s[len-1]=='\n'||s[len-1]=='\r')){s[--len]='\0';}
	if(len>0&&s[0]=='"'&&s[len-1]=='"'){memmove(s,s+1,len-2);s[len-2]='\0';}
}

//Função salvarProdutosEmArquivo -> exporta para CSV
void salvarProdutosEmArquivo(){
	char nomeArquivo[128];
	FILE *fp;
	printf("Digite o nome do arquivo para salvar (ex: produtos.csv): ");
	scanf(" %127[^\n]",nomeArquivo);
	fp=fopen(nomeArquivo,"w");
	if(!fp){printf("Erro ao criar/abrir o arquivo '%s'\n",nomeArquivo);return;}
	fprintf(fp,"ID,Nome,Categoria,Preco,Quantidade,Fornecedor\n");
	for(int i=0;i<n;i++){
		fprintf(fp,"%d,\"%s\",\"%s\",%.2f,%d,\"%s\"\n",
		        lista[i].id,lista[i].nome,lista[i].categoria,
		        lista[i].preco,lista[i].quantidade,lista[i].fornecedor);
	}
	fclose(fp);
	printf("Arquivo '%s' salvo com sucesso (%d produtos).\n",nomeArquivo,n);
}

//Função carregarProdutosDeArquivo -> lê dados do CSV
void carregarProdutosDeArquivo(){
	char nomeArquivo[128];
	FILE *fp;
	char linha[512];
	printf("Digite o nome do arquivo para carregar (ex: produtos.csv): ");
	scanf(" %127[^\n]",nomeArquivo);
	fp=fopen(nomeArquivo,"r");
	if(!fp){printf("Erro ao abrir o arquivo '%s'\n",nomeArquivo);return;}
	if(fgets(linha,sizeof(linha),fp)==NULL){printf("Arquivo vazio.\n");fclose(fp);return;}
	int indice=0;
	while(fgets(linha,sizeof(linha),fp)!=NULL&&indice<MAX){
		char buffer[6][128];int campo=0;char *p=linha;char campoBuf[512];int bi=0;int inQuotes=0;
		for(;*p&&campo<6;p++){
			if(*p=='"'){inQuotes=!inQuotes;continue;}
			if(*p==','&&!inQuotes){campoBuf[bi]='\0';strncpy(buffer[campo],campoBuf,sizeof(buffer[campo])-1);buffer[campo][sizeof(buffer[campo])-1]='\0';campo++;bi=0;continue;}
			campoBuf[bi++]=*p;if(bi>=511)bi=510;
		}
		campoBuf[bi]='\0';
		if(campo<6){strncpy(buffer[campo],campoBuf,sizeof(buffer[campo])-1);buffer[campo][sizeof(buffer[campo])-1]='\0';campo++;}
		for(int i=0;i<campo;i++)trim_quotes(buffer[i]);
		if(campo>=6){
			Produto pdt;
			pdt.id=atoi(buffer[0]);
			strncpy(pdt.nome,buffer[1],sizeof(pdt.nome)-1);pdt.nome[sizeof(pdt.nome)-1]='\0';
			strncpy(pdt.categoria,buffer[2],sizeof(pdt.categoria)-1);pdt.categoria[sizeof(pdt.categoria)-1]='\0';
			pdt.preco=(float)atof(buffer[3]);
			pdt.quantidade=atoi(buffer[4]);
			strncpy(pdt.fornecedor,buffer[5],sizeof(pdt.fornecedor)-1);pdt.fornecedor[sizeof(pdt.fornecedor)-1]='\0';
			lista[indice++]=pdt;
		}
	}
	n=indice;
	proximoID=1;
	for(int i=0;i<n;i++)if(lista[i].id>=proximoID)proximoID=lista[i].id+1;
	fclose(fp);
	printf("Carregamento concluido: %d produtos importados. proximoID=%d\n",n,proximoID);
}

//Função principal -> controla o menu e as opções do usuário
int main(){
	inicializar();
	int opc;
	while(1){
		printf("\nMENU\n1-Listar \n2-Inserir \n3-Alterar \n4-Excluir \n5-Buscar \n6-Ordenar Nome A-Z \n7-Ordenar Preco (menor->maior) \n8-Salvar Arquivo \n9-Carregar Arquivo \n10-Sair \n11-Ordenar Nome Z-A \n12-Ordenar Preco (maior->menor)\n");
		scanf("%d",&opc);
		switch(opc){
			case 1:listar();break;
			case 2:inserir();break;
			case 3:alterar();break;
			case 4:excluir();break;
			case 5:buscar();break;
			case 6:ordenarNome();printf("Ordenado por nome A-Z!\n");break;
			case 7:ordenarPreco();printf("Ordenado por preco (menor->maior)!\n");break;
			case 8:salvarProdutosEmArquivo();break;
			case 9:carregarProdutosDeArquivo();break;
			case 11:ordenarNomeDesc();printf("Ordenado por nome Z-A!\n");break;
			case 12:ordenarPrecoDesc();printf("Ordenado por preco (maior->menor)!\n");break;
			case 10:exit(0);
			default:printf("Opcao invalida!\n");
		}
	}
	return 0;
}
