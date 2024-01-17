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

void imprimeArray(ArrayDinamico *arrayDinamico, int qtdInfo) // fiz o parametro qtdInfo para simplificar na hora de buscar ou remover, apenas quando pela opcao do menu for selecionado imprimir alunos ele imprime todas as informacoes
{
    

    ordenaArray((void **)arrayDinamico->ptr_dados, 0, arrayDinamico->quantidade - 1, comparaAlunoNome); // ordena antes de imprimir
    printf("Imprimindo alunos:\n");
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        if (qtdInfo == 2) // imprime todas as informações
        {
            printf("\n------------------------------\n");
            printf("Aluno %d\nNome: %s\nRA: %d\nData de Nascimento: %s\nEndereco 1:\n Rua: %s\n Numero Casa: %d\n Estado: %s\n Cidade: %s \n Bairro: %s\nEndereco 2:\n Rua: %s\n Numero Casa: %d\n Estado: %s\n Cidade: %s\n Bairro: %s\nMateria 1 - Nome: %s | Media: %f\nMateria 2 - Nome: %s | Media: %f\nMateria 3 - Nome: %s | Media: %f\nMateria 4 - Nome: %s | Media: %f\nMateria 5 - Nome: %s | Media: %f\n",
                   i,
                   arrayDinamico->ptr_dados[i]->nome,
                   arrayDinamico->ptr_dados[i]->RA,
                   arrayDinamico->ptr_dados[i]->dataNascimento,
                   arrayDinamico->ptr_dados[i]->endereco1.rua,
                   arrayDinamico->ptr_dados[i]->endereco1.numeroCasa,
                   arrayDinamico->ptr_dados[i]->endereco1.estado,
                   arrayDinamico->ptr_dados[i]->endereco1.cidade,
                   arrayDinamico->ptr_dados[i]->endereco1.bairro,
                   arrayDinamico->ptr_dados[i]->endereco2.rua,
                   arrayDinamico->ptr_dados[i]->endereco2.numeroCasa,
                   arrayDinamico->ptr_dados[i]->endereco2.estado,
                   arrayDinamico->ptr_dados[i]->endereco2.cidade,
                   arrayDinamico->ptr_dados[i]->endereco2.bairro,
                   arrayDinamico->ptr_dados[i]->materia[0].nomeMateria,
                   arrayDinamico->ptr_dados[i]->materia[0].mediaMateria,
                   arrayDinamico->ptr_dados[i]->materia[1].nomeMateria,
                   arrayDinamico->ptr_dados[i]->materia[1].mediaMateria,
                   arrayDinamico->ptr_dados[i]->materia[2].nomeMateria,
                   arrayDinamico->ptr_dados[i]->materia[2].mediaMateria,
                   arrayDinamico->ptr_dados[i]->materia[3].nomeMateria,
                   arrayDinamico->ptr_dados[i]->materia[3].mediaMateria,
                   arrayDinamico->ptr_dados[i]->materia[4].nomeMateria,
                   arrayDinamico->ptr_dados[i]->materia[4].mediaMateria);
            printf("\n------------------------------\n");
        }
        else // apenas o essencial aqui
        {
            printf("Aluno %d - Nome: %s - RA: %d - Data de Nascimento: %s\n", i, arrayDinamico->ptr_dados[i]->nome, arrayDinamico->ptr_dados[i]->RA, arrayDinamico->ptr_dados[i]->dataNascimento);
        }
    }
}

void adicionarArray(ArrayDinamico *arrayDinamico, Aluno *aluno)
{
    if (VerificaDisponibilidade(arrayDinamico) == 1) // ve se tem espaço para armazenar novo aluno
    {                                                // aqui é se está lotado o array
        aumentarArrayDinamico(arrayDinamico);        // dobramos o tamanho dele
    }
    arrayDinamico->ptr_dados[arrayDinamico->quantidade] = aluno; // adicionamos na posição quantidade(já que o array começa no 0)
    arrayDinamico->quantidade = arrayDinamico->quantidade + 1;   // depois aumentamos o valor da quantidade em 1 = 1 aluno adicionado
}

int buscaArray(ArrayDinamico *arrayDinamico, int valorRA)
{
    int i;
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        if (arrayDinamico->ptr_dados[i]->RA == valorRA) // RA de algum aluno igual ao que vem do parametro é match
        {
            return i; // retorna index desse aluno
        }
    }
    return -1; //-1 se não encontrar
}

void removeArray(ArrayDinamico *arrayDinamico, int index) // aqui nao ocorre a tratativa de verificação do index pq eu já uso a função procurar index antes de chamar esta
{
    free(arrayDinamico->ptr_dados[index]);                                                     // limpa a posição que queremos da memória
    arrayDinamico->ptr_dados[index] = arrayDinamico->ptr_dados[arrayDinamico->quantidade - 1]; // passamos para aquela posição o que tinha no final do array
    arrayDinamico->ptr_dados[arrayDinamico->quantidade - 1] = NULL;                            // deixamos nulo a ultima posição
    arrayDinamico->quantidade = arrayDinamico->quantidade - 1;                                 // removemos da quantidadade pq um aluno foi removido
    diminuirArrayDinamico(arrayDinamico);                                                      // chamamos pq talvez precise diminuir o array
    printf("\nAluno removido!\n");
}

Aluno *acessarArray(const ArrayDinamico *arrayDinamico, int index) // apenas acessa uma posição (pode ou não haver aluno nela)
{
    if (arrayDinamico->tamanho > index) // verifica se está dentro do (tamanho), menor (começa em 0, lógica), tem algum espaço ali (não precisa estar preenchido)
    {
        return arrayDinamico->ptr_dados[index]; // retorna o que tem ali
    }
    return NULL; // senao null
}

Aluno *acessarVerificado(const ArrayDinamico *arrayDinamico, int index) // verificado = contem aluno
{
    if (arrayDinamico->quantidade > index) // como a quantidade é a que salva numero de alunos, então se index for menor (começa em 0, lógica) tem aluno ali
    {
        return arrayDinamico->ptr_dados[index]; // retorna ele
    }
    return NULL; // senao nulo
}

int tamanhoArray(const ArrayDinamico *arrayDinamico)
{
    return arrayDinamico->tamanho; // retorna tamanho do array (independente de estar preenchida ou não)
}

int quantidadeArray(const ArrayDinamico *arrayDinamico)
{
    return arrayDinamico->quantidade; // retorna quantidade (que está preenchida com alunos) do array
}

void carregarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo) // implementar leitura do arquivo e depois passar para o ponteiro
{
    FILE *file;

    file = fopen(caminhoArquivo, "rb"); // Abre o arquivo em modo de leitura binária
    if (file == NULL)
    {
        // printf("Erro ao abrir o arquivo.\n");
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

void gravarArquivo(ArrayDinamico *arrayDinamico, char *caminhoArquivo) // grava dados do ponteiro no arquivo
{
    FILE *file = fopen(caminhoArquivo, "wb"); // Abre o arquivo em modo de escrita binária
    if (file == NULL)
    {
        printf("\nErro ao salvar no arquivo.\n");
        return;
    }

    int i;
    // Escreve os dados dos alunos no arquivo
    for (i = 0; i < arrayDinamico->quantidade; i++)
    {
        fwrite(arrayDinamico->ptr_dados[i], sizeof(Aluno), 1, file);
    }

    fclose(file); // Fecha o arquivo
}

void imprimeAluno(Aluno *aluno)
{
    

    if (aluno != NULL)
    {
        printf("Nome: %s\nRA: %d\nData de Nascimento: %s\nEndereco 1:\n Rua: %s\n Numero Casa: %d\n Estado: %s\n Cidade: %s \n Bairro: %s \nEndereco 2:\n Rua: %s\n Numero Casa: %d\n Estado: %s\n Cidade: %s\n Bairro: %s\nMateria 1 - Nome: %s | Media: %f\nMateria 2 - Nome: %s | Media: %f\nMateria 3 - Nome: %s | Media: %f\nMateria 4 - Nome: %s | Media: %f\nMateria 5 - Nome: %s | Media: %f\n",
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

char *ajustarString(char *str)
{ // metodo que peguei com o Jhom para evitar erros na hora de salvar as "strings" no array
    int tamanho = strlen(str);

    if (str[tamanho - 1] == '\n')
    {
        str[tamanho - 1] = '\0';
    }

    return str;
}

void menuCriarAluno(ArrayDinamico *arrayDinamico)
{
    Aluno *aluno = (Aluno *)malloc(1 * sizeof(Aluno *)); // cria aluno
    int raAluno;

    // salva informacoes abaixo
    printf("Digite o nome do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->nome, sizeof(aluno->nome), stdin);
    strcpy(aluno->nome, ajustarString(aluno->nome));

    printf("Digite o RA do aluno:\n");
    scanf("%d", &raAluno);
    if (buscaArray(arrayDinamico, raAluno) == -1)
    { // verificando se o RA já existe
        aluno->RA = raAluno;
    }
    else
    {
        printf("\nEste RA ja existe, nao pode haver duplicatas. Voltando ao menu...\n");
        free(aluno);
        return;
    }

    
    printf("Digite a data de nascimento do aluno:\n");
    scanf("%s", &aluno->dataNascimento);

    printf("Digite a rua 1 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco1.rua, sizeof(aluno->endereco1.rua), stdin);
    strcpy(aluno->endereco1.rua, ajustarString(aluno->endereco1.rua));

    printf("Digite o numero 1 da casa do aluno:\n");
    scanf("%d", &aluno->endereco1.numeroCasa);

    printf("Digite o bairro 1 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco1.bairro, sizeof(aluno->endereco1.bairro), stdin);
    strcpy(aluno->endereco1.bairro, ajustarString(aluno->endereco1.bairro));

    printf("Digite a cidade 1 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco1.cidade, sizeof(aluno->endereco1.cidade), stdin);
    strcpy(aluno->endereco1.cidade, ajustarString(aluno->endereco1.cidade));

    printf("Digite o estado 1 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco1.estado, sizeof(aluno->endereco1.estado), stdin);
    strcpy(aluno->endereco1.estado, ajustarString(aluno->endereco1.estado));

    printf("Digite a rua 2 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco2.rua, sizeof(aluno->endereco2.rua), stdin);
    strcpy(aluno->endereco2.rua, ajustarString(aluno->endereco2.rua));

    printf("Digite o numero 2 da casa do aluno:\n");
    scanf("%d", &aluno->endereco2.numeroCasa);

    printf("Digite o bairro 2 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco2.bairro, sizeof(aluno->endereco2.bairro), stdin);
    strcpy(aluno->endereco2.bairro, ajustarString(aluno->endereco2.bairro));

    printf("Digite a cidade 2 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco2.cidade, sizeof(aluno->endereco2.cidade), stdin);
    strcpy(aluno->endereco2.cidade, ajustarString(aluno->endereco2.cidade));

    printf("Digite o estado 2 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->endereco2.estado, sizeof(aluno->endereco2.estado), stdin);
    strcpy(aluno->endereco2.estado, ajustarString(aluno->endereco2.estado));

    printf("Digite o nome da materia 1 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->materia[0].nomeMateria, sizeof(aluno->materia[0].nomeMateria), stdin);
    strcpy(aluno->materia[0].nomeMateria, ajustarString(aluno->materia[0].nomeMateria));

    printf("Digite a media da materia do aluno:\n");
    scanf("%f", &aluno->materia[0].mediaMateria);

    printf("Digite o nome da materia 2 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->materia[1].nomeMateria, sizeof(aluno->materia[1].nomeMateria), stdin);
    strcpy(aluno->materia[1].nomeMateria, ajustarString(aluno->materia[1].nomeMateria));

    printf("Digite a media da materia do aluno:\n");
    scanf("%f", &aluno->materia[1].mediaMateria);

    printf("Digite o nome da materia 3 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->materia[2].nomeMateria, sizeof(aluno->materia[2].nomeMateria), stdin);
    strcpy(aluno->materia[2].nomeMateria, ajustarString(aluno->materia[2].nomeMateria));

    printf("Digite a media da materia 3 do aluno:\n");
    scanf("%f", &aluno->materia[2].mediaMateria);

    printf("Digite o nome da materia 4 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->materia[3].nomeMateria, sizeof(aluno->materia[3].nomeMateria), stdin);
    strcpy(aluno->materia[3].nomeMateria, ajustarString(aluno->materia[3].nomeMateria));

    printf("Digite a media da materia 4 do aluno:\n");
    scanf("%f", &aluno->materia[3].mediaMateria);

    printf("Digite o nome da materia 5 do aluno:\n");
    setbuf(stdin, NULL);
    fgets(aluno->materia[4].nomeMateria, sizeof(aluno->materia[4].nomeMateria), stdin);
    strcpy(aluno->materia[4].nomeMateria, ajustarString(aluno->materia[4].nomeMateria));

    printf("Digite a media da materia 5 do aluno:\n");
    scanf("%f", &aluno->materia[4].mediaMateria);


    adicionarArray(arrayDinamico, aluno); // adiciona o ponteiro do aluno dentro do array dinamico

    printf("\nAluno adicionado com sucesso!\n");
}

void menuBuscarAluno(ArrayDinamico *arrayDinamico)
{
    imprimeArray(arrayDinamico, 1);

    int raAluno, index;
    printf("\nDigite o RA que deseja acessar:\n");
    scanf("%d", &raAluno); // pega o RA do aluno

    index = buscaArray(arrayDinamico, raAluno);
    if (index != -1) // se veio diferente de -1 quer dizer que existe esse aluno
    {
        Aluno *alunoProcura = acessarVerificado(arrayDinamico, index);
        imprimeAluno(alunoProcura); // imprime as informações que foram salvas no aluno pelo retorno
        free(alunoProcura);         // limpa espaço da mem
    }
}

void menuRemoveAluno(ArrayDinamico *arrayDinamico)
{
    imprimeArray(arrayDinamico, 1);

    int raAluno, index;
    printf("\nDigite o RA que deseja apagar:\n");
    scanf("%d", &raAluno); // pega o RA

    index = buscaArray(arrayDinamico, raAluno); // busca o ra e salva index dele
    if (index != -1)                            // se existe entra
    {
        removeArray(arrayDinamico, index); // remove o aluno e reorganiza para diminuir posição
    }
    else // senao da erro
    {
        printf("\nEste RA nao existe, portanto nao posso apagar!\n");
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
        printf(" -------------------------------------------\n");
        printf("|             MENU DE OPERACOES             |\n");
        printf("| 1 - Salvar novo aluno.                    |\n");
        printf("| 2 - Buscar aluno pelo RA.                 |\n");
        printf("| 3 - Remover aluno do array.               |\n");
        printf("| 4 - Imprimir todos os alunos.             |\n");
        printf("| 5 - Checar tamanho e quantidade do vetor. |\n");
        printf("| 6 - Sair.                                 |\n");
        printf(" -------------------------------------------\n");
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
            imprimeArray(arrayDinamico, 2);
            break;
        case 5: // verifica o tamanho e a quantidade do array
            printf("\nO array possui tamanho: %d - e a quantidade: %d\n", tamanhoArray(arrayDinamico), quantidadeArray(arrayDinamico));
            break;
        case 6: // destroi o array dinamico e apaga ele da memoria e sai do programa
            gravarArquivo(arrayDinamico, caminhoArquivo);
            destroiArrayDinamico(&arrayDinamico);
            printf("\nSaindo...\n");
            exit(1);
            break;
        default: // default
            
            printf("\nEssa opcao nao existe!\n");
            break;
        }
    }
}
