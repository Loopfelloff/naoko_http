const char* status_text(int code);

char* build_response(int status , const char* mime, const char* body , size_t body_len , size_t *out_len);
