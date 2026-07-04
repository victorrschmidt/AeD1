int maior( int a, int b ) {
    return a > b ? a : b;
}

bool isIdealPermutation( int *nums, int numsSize ) {
    int maximo = 0;

    for ( int i = 0; i < numsSize - 2; i++ ) {
        maximo = maior( maximo, nums[i] );

        if ( maximo > nums[i + 2] ) {
            return false;
        }
    }

    return true;
}