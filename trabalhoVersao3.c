#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//const int tamanhoVetorAlunos = 3; // constante com tamanho do vetor dos alunos para facilitar nos meu testes

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
    // char dataNascimento[10];
    // Endereco endereco1;
    // Endereco endereco2;
    // Materia materia[5];
};
typedef struct Aluno Aluno;

struct ArrayDinamico // estrutura do array dinâmico
{
    bool ordenado;     // true indica que quer manter o array ordenado.
    int tamanho;       // número máximo de elementos que podemos armazenados no array.
    int quantidade;    // quantidade atual de elementos armazenados
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
    free(arrayDinamico->ptr_dados);
    free(arrayDinamico);
    *arrayDinamicoMem = NULL;
}

int VerificaDisponibilidade(ArrayDinamico *arrayDinamico)
{
    if (arrayDinamico->tamanho == arrayDinamico->quantidade)
    {
        return 0;
    }
    return 1;
}

// se array estiver cheio, aumentamos 2 vezes o seu tamanho.
void aumentarArrayDinamico(ArrayDinamico *arrayDinamico)
{
    Aluno **temp = arrayDinamico->ptr_dados;
    arrayDinamico->tamanho *= 2;

    arrayDinamico->ptr_dados = (Aluno **)calloc(arrayDinamico->tamanho, sizeof(Aluno));
    int i;
    for (i = 0; i < arrayDinamico->tamanho; i++)
    {
        arrayDinamico->ptr_dados[i] = temp[i];
    }
    free(temp);
}

// diminuir o tamanho do array pela metade quando tiver 1/4 ou 25% cheio
void diminuirArrayDinamico(ArrayDinamico *arrayDinamico)
{
    if ((arrayDinamico->quantidade < arrayDinamico->tamanho / 4) && (arrayDinamico->tamanho >= 4))
    {
        Aluno **temp = arrayDinamico->ptr_dados;
        arrayDinamico->tamanho /= 2;

        arrayDinamico->ptr_dados = (Aluno **)calloc(arrayDinamico->tamanho, sizeof(Aluno));
        int i;
        for (i = 0; i < arrayDinamico->tamanho; i++)
        {
            arrayDinamico->ptr_dados[i] = temp[i];
        }
        free(temp);
    }
}

void imprimeArray(ArrayDinamico *arrayDinamico)
{
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        printf("Nome: %s - RA: %d\n", arrayDinamico->ptr_dados[i]->nome, arrayDinamico->ptr_dados[i]->RA);
    }
}

void ordenaArray(ArrayDinamico *arrayDinamico)
{
    // Implemente
}

void adicionarArray(ArrayDinamico *arrayDinamico, Aluno *aluno)
{
    if (VerificaDisponibilidade(arrayDinamico) == 0) //ve se tem espaço para armazenar novo aluno
    {                                                //aqui é se está lotado o array
        aumentarArrayDinamico(arrayDinamico);        //dobramos o tamanho dele
    }
    arrayDinamico->ptr_dados[arrayDinamico->quantidade] = aluno;
    arrayDinamico->quantidade = arrayDinamico->quantidade + 1;
}

int buscaArray(ArrayDinamico *arrayDinamico, Aluno valor)
{
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        // if (arrayDinamico->ptr_dados[i] == valor)
        // {
        //     return i;
        // }
    }
    return -1;
}

void removeArray(ArrayDinamico *arrayDinamico, int index)
{
    free(arrayDinamico->ptr_dados[index]);
    arrayDinamico->ptr_dados[index] = arrayDinamico->ptr_dados[arrayDinamico->quantidade];
    arrayDinamico->ptr_dados[arrayDinamico->quantidade - 1] = NULL;
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

// implementar leitura do arquivo e depois passar para o ponteiro
void carregarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo)
{
    FILE *file = fopen("aalunos.txt", "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo");
    }
    fclose(file);
}

// gravar dados do ponteiro no arquivo
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
    Aluno *aluno = (Aluno *)malloc(1 * sizeof(Aluno *));
    aluno->RA = ra;
    strcpy(aluno->nome, nome);

    return aluno;
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
    int tamanho = 4;                                                     // tamanhos pré-definidos
    bool ordenado = false;                                               // no começo ele não vai ser ordenado
    ArrayDinamico *arrayDinamico = criaArryaDinamico(tamanho, ordenado); // cria o ponteiro de Array Dinamico

    char nomeAluno[30];       //nome
    int raAluno;              //RA
    int index;                //Index
    char caminhoArquivo[250]; //Endereço do arquivo

    int escolha = 0;      //int da escolha do menu
    while (escolha != 13) // menu que funciona até escolherem o 13
    {
        printf("Menu de Operacoes\n");
        printf("1 - Salvar novo aluno.\n");
        printf("2 - Buscar aluno por index.\n");
        printf("3 - Remover aluno do array.\n");
        printf("4 - Imprimir todos os alunos.\n");
        printf("5 - Ordenar vetor dos alunos.\n");
        printf("6 - Acessar index do vetor.\n");
        printf("7 - Acessar index existente do vetor.\n");
        printf("8 - Aumentar vetor.\n");
        printf("9 - Diminuir vetor.\n");
        printf("10 - Checar tamanho do vetor.\n");
        printf("11 - Checar quantidade no vetor.\n");
        printf("12 - Salvar no arquivo.\n");
        printf("13 - Sair.\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1: //salvar novo aluno
            printf("Digite o nome do aluno:\n");
            scanf("%s29", &nomeAluno); //pega a string com o nome do aluno
            printf("Digite o RA do aluno:\n");
            scanf("%d", &raAluno); //pega o RA do aluno

            Aluno *aluno = criarAluno(raAluno, nomeAluno); //aqui dentro ele salva no endereço da Memoria o nome e RA
            adicionarArray(arrayDinamico, aluno);          //adiciona o ponteiro do aluno dentro do array dinamico
            break;
        case 2: //procurar aluno no array
            printf("Digite o index que deseja acessar:\n");
            scanf("%d", &index);                                     //pega o index do aluno
            Aluno *alunoProcura = buscarAluno(arrayDinamico, index); //procura o index dentro do array
            imprimeAluno(alunoProcura);                              //imprime as informações que foram salvas no aluno pelo retorno
            break;
        case 3: //apagar index do array
            printf("Digite o index que deseja apagar:\n");
            scanf("%d", &index);               //pega qual o index
            removeArray(arrayDinamico, index); //remove o index e reorganiza para diinuir posição
            printf("Index com aluno removido!");
            break;
        case 4: //aqui imprime os alunos do array
            imprimeArray(arrayDinamico);
            break;
        case 5: //aqui ordena os alunos no array
            ordenaArray(arrayDinamico);
            break;
        case 6: //verifica se uma posição existe no array
            printf("Digite o index que deseja verificar se existe:\n");
            scanf("%d", &index);                //pega posição
            acessarArray(arrayDinamico, index); //acessa o array na posição
            break;
        case 7: //verifica se uma posição do array possui algum aluno salvo
            printf("Digite o index que deseja verificar se possui dados:\n");
            scanf("%d", &index);                     //pega a posição
            acessarVerificado(arrayDinamico, index); //ve se na posição algum aluno existe
            break;
        case 8: //aumenta o tamanho do array
            aumentarArrayDinamico(arrayDinamico);
            break;
        case 9: //diminui o tamanho do array
            diminuirArrayDinamico(arrayDinamico);
            break;
        case 10: //verifica o tamanho que o array está no momento
            printf("O array possui tamanho %d", tamanhoArray(arrayDinamico));
            break;
        case 11: //verificar quantos alunos possuimos no array no momento
            printf("O array possui quantidade %d", quantidadeArray(arrayDinamico));
            break;
        case 12: //salva no arquivo os alunos
            printf("Digite o caminho do arquivo a ser salvo:\n");
            gets(caminhoArquivo);
            gravarArquivo(arrayDinamico, caminhoArquivo);
            break;
        case 13: //destroi o array dinamico e apaga ele da memoria e sai do programa
            destroiArrayDinamico(&arrayDinamico);
            printf("Saindo...");
            system("pause");
            exit(1);
            break;
        default: //default
            printf("Essa opcao nao existe!");
            break;
        }
    }
    printf("Chegou aqui 2");
}
