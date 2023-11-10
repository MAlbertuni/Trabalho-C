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
    arrayDinamico->tamanho = arrayDinamico->tamanho * 2;

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
        arrayDinamico->tamanho = arrayDinamico->tamanho / 2;

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
        printf("Index %d - Nome: %s - RA: %d\n", i, arrayDinamico->ptr_dados[i]->nome, arrayDinamico->ptr_dados[i]->RA);
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
    if (index < arrayDinamico->quantidade)
    {
        free(arrayDinamico->ptr_dados[index]);
        arrayDinamico->ptr_dados[index] = arrayDinamico->ptr_dados[arrayDinamico->quantidade - 1];
        arrayDinamico->ptr_dados[arrayDinamico->quantidade - 1] = NULL;
        arrayDinamico->quantidade = arrayDinamico->quantidade - 1;
    }
    else
    {
        printf("Esse index nao existe.\n");
    }
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
    FILE *file = fopen("alunos.txt", "rb");
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
    if ((index < arrayDinamico->quantidade) && (index > -1))
    {
        return arrayDinamico->ptr_dados[index];
    }
    else {
        printf("Index nao existe. Retornando ultimo aluno da lista.\n");
        return arrayDinamico->ptr_dados[arrayDinamico->quantidade - 1];
    }
}

void imprimeAluno(Aluno *aluno)
{
    printf("%s - %d\n", aluno->nome, aluno->RA);
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
            printf("\n");
            printf("Digite o nome do aluno:\n");
            scanf("%s29", &nomeAluno); //pega a string com o nome do aluno
            printf("\n");
            printf("Digite o RA do aluno:\n");
            scanf("%d", &raAluno); //pega o RA do aluno
            printf("\n");

            Aluno *aluno = criarAluno(raAluno, nomeAluno); //aqui dentro ele salva no endereço da Memoria o nome e RA
            adicionarArray(arrayDinamico, aluno);          //adiciona o ponteiro do aluno dentro do array dinamico
            break;
        case 2: //procurar aluno no array
            printf("\n");
            imprimeArray(arrayDinamico);
            printf("Digite o index que deseja acessar:\n");
            scanf("%d", &index);                                     //pega o index do aluno
            printf("\n");
            Aluno *alunoProcura = buscarAluno(arrayDinamico, index); //procura o index dentro do array
            imprimeAluno(alunoProcura);                              //imprime as informações que foram salvas no aluno pelo retorno
            printf("\n");
            break;
        case 3: //apagar index do array
            printf("\n");
            imprimeArray(arrayDinamico);
            printf("Digite o index que deseja apagar:\n");
            scanf("%d", &index);               //pega qual o index
            removeArray(arrayDinamico, index); //remove o index e reorganiza para diinuir posição
            printf("\n");
            printf("Index com aluno removido!\n");
            printf("\n");
            break;
        case 4: //aqui imprime os alunos do array
            printf("\n");
            imprimeArray(arrayDinamico);
            printf("\n");
            break;
        case 5: //aqui ordena os alunos no array
            printf("\n");
            ordenaArray(arrayDinamico);
            printf("\n");
            break;
        case 6: //verifica se uma posição existe no array
            printf("\n");
            printf("Digite o index que deseja verificar se existe:\n");
            scanf("%d", &index);                //pega posição
            acessarArray(arrayDinamico, index); //acessa o array na posição
            printf("\n");
            break;
        case 7: //verifica se uma posição do array possui algum aluno salvo
            printf("\n");
            printf("Digite o index que deseja verificar se possui dados:\n");
            scanf("%d", &index);                     //pega a posição
            acessarVerificado(arrayDinamico, index); //ve se na posição algum aluno existe
            printf("\n");
            break;
        case 8: //aumenta o tamanho do array
            printf("\n");
            printf("O array possui tamanho: %d\n", arrayDinamico->tamanho);
            aumentarArrayDinamico(arrayDinamico);
            printf("\n");
            printf("O array agora possui tamanho: %d\n", arrayDinamico->tamanho);
            printf("\n");
            break;
        case 9: //diminui o tamanho do array
            printf("\n");
            printf("O array possui tamanho: %d\n", arrayDinamico->tamanho);
            diminuirArrayDinamico(arrayDinamico);
            printf("\n");
            printf("O array agora possui tamanho: %d\n", arrayDinamico->tamanho);
            printf("\n");
            break;
        case 10: //verifica o tamanho que o array está no momento
            printf("\n");
            printf("O array possui tamanho %d\n", tamanhoArray(arrayDinamico));
            printf("\n");
            break;
        case 11: //verificar quantos alunos possuimos no array no momento
            printf("\n");
            printf("O array possui quantidade %d\n", quantidadeArray(arrayDinamico));
            printf("\n");
            break;
        case 12: //salva no arquivo os alunos
            printf("\n");
            printf("Digite o caminho do arquivo a ser salvo:\n");
            gets(caminhoArquivo);
            gravarArquivo(arrayDinamico, caminhoArquivo);
            printf("\n");
            break;
        case 13: //destroi o array dinamico e apaga ele da memoria e sai do programa
            destroiArrayDinamico(&arrayDinamico);
            printf("\n");
            printf("Saindo...\n");
            system("pause");
            exit(1);
            break;
        default: //default
            printf("\n");
            printf("Essa opcao nao existe!\n");
            printf("\n");
            break;
        }
    }
}
