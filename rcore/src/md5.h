#ifndef _MD5_H
#define _MD5_H

#ifdef __cplusplus
extern "C"
{
#endif//__cplusplus

// raiden 20110513
char* get_md5_str(const char* md5);
char* get_md5_file(const char* file);


void *create_md5_ctx();
void release_md5_ctx(void *ctx);
void md5_init(void *ctx);
void md5_update(void *ctx, const unsigned char *data, unsigned int len);
void md5_final(void *ctx, unsigned char *out);

#ifdef __cplusplus
} // extern "C"
#endif


#endif//_MD5_H
