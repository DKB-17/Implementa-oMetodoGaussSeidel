#include <iostream>
#include <math.h>

#define ordemMax 50

using namespace std;

float norma(float v[], float x[], int tam){

    float maxnum = 0;
    float maxden = 0;
    for(int i=0; i < tam;i++){
        int num = abs(v[i] - x[i]);
        if(num > maxnum){
            maxnum = num;
        }
        int den = abs(v[i]);
        if(den > maxden){
            maxden = den;
        }
    }
    return maxnum/maxden;
}

float* seidel (float A[][ordemMax], float b[], float epsilon, int interMax, int tam){

    interMax = 50;
    float x[tam];
    float v[tam];

    for(int i=0;i < tam;i++){
        for(int j=0;j < tam;j++){
            if (i != j){
                    A[i][j] = A[i][j]/A[i][i];
            }
        }
        b[i] = b[i]/A[i][i];
    }
    for(int k=1;k<interMax;k++){
        for(int i = 0; i<tam; i++){
            int S = 0;
            for(int j=0; j<tam; j++){
                if(i != j){
                    S = S + A[i][j] * x[j];
                }
            }
            x[i] = b[i] - S;
        }
        float d = norma(x, v, tam);
        if (d <= epsilon){
            return x;
        }

        for(int i=0;i<tam;i++){
            v[i] = x[i];
        }
    }


}

void lerVetor(float b[], int ordem){
    cout << endl;
    for(int j=0;j<ordem;j++){
        cout << "\tx[" << (j+1) << "]: ";
        cin >> b[j];
    }
}

void lerMatriz(float A[][ordemMax], int ordem){
    for(int i=0;i<ordem;i++){
        cout << "\n\t" << (i+1) << " Equacao:";
        lerVetor(A[i], ordem);
    }
}

void imprimirVetor(float b[], int ordem){
    cout << endl;
    for(int j=0; j<ordem; j++){
        cout << "\t" ;
        if(j>0){
            if(b[j]<0){
                cout << "- ";
            }else{
                cout << "+ ";
            }
        }
        cout << b[j] << "x[" << (j+1) << "]";
    }
}

void imprimirSistema(float A[][ordemMax], float b[], int ordem){
    for(int i=0;i<ordem;i++){
        imprimirVetor(A[i], ordem);
        cout << "\t= " << b[i];
    }
}

void lerErro(float *e){
    cout << "\nDigite o erro relativo: ";
    cin >> *e;
}


int main(){

    int tam;
    int op;
    float equacao[ordemMax][ordemMax];
    float igualdade[ordemMax];
    float erro = 0.00;

    do{
        system("cls");
        cout << "\nQuantidade de elementos da equacao: ";
        cin >> tam;

        lerMatriz(equacao, tam);
        lerVetor(igualdade, tam);

        imprimirSistema(equacao, igualdade, tam);

        lerErro(&erro);
        cout << erro;



        cout << "\n\nContinuar(1 = sim/0 = nao) ";
        cin >> op;

    }while(op != 0);

    return 0;
}
