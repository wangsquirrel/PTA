#include <time.h>
#include <stdlib.h>
class TokenBucket
{
public:
    unsigned long long bucket_size;
    unsigned long long produce_rate;
    unsigned long long tokens;
    time_t produce_time;
    void produce_token();
    unsigned long long get_token(unsigned long long want);
    TokenBucket(unsigned long long bs, unsigned long long pr) :
        bucket_size(bs), produce_rate(pr), tokens(0), produce_time(0) {}
};
