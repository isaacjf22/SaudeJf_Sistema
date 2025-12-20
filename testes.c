#include <stdio.h>
#include <windows.h> // Precisa dessa biblioteca!

int main() {
   // PRIMEIRO SOM (O "Dimm")
    // 750 é a frequência (meio agudo)
    // 500 é o tempo (meio segundo)
    Beep(750, 500); 
    
    // Pequena pausa dramática
    Sleep(100); 

    // SEGUNDO SOM (O "Dommm")
    // 550 é a frequência (mais grave, tom de encerramento)
    // 800 é o tempo (dura um pouquinho mais)
    Beep(550, 800);
    return 0;
}
    
