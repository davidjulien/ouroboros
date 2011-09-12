#include <stdio.h>
#include <substring_matching.h>

int main()
{
    t_file_info file1, file2;
/*    t_list_single l;
    t_list_words wl;
    */
    double d;

    file1.filepath = "TEST1.txt";
    file1.compressed_size = -1;

    file2.filepath = "TEST2.txt";
    file2.compressed_size = -1;

/*    
    wl = analyse_file(file1.filepath, 4, 2, &l, 1);
    display_list(wl); 
    free_list(&wl);
    free_single_list(&l);
    */

    d = distance_substring_matching(&file1, &file2, 6, 3);
    printf("%.3f\n", d); /* 0.8 dans le cas de l'exemple */

    return 0;
}
