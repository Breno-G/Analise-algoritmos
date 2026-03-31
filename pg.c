#include <stdio.h>
#include <math.h>
#include <time.h>

double calculaTempo(clock_t inicio, clock_t fim){ 
    return ((double) (fim - inicio)) / CLOCKS_PER_SEC;
}

double calculaTermoGeral(double primeiroTermo, double quociente, int nTermos){
    return primeiroTermo * pow(quociente, nTermos - 1);
}

double somaArray(
    double (*calculaTermoGeral)(double, double, int), 
    double (*calculaTempo)(clock_t, clock_t),
    double primeiroTermo, 
    double quociente, 
    int nTermos){

    clock_t tInicial, tFinal;
    double arrayResultados[30];
    double somatorio = 0.0;
    int i;

    tInicial = clock();

    for (i = 1; i <= nTermos; i++){
        arrayResultados[i-1] = calculaTermoGeral(primeiroTermo, quociente, i);
    }
    
    for (i = 0; i < nTermos ; i++){
        somatorio += arrayResultados[i];
    }

    tFinal =  clock();
    return calculaTempo(tInicial,tFinal);
}

double calculaNovoElemento(
    double(*calculaTermoGeral)(double,double,int),
    double(*calculaTempo)(clock_t,clock_t),
    double primeiroTermo, 
    double quociente, 
    int nTermos)
{
    clock_t tInicial, tFinal;
    double somatorio = 0.0;
    int i;
    
    tInicial = clock();

    for (i = 1; i <= nTermos; i++){
        somatorio += calculaTermoGeral(primeiroTermo, quociente, i);
    }

    tFinal = clock();
    
    return calculaTempo(tInicial, tFinal);
}

double calculaFormula(
    double (*calculaTempo)(clock_t,clock_t),
    double primeiroTermo, 
    double quociente, 
    int nTermos){
    clock_t tInicial, tFinal;
    
    tInicial = clock();

    double somatorio =  primeiroTermo * (pow(quociente,nTermos-1)-1) / (quociente - 1);
   
    tFinal = clock();

    return calculaTempo(tInicial,tFinal); 
}

int main()
{
    double a1 = 3.0 / 2.0;
    double q = 2.0 / 3.0;
    int n = 30;

    double tempoArray = somaArray(calculaTermoGeral, calculaTempo, a1, q, n);
    double tempoSomaElemento = calculaNovoElemento(calculaTermoGeral, calculaTempo, a1, q, n);
    double tempoFormula = calculaFormula(calculaTempo, a1, q, n);

    printf("Tempo array: %.10f segundos \n", tempoArray);
    printf("Tempo por elemento: %.10f segundo \n", tempoSomaElemento);
    printf("Tempo formula: %.10f segundos \n", tempoFormula);

    return 0;
}
