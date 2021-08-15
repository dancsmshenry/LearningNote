int numWaterBottles(int numBottles, int numExchange)
{
    int sum, bottles;
    sum = numBottles;
    bottles = numBottles;

    while (bottles - numExchange >= 0)
    {
        sum = sum + (bottles / numExchange);
        bottles = bottles % numExchange + bottles / numExchange;
    }

    return sum;
}
