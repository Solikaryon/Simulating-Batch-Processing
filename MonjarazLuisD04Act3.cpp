#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <cctype>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

// Código creado por Monjaraz Briseño Luis Fernando

int totalProcesses;
int totallotes;
int totallotesr;
int totallotesrr;
int timer = 0;
int timecontador = 0;


struct Process {
    string name;
    string operation;
    int number1;
    int number2;
    int result;
    int estimatedTime;
    int programNumber;
    int currentQueue;
    int timeelapsed;
};

// Función que valida que los datos ingresados por el usuario sean números enteros
bool ValidaNumerosEnteros(char *dato){
    bool ban = true;
    int i = 0;
    if (*dato == '-' || *dato == '+') {
        i++;
    }
    while (*(dato + i) != '\0') {
        if (*(dato + i) < '0' || *(dato + i) > '9') {
            ban = false;
            break;
        }
        i++;
    }
    return ban;
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  


    const int maxProcessesPerQueue = 5;
    const int maxQueues = maxProcessesPerQueue;
    queue<Process> queues[maxQueues];
    unordered_set<int> usedProgramNumbers;

void IWillHaveOrder(){
    int x = 1, y = 1;
    gotoxy(0,0);
    printf("%c", 201); //╔
    gotoxy(132,0);
    printf("%c", 187); //╗
    gotoxy(0,31);
    printf("%c", 200); //╚
    gotoxy(132,31);
    printf("%c", 188); //╝
    while (y<=30)
    {
        gotoxy(0,y);
        printf("%c", 186); //║
        gotoxy(132,y);
        printf("%c", 186); //║
        y++;
    }
    while (x<=131)
    {
        gotoxy(x,0);
        printf("%c", 205); //═
        gotoxy(x,31);
        printf("%c", 205); //═
        x++;
    }
    y = 1;
    int y2 = 3;
    gotoxy(11,2);
    printf("%c", 203); //╦
    gotoxy(11,31);
    printf("%c", 202); //╩
    gotoxy(33,0);
    printf("%c", 203); //╦
    gotoxy(33,31);
    printf("%c", 202); //╩
    gotoxy(79,0);
    printf("%c", 203); //╦
    gotoxy(79,31);
    printf("%c", 202); //╩
    while (y<=30)
    {
        gotoxy(33,y);
        printf("%c", 186); //║
        gotoxy(79,y);
        printf("%c", 186); //║
        y++;
    }
    while (y2<=30){
        gotoxy(11,y2);
        printf("%c", 186); //║
        y2++;
    }
    x = 1;
    gotoxy(0,2);
    printf("%c", 204); //╠
    gotoxy(23,2);
    printf("%c", 185); //╣
    while (x<=32)
    {
        gotoxy(x,2);
        printf("%c", 205); //═
        x++;
    }
    gotoxy(11,2);
    printf("%c", 203); //╦
}

void ThisIsOrder(){
    int x = 1, y = 1;
    gotoxy(0,0);
    printf("%c", 201); //╔
    gotoxy(132,0);
    printf("%c", 187); //╗
    gotoxy(0,31);
    printf("%c", 200); //╚
    gotoxy(132,31);
    printf("%c", 188); //╝
    while (y<=30)
    {
        gotoxy(0,y);
        printf("%c", 186); //║
        gotoxy(132,y);
        printf("%c", 186); //║
        y++;
    }
    while (x<=131)
    {
        gotoxy(x,0);
        printf("%c", 205); //═
        gotoxy(x,31);
        printf("%c", 205); //═
        x++;
    }
}

void datosLotes(){
    char totalProcessesc[100];
    gotoxy(1,1);
    cout << "Ingrese el numero de procesos: ";
    cin >> totalProcessesc;
    while(!ValidaNumerosEnteros(totalProcessesc)){
        gotoxy(1,1);
        cout << "                                                 ";
        gotoxy(1,1);
        cout << "Ingrese el numero de procesos de nuevo: ";
        cin >> totalProcessesc;
    }
    totalProcesses = atoi(totalProcessesc);
    totallotes = totalProcesses % 5;
    if (totallotes == 0) {
        totallotes = 0;
    } else {
        totallotes = totalProcesses + (5 - totallotes);
    }
    totallotesr = totallotes / 5;
    totallotesrr = totallotes - (totallotesr*4);

    int currentQueue = 0;
    for (int i = 1; i <= totalProcesses; ++i) {
        Process newProcess;
        system("cls");
        ThisIsOrder();
        gotoxy(1,1);
        cout << "Proceso #" << i << ":" << endl;
        gotoxy(1,3);
        cout << "Ingrese el nombre del proceso: ";
        cin >> newProcess.name;
        newProcess.currentQueue = currentQueue+1;
        do{
            gotoxy(1,5);
            cout << "                                                                                                    ";
            gotoxy(1,5);
            cout << "Ingrese la operación a realizar (+, -, *, /, residuo, porcentaje): ";
            cin >> newProcess.operation;
        }while(newProcess.operation != "+" && newProcess.operation != "-" && newProcess.operation != "*" && newProcess.operation != "/" && newProcess.operation != "residuo" && newProcess.operation != "porcentaje");
        gotoxy(1,7);
        cout << "Ingrese el primer numero: ";
        char number1[100];
        cin >> number1;
        while (!ValidaNumerosEnteros(number1)) {
            gotoxy(1,7);
            cout << "Ingrese el primer numero de nuevo: ";
            cin >> number1;
        }
        newProcess.number1 = atoi(number1);
        gotoxy(1,9);
        cout << "Ingrese el segundo numero: ";
        char number2[100];
        cin >> number2;
        while (!ValidaNumerosEnteros(number2)) {
            gotoxy(1,9);
            cout << "                                                                     ";
            gotoxy(1,9);
            cout << "Ingrese el segundo numero de nuevo: ";
            cin >> number2;
        }
        newProcess.number2 = atoi(number2);
        if(newProcess.operation == "/"){
            while(newProcess.number2 == 0){
                gotoxy(1,9);
                cout << "                                                                     ";
                gotoxy(1,9);
                cout << "Ingrese el segundo numero de nuevo: ";
                cin >> newProcess.number2;
            }
        }
        if(newProcess.operation == "+"){
            newProcess.result = newProcess.number1 + newProcess.number2;       
        }
        else if(newProcess.operation == "-"){
            newProcess.result = newProcess.number1 - newProcess.number2;       
        }
        else if(newProcess.operation == "*"){
            newProcess.result = newProcess.number1 * newProcess.number2;       
        }
        else if(newProcess.operation == "/"){
            newProcess.result = newProcess.number1 / newProcess.number2;       
        }
        else if(newProcess.operation == "residuo"){
            newProcess.result = newProcess.number1 % newProcess.number2;       
        }
        else if(newProcess.operation == "porcentaje"){
            newProcess.result = (newProcess.number1 * newProcess.number2) / 100;;        
        }
        else {
            gotoxy(1,11);
            cout << "Operacion no valida" << endl;
        }

        gotoxy(1,11);
        cout << "Ingrese el tiempo maximo estimado (mayor a 0): ";
        cin >> newProcess.estimatedTime;
        while(newProcess.estimatedTime == 0){
            gotoxy(1,11);
            cout << "Ingrese el tiempo maximo estimado (mayor a 0) de nuevo: ";
            cin >> newProcess.estimatedTime;
        }

        do {
            gotoxy(1,13);
            cout << "Ingrese el numero de programa (único): ";
            cin >> newProcess.programNumber;
        } while (usedProgramNumbers.count(newProcess.programNumber) > 0);
        usedProgramNumbers.insert(newProcess.programNumber);

        queues[currentQueue].push(newProcess);

        if (queues[currentQueue].size() >= maxProcessesPerQueue) {
            currentQueue++;
        }
    }
}

void imprimirdata() {
    int procesosTotales = totalProcesses;
    int lotesf = totallotesrr;
    int ffy = 7;
    for (int i = 0; i < maxQueues; i++) {
        gotoxy(1,1);
        cout << "Lotes restantes: " << lotesf;
        int ay = 7;
        int y = 7;
        if (!queues[i].empty()) {
            gotoxy(3,3);
            cout << "Lote #" << i + 1 << endl;
            queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
            while (!tempQueue.empty()) {
                // fila 1
                Process tprocess = tempQueue.front();
                tempQueue.pop();
                gotoxy(3,5);
                cout << "ID";
                gotoxy(3,y);
                cout << tprocess.programNumber;
                gotoxy(6,5);
                cout << "TME";
                gotoxy(6,y);
                cout << tprocess.estimatedTime;
                y = y + 2;
            }
            while(!queues[i].empty()){
                // fila 2
                Process process = queues[i].front();
                gotoxy(12,3);
                cout << "Ejec";
                gotoxy(12,5);
                cout << "Nn "; // nombre
                gotoxy(12,7);
                cout << "ID";
                gotoxy(12,9);
                cout << "Ope";
                gotoxy(12,11);
                cout << "TME";
                gotoxy(12,13);
                cout << "TT";
                gotoxy(12,15);
                cout << "TR";
                gotoxy(18,5);
                cout << process.name;
                gotoxy(18,7);
                cout << process.programNumber;
                gotoxy(18,9);
                cout << process.operation;
                gotoxy(18,11);
                cout << process.estimatedTime;
                gotoxy(80,5);
                cout << "Procesos restantes";
                gotoxy(80,7);
                cout << "            ";
                gotoxy(80,7);
                cout << procesosTotales;
                int tiempo = process.estimatedTime;
                int tiempotranscurrido = 0;
                while(tiempo > 0){
                    gotoxy(18,13);
                    cout << tiempotranscurrido;
                    gotoxy(18,15);
                    cout << "   ";
                    gotoxy(18,15);
                    cout << tiempo;
                    gotoxy(80,9);
                    cout << "Tiempo total";
                    gotoxy(80,11);
                    cout << timer;
                    gotoxy(80,11);
                    cout << timecontador;
                    tiempo = tiempo - 1;
                    timer = timer + 1;
                    timecontador = timecontador + 1;
                    tiempotranscurrido = tiempotranscurrido + 1;
                    process.timeelapsed = tiempotranscurrido;
                    Sleep(1000);
                }
                procesosTotales = procesosTotales - 1;
                // fila 3           
                gotoxy(34,3);
                cout << "Terminados";
                gotoxy(34,5);
                cout << "ID";
                gotoxy(38,5);
                cout << "Ope";
                gotoxy(60,5);
                cout << "Res";
                gotoxy(74,5);
                cout << "Lote";
                gotoxy(34,ffy);
                cout << "      ";
                gotoxy(34,ffy);
                cout << process.programNumber;
                gotoxy(38,ffy);
                cout << "      ";
                gotoxy(38,ffy);
                cout << process.number1 << process.operation << process.number2;
                gotoxy(60,ffy);
                cout << "      ";
                gotoxy(60,ffy);
                cout << process.result;
                gotoxy(66,ffy);
                cout << "      ";
                gotoxy(74,ffy);
                cout << process.currentQueue;
                ffy = ffy + 2;
                // acomodar fila 1
                gotoxy(3,ay);
                cout << "       ";
                ay = ay + 2;
                queues[i].pop(); 
            }
            int contador = 0;
            int by = 9;
            while (contador <= 5){
                gotoxy(3,by);
                cout << "       ";
                by = by + 2;
                contador++;
            }
        }
        lotesf = lotesf - 1;
    }
    procesosTotales = 0;
    gotoxy(80,7);
    cout << "            ";
    gotoxy(18,13);
    cout << "   ";
    gotoxy(18,13);
    cout << "0";
    gotoxy(80,11);
    cout << timer;
    gotoxy(18,15);
    cout << "0";
    gotoxy(1,1);
    cout << "Lotes restantes: " << "    ";
    gotoxy(1,1);
    cout << "Lotes restantes: " << 0;
}

int main() {
    HWND consoleWindow = GetConsoleWindow();
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    MoveWindow(consoleWindow, desktop.left, desktop.top, desktop.right, desktop.bottom, TRUE);
    system("pause");
    ThisIsOrder();
    datosLotes();
    system("cls");
    IWillHaveOrder();
    imprimirdata();
    gotoxy(80,30);
    system("pause");
    system("cls");
    return 0;
}
