bool isPowerOfFour( int n ) {
    // Potencia de 4 terao um unico bit ligado, e em posicoes multiplas de 2
    // Ex:  1 = 00000000000000000000000000000001
    // Ex:  4 = 00000000000000000000000000000100
    // Ex: 16 = 00000000000000000000000000010000
    // Ex: 64 = 00000000000000000000000001000000
    // ...

    // Iterar sobre as potencias de 4 ate encontrar n
    int power = 1;

    for ( int i = 0; i < 16; i++ ) {
        if ( n == power ) {
            return true;
        }
        if ( i < 15 ) {
            // Deslocar o bit duas casas para a esquerda
            power <<= 2;
        }
    }

    return false;
}
