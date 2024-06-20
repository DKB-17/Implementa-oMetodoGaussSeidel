#include <iostream>
#include <math.h>

#define ordemMax 50

using namespace std;

float parada(float v[], float x[], int tam){

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

void gaussSeidel (float A[][ordemMax], float b[], float e, int interMax, int tam){

    float x[tam];
    float v[tam];

    for(int i=0;i < tam;i++){
        x[i] = b[i]/A[i][i];
        v[i] = 0;
    }
    for(int k=1;k<interMax;k++){
        for(int i = 0; i<tam; i++){
            int S = 0;
            for(int j=0; j<tam; j++){
                if(i != j){
                    S -= A[i][j] * x[j];
                }
            }
            x[i] = (float) ((b[i] - S) / A[i][i]);
        }
        float d = parada(x, v, tam);
        if (d <= e){
            for(int i=0;i<tam;i++){
                cout << x[i] << "|";
            }
            return;
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
    cout << "\n\nDigite o erro relativo: ";
    cin >> *e;
}

bool converge(float A[][ordemMax], int tam){

    double b[tam];
    for(int i=0; i<tam; i++){
        b[i] = 1;
    }
    float maxnum = 0;
    for(int i=0; i < tam;i++){
        float den = A[i][i];
        float num = 0;
        for(int j=0;j < tam;j++){
            if(i != j){
                num += (A[i][j] * b[j]);
            }
        }
        b[i] = (double) num/den;
        if(maxnum < abs(b[i])){
            maxnum = abs(b[i]);
        }
    }
    if(maxnum < 1){
        return true;
    }else{
        return false;
    }
}

int main(){

    int tam;
    int op;
    int interMax = 50;
    float equacao[ordemMax][ordemMax];
    float igualdade[ordemMax];
    float erro = 0.00;

    do{
        system("cls");
        cout << "\nQuantidade de elementos da equacao: ";
        cin >> tam;

        lerMatriz(equacao, tam);

        if(converge(equacao, tam)){
            cout << "\nConverge";

            cout << "\n\tResultados: ";
            lerVetor(igualdade, tam);

            imprimirSistema(equacao, igualdade, tam);

            lerErro(&erro);

            gaussSeidel(equacao, igualdade, erro, interMax ,tam);

        }else{
            cout << "Nao converge";
        }




        cout << "\n\nContinuar(1 = sim/0 = nao) ";
        cin >> op;

    }while(op != 0);

    return 0;
}
