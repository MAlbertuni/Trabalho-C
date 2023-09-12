#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Endereco
{
    char rua[40];
    int numeroCasa;
    char bairro[20];
    char cidade[20];
    char estado[20];
};
struct Materia
{
    char nomeMateria[20];
    float mediaMateria;
};
struct Aluno
{
    char nome[25];
    int RA;
    char dataNascimento[10];
    struct Endereco endereco1;
    struct Endereco endereco2;
    struct Materia materia[5];
};

void main()
{
    struct Aluno aluno[20];
    int escolha = 0;

    printf("Menu de Operações\n");
    printf("1 - Criar/Armazenar novo aluno.\n");
    printf("2 - Apagar informações de algúm aluno.\n");
    printf("3 - Ver informação pelo RA do aluno.\n");
    printf("4 - Ver informação de todos os alunos.\n");
    printf("5 - Sair da aplicação.\n");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 1:
        CriarAluno(&aluno[20]);
        break;
    
    default:
        break;
    }
}

void CriarAluno(struct Aluno aluno[20])
{
    printf("Digite o nome do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].nome);
    printf("Digite o RA do aluno:\n");
    scanf("%d", &aluno[20].RA);
    printf("Digite a data de nascimento do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].dataNascimento);
    printf("Digite a rua1 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco1.rua);
    printf("Digite o numero1 da casa do aluno:\n");
    scanf("%d", &aluno[20].endereco1.numeroCasa);
    printf("Digite o bairro1 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco1.bairro);
    printf("Digite a cidade1 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco1.cidade);
    printf("Digite o estado1 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco1.estado);
    printf("Digite a rua2 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco2.rua);
    printf("Digite o numero2 da casa do aluno:\n");
    scanf("%d", &aluno[20].endereco2.numeroCasa);
    printf("Digite o bairro2 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco2.bairro);
    printf("Digite a cidade2 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco2.cidade);
    printf("Digite o estado2 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].endereco2.estado);
    printf("Digite o nome da materia1 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].materia[0].nomeMateria);
    printf("Digite o nome da media1 do aluno:\n");
    setbuf(stdin, NULL);
    scanf("%d", &aluno[20].materia[0].mediaMateria);
    printf("Digite o nome da materia2 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].materia[1].nomeMateria);
    printf("Digite o nome da media2 do aluno:\n");
    setbuf(stdin, NULL);
    scanf("%d", &aluno[20].materia[1].mediaMateria);
    printf("Digite o nome da materia3 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].materia[2].nomeMateria);
    printf("Digite o nome da media3 do aluno:\n");
    setbuf(stdin, NULL);
    scanf("%d", &aluno[20].materia[2].mediaMateria);
    printf("Digite o nome da materia4 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].materia[3].nomeMateria);
    printf("Digite o nome da media4 do aluno:\n");
    setbuf(stdin, NULL);
    scanf("%d", &aluno[20].materia[3].mediaMateria);
    printf("Digite o nome da materia5 do aluno:\n");
    setbuf(stdin, NULL);
    gets(aluno[20].materia[4].nomeMateria);
    printf("Digite o nome da media5 do aluno:\n");
    setbuf(stdin, NULL);
    scanf("%d", &aluno[20].materia[4].mediaMateria);
}