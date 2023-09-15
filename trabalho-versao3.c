#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int VerificaArmazenamento(struct Aluno *aluno[])
{
    int i;
    for (i = 0; i < 20; i++)
    {
        if (aluno[i]->nome == "" || aluno[i]->nome == NULL)
        {
            printf("Espaco vazio encontrado, pode armazenar um novo aluno!\n");
            return i;
        }
    }
    printf("Nao havia espaco para armazenar um novo aluno!\n");
    return -1;
}

int VerificaRA(struct Aluno *aluno[], int *RA_aluno)
{
    int i;
    for (i = 0; i < 20; i++)
    {
        if (aluno[i]->RA == *RA_aluno)
        {
            printf("RA ja esta armazenado!\n");
            return 0;
        }
    }
    printf("RA nao esta armazenado!\n");
    return 1;
}

void CriarAluno(struct Aluno *aluno[])
{
    int refRAbool, RA_aluno, i = VerificaArmazenamento(*aluno);
    if (i > -1)
    {
        printf("Digite o nome do aluno:\n");
        setbuf(stdin, NULL);
        gets(aluno[i]->nome);
        if (aluno[i]->nome == "")
        {
            *aluno[i]->nome = "Aluno " + i;
        }
        printf("Digite o RA do aluno:\n");
        scanf("%d", &RA_aluno);
        refRAbool = VerificaRA(*aluno, RA_aluno);
        switch (refRAbool)
        {
        case 1:
            aluno[i]->RA = RA_aluno;
            printf("Digite a data de nascimento do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->dataNascimento);
            printf("Digite a rua 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco1.rua);
            printf("Digite o numero 1 da casa do aluno:\n");
            scanf("%d", &aluno[i]->endereco1.numeroCasa);
            printf("Digite o bairro 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco1.bairro);
            printf("Digite a cidade 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco1.cidade);
            printf("Digite o estado 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco1.estado);
            printf("Digite a rua 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco2.rua);
            printf("Digite o numero 2 da casa do aluno:\n");
            scanf("%d", &aluno[i]->endereco2.numeroCasa);
            printf("Digite o bairro 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco2.bairro);
            printf("Digite a cidade 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco2.cidade);
            printf("Digite o estado 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->endereco2.estado);
            printf("Digite o nome da materia 1 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->materia[0].nomeMateria);
            printf("Digite o nome da media 1 do aluno:\n");
            setbuf(stdin, NULL);
            scanf("%d", &aluno[i]->materia[0].mediaMateria);
            printf("Digite o nome da materia 2 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->materia[1].nomeMateria);
            printf("Digite o nome da media 2 do aluno:\n");
            setbuf(stdin, NULL);
            scanf("%d", &aluno[i]->materia[1].mediaMateria);
            printf("Digite o nome da materia 3 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->materia[2].nomeMateria);
            printf("Digite o nome da media 3 do aluno:\n");
            setbuf(stdin, NULL);
            scanf("%d", &aluno[i]->materia[2].mediaMateria);
            printf("Digite o nome da materia 4 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->materia[3].nomeMateria);
            printf("Digite o nome da media 4 do aluno:\n");
            setbuf(stdin, NULL);
            scanf("%d", &aluno[i]->materia[3].mediaMateria);
            printf("Digite o nome da materia 5 do aluno:\n");
            setbuf(stdin, NULL);
            gets(aluno[i]->materia[4].nomeMateria);
            printf("Digite o nome da media 5 do aluno:\n");
            setbuf(stdin, NULL);
            scanf("%d", &aluno[i]->materia[4].mediaMateria);
            printf("Aluno foi registrado com sucesso!");
            break;
        default:
            printf("RA ja esta preenchido, voltando para tela inicial...\n");
            *aluno[i]->nome = NULL;
            break;
        }
    }
}

void ApagaAluno(struct Aluno *aluno[])
{
    int numAluno, c;
    printf("Lista de alunos:\n");
    for (c = 0; c < 20; c++)
    {
        printf("Numero da lista: %d. Nome aluno: %s", c, aluno[c]->nome);
    }
    printf("Qual o index do aluno que deseja apagar (numero na lista)?\n");
    scanf("%d", &numAluno);
    if (aluno[numAluno]->nome != "" || aluno[numAluno]->nome != NULL)
    {
        *aluno[numAluno]->nome = NULL;
        aluno[numAluno]->RA = NULL;
        *aluno[numAluno]->dataNascimento = NULL;
        *aluno[numAluno]->endereco1.rua = NULL;
        aluno[numAluno]->endereco1.numeroCasa = NULL;
        *aluno[numAluno]->endereco1.estado = NULL;
        *aluno[numAluno]->endereco1.cidade = NULL;
        *aluno[numAluno]->endereco1.bairro = NULL;
        *aluno[numAluno]->endereco2.rua = NULL;
        aluno[numAluno]->endereco2.numeroCasa = NULL;
        *aluno[numAluno]->endereco2.estado = NULL;
        *aluno[numAluno]->endereco2.cidade = NULL;
        *aluno[numAluno]->endereco2.bairro = NULL;
        *aluno[numAluno]->materia[0].nomeMateria = NULL;
        aluno[numAluno]->materia[0].mediaMateria = 0;
        *aluno[numAluno]->materia[1].nomeMateria = NULL;
        aluno[numAluno]->materia[1].mediaMateria = 0;
        *aluno[numAluno]->materia[2].nomeMateria = NULL;
        aluno[numAluno]->materia[2].mediaMateria = 0;
        *aluno[numAluno]->materia[3].nomeMateria = NULL;
        aluno[numAluno]->materia[3].mediaMateria = 0;
        *aluno[numAluno]->materia[4].nomeMateria = NULL;
        aluno[numAluno]->materia[4].mediaMateria = 0;
        printf("O aluno %d foi apagado!\n", numAluno);
    }
    else
    {
        printf("Nao podemos apagar o aluno pois ele nao existe!\n");
    }
}

void InformacoesRA(struct Aluno *aluno[])
{
    int alunoRA, i;
    printf("Digite o RA do aluno que deseja ver:\n");
    scanf("%d", &alunoRA);
    for (i = 0; i < 20; i++)
    {
        if (aluno[i]->RA == alunoRA)
        {
            
            printf("Nome: %s\n RA: %d\n Data de Nascimento: %s\n Endereco 1 - Rua: %s\n Endereco 1 - Numero Casa: %d\n Endereco 1 - Estado: %s\n Endereco 1 - Cidade: %s\n Endereco 1 - Bairro: %s\n Endereco 2 - Rua: %s\n Endereco 2 - Numero Casa: %d\n Endereco 2 - Estado: %s\n Endereco 2 - Cidade: %s\n Endereco 2 - Bairro: %s\n Materia 1 - Nome: %s\n Materia 1 - Media: %f\n Materia 2 - Nome: %s\n Materia 2 - Media: %f\n Materia 3 - Nome: %s\n Materia 3 - Media: %f\n Materia 4 -Nome: %s\n Materia 4 - Media: %f\n Materia 5 - Nome: %s \nMateria 5 - Media: %f\n ",
                         aluno[i]->nome,
                     aluno[i]->RA,
                     aluno[i]->dataNascimento,
                     aluno[i]->endereco1.rua,
                     aluno[i]->endereco1.numeroCasa,
                     aluno[i]->endereco1.estado,
                     aluno[i]->endereco1.cidade,
                     aluno[i]->endereco1.bairro,
                     aluno[i]->endereco2.rua,
                     aluno[i]->endereco2.numeroCasa,
                     aluno[i]->endereco2.estado,
                     aluno[i]->endereco2.cidade,
                     aluno[i]->endereco2.bairro,
                     aluno[i]->materia[0].nomeMateria,
                     aluno[i]->materia[0].mediaMateria,
                     aluno[i]->materia[1].nomeMateria,
                     aluno[i]->materia[1].mediaMateria,
                     aluno[i]->materia[2].nomeMateria,
                     aluno[i]->materia[2].mediaMateria,
                     aluno[i]->materia[3].nomeMateria,
                     aluno[i]->materia[3].mediaMateria,
                     aluno[i]->materia[4].nomeMateria,
                     aluno[i]->materia[4].mediaMateria);
             
            break;
        }
    }
    printf("Não foi encontrado nenhum aluno com o RA indicado!\n");
}

void InformacaoTodos(struct Aluno *aluno[])
{
    int i;
    for (i = 0; i < 20; i++)
    {
        if (aluno[i]->nome != "" || aluno[i]->nome != NULL)
        {
            
            printf("Nome: %s\n RA: %d\n Data de Nascimento: %s\n Endereco 1 - Rua: %s\n Endereco 1 - Numero Casa: %d\n Endereco 1 - Estado: %s\n Endereco 1 - Cidade: %s\n Endereco 1 - Bairro: %s\n Endereco 2 - Rua: %s\n Endereco 2 - Numero Casa: %d\n Endereco 2 - Estado: %s\n Endereco 2 - Cidade: %s\n Endereco 2 - Bairro: %s\n Materia 1 - Nome: %s\n Materia 1 - Media: %f\n Materia 2 - Nome: %s\n Materia 2 - Media: %f\n Materia 3 - Nome: %s\n Materia 3 - Media: %f\n Materia 4 -Nome: %s\n Materia 4 - Media: %f\n Materia 5 - Nome: %s \nMateria 5 - Media: %f\n ",
                         aluno[i]->nome,
                     aluno[i]->RA,
                     aluno[i]->dataNascimento,
                     aluno[i]->endereco1.rua,
                     aluno[i]->endereco1.numeroCasa,
                     aluno[i]->endereco1.estado,
                     aluno[i]->endereco1.cidade,
                     aluno[i]->endereco1.bairro,
                     aluno[i]->endereco2.rua,
                     aluno[i]->endereco2.numeroCasa,
                     aluno[i]->endereco2.estado,
                     aluno[i]->endereco2.cidade,
                     aluno[i]->endereco2.bairro,
                     aluno[i]->materia[0].nomeMateria,
                     aluno[i]->materia[0].mediaMateria,
                     aluno[i]->materia[1].nomeMateria,
                     aluno[i]->materia[1].mediaMateria,
                     aluno[i]->materia[2].nomeMateria,
                     aluno[i]->materia[2].mediaMateria,
                     aluno[i]->materia[3].nomeMateria,
                     aluno[i]->materia[3].mediaMateria,
                     aluno[i]->materia[4].nomeMateria,
                     aluno[i]->materia[4].mediaMateria); 
        }
    }
}

void main() // metodo principal
{
    struct Aluno aluno[20]; // arrya de 20 alunos (estrutura)
    int escolha = 0;

    while (escolha != 6)
    {
        printf("Menu de Operações\n");
        printf("1 - Criar/Armazenar novo aluno.\n");
        printf("2 - Verificar se tem espaco para armazenar novo aluno.\n");
        printf("3 - Apagar informações de algum aluno.\n");
        printf("4 - Ver informação pelo RA do aluno.\n");
        printf("5 - Ver informação de todos os alunos.\n");
        printf("6 - Sair da aplicação.\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            CriarAluno(&aluno);
            break;
        case 2:
            VerificaArmazenamento(&aluno);
            break;
        case 3:
            ApagaAluno(&aluno);
            break;
        case 4:
            InformacoesRA(&aluno);
            break;
        case 5:
            InformacaoTodos(&aluno);
            break;
        default:
            printf("Essa opcao nao existe!");
            break;
        }
    }
    printf("Saindo...");
    system("pause");
}
