void transform_pdf(const char *source_path, const char *dest_path);
int transform_word(const char *source_path, const char *dest_path);
int transform_ppt(const char *source_path, const char *dest_path);
void transform_xls(const char *source_path, const char *dest_path);
/*void transform_encoding(const char *source_path, const char *dest_path,
  const char *source_encoding, const char *dest_encoding);*/

int transform(const char *source_path, const char *dest_path, 
        const char *format, const char *encoding);
