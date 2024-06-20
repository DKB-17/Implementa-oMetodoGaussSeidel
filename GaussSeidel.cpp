#include <iostream>
#include <math.h>

#define ordemMax 50

using namespace std;

void lerVetor(double b[], int ordem){
    cout << endl;
    for(int j=0;j<ordem;j++){
        cout << "\tx[" << (j+1) << "]: ";
        cin >> b[j];
    }
}

void lerMatriz(double A[][ordemMax], int ordem){
    for(int i=0;i<ordem;i++){
        cout << "\n\t" << (i+1) << " Equacao:";
        lerVetor(A[i], ordem);
    }
}

void imprimirVetor(double b[], int ordem){
    cout << endl;
    for(int j=0; j<ordem; j++){
        cout << "\t" ;
        if(j>0){
            if(b[j]<0){
                cout << " ";
            }else{
                cout << "+";
            }
        }
        cout << b[j] << "x[" << (j+1) << "]";
    }
}

void imprimirSistema(double A[][ordemMax], double b[], int ordem){
    for(int i=0;i<ordem;i++){
        imprimirVetor(A[i], ordem);
        cout << "\t= " << b[i];
    }
}

void lerErro(float *e){
    cout << "\n\nDigite o erro relativo: ";
    cin >> *e;
}

bool converge(double A[][ordemMax], int tam){

    double b[tam];
    for(int i=0; i<tam; i++){
        b[i] = 1;
    }
    double maxnum = 0;
    for(int i=0; i < tam;i++){
        double den = A[i][i];
        double num = 0;
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

double parada(double v[], double x[], int tam){

    double maxnum = 0.0;
    double maxden = 0.0;
    for(int i=0; i < tam;i++){
        float num = (v[i] - x[i]);
        if(num > maxnum){
            maxnum = num;
        }
        float den = abs(v[i]);
        if(den > maxden){
            maxden = den;
        }
    }
    return (maxnum/maxden);
}

void gaussSeidel (double A[][ordemMax], double b[], float e, int tam){

    int interMax = 50;
    double x[tam];
    double v[tam];

    for(int i=0;i < tam;i++){
        x[i] = b[i]/A[i][i];
        v[i] = 0;
    }
    for(int k=1;k<interMax;k++){
            cout << "\n\t" << k << " Interacao: ";
            for(int i=0;i<tam;i++){
                cout << x[i] << "|";
            }
        for(int i = 0; i<tam; i++){
            double S = 0;
            for(int j=0; j<tam; j++){
                if(i != j){
                    S += A[i][j] * x[j];
                }
            }
            //cout << "\n" << b[i] << "-" << S << "/" << A[i][i] << "=" << ((b[i] - S) / A[i][i]);
            x[i] = (double) ((b[i] - S) / A[i][i]);
        }
        double d = parada(x, v, tam);
        if (d <= e){
                cout << endl;
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


int main(){

    int tam;
    int op;
    double equacao[ordemMax][ordemMax] = {{3,-1,1},{2,5,-1},{1,2,5}};
    double igualdade[ordemMax] = {5,-8,-3};
    float erro = 0.05;

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

            gaussSeidel(equacao, igualdade, erro ,tam);

        }else{
            cout << "Nao converge";
        }




        cout << "\n\nContinuar(1 = sim/0 = nao) ";
        cin >> op;

    }while(op != 0);

    return 0;
}
