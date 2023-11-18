#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Endereco // estrutura do endereço
{
    char rua[40];
    int numeroCasa;
    char bairro[30];
    char cidade[30];
    char estado[30];
};
typedef struct Endereco Endereco;

struct Materia // estrutura da matéria
{
    char nomeMateria[30];
    float mediaMateria;
};
typedef struct Materia Materia;

struct Aluno // estrutura do aluno
{
    char nome[30];
    int RA;
    char dataNascimento[11];
    Endereco endereco1;
    Endereco endereco2;
    Materia materia[5];
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
        arrayDinamico->ptr_dados[i] = NULL;
    }
    free(arrayDinamico->ptr_dados);
    free(arrayDinamico);
    *arrayDinamicoMem = NULL;
}

int VerificaDisponibilidade(ArrayDinamico *arrayDinamico)
{
    if (arrayDinamico->tamanho == arrayDinamico->quantidade)
    {
        return 1;
    }
    return 0;
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
        temp[i] = NULL;
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
            temp[i] = NULL;
        }
        free(temp);
    }
}

int comparaAlunoNome(const void *aluno1, const void *aluno2)
{
    return strcmp((*(Aluno *)aluno1).nome, (*(Aluno *)aluno2).nome);
}

int comparaAlunoRA(const void *aluno1, const void *aluno2)
{
    return (*(Aluno *)aluno1).RA - (*(Aluno *)aluno2).RA;
}

// odenação quick sort

// função que troca posições no array
void trocarPosicoes(void **array, int pos1, int pos2)
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
            trocarPosicoes(array, i, j); // alterar as posições dos elementos antes e depois do elemento ordenado
        }
    }
    trocarPosicoes(array, i + 1, r); // mova o elemento inicial para sua posição final

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

void imprimeArray(ArrayDinamico *arrayDinamico)
{
    ordenaArray((void **)arrayDinamico->ptr_dados, 0, arrayDinamico->quantidade - 1, comparaAlunoNome); // ordena antes de imprimir
    printf("Imprimindo alunos:\n");
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        printf("Index %d - Nome: %s - RA: %d - Data de Nascimento: %s\n", i, arrayDinamico->ptr_dados[i]->nome, arrayDinamico->ptr_dados[i]->RA, arrayDinamico->ptr_dados[i]->dataNascimento);
    }
}

void adicionarArray(ArrayDinamico *arrayDinamico, Aluno *aluno)
{
    if (VerificaDisponibilidade(arrayDinamico) == 1) // ve se tem espaço para armazenar novo aluno
    {                                                // aqui é se está lotado o array
        aumentarArrayDinamico(arrayDinamico);        // dobramos o tamanho dele
    }
    arrayDinamico->ptr_dados[arrayDinamico->quantidade] = aluno;
    arrayDinamico->quantidade = arrayDinamico->quantidade + 1;
}

int buscaArray(ArrayDinamico *arrayDinamico, int valorRA)
{
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        if (arrayDinamico->ptr_dados[i]->RA == valorRA)
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
        diminuirArrayDinamico(arrayDinamico);
    }
    else
    {
        printf("Esse index nao existe.\n");
    }
}

Aluno *acessarArray(const ArrayDinamico *arrayDinamico, int index)
{
    if (arrayDinamico->tamanho > index)
    {
        return arrayDinamico->ptr_dados[index];
    }
    return NULL;
}

Aluno *acessarVerificado(const ArrayDinamico *arrayDinamico, int index)
{
    if (arrayDinamico->quantidade > index)
    {
        return arrayDinamico->ptr_dados[index];
    }
    return NULL;
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

    file = fopen(caminhoArquivo, "rb"); // Abre o arquivo em modo de leitura binária
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (!feof(file))
    {
        Aluno *aluno = malloc(sizeof(Aluno));
        if (fread(aluno, sizeof(Aluno), 1, file))
        {
            adicionarArray(arrayDinamico, aluno);
        }
        else
        {
            free(aluno);
        }
    }

    fclose(file);
}

// gravar dados do ponteiro no arquivo
void gravarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo)
{
    FILE *file;

    file = fopen(caminhoArquivo, "wb"); // Abre o arquivo em modo de escrita binária
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i;
    // Escreve os dados dos alunos no arquivo
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        fwrite(&arrayDinamico->ptr_dados[i], sizeof(Aluno), 1, file);
    }

    fclose(file); // Fecha o arquivo
}

Aluno *buscarAluno(ArrayDinamico *arrayDinamico, int valorRA)
{
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        if (arrayDinamico->ptr_dados[i]->RA == valorRA)
        {
            return arrayDinamico->ptr_dados[i];
        }
    }
    printf("Nao existe aluno com este RA.\n");
    return NULL;
}

void imprimeAluno(Aluno *aluno)
{
    if (aluno != NULL)
    {
        printf("\nALUNO \nNome: %s \nRA: %d \nData de Nascimento: %s \nEndereco 1 - Rua: %s \nEndereco 1 - Numero Casa: %d \nEndereco 1 - Estado: %s \nEndereco 1 - Cidade: %s \nEndereco 1 - Bairro: %s \nEndereco 2 - Rua: %s \nEndereco 2 - Numero Casa: %d \nEndereco 2 - Estado: %s \nEndereco 2 - Cidade: %s \nEndereco 2 - Bairro: %s \nMateria 1 - Nome: %s \nMateria 1 - Media: %f \nMateria 2 - Nome: %s \nMateria 2 - Media: %f \nMateria 3 - Nome: %s \nMateria 3 - Media: %f \nMateria 4 -Nome: %s \nMateria 4 - Media: %f \nMateria 5 - Nome: %s \nMateria 5 - Media: %f \n",
               aluno->nome,
               aluno->RA,
               aluno->dataNascimento,
               aluno->endereco1.rua,
               aluno->endereco1.numeroCasa,
               aluno->endereco1.estado,
               aluno->endereco1.cidade,
               aluno->endereco1.bairro,
               aluno->endereco2.rua,
               aluno->endereco2.numeroCasa,
               aluno->endereco2.estado,
               aluno->endereco2.cidade,
               aluno->endereco2.bairro,
               aluno->materia[0].nomeMateria,
               aluno->materia[0].mediaMateria,
               aluno->materia[1].nomeMateria,
               aluno->materia[1].mediaMateria,
               aluno->materia[2].nomeMateria,
               aluno->materia[2].mediaMateria,
               aluno->materia[3].nomeMateria,
               aluno->materia[3].mediaMateria,
               aluno->materia[4].nomeMateria,
               aluno->materia[4].mediaMateria);
    }
}

void menuCriarAluno(ArrayDinamico *arrayDinamico)
{
    Aluno *aluno = (Aluno *)malloc(1 * sizeof(Aluno *));

    printf("\n");
    printf("Digite o nome do aluno:\n");
    scanf("%s", aluno->nome);
    printf("Digite o RA do aluno:\n");
    scanf("%d", &aluno->RA);
    printf("Digite a data de nascimento do aluno:\n");
    scanf("%s", &aluno->dataNascimento); // pega a string com o nome do aluno
    printf("Digite a rua 1 do aluno:\n");
     scanf("%s", &aluno->endereco1.rua); // pega a string com o nome do aluno
    printf("Digite o numero 1 da casa do aluno:\n");
    scanf("%d", &aluno->endereco1.numeroCasa); // pega a string com o nome do aluno
    printf("Digite o bairro 1 do aluno:\n");
    scanf("%s", &aluno->endereco1.bairro); // pega a string com o nome do aluno
    printf("Digite a cidade 1 do aluno:\n");
    scanf("%s", &aluno->endereco1.cidade); // pega a string com o nome do aluno
    printf("Digite o estado 1 do aluno:\n");
    scanf("%s", &aluno->endereco1.estado); // pega a string com o nome do aluno
    printf("Digite a rua 2 do aluno:\n");
    scanf("%s", &aluno->endereco2.rua); // pega a string com o nome do aluno
    printf("Digite o numero 2 da casa do aluno:\n");
    scanf("%d", &aluno->endereco2.numeroCasa); // pega a string com o nome do aluno
    printf("Digite o bairro 2 do aluno:\n");
    scanf("%s", &aluno->endereco2.bairro); // pega a string com o nome do aluno
    printf("Digite a cidade 2 do aluno:\n");
    scanf("%s", &aluno->endereco2.cidade); // pega a string com o nome do aluno
    printf("Digite o estado 2 do aluno:\n");
    scanf("%s", &aluno->endereco2.estado); // pega a string com o nome do aluno
    printf("Digite o nome da materia 1 do aluno:\n");
    scanf("%s", &aluno->materia[0].nomeMateria); // pega a string com o nome do aluno
    printf("Digite a media da materia do aluno:\n");
    scanf("%f", &aluno->materia[0].mediaMateria);
    printf("Digite o nome da materia 2 do aluno:\n");
    scanf("%s", &aluno->materia[1].nomeMateria); // pega a string com o nome do aluno
    printf("Digite a media da materia do aluno:\n");
    scanf("%f", &aluno->materia[1].mediaMateria);
    printf("Digite o nome da materia 3 do aluno:\n");
    scanf("%s", &aluno->materia[2].nomeMateria); // pega a string com o nome do aluno
    printf("Digite a media da materia 3 do aluno:\n");
    scanf("%f", &aluno->materia[2].mediaMateria);
    printf("Digite o nome da materia 4 do aluno:\n");
    scanf("%s", &aluno->materia[3].nomeMateria); // pega a string com o nome do aluno
    printf("Digite a media da materia 4 do aluno:\n");
    scanf("%f", &aluno->materia[3].mediaMateria);
    printf("Digite o nome da materia 5 do aluno:\n");
    scanf("%s", &aluno->materia[4].nomeMateria); // pega a string com o nome do aluno
    printf("Digite a media da materia 5 do aluno:\n");
    scanf("%f", &aluno->materia[4].mediaMateria);
    printf("\n");

    adicionarArray(arrayDinamico, aluno); // adiciona o ponteiro do aluno dentro do array dinamico

    printf("\n");
    printf("Aluno adicionado com sucesso!\n");
    printf("\n");
}

void menuBuscarAluno(ArrayDinamico *arrayDinamico)
{
    int raAluno;
    printf("\n");
    imprimeArray(arrayDinamico);
    printf("Digite o RA que deseja acessar:\n");
    scanf("%d", &raAluno); // pega o RA do aluno
    printf("\n");
    Aluno *alunoProcura = buscarAluno(arrayDinamico, raAluno); // procura o RA dentro do array
    imprimeAluno(alunoProcura);                                // imprime as informações que foram salvas no aluno pelo retorno
    printf("\n");
    free(alunoProcura);
}

void menuRemoveAluno(ArrayDinamico *arrayDinamico)
{
    int raAluno, index;
    printf("\n");
    imprimeArray(arrayDinamico);
    printf("Digite o RA que deseja apagar:\n");
    scanf("%d", &raAluno); // pega qual o RA
    printf("\n");
    index = buscaArray(arrayDinamico, raAluno);
    if (index != -1)
    {
        removeArray(arrayDinamico, index); // remove o aluno e reorganiza para diminuir posição
        printf("\n");
    }
    else
    {
        printf("Este RA nao existe!\n");
        printf("\n");
    }
}

void main(int argc, char *argv[]) // metodo principal
{
    ArrayDinamico *arrayDinamico = criaArryaDinamico(4, false); // cria o ponteiro de Array Dinamico
    char caminhoArquivo[250];                                   // Endereço do arquivo

    if (argc == 2)
    {
        strcpy(caminhoArquivo, argv[argc - 1]);
    }

    carregarArquivo(arrayDinamico, caminhoArquivo);

    int escolha = 0;     // int da escolha do menu
    while (escolha != 6) // menu que funciona até escolherem o 13
    {
        printf("Menu de Operacoes\n");
        printf("1 - Salvar novo aluno.\n");
        printf("2 - Buscar aluno pelo RA.\n");
        printf("3 - Remover aluno do array.\n");
        printf("4 - Imprimir todos os alunos.\n");
        printf("5 - Checar tamanho e quantidade do vetor.\n");
        printf("6 - Sair.\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1: // salvar novo aluno
            menuCriarAluno(arrayDinamico);
            break;
        case 2: // procurar aluno no array
            menuBuscarAluno(arrayDinamico);
            break;
        case 3: // apagar aluno do array
            menuRemoveAluno(arrayDinamico);
            break;
        case 4: // aqui imprime os alunos do array
            printf("\n");
            imprimeArray(arrayDinamico);
            printf("\n");
            break;
        case 5: // verifica o tamanho e a quantidade do array
            printf("\n");
            printf("O array possui tamanho: %d - e a quantidade: %d\n", tamanhoArray(arrayDinamico), quantidadeArray(arrayDinamico));
            printf("\n");
            break;
        case 6: // destroi o array dinamico e apaga ele da memoria e sai do programa
            gravarArquivo(arrayDinamico, caminhoArquivo);
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
