int game(int* guess, int guessSize, int* answer, int answerSize)
{
    int sum = 0, i, j;
    
    for (i = 0, j = 0; i < guessSize, j < answerSize; i++, j++)
    {
        if ( guess[i] == answer[j]) sum++;
    }
    
    return sum;
}
