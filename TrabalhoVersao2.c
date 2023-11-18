#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        free(arrayDinamico->ptr_dados[i]);
    }
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
    printf("Imprimindo alunos:\n");
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        printf("Index %d - Nome: %s - RA: %d\n", i, arrayDinamico->ptr_dados[i]->nome, arrayDinamico->ptr_dados[i]->RA);
    }
}

#pragma region COMPARADOR

int compare_strucs_pessoa_nome(const void *aluno1, const void *aluno2)
{
    return strcmp((*(Aluno *)aluno1).nome, (*(Aluno *)aluno2).nome);
}

int compare_strucs_pessoa_ra(const void *aluno1, const void *aluno2)
{
    return (*(Aluno *)aluno1).RA - (*(Aluno *)aluno2).RA;
}

// odenação quick sort

// função que troca posições no array
void trocar(void **array, int pos1, int pos2)
{

    void *temp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = temp;
}

int particionar(void **array, int p, int r, int (*compare)(const void *, const void *))
{

    void *value = array[r]; // elemento pivô
    int i = p - 1;
    int j;
    for (j = p; j < r; j++)
    { // com este loop, os valores são separados em 2 partições, as maiores e as menores do pivô
        if (compare(array[j], value) <= 0)
        {
            i = i + 1;
            trocar(array, i, j); // alterar as posições dos elementos antes e depois do elemento ordenado
        }
    }
    trocar(array, i + 1, r); // mova o elemento inicial para sua posição final

    return i + 1;
}

void ordenaArray(void **array, int p, int r, int (*compare)(const void *, const void *))
{

    if (p < r)
    {
        int q = particionar(array, p, r, compare); /* pivô */
        ordenaArray(array, p, q - 1, compare);
        ordenaArray(array, q + 1, r, compare);
    }
}

#pragma endregion COMPARADO

void adicionarArray(ArrayDinamico *arrayDinamico, Aluno *aluno)
{
    if (VerificaDisponibilidade(arrayDinamico) == 0) // ve se tem espaço para armazenar novo aluno
    {                                                // aqui é se está lotado o array
        aumentarArrayDinamico(arrayDinamico);        // dobramos o tamanho dele
    }
    arrayDinamico->ptr_dados[arrayDinamico->quantidade] = aluno;
    arrayDinamico->quantidade = arrayDinamico->quantidade + 1;
}

int buscaArray(ArrayDinamico *arrayDinamico, int valor)
{
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        if (arrayDinamico->ptr_dados[i]->RA == valor)
        {
            return i;
        }
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
        printf("Index com aluno removido!\n");
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
    FILE *file;

    int i = 0;

    file = fopen("alunos.bin", "rb"); // Abre o arquivo em modo de leitura binária
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while(!feof(file)) {
        Aluno *aluno = malloc(sizeof(Aluno));
        if(fread(aluno, sizeof(Aluno), 1, file)){
            adicionarArray(arrayDinamico, aluno);
            i++;
        }else {
            free(aluno);
        }
    }

    printf("Alunos lido com sucesso!\n");
    fclose(file);
}

// gravar dados do ponteiro no arquivo
void gravarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo)
{
    FILE *file;

    file = fopen("alunos.bin", "wb"); // Abre o arquivo em modo de escrita binária
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i;
        // Escreve os dados dos alunos no arquivo
    for(i = 0; i < arrayDinamico->quantidade; i++)
    {
        fwrite(arrayDinamico->ptr_dados[i], sizeof(Aluno), 1, file);
    }

    fclose(file); // Fecha o arquivo

    printf("Arquivo lido com sucesso.\n");

    return;
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
    else
    {
        printf("Index nao existe. Retornando ultimo aluno da lista.\n");
        return arrayDinamico->ptr_dados[arrayDinamico->quantidade - 1];
    }
}

void imprimeAluno(Aluno *aluno)
{
    printf("%s - %d\n", aluno->nome, aluno->RA);
}

void main(int argc, char *argv[]) // metodo principal
{
    int tamanho = 4;                                                     // tamanhos pré-definidos
    bool ordenado = false;                                               // no começo ele não vai ser ordenado
    ArrayDinamico *arrayDinamico = criaArryaDinamico(tamanho, ordenado); // cria o ponteiro de Array Dinamico
    carregarArquivo(arrayDinamico, "teste");

    char nomeAluno[30];       // nome
    int raAluno;              // RA
    int index;                // Index
    char caminhoArquivo[250]; // Endereço do arquivo

    if (argc == 2)
    {
        strcpy(caminhoArquivo, argv[argc - 1]);
    }

    int escolha = 0;      // int da escolha do menu
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
        case 1: // salvar novo aluno
            printf("\n");
            printf("Digite o nome do aluno:\n");
            scanf("%s29", &nomeAluno); // pega a string com o nome do aluno
            printf("\n");
            printf("Digite o RA do aluno:\n");
            scanf("%d", &raAluno); // pega o RA do aluno
            printf("\n");

            Aluno *aluno = criarAluno(raAluno, nomeAluno); // aqui dentro ele salva no endereço da Memoria o nome e RA
            adicionarArray(arrayDinamico, aluno);          // adiciona o ponteiro do aluno dentro do array dinamico
            break;
        case 2: // procurar aluno no array
            printf("\n");
            imprimeArray(arrayDinamico);
            printf("Digite o index que deseja acessar:\n");
            scanf("%d", &index); // pega o index do aluno
            printf("\n");
            Aluno *alunoProcura = buscarAluno(arrayDinamico, index); // procura o index dentro do array
            imprimeAluno(alunoProcura);                              // imprime as informações que foram salvas no aluno pelo retorno
            printf("\n");
            break;
        case 3: // apagar index do array
            printf("\n");
            imprimeArray(arrayDinamico);
            printf("Digite o index que deseja apagar:\n");
            scanf("%d", &index);               // pega qual o index
            printf("\n");
            removeArray(arrayDinamico, index); // remove o index e reorganiza para diinuir posição
            printf("\n");
            break;
        case 4: // aqui imprime os alunos do array
            printf("\n");
            imprimeArray(arrayDinamico);
            printf("\n");
            break;
        case 5: // aqui ordena os alunos no array
            printf("\n");
            ordenaArray((void **)arrayDinamico->ptr_dados, 0, arrayDinamico->quantidade - 1, compare_strucs_pessoa_nome);
            printf("Array foi ordenado, imprimindo nova ordem:\n");
            imprimeArray(arrayDinamico);
            printf("\n");
            break;
        case 6: // verifica se uma posição existe no array
            printf("\n");
            printf("Digite o index que deseja verificar se existe:\n");
            scanf("%d", &index);                // pega posição
            acessarArray(arrayDinamico, index); // acessa o array na posição
            printf("\n");
            break;
        case 7: // verifica se uma posição do array possui algum aluno salvo
            printf("\n");
            printf("Digite o index que deseja verificar se possui dados:\n");
            scanf("%d", &index);                     // pega a posição
            acessarVerificado(arrayDinamico, index); // ve se na posição algum aluno existe
            printf("\n");
            break;
        case 8: // aumenta o tamanho do array
            printf("\n");
            printf("O array possui tamanho: %d\n", arrayDinamico->tamanho);
            aumentarArrayDinamico(arrayDinamico);
            printf("\n");
            printf("O array agora possui tamanho: %d\n", arrayDinamico->tamanho);
            printf("\n");
            break;
        case 9: // diminui o tamanho do array
            printf("\n");
            printf("O array possui tamanho: %d\n", arrayDinamico->tamanho);
            diminuirArrayDinamico(arrayDinamico);
            printf("\n");
            printf("O array agora possui tamanho: %d\n", arrayDinamico->tamanho);
            printf("\n");
            break;
        case 10: // verifica o tamanho que o array está no momento
            printf("\n");
            printf("O array possui tamanho %d\n", tamanhoArray(arrayDinamico));
            printf("\n");
            break;
        case 11: // verificar quantos alunos possuimos no array no momento
            printf("\n");
            printf("O array possui quantidade %d\n", quantidadeArray(arrayDinamico));
            printf("\n");
            break;
        case 12: // salva no arquivo os alunos
            printf("\n");
            printf("Indo salvar no arquivo.\n");
            gravarArquivo(arrayDinamico, caminhoArquivo);
            printf("\n");
            break;
        case 13: // destroi o array dinamico e apaga ele da memoria e sai do programa
            destroiArrayDinamico(&arrayDinamico);
            printf("\n");
            printf("Saindo...\n");
            exit(1);
            break;
        default: // default
            printf("\n");
            printf("Essa opcao nao existe!\n");
            printf("\n");
            break;
        }
    }
}
