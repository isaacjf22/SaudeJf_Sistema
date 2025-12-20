#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h> 

#define tam 50
#define pessoa 500

typedef struct dados_endereco{
    char cep[tam];
    char logradouro[tam];
    int numero; 
    char complem[tam];
    char bairro[tam]; 
    char cidade[tam]; 
    char uf[5]; 
}endereco; 

typedef struct dados_pessoais{
    char nome[tam];
    int idade; //vai ser transformado em ano,mes e dias. 
    char cpf[15]; 
    char telefone[tam];    
    endereco localizacao; 
    int ativo; // =0 não ativo , =1 ativo , para aparecer na lista ativa 
}pessoal; 

typedef struct dados_medicos{
    char sintomas[150];
    int nivel;
    int registrado; //garantir q n repita  , =0 não atendido , =1 atendido
}medico; 

//prototipos das funções 
void menu(); 
int cadastroPaciente(int atual,pessoal pacientes[],int *pA); 
void preencherEndereco(endereco *end);
void enter(); 
void cor(int cor_letra); 
void saudePaciente(int atual,pessoal pacientes[], medico paciente[]); 
void listarAtivos(int ativo, int atual, pessoal ap[], medico bp[]); 

int main(){
    setlocale(LC_ALL,"portuguese"); 
    menu(); 
}

void menu(){
    time_t tempo; //para guardar o tempo do computador 
    struct tm *atual; // uma struct da biblioteca time guarda as datas e horarios atuais , que vao ser traduzidas e guardada pela função, o ponteiro vai servir para pegar os dados 
    char esc; //escolha de opções no menu 
    int pacientesR=0; //contador de pacientes registrados
    int pacientesA=0; //contador de pacientes ativos   
    pessoal pacientes[pessoa]={0};
    medico prontuario[pessoa]={0}; //zerando tudo da struct
    do{
        while(!kbhit()){ //esquema do relogio e data , e o loop roda enquanto nenhuma tecla for teclada
            system("cls"); 
            printf("  _   _            _ _   _     \n");
            printf(" | | | |          | | | | |    \n");
            printf(" | |_| | ___  __ _| | |_| |__  \n");
            printf(" |  _  |/ _ \\/ _` | | __| '_ \\ \n");
            printf(" | | | |  __/ (_| | | |_| | | |\n");
            printf(" \\_| |_/\\___|\\__,_|_|\\__|_| |_|\n");
            printf("                       _ ______\n");
            printf("                      | |  ____|\n");
            printf("                   _  | | |__   \n");
            printf("                  | | | |  __|  \n");
            printf("                  | |_| | |     \n");
            printf("                   \\___/|_|     \n");
            printf("+---------------------------------+\n"); 
            printf("        SISTEMA HOSPITALAR         \n");
            printf("+---------------------------------+\n"); 
            time(&tempo); //pegando o tempo atual do computador e armazenando na variavel 
            atual=localtime(&tempo); // a função organiza o tempo e coloca na struct , o ponteiro recebe o endereço dos dados organizados na struct, para q possa ser usado
            printf("HORÁRIO: %02d:%02d:%02d         ",atual->tm_hour,atual->tm_min,atual->tm_sec); //o ponteiro aponta as horas,min,seg da struct traduzida
            printf("DATA: %d/%d/%d\n",atual->tm_mday,atual->tm_mon+1,atual->tm_year+1900); // o ponteiro indicou dia,mes,ano e foi colocado as correções 
            puts(""); 
            printf("Quantidade de pacientes registrados: %d\n",pacientesR); 
            printf("Quantidade de pacientes ativos: %d\n",pacientesA);
            puts("Qual opção deseja escolher?");
            puts(""); 
            printf("    1-Registar dados de paciente\n"); 
            printf("    2-Registar saúde de paciente\n"); 
            printf("    3-Realizar atendimento\n"); 
            printf("    4-Listar pacientes ativos\n"); 
            printf("    5-Histórico de pacientes\n"); 
            printf("    6-Sair do sistema\n");  
            puts(""); 
            Sleep(1000); //nao sobrecarregar a maquina
        }  
        do{ //validação
            esc=getch(); //pegando a opção 
        }while(esc!='1' && esc!='2' && esc!='3' && esc!='4' && esc!='5' && esc!='6'); 
        switch(esc){
            case '1':   pacientesR=cadastroPaciente(pacientesR,pacientes,&pacientesA);  
            break;
            case '2':   saudePaciente(pacientesR,pacientes,prontuario); 
            break; 
            case '3':
            break;
            case '4':   listarAtivos(pacientesA,pacientesR,pacientes,prontuario); 
            break;
            case '5':
            break; 
            case '6': puts("Saindo do sistema...");
            break; 
        }
    }while(esc!='6');

    return; 
}

void cor(int cor_letra){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hConsole, cor_letra);      
}

int cadastroPaciente(int atual,pessoal pacientes[],int *pA){ //quando fizer vetor de struct , declare um ponteiro para manipular 
    pessoal *p=&pacientes[atual]; //um ponteiro que pegou o endereço do paciente na posição 'atual' e vai manipular , indicando onde vai cada parte da struct
    // o ponteiro pega a variavel pacientes atual e manipula ele 
    p->ativo=1; 
    system("cls"); 
    printf("=========================\n");
    printf("        CADASTRO         \n");
    printf("=========================\n");
    puts(""); 
    puts("+PESSOAL");
    puts("  Qual é o nome do paciente?");
    printf("  ---> ");
    fgets(p->nome,tam,stdin); 
    p->nome[strcspn(p->nome,"\n")]=0; //retirando o enter 
    puts("  Qual é a idade do paciente?"); 
    printf("  ---> ");
    scanf("%d",&p->idade);
    getchar(); 
    puts("  Qual é o CPF do paciente?");
    printf("  ---> ");
    fgets(p->cpf,tam,stdin);
    p->cpf[strcspn(p->cpf,"\n")]=0; //retirando o enter
    puts(   "Qual é o telefone do paciente?");
    printf("  ---> ");
    fgets(p->telefone,tam,stdin); 
    p->telefone[strcspn(p->telefone,"\n")]=0; //retirando o enter
    puts(""); 
    preencherEndereco(&p->localizacao); // essa função vai pegar o endereço da variavel struct localização e passar pra funçõa responsavel pro preencher essa parte
    *pA+=1; //vai somar +1 no total de pacientes ativos 
    puts(""); 
    enter();  
    return atual+1; //n rola colocar atual++ pq o pc n soma antes de retornar 
}

void preencherEndereco(endereco *end){ //a função vai receber o endereço antes e ja vai saber onde encaixar os dados,
    //vai usar a struct endereco e vai colocar na variavel pessoa onde o endereço foi pego antes 
    puts("+ENDEREÇO");
    puts("  Qual é o CEP do paciente?");
    printf("  ---> ");
    fgets(end->cep,tam,stdin); 
    end->cep[strcspn(end->cep,"\0")]=0;
    puts("  Qual é o logradouro do paciente?");
    printf("  ---> ");
    fgets(end->logradouro,tam,stdin); 
    end->logradouro[strcspn(end->logradouro,"\0")]=0; //tirar o enter 
    puts("  Qual é o número do logradouro do paciente?");
    printf("  ---> ");
    scanf("%d",&end->numero); 
    getchar(); 
    puts("  Qual é o complemento do logradouro do paciente?");
    printf("  ---> ");
    fgets(end->complem,tam,stdin); 
    end->complem[strcspn(end->complem,"\0")]=0;
    puts("  Qual é o bairro do paciente?"); 
    printf("  ---> ");
    fgets(end->bairro,tam,stdin); 
    end->bairro[strcspn(end->bairro,"\0")]=0;
    puts("  Qual é a cidade do paciente?");
    printf("  ---> ");
    fgets(end->cidade,tam,stdin); 
    end->cidade[strcspn(end->cidade,"\0")]=0;
    puts("  Qual é a UF do paciente?");
    printf("  ---> ");
    fgets(end->uf,5,stdin); 
    end->uf[strcspn(end->uf,"\0")]=0;
    return; 
}

void enter(){
    puts("Aperte ENTER para voltar ao MENU..."); 
    getch(); 
}

void saudePaciente(int atual,pessoal pacientes[], medico paciente[]){
    medico *m; //ponteiro para pegar o endereço do struct medico e manipular dps
    int i; 
    int escolhido, escolhidoC; 
    system("cls"); 
    if(atual==0){
        puts("Nenhum paciente ativo!"); 
        enter(); 
    }else{
        for(i=0;i<atual;i++){
                pessoal *p=&pacientes[i]; //ponteiro que vai pegar o endereço da struct pessoal e manipular //so botar o nome //dado da struct
                //o ponteiro vai acessar o conteudo da struct em tal i
                printf("Nº%d\n",i+1); 
                printf("Nome: %s\n",p->nome);
                printf("CPF: %s\n",p->cpf); 
                puts("+------------------------+");
        }
        puts(""); 
        puts("Qual paciente vai ter a saúde analisada?");
        scanf("%d",&escolhido);
        getchar(); 
        escolhidoC=escolhido-1; 
        system("cls"); 
        m=&paciente[escolhidoC];
        if(m->registrado==0){
            puts("Quais são os sintomas do paciente?");
            fgets(m->sintomas,150,stdin); 
            m->sintomas[strcspn(m->sintomas,"\n")]=0; //tirando o enter 
            puts("Qual estado saúde do paciente?");
            cor(10); 
            printf("1-ESTÁVEL  "); 
            cor(14);
            printf("2-ATENÇÃO  ");
            cor(12);
            printf("3-GRAVE  \n"); 
            cor(7); 
            do{
                scanf("%d",&m->nivel); 
                getchar();
            }while(m->nivel!=1 && m->nivel!=2 && m->nivel!=3);
            m->registrado=1;
            enter(); 
        }else{
            puts("Esse paciente já foi registrado!");
            enter();
        }
    }
    return; 
}

void listarAtivos(int ativo, int atual, pessoal ap[], medico bp[]){
    pessoal *a; //declaro a variavel 
    medico *b; 
    int grave=1,atencao=1,estavel=1; 
    int i; 
    system("cls"); 
    if(atual==0){
        puts("Nenhum paciente ativo!"); 
        enter();
    }else{
        printf("TOTAL DE ATIVOS: %d\n",ativo); 
        puts("");
        cor(12); 
        puts("GRAVE");
        cor(7);
        for(i=0;i<atual;i++){ //analisar os pacientes graves 
            a=&ap[i]; //apontando o endereço pros ponteiros indicando oq eles vao mexer/mostrar o conteudo 
            b=&bp[i]; 
            if(a->ativo==1 && b->nivel==3){
                printf("Nº%d\n",grave); 
                printf("Nome: %s\n",a->nome);
                printf("CPF: %s\n",a->cpf); 
                printf("Sintomas: %s\n",b->sintomas); 
                puts("+---------------------------+");
                grave++; 
            }
        }
        puts("");
        cor(14);
        puts("ATENÇÃO"); 
        cor(7); 
        for(i=0;i<atual;i++){ //analisar os pacientes em atenção
            a=&ap[i]; //apontando o endereço pros ponteiros indicando oq eles vao mexer
            b=&bp[i];
            if(a->ativo==1 && b->nivel==2){
                printf("Nº%d\n",atencao); 
                printf("Nome: %s\n",a->nome);
                printf("CPF: %s\n",a->cpf); 
                printf("Sintomas: %s\n",b->sintomas); 
                puts("+---------------------------+");
                atencao++; 
            }
        }
        puts(""); 
        cor(10);
        puts("ESTÁVEL"); 
        cor(7);
        for(i=0;i<atual;i++){ //analisar os pacientes estaveis 
            a=&ap[i]; //apontando o endereço pros ponteiros indicando oq eles vao mexer
            b=&bp[i];
            if(a->ativo==1 && b->nivel==1){
                printf("Nº%d\n",estavel); 
                printf("Nome: %s\n",a->nome);
                printf("CPF: %s\n",a->cpf); 
                printf("Sintomas: %s\n",b->sintomas); 
                puts("+---------------------------+");
                estavel++; 
            }
        }
        puts("");
        enter(); 
    }
    return; 
}