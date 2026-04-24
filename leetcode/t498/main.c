/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findDiagonalOrder( int **mat, int matSize, int *matColSize, int *returnSize ) {
    const int L = matSize;
    const int C = *matColSize;
    *returnSize = L * C;
    int *diagList = malloc( *returnSize * sizeof(int) );
    int diagPtr = 0;
    int curLine = 0;
    int curCol = 0;
    bool direction = 0; // 0 direita e pra cima, 1 esquerda e pra baixo

    while ( diagPtr != *returnSize ) {
        diagList[diagPtr] = mat[curLine][curCol];
        diagPtr++;
        if ( direction == false ) {
            curLine--;
            curCol++;
            // Saiu SÓ da linha = direita
            // Saiu SÓ da coluna = baixo
            // Saiu dos dois = baixo
            if ( curCol == C ) {
                curLine += 2;
                curCol--;
                direction = !direction;
            } else if ( curLine < 0 ) {
                curLine++;
                direction = !direction;
            }
        } else {
            curLine++;
            curCol--;
            // Saiu SÓ da linha = direita
            // Saiu SÓ da coluna = baixo
            // Saiu dos dois = direita
            if ( curLine == L ) {
                curLine--;
                curCol += 2;
                direction = !direction;
            } else if ( curCol < 0 ) {
                curCol++;
                direction = !direction;
            }
        }
    }

    return diagList;   
}
