bool isPalindrome( int x ) {
    char digits[10];
    if ( x < 0 ) {
        return false;
    }
    if ( x == 0 ) {
        return true;
    }
    size_t i;
    for ( i = 0; x > 0; i++, x /= 10 ) {
        digits[i] = ( char ) ( x % 10 ) + '0';
    }
    i--;
    for ( size_t j = 0; j < i; j++, i-- ) {
        if ( digits[j] != digits[i] ) {
            return false;
        }
    }
    return true;
}