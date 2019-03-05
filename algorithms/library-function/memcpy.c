void *memcpy(void *dest, const void *src, size_t n)
{
    char *tmp = dest;
    
    while(n--)
        *tmp++ = *src++;
    
    return dest;
}