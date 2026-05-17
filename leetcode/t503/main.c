/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *nextGreaterElements( int *nums, int numsSize, int *returnSize ) {
    *returnSize = numsSize;
    int *retval = malloc( *returnSize * sizeof( int ) );
    for ( int i = 0; i < numsSize; i++ ) {
        bool flag = false;
        for ( int j = ( i + 1 ) % numsSize; j != i; j = ( j + 1 ) % numsSize ) {
            if ( nums[i] < nums[j] ) {
                retval[i] = nums[j];
                flag = true;
                break;
            }
        }
        if ( !flag ) {
            retval[i] = -1;
        }
    }
    return retval;
}