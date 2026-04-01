#include <stdio.h>
#include <math.h>
#include <time.h>

double calculaTempo(clock_t inicio, clock_t fim);
double calculaTermoAtual(double primeiroTermo, double quociente, double base, int nTermos);
double somaArray(double primeiroTermo, double quociente, double base, int nTermos);
double calculaNovoElemento(double primeiroTermo, double quociente, double base, int nTermos);
double calculaFormula(double primeiroTermo, double quociente, double base, int nTermos);

int main()
{
    while(1){
        double a1 = 1.5, q = 2.0 / 3.0, baseLog = 2.0/3.0;

        int opcao, n = 999999;

        double tempoArray = somaArray(a1, q, baseLog, n );
        double tempoSomaElemento = calculaNovoElemento(a1, q, baseLog, n );
        double tempoFormula = calculaFormula(a1, q, baseLog, n );

        printf("\n%s\n", "------------------------------------------------------------");
        printf("%-25s | %-20s\n", "Metodo de Calculo", "Tempo Decorrido(s)");
        printf("%s\n", "--------------------------|--------------------------------");
        printf("%-25s | %.10f\n", "Soma com Array", tempoArray);
        printf("%-25s | %.10f\n", "Soma por Elemento", tempoSomaElemento);
        printf("%-25s | %.10f\n", "Soma por Formula (PA)", tempoFormula);
        printf("%s\n", "------------------------------------------------------------\n");

        printf("Digite 0 para sair ou qualquer outro numero para continuar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        if(opcao == 0){break;};
    }
    return 0;
}

double calculaTempo(clock_t inicio, clock_t fim){ 
    return ((double) (fim - inicio)) / CLOCKS_PER_SEC;
}

double calculaTermoAtual(double primeiroTermo, double quociente, double base, int nTermos){
    double logaritmando = primeiroTermo * pow(quociente, nTermos - 1);
    return log(logaritmando) / log(base);
}

double somaArray(double primeiroTermo, double quociente, double base, int nTermos){
    clock_t tInicial, tFinal;
    double arrayResultados[nTermos];
    double somatorio = 0.0;

    tInicial = clock();

    for (int i = 1; i <= nTermos; i++){
        arrayResultados[i-1] = calculaTermoAtual(primeiroTermo, quociente, base, i);
    }
    
    for (int i = 0; i < nTermos ; i++){
        somatorio += arrayResultados[i];
    }

    tFinal =  clock();
    return calculaTempo(tInicial,tFinal);
}

double calculaNovoElemento(double primeiroTermo, double quociente, double base, int nTermos){
    clock_t tInicial, tFinal;
    double somatorio = 0.0;
    
    tInicial = clock();

    for (int i = 1; i <= nTermos; i++){
        somatorio += calculaTermoAtual(primeiroTermo, quociente, base, i);
    }

    tFinal = clock();
    
    return calculaTempo(tInicial, tFinal);
}

double calculaFormula(double primeiroTermo, double quociente, double base, int nTermos){
    clock_t tInicial, tFinal;
    
    tInicial = clock();

    double logA1 = log(primeiroTermo) / log(base);
    double resultado = (nTermos * logA1) + (double)(nTermos * (nTermos - 1)) / 2.0;

    tFinal = clock();
    
    return calculaTempo(tInicial,tFinal); 
}
