/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* swapNumbers(int* numbers, int numbersSize, int* returnSize)
{
    * returnSize = numbersSize;

    numbers[0] = numbers[0] - numbers[1];
    numbers[1] = numbers[0] + numbers[1];
    numbers[0] = numbers[1] - numbers[0];
    
    return numbers;
}//这两种方法都可以，但是加法会出现溢出的情况，建议做好用异或解决


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* swapNumbers(int* numbers, int numbersSize, int* returnSize)
{
    * returnSize = numbersSize;

    numbers[0] = numbers[0] + numbers[1];
    numbers[1] = numbers[0] - numbers[1];
    numbers[0] = numbers[0] - numbers[1];
    
    return numbers;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* swapNumbers(int* numbers, int numbersSize, int* returnSize){
    numbers[0] ^= numbers[1];
    numbers[1] ^= numbers[0];
    numbers[0] ^= numbers[1];
    *returnSize = numbersSize;
    return numbers;
}//最好的方法