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
    int *temp = arrayDinamico->dados;
    arrayDinamico->tamanho *= 2;

    arrayDinamico->dados = (int *)calloc(arrayDinamico->tamanho, sizeof(int));
    int i;
    for (i = 0; i < arrayDinamico->tamanho; i++)
    {
        arrayDinamico->dados[i] = temp[i];
    }
    free(temp);
}

//diminuir o tamanho do array pela metade quando tiver 1/4 ou 25% cheio
void diminuirArrayDinamico(ArrayDinamico *arrayDinamico)
{
    if ((arrayDinamico->quantidade < arrayDinamico->tamanho / 4) && (arrayDinamico->tamanho >= 4))
    {
        int *temp = arrayDinamico->dados;
        arrayDinamico->tamanho /= 2;

        arrayDinamico->dados = (int *)calloc(arrayDinamico->tamanho, sizeof(int));
        int i;
        for (i = 0; i < arrayDinamico->tamanho; i++)
        {
            arrayDinamico->dados[i] = temp[i];
        }
        free(temp);
    }
}

void imprimeArray(const ArrayDinamico *arrayDinamico)
{
    int i;
    for (i = 0; i < arrayDinamico->tamanho; i++)
    {
        printf("Nome: %s - Idade: %d\n", arrayDinamico->dados[i]);
    }
}

void ordenaArray(const ArrayDinamico *arrayDinamico)
{
    //Implemente
}

void adicionarArray(ArrayDinamico *arrayDinamico, Aluno *aluno)
{
    arrayDinamico->ptr_dados[arrayDinamico->quantidade] = aluno;
    arrayDinamico->quantidade = arrayDinamico->quantidade + 1;
}

int buscaArray(ArrayDinamico *arrayDinamico, int valor)
{
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        if (arrayDinamico->dados[i] == valor)
        {
            return i;
        }
    }
    return -1;
}

void removeArray(ArrayDinamico *arrayDinamico, int index)
{
    free(arrayDinamico->ptr_dados[index]);
    arrayDinamico->ptr_dados[index] = arrayDinamico->ptr_dados[arrayDinamico->quantidade];
    arrayDinamico->ptr_dados[arrayDinamico->quantidade] = NULL;
    arrayDinamico->quantidade = arrayDinamico->quantidade - 1;
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
{
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
    FILE *file = fopen("aalunos.txt", "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo");
    }
    fclose(file);
}

void gravarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo)
{
    FILE *file = fopen("alunos.txt", "wb");
    if (file)
    {
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
}

Aluno *criarAluno(int ra, char *nome)
{
    Aluno *aluno01 = (Aluno *)malloc(1 * sizeof(Aluno *));
    aluno01->RA = ra;
    strcpy(aluno01->nome, nome);

    return aluno01;
}

Aluno *buscarAluno(ArrayDinamico *arrayDinamico, int index)
{
    return arrayDinamico->ptr_dados[index];
}

void imprimeAluno(Aluno *aluno)
{
    printf("%d - %s\n", aluno->RA, aluno->nome);
}

void main() // metodo principal
{
    int tamanho = 0;
    bool ordenado = false;

    ArrayDinamico *arrayDinamico;

    char nomeAluno[30];
    int raAluno;
    //free(aluno);
    //destroiArrayDinamico(&arrayDinamico);

    int escolha = 0;
    while (escolha != 6) //menu que funciona até escolherem o 6
    {
        printf("Menu de Operacoes\n");
        printf("1 - Criar array dinamico.\n");
        printf("2 - Salvar novo aluno.\n");
        printf("3 - Buscar aluno por index.\n");
        printf("4 - Diminuir index do array.\n");
        printf("5 - Imprimir todos os alunos.\n");
        printf("6 - Sair da aplicacao.\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            printf("Qual será o tamanho do array?\n");
            scanf("%d", &tamanho);
            arrayDinamico = criaArryaDinamico(tamanho, ordenado);
            break;
        case 2:
            printf("Digite o nome do aluno:\n");
            gets(nomeAluno);
            printf("Digite o RA do aluno:\n");
            scanf("%d", raAluno);

            Aluno *aluno = (Aluno *)malloc(1 * sizeof(Aluno *));
            aluno = criarAluno(raAluno, nomeAluno);
            adicionarArray(arrayDinamico, aluno);
            break;
        case 3:
            printf("Digite o index que deseja acessar:\n");
            int index;
            scanf("%d", index);
            aluno = buscarAluno(arrayDinamico, index);
            imprimeAluno(aluno);
            break;
        case 4:
            printf("Digite o index que deseja apagar:\n");
            int index;
            scanf("%d", index);
            removeArray(arrayDinamico, index);
            printf("Index com aluno removido!");
            break;
        case 5:
            imprimeArray(arrayDinamico);
            break;
        case 6:
            printf("Saindo...");
            system("pause");
            break;
        default:
            printf("Essa opcao nao existe!");
            break;
        }
    }
}
