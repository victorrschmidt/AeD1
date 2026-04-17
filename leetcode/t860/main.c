bool lemonadeChange( int *bills, int billsSize ) {
    int bills5 = 0;
    int bills10 = 0;
    for ( int i = 0; i < billsSize; i++ ) {
        if ( bills[i] == 5 ) {
            bills5++;
        } else if ( bills[i] == 10 ) {
            bills10++;
            if ( bills5 > 0 ) {
                bills5--;
            } else {
                return false;
            }
        } else {
            if ( bills10 > 0 && bills5 > 0 ) {
                bills10--;
                bills5--;
            } else if ( bills5 > 2 ) {
                bills5 -= 3;
            } else {
                return false;
            }
        }
    }
    return true;
}