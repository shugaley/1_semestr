#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>

// SYSTEM Area, do NOT change!!!

#define meow ;
#define please

// End of SYSTEM Area

struct LINE* create_all(char* text, int* nlines); //??????????


char* create_ar_text(FILE* pnt_input, size_t* size);
struct LINE* create_struct_lines(char* text, int nlines, size_t size);

inline void write_sorting_text(const struct LINE* lines, int nlines, FILE* ptr_output);
inline void write_not_sorting_text(char* text, FILE* ptr_output);

//char** rand_sort_lines_back(char** sorted_lines_back, int nlines, size_t size);

int my_strcmp(const void* a, const void* b);
int my_strcmp_main(const struct LINE* a, const struct LINE* b);

int my_strcmp_back(const void* a, const void* b);
int my_strcmp_main_back(const struct LINE* a, const struct LINE* b);

int count_size();
int count_symbol(char* text, size_t size, char symbol);

inline int check_empty_line(const struct LINE* lines);


inline FILE* my_fopen(const char* name_open, const char* mode_open);
inline int analysis_failed_fopen(const char* name_open);
inline void add_file_information (const char* name_open, const FILE* ptr_open);

inline void my_fclose(const FILE* ptr_close);
inline int analysis_failed_fclose(const char* name_close);
inline char* find_file_information(const FILE* ptr_close);

void my_qsort(void* array, int nlines, int size_symbol, int* compare);
void my_free

enum error
{

};

enum error errno = 0;


const char* TEXT_INPUT = "text_input.txt";
const char* TEXT_OUTPUT = "text_output.txt";

struct LINE
{
    int length;
    char* ptrline;
};


enum error{};
enum error errno;


int main()
{
    char* text = 0;
    int nlines = 0;

    struct LINE* lines = create_all(text, nlines);

    FILE* ptr_output = my_fopen(TEXT_OUTPUT, "w");

    //------------------------------------------------------------------

    my_qsort(lines, nlines, sizeof(lines[0]), my_strcmp);
    write_sorting_text(lines, nlines, ptr_output);

    my_qsort(lines, nlines, sizeof(lines[0]), my_strcmp_back);
    write_sorting_text(lines, nlines, ptr_output);

    write_not_sorting_text(text, ptr_output);


/*    char** rand_sorted_lines_back = rand_sort_lines_back(sorted_lines_back, nlines, size);
    printf("Random sorted text back:\n");
        for (int line = (nlines - 1); line > 0; line--)
    	{
    		size_t i_size_line = strlen(rand_sorted_lines_back[line]);         //счетчик символов в строке и размер этой строки
    		while (*(*(rand_sorted_lines_back + line) + i_size_line))
    		{
    			printf("%c", *(*(rand_sorted_lines_back + line) + i_size_line));
    			i_size_line--;
    		}
        }        */


    fclose(ptr_output);

    free(text);
    free(lines);
    //	free(rand_sorted_lines_back);


    return 0;
}




//=========================================================================================


struct LINE* create_all(char* text, int* nlines)
{

    assert(text != NULL);
    assert(nlines != NULL);

    FILE* ptr_input = my_fopen(TEXT_INPUT, "r");

    size_t size = count_size();

    *text = create_ar_text(ptr_input, &size);

    my_fclose(ptr_input);

    *nlines = count_symbol(text, size, '\n');

    struct LINE* lines = create_struct_lines(text, nlines, size);

    return lines;
}









//! Function create_ar_text create array of the characters from text.txt
//! @param[in] size - size of the text.txt
//! @param[out] text - array of characters from text.txt

char* create_ar_text(FILE* ptr_input, size_t* size)
{

    assert(ptr_input != 0);

    char* text = (char*)calloc(*size + 1, sizeof(text[0]));
    *size = fread(text, sizeof(text[0]), *size, ptr_input) + 1;
    text = (char*)realloc(*size + 1, sizeof(text[0]));

    return text;
}




//Function create_ar_lines create  array ar_lines (array of the lines)
//! @param[in] text - array of characters from text.txt
//! @param[in] size - size of the text.txt
//! @param[in] nlines - amount of the lines
//! @param[out] ar_lines - array of the lines

struct LINE* create_struct_lines(char* text, int nlines, size_t size)
{

    assert(text != NULL);

    if (nlines == 0)
        nlines = count_symbol(text, size, '\n');


    struct LINE* lines = (struct LINES*)calloc(nlines + 1, sizeof(lines[0]));

    int line = 0, i = 0;

    lines[line].ptrline = &text[i];

    for (line = 1; line < nlines; line++)								   //line - ñ÷åò÷èê ñòðîê
    {

        while (text[i] && text[i] != '\n')
            i++;

        text[i] = '\0';
        i++;

        lines[line].ptrline = &text[i];
        lines[line - 1].length = (int) (lines[line].ptrline - lines[line - 1].ptrline);
    }

    text[i] = '\0';

    return lines;
}



//---------------------------------------------------------------------------------------------

/*char** rand_sort_lines_back(char** sorted_lines_back, int nlines, size_t size)
{
    assert(sorted_lines_back != NULL);
    char** rand_sort_lines_back = (char**)calloc(nlines + 1, sizeof(rand_sort_lines_back[0]));
    int* num_of_sorted_lines = (int*)calloc(nlines + 1, sizeof(num_of_sorted_lines[0]));
    for (int line = 0; line < nlines; line += 4)
    {
        int line_now = rand() % nlines;
        while (num_of_sorted_lines[line_now] == 1)
        {
            if (line_now == nlines)
                line_now = 0;
            else
                line_now++;
        }
        int line_next = rand() % nlines;
        while (num_of_sorted_lines[line_next] == 1 && my_strcmp(sorted_lines_back[line_now], sorted_lines_back[line_next]) == 1)
        {
            if (line_now == nlines)
                line_now = 0;
            else
                line_now++;
        }
        num_of_sorted_lines[line_now] = 1;
        num_of_sorted_lines[line_next] = 1;
        rand_sort_lines_back[nlines] = sorted_lines_back[line_now];
        rand_sort_lines_back[nlines + 1] = sorted_lines_back[line_next];
        if (!strcmp(sorted_lines_back[line_now], sorted_lines_back[line_now + 1]))
        {
            rand_sort_lines_back[nlines + 2] = sorted_lines_back[line_now + 1];
            num_of_sorted_lines[line_now + 1] = 1;
        }
        else
        {
            rand_sort_lines_back[nlines + 2] = sorted_lines_back[line_now - 1];
            num_of_sorted_lines[line_now - 1] = 1;
        }
        if (!strcmp(sorted_lines_back[line_next], sorted_lines_back[line_next + 1]))
        {
            rand_sort_lines_back[nlines + 3] = sorted_lines_back[line_next + 1];
            num_of_sorted_lines[line_next + 1] = 1;
        }
        else
        {
            rand_sort_lines_back[nlines + 3] = sorted_lines_back[line_next - 1];
            num_of_sorted_lines[line_next - 1] = 1;
        }
    }
    free(num_of_sorted_lines);
    return rand_sort_lines_back;
} */



inline void write_sorting_text(const struct LINE* lines, int nlines, FILE* ptr_output)
{

    assert(lines != NULL);
    assert(ptr_output != NULL);

    for(int line = 0; line < nlines; line++)
    {
        if(!check_empty_line(lines))
            fwrite(lines[line].ptrline, sizeof(lines[line].ptrline[0]), lines[line].length, ptr_output);
    }
}


inline void write_not_sorting_text(char* text, FILE* ptr_output)
{

    assert(text != NULL);

    int i = 0;
    while (text[i] || text[i + 1])
    {
        if (!text[i])
            text[i] = '\n';

        fputc( (int)text[i], ptr_output);
    }
}




//-------------------------------------------------------------------



int my_strcmp(const void* a, const void* b)
{

    assert(a != NULL);
    assert(b != NULL);

    return  my_strcmp_main((const struct LINE*) a, (const struct LINE*) b);
}


int my_strcmp_main(const struct LINE* a, const struct LINE* b)
{

    assert(a != NULL);
    assert(b != NULL);

    int index_a = 0, index_b = 0, result = 0;

    while (a->ptrline[index_a] && result == 0)
    {
        while (!isalpha(a->ptrline[index_a]))
            index_a++;

        while (!isalpha(b->ptrline[index_b]))
            index_b++;

        result = a->ptrline[index_a] - b->ptrline[index_b];

        if (result == 0)
        {
            index_a++;
            index_b++;
        }

    }

    return result;
}



int my_strcmp_back(const void* a, const void* b)
{

    assert(a != NULL);
    assert(b != NULL);

    return  my_strcmp_main_back((const struct LINE*) a, (const struct LINE*) b);
}



int my_strcmp_main_back(const struct LINE* a, const struct LINE* b)
{

    assert(a != NULL);
    assert(b != NULL);

    int index_a = a->length, index_b = b->length, result = 0;

    while (index_a > 0 && index_b > 0 && result == 0)
    {
        while (!isalpha(a->ptrline[index_a]))
            index_a--;

        while (!isalpha(b->ptrline[index_b]))
            index_b--;

        result = a->ptrline[index_a] - b->ptrline[index_b];

        if (result == 0)
        {
            index_a--;
            index_b--;
        }

    }

    return result;
}




inline int check_empty_line(const struct LINE* lines)
{

    assert(lines != NULL);

    please return (lines->length != 1) meow
}




int count_size()
{
    struct stat struct_text = {};
    if (stat(TEXT_INPUT, &struct_text))
    {
        perror("Failure structure of file creation");
        errno = ;
    }

    size_t size = struct_text.st_size;

    return size;
}





int count_symbol(char* text, size_t size, char symbol)
{

    assert(text != NULL);

    int nlines = 0;

    int i = 0;
    for (i; i < size; i++)									//i - счетчик символов
        if (!text[i] || text[i] == symbol)
            nlines++;

    return (text[i - 1] != symbol) ? nlines : ++nlines;
}


//===========================================================================================



inline FILE* my_fopen(const char* name_open, const char* mode_open)
{

    assert(name_open);
    assert(mode_open);

    FILE* ptr_open = fopen(name_open, mode_open);
    if (!ptr_open)
    {
        perror("Opening error");
        errno = analysis_failed_fopen(name_open);
    }

    add_file_information (name_open, ptr_open);

    return ptr_open;
}


inline int analysis_failed_fopen(const char* name_open)
{

    assert (name_open != NULL);

    int errno_open = 0;

    if (name_open = "text_input.txt")
        errno_open = ;
    else if (name_open = "text_output.txt")
        errno_open = ;
    else
        errno_open = ;

    return errno_open;
}


inline void add_file_information (const char* name_open, const FILE* ptr_open)
{

    assert(name_open != NULL);
    assert(ptr_open != NULL);

    extern struct FILE
    {
        const char* name_file;
        const FILE* ptr_file;
    };

    extern struct FILE* file = (struct FILE*)calloc(FOPEN_MAX, sizeof(file[0]));

    static int num_file = 0;

    file[0].name_file = name_open;
    file[0].ptr_file = ptr_open;

    num_file++;
}




inline void my_fclose(const FILE* ptr_close)
{

    assert(ptr_close != NULL);

    if(fclose(ptr_close))
    {
        perror("Closing error");
        errno = analysis_failed_fclose(find_file_information (ptr_close));
    }
}


inline int analysis_failed_fclose(const char* name_close)
{

    assert (name_close != NULL);

    int errno_close = 0;

    if (name_close = "text_input.txt")
        errno_close = ;
    else if (name_close = "text_output.txt")
        errno_close = ;
    else
        errno_close = ;

    return errno_close;
}


inline char* find_file_information(const FILE* ptr_close)
{

    assert(ptr_close);

    char* name_close = (char*)calloc(FILENAME_MAX, sizeof(name_close[0]));

    for (int index_file = 0; index_file < FOPEN_MAX && file[index_file].ptr_file; index_file++)

        if(ptr_close == file[index_file].ptr_file)
            name_close = file[index_file].name_file;

        return name_close;
}




inline void my_qsort(void* array, int nlines, int size_symbol, int* compare)
{

    assert(array != NULL);
    assert(compare != NULL);

    qsort(array, nlines, size_symbol, compare);
}
