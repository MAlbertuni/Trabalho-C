#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int tamanhoVetorAlunos = 3; //constante com tamanho do vetor dos alunos para facilitar nos meu testes

struct Endereco // estrutura do endereço
{
    char rua[40];
    int numeroCasa;
    char bairro[20];
    char cidade[20];
    char estado[20];
};
typedef struct Endereco Endereco;

struct Materia // estrutura da matéria
{
    char nomeMateria[20];
    float mediaMateria;
};
typedef struct Materia Materia;

struct Aluno // estrutura do aluno
{
    char nome[25];
    int RA;
    //char dataNascimento[10];
    //Endereco endereco1;
    //Endereco endereco2;
    //Materia materia[5];
};
typedef struct Aluno Aluno;

struct ArrayDinamico // estrutura do array dinâmico
{
    bool ordenado;     // true indica que quer manter o array ordenado.
    int tamanho;       // número máximo de elementos que podemos armazenados no array.
    int quantidade;    // quantidade atual de elementos armazenados
    int *dados;        // quantidade atual de elementos armazenados
    Aluno **ptr_dados; // array de int que representa nossos dados.
};
typedef struct ArrayDinamico ArrayDinamico;

ArrayDinamico *criaArryaDinamico(int tamanhoArray, bool ordenado)
{
    ArrayDinamico *arrayDinamico = (ArrayDinamico *)malloc(sizeof(ArrayDinamico));
    arrayDinamico->ordenado = ordenado;
    arrayDinamico->quantidade = 0;
    arrayDinamico->tamanho = tamanhoArray;
    arrayDinamico->ptr_dados = (Aluno **)calloc(tamanhoArray, sizeof(Aluno **));

    return arrayDinamico;
}

void destroiArrayDinamico(ArrayDinamico **arrayDinamicoMem)
{
    ArrayDinamico *arrayDinamico = *arrayDinamicoMem;
    free(arrayDinamico->dados);
    free(arrayDinamico);
    *arrayDinamicoMem = NULL;
}

bool VerificaDisponibilidade(ArrayDinamico *arrayDinamico)
{
    if (arrayDinamico->tamanho == arrayDinamico->quantidade)
    {
        return 0;
    }
    return 1;
}

//se array estiver cheio, aumentamos 2 vezes o seu tamanho.
void aumentarArrayDinamico(ArrayDinamico *arrayDinamico)
{
    //printf("Aumentando 2 vezes o tamanho atual do array( 2 * %d )\n", arrayDinamico->tamanho);

    int *temp = arrayDinamico->dados;
    //arrayDinamico->tamanho *= 2;
    arrayDinamico->tamanho = arrayDinamico->tamanho * 2;

    arrayDinamico->dados = (Aluno *)calloc(arrayDinamico->tamanho, sizeof(Aluno));

    for (int i = 0; i < arrayDinamico->tamanho; i++)
    {
        arrayDinamico->dados[i] = temp[i];
    }
    free(temp);
}

//diminuir o tamanho do array pela metade quando tiver 1/4 ou 25% cheio
void diminuirArrayDinamico(ArrayDinamico *arrayDinamico)
{
    if ((arrayDinamico->quantidade < arrayDinamico->tamanho / 4) &&
        (arrayDinamico->tamanho >= 4))
    {

        //printf("Diminuindo o tamanho atual do array pela metade ( %d / 2 )\n", arrayDinamico->tamanho);

        int *temp = arrayDinamico->dados;
        arrayDinamico->tamanho /= 2;
        //arrayDinamico->tamanho = array_dinamico->tamanho / 2;

        arrayDinamico->dados = (Aluno *)calloc(arrayDinamico->tamanho, sizeof(Aluno));

        for (int j = 0; j < arrayDinamico->tamanho; j++)
        {
            arrayDinamico->dados[j] = temp[j];
        }
        free(temp);
    }
}

void imprimeArray(const ArrayDinamico *arrayDinamico)
{

    //Implemente
    for (int j = 0; j < arrayDinamico->tamanho; j++)
    {
        printf("Nome: %s - Idade: %d\n", arrayDinamico->dados[j]);
    }
}

void ordenaArray(const ArrayDinamico *arrayDinamico)
{

    //Implemente
}

void adicionarArray(ArrayDinamico *arrayDinamico, Aluno valor)
{

    //implemente
}

int buscaArray(ArrayDinamico *arrayDinamico, int valor)
{

    //implemente

    return 0;
}

void removeArray(ArrayDinamico *arrayDinamico, int index)
{

    //implemente
}

int acessarArray(const ArrayDinamico *arrayDinamico, int index)
{
    if (arrayDinamico->tamanho > index)
    {
        return 1;
    }
    return 0;
}

int acessarVerificado(const ArrayDinamico *arrayDinamico, int index)
{ // verifica se tem elemento

    if (arrayDinamico->quantidade > index)
    {
        return 1;
    }
    return 0;
}

int tamanhoArray(const ArrayDinamico *arrayDinamico)
{
    return arrayDinamico->tamanho;
}

int quantidadeArray(const ArrayDinamico *arrayDinamico)
{
    return arrayDinamico->quantidade;
}

void carregarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo)
{

    //ler o arquivo
    FILE *file = fopen("aalunos.txt", "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo");
    }
    fclose(file);
}

void gravarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo)
{
    //se arquivo já existir remove tudo e cria novamente
    //gravar no arquivo no disco
    FILE *file = fopen("alunos.txt", "wb");
    if (!file)
    {
        return 1;
    }
    char nome[30];
    printf("Nome: ");
    scanf("%s", nome);

    int RA;
    printf("\nRA: ");
    scanf("%d", RA);

    // Print to file
    fprintf(file, "%s,%d\n", nome, RA);

    // Close filef
    fclose(file);
}

void main() // metodo principal
{

    int tamanho = 4; //vamos começar com um tamanho fixo e depois vamos dobrando o seu tamanho.

    bool ordenado = false;

    ArrayDinamico *arrayDinamico = criaArryaDinamico(tamanho, ordenado);

    Aluno *aluno01 = (Aluno *)malloc(1 * sizeof(Aluno *));

    void adicionarArray(arrayDinamico, aluno01);

    //Aluno *aluno_do_array = array_dinamico->ptr_dados[0];

    //printf("%d %s\n", aluno01->ra, aluno_do_array->nome );

    free(aluno01);
    destroiArrayDinamico(&arrayDinamico);

    // Aluno aluno[tamanhoVetorAlunos]; // vetor de 20 alunos (estrutura)
    // apagaInformacoes(aluno, -1);

    // int escolha = 0;

    // while (escolha != 6) //menu que funciona até escolherem o 6
    // {
    //     printf("Menu de Operacoes\n");
    //     printf("1 - Criar/Armazenar novo aluno.\n");
    //     printf("2 - Verificar se tem espaco para armazenar novo aluno.\n");
    //     printf("3 - Apagar informacoes de algum aluno.\n");
    //     printf("4 - Ver informacao pelo RA do aluno.\n");
    //     printf("5 - Ver informacao de todos os alunos.\n");
    //     printf("6 - Sair da aplicacao.\n");
    //     scanf("%d", &escolha);
    //     switch (escolha)
    //     {
    //     case 1:
    //         CriarAluno(aluno);
    //         break;
    //     case 2:
    //         VerificaArmazenamento(aluno);
    //         break;
    //     case 3:
    //         ApagaAluno(aluno);
    //         break;
    //     case 4:
    //         InformacoesRA(aluno);
    //         break;
    //     case 5:
    //         InformacaoTodos(aluno);
    //         break;
    //     case 6:
    //         printf("Saindo...");
    //         system("pause");
    //         break;
    //     default:
    //         printf("Essa opcao nao existe!");
    //         break;
    //     }
    // }
}
