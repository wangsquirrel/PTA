#include "TokenBucket.h"
#include <iostream>

void TokenBucket::produce_token()
{
    if (tokens == bucket_size)
    {
       return;
    }      
    unsigned long long product = 0;
    if (produce_time == 0)
    {
        produce_time = time(NULL);
        product = 0;
    }
    else
    {
        time_t cur_time = time(NULL);
        product = (cur_time - produce_time) * produce_rate;
        if (product > 0)    
        {
            produce_time = cur_time;
        }
    }
    tokens = tokens + product;
    if(tokens > bucket_size)
    {
        tokens = bucket_size;
    }
}

unsigned long long TokenBucket::get_token(unsigned long long want)
    
{
    produce_token();
    srand(time(NULL));
    // genarate bigger random integer for upload ratio
    // This RAN_MAX is 2147516416 
    // !!!!!!! Maybe not inappropriate ~~~100000~~~
    // to be rewrite
    std::cout << "this torrent want  "<<want<<std::endl;
    unsigned long long r = (rand() * 100000) % want;

    if (r > tokens)
    {
        r = tokens;
        tokens = 0;
    }
    else
    {
        tokens -= r;
    }
    return r;
}
