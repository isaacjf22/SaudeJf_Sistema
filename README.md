# 🏥 Sistema de Gestão Hospitalar em C

Este é um projeto desenvolvido em **Linguagem C** para simular o fluxo de atendimento de um hospital, desde o cadastro do paciente, passando pela triagem de risco (Sintomas e Gravidade), até a chamada para o consultório médico com alertas sonoros e visuais.

O projeto foi criado com foco na consolidação de conceitos fundamentais da programação estruturada e manipulação de memória.

## ⚠️ Requisito de Sistema (Importante)

> **Este projeto foi desenvolvido para rodar exclusivamente em ambiente WINDOWS.**

Isso se deve ao uso de bibliotecas específicas do sistema operacional para manipulação do console e áudio:
* `<windows.h>`: Para cores, posicionamento, sons (Beep) e comandos do sistema.
* `<conio.h>`: Para captura de teclas em tempo real (`kbhit`, `getch`).

Caso tente rodar em Linux ou MacOS, será necessário adaptar essas bibliotecas.

## 🎯 Objetivos do Projeto

* Simular um sistema de **Triagem e Atendimento** (Classificação de Risco).
* Praticar o uso avançado de **Ponteiros** para manipulação de dados na memória.
* Implementar **Persistência de Dados** simples (Exportação de arquivos `.txt`).
* Criar uma interface de console interativa e amigável (UX) com feedback visual e sonoro.

## 🛠️ Tecnologias e Bibliotecas

* **Linguagem:** C 
* **IDE:** VS Code

### Bibliotecas Utilizadas:
* `stdio.h`, `stdlib.h`, `string.h`: Manipulação padrão de entrada/saída e strings.
* `locale.h`: Suporte para acentuação (Português).
* `time.h`: Exibição de relógio em tempo real no menu.
* `windows.h`: Manipulação de cores no terminal, sons (`Beep`) e pausas (`Sleep`).
* `conio.h`: Interação com o teclado sem necessidade de "Enter" (`kbhit`, `getch`).

## ⚙️ Funcionalidades e Técnicas Aplicadas

O código utiliza diversos conceitos importantes da Engenharia de Software aplicada a C:

### 1. Estruturas de Dados (Structs)
Utilização de **Structs Aninhadas** para organizar os dados. A `struct endereco` fica dentro da `struct pessoal`, organizando melhor a memória.

### 2. Manipulação de Ponteiros
O sistema faz uso intensivo de ponteiros para:
* Passagem de parâmetros por referência para funções (evitando cópia desnecessária de dados).
* Manipulação direta dos vetores de pacientes e médicos.

### 3. Sistema de Arquivos (File I/O)
* Capacidade de gerar relatórios externos.
* Uso de `fopen`, `fprintf` e `fclose` para exportar o histórico de atendimentos para um arquivo `.txt`.

### 4. Interface Dinâmica
* **Relógio em Tempo Real:** O menu exibe hora e data atualizadas segundo a segundo sem travar a execução (uso de `kbhit`).
* **Alertas Sonoros:** Sistema de "Bip" estilo hospitalar para chamar a atenção quando um paciente é convocado.
* **Código de Cores:** Identificação visual da gravidade (🔴 Grave, 🟡 Atenção, 🟢 Estável).
