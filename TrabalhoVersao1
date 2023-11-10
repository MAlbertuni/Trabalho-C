#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int tamanhoVetorAlunos = 20;//constante com tamanho do vetor dos alunos para facilitar nos meu testes

struct Endereco // estrutura do endereço
{
    char rua[40];
    int numeroCasa;
    char bairro[20];
    char cidade[20];
    char estado[20];
};
struct Materia // estrutura da matéria
{
    char nomeMateria[20];
    float mediaMateria;
};
struct Aluno // estrutura do aluno
{
    char nome[25];
    int RA;
    char dataNascimento[10];
    struct Endereco endereco1;
    struct Endereco endereco2;
    struct Materia materia[5];
};

void apagaInformacoes(struct Aluno aluno[], int indexApaga)
{
    //criei este método porque quando istanciamos a estrutura, ele não salva todas as casas como null ou ""
    //então tive que limpar dado por dado para não dar conflito co a validação no nome por exemplo, já que 
    //em diversos testes que fiz, o campo nome vinha preenchido com algum caractere que o sistema mesmo colocou
    int v, tamanho;
    if (indexApaga != -1)//aqui é qualquer numero fora -1 e que esteja dentro do BOUND
    {
        v = indexApaga;//coloca a posição a apagar
        tamanho = indexApaga + 1;//adiciona mais um por causa de eu utilizar no for
    }
    else//então se for para limpar todos os campos, eu passo -1 como parâmetro
    {
        v = 0;//aqui coloca o 0, pois vamos apagar de todos
        tamanho = tamanhoVetorAlunos;//e o máximo
    }
    for (; v < tamanho; v++)//aqui ele apaga no index
    {
        strcpy(aluno[v].nome, "");
        aluno[v].RA = 0;
        strcpy(aluno[v].dataNascimento, "");
        strcpy(aluno[v].endereco1.rua, "");
        aluno[v].endereco1.numeroCasa = 0;
        strcpy(aluno[v].endereco1.estado, "");
        strcpy(aluno[v].endereco1.cidade, "");
        strcpy(aluno[v].endereco1.bairro, "");
        strcpy(aluno[v].endereco2.rua, "");
        aluno[v].endereco2.numeroCasa = 0;
        strcpy(aluno[v].endereco2.estado, "");
        strcpy(aluno[v].endereco2.cidade, "");
        strcpy(aluno[v].endereco2.bairro, "");
        strcpy(aluno[v].materia[0].nomeMateria, "");
        aluno[v].materia[0].mediaMateria = 0;
        strcpy(aluno[v].materia[1].nomeMateria, "");
        aluno[v].materia[1].mediaMateria = 0;
        strcpy(aluno[v].materia[2].nomeMateria, "");
        aluno[v].materia[2].mediaMateria = 0;
        strcpy(aluno[v].materia[3].nomeMateria, "");
        aluno[v].materia[3].mediaMateria = 0;
        strcpy(aluno[v].materia[4].nomeMateria, "");
        aluno[v].materia[4].mediaMateria = 0;
    }
}

int VerificaArmazenamento(struct Aluno aluno[])
{
    //método para ver se alguma posição do array está livre para poder gravar informações
    int i, c;
    for (i = 0; i < tamanhoVetorAlunos; i++)//percorre array inteiro
    {
        if (strlen(aluno[i].nome) == 0)//em um método mais a baixo no código explquei como fiz a validação
        //no caso, todos os alunos possuem algum nome, mesmo que o usuário digitar "" vazio e dar enter
        //fiz para ter um dado lá, assim consigo validar aqui que posso gravar um novo aluno em tal posição
        {
            printf("Espaco vazio encontrado, pode armazenar um novo aluno!\n");
            return i;//ele retorna a posição para o método de CriarAluno já salvar na posição em esecífico
        }
    }
    printf("Nao havia espaco para armazenar um novo aluno!\n");
    return -1;//-1 por que não possui tal posição
}

int VerificaRA(struct Aluno aluno[], int RA_aluno)
{
    //método para verificar se RA já está com algum aluno
    //aqui ele roda um for em todos as posições e ve se em algum RA já possui o numero que vamos comparar
    int i;
    for (i = 0; i < tamanhoVetorAlunos; i++)
    {
        if (aluno[i].RA == RA_aluno)//aqui valida em cada vez
        {
            printf("RA ja esta armazenado!\n");
            return 0;
        }
    }
    printf("RA nao esta armazenado!\n");
    return 1;//isso utiizamos em outros metodos para poder salvar algum aluno com este RA
}

void CriarAluno(struct Aluno aluno[])
{
    //método para criar novo aluno
    int refRAbool, ref, RA_aluno;
    int i = VerificaArmazenamento(aluno);//chama metodo de verificar espaço no array
    if (i > -1)
    {
        //o mais perto da validação que fiz no geral, é que todo aluno que for cadastrado vai ter um nome
        //mesmo que o cara aperte um enter sem ter digitado nada, uma valor padrao vai no lugar dele
        //para que assim eu consiga validar se uma posição no array está contendo dados ou não
        printf("Digite o nome do aluno:\n");
        setbuf(stdin, NULL);
        gets(aluno[i].nome);

        if (strlen(aluno[i].nome) == 0)//valida se o cara só não deu enter no "vazio"
        {
            strcpy(aluno[i].nome, "Aluno");//se deu coloca Aluno no lugar do nome
        }
        printf("Digite o RA do aluno:\n");
        scanf("%d", &RA_aluno);
        refRAbool = VerificaRA(aluno, RA_aluno);//verifica se o RA já existe
        if (refRAbool == 1)//se não existe ele deixa gravar novo aluno
        {
            aluno[i].RA = RA_aluno;
            printf("Digite a data de nascimento do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].dataNascimento);
            printf("Digite a rua 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco1.rua);
            printf("Digite o numero 1 da casa do aluno:\n");
            scanf("%d", &aluno[i].endereco1.numeroCasa);
            printf("Digite o bairro 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco1.bairro);
            printf("Digite a cidade 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco1.cidade);
            printf("Digite o estado 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco1.estado);
            printf("Digite a rua 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco2.rua);
            printf("Digite o numero 2 da casa do aluno:\n");
            scanf("%d", &aluno[i].endereco2.numeroCasa);
            printf("Digite o bairro 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco2.bairro);
            printf("Digite a cidade 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco2.cidade);
            printf("Digite o estado 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].endereco2.estado);
            printf("Digite o nome da materia 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].materia[0].nomeMateria);
            printf("Digite a media da materia do aluno:\n");
            scanf("%f", &aluno[i].materia[0].mediaMateria);
            printf("Digite o nome da materia 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].materia[1].nomeMateria);
            printf("Digite a media da materia do aluno:\n");
            scanf("%f", &aluno[i].materia[1].mediaMateria);
            printf("Digite o nome da materia 3 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].materia[2].nomeMateria);
            printf("Digite a media da materia 3 do aluno:\n");
            scanf("%f", &aluno[i].materia[2].mediaMateria);
            printf("Digite o nome da materia 4 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].materia[3].nomeMateria);
            printf("Digite a media da materia 4 do aluno:\n");
            scanf("%f", &aluno[i].materia[3].mediaMateria);
            printf("Digite o nome da materia 5 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i].materia[4].nomeMateria);
            printf("Digite a media da materia 5 do aluno:\n");
            scanf("%f", &aluno[i].materia[4].mediaMateria);

            printf("Aluno foi registrado com sucesso!\n");
        }
        else//se não irá dar erro e voltar ao menu sem ter gravado nenhum aluno novo
        {
            printf("RA ja esta preenchido, voltando para tela inicial...\n");
            strcpy(aluno[i].nome, "");
        }
    }
}

void ApagaAluno(struct Aluno aluno[])
{
    //método para apagar aluno
    int numAluno, c;
    printf("Lista de alunos:\n");//mostro todos os alunos que possuim informacao e seu index no vetor
    for (c = 0; c < tamanhoVetorAlunos; c++)
    {
        if (strlen(aluno[c].nome) != 0)
        {
            printf("Numero da lista: %d. Nome aluno: %s \n", c, aluno[c].nome);
        }
    }
    printf("Qual o index do aluno que deseja apagar (numero na lista)?\n");
    scanf("%d", &numAluno);
    if (numAluno < tamanhoVetorAlunos && numAluno > -1)//ve se o index é valido dentro do nosso tamanho
    {
        if (strlen(aluno[numAluno].nome) != 0)//ve se o index possui informação para apagar
        {
            apagaInformacoes(aluno, numAluno);//chama método de limpeza
            printf("O aluno %d foi apagado!\n", numAluno);
        }
        else
        {
            printf("Nao podemos apagar o aluno pois ele nao existe!\n");//caso não tenha informação, não tem oq apagar
        }
    }
    else
    {
        printf("O numero digitado nao esta dentro do intervalo!\n");//aqui se saiu do intervalo
    }
}

void InformacoesRA(struct Aluno aluno[])
{
    //aqui ele valida dentro do do array de alunos se possui um RA especifico já cadastrado
    int alunoRA, i;
    printf("Digite o RA do aluno que deseja ver:\n");
    scanf("%d", &alunoRA);
    for (i = 0; i < tamanhoVetorAlunos; i++)
    {
        if (aluno[i].RA == alunoRA)//valida
        {
            printf("\nALUNO %d\nNome: %s \nRA: %d \nData de Nascimento: %s \nEndereco 1 - Rua: %s \nEndereco 1 - Numero Casa: %d \nEndereco 1 - Estado: %s \nEndereco 1 - Cidade: %s \nEndereco 1 - Bairro: %s \nEndereco 2 - Rua: %s \nEndereco 2 - Numero Casa: %d \nEndereco 2 - Estado: %s \nEndereco 2 - Cidade: %s \nEndereco 2 - Bairro: %s \nMateria 1 - Nome: %s \nMateria 1 - Media: %f \nMateria 2 - Nome: %s \nMateria 2 - Media: %f \nMateria 3 - Nome: %s \nMateria 3 - Media: %f \nMateria 4 -Nome: %s \nMateria 4 - Media: %f \nMateria 5 - Nome: %s \nMateria 5 - Media: %f \n",
                   i,
                   aluno[i].nome,
                   aluno[i].RA,
                   aluno[i].dataNascimento,
                   aluno[i].endereco1.rua,
                   aluno[i].endereco1.numeroCasa,
                   aluno[i].endereco1.estado,
                   aluno[i].endereco1.cidade,
                   aluno[i].endereco1.bairro,
                   aluno[i].endereco2.rua,
                   aluno[i].endereco2.numeroCasa,
                   aluno[i].endereco2.estado,
                   aluno[i].endereco2.cidade,
                   aluno[i].endereco2.bairro,
                   aluno[i].materia[0].nomeMateria,
                   aluno[i].materia[0].mediaMateria,
                   aluno[i].materia[1].nomeMateria,
                   aluno[i].materia[1].mediaMateria,
                   aluno[i].materia[2].nomeMateria,
                   aluno[i].materia[2].mediaMateria,
                   aluno[i].materia[3].nomeMateria,
                   aluno[i].materia[3].mediaMateria,
                   aluno[i].materia[4].nomeMateria,
                   aluno[i].materia[4].mediaMateria);
            break;
        }
    }
    printf("Nao foi encontrado nenhum aluno com o RA indicado!\n");
}

void InformacaoTodos(struct Aluno aluno[])
{
    //neste método ele percorre o array de alunos inteiro e se tiver informação
    //ele irá imprimir na tela
    int i, c;
    for (i = 0; i < tamanhoVetorAlunos; i++)
    {
        if (strlen(aluno[i].nome) != 0)
        {
            printf("\nALUNO %d\nNome: %s \nRA: %d \nData de Nascimento: %s \nEndereco 1 - Rua: %s \nEndereco 1 - Numero Casa: %d \nEndereco 1 - Estado: %s \nEndereco 1 - Cidade: %s \nEndereco 1 - Bairro: %s \nEndereco 2 - Rua: %s \nEndereco 2 - Numero Casa: %d \nEndereco 2 - Estado: %s \nEndereco 2 - Cidade: %s \nEndereco 2 - Bairro: %s \nMateria 1 - Nome: %s \nMateria 1 - Media: %f \nMateria 2 - Nome: %s \nMateria 2 - Media: %f \nMateria 3 - Nome: %s \nMateria 3 - Media: %f \nMateria 4 -Nome: %s \nMateria 4 - Media: %f \nMateria 5 - Nome: %s \nMateria 5 - Media: %f \n",
                   i,
                   aluno[i].nome,
                   aluno[i].RA,
                   aluno[i].dataNascimento,
                   aluno[i].endereco1.rua,
                   aluno[i].endereco1.numeroCasa,
                   aluno[i].endereco1.estado,
                   aluno[i].endereco1.cidade,
                   aluno[i].endereco1.bairro,
                   aluno[i].endereco2.rua,
                   aluno[i].endereco2.numeroCasa,
                   aluno[i].endereco2.estado,
                   aluno[i].endereco2.cidade,
                   aluno[i].endereco2.bairro,
                   aluno[i].materia[0].nomeMateria,
                   aluno[i].materia[0].mediaMateria,
                   aluno[i].materia[1].nomeMateria,
                   aluno[i].materia[1].mediaMateria,
                   aluno[i].materia[2].nomeMateria,
                   aluno[i].materia[2].mediaMateria,
                   aluno[i].materia[3].nomeMateria,
                   aluno[i].materia[3].mediaMateria,
                   aluno[i].materia[4].nomeMateria,
                   aluno[i].materia[4].mediaMateria);
        }
    }
}

void main() // metodo principal
{
    struct Aluno aluno[tamanhoVetorAlunos]; // vetor de 20 alunos (estrutura)
    apagaInformacoes(aluno, -1);

    int escolha = 0;

    while (escolha != 6)//menu que funciona até escolherem o 6
    {
        printf("Menu de Operacoes\n");
        printf("1 - Criar/Armazenar novo aluno.\n");
        printf("2 - Verificar se tem espaco para armazenar novo aluno.\n");
        printf("3 - Apagar informacoes de algum aluno.\n");
        printf("4 - Ver informacao pelo RA do aluno.\n");
        printf("5 - Ver informacao de todos os alunos.\n");
        printf("6 - Sair da aplicacao.\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            CriarAluno(aluno);
            break;
        case 2:
            VerificaArmazenamento(aluno);
            break;
        case 3:
            ApagaAluno(aluno);
            break;
        case 4:
            InformacoesRA(aluno);
            break;
        case 5:
            InformacaoTodos(aluno);
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
