//ячейки
struct Cell{
  int i;
  int j;
  int index;
  int top;
  int right;
  int bottom;
  int left;
  int visited;
  int empty;
  int ply;
  int endd;
  int wall;
};
typedef struct Cell Cell;
int CreateCell(Cell *array,int sizze);
int FindNeighbors(int *neighbors_ids, int sizze, Cell *array,  int *start_point_x, int *start_point_y, int *end_point_x, int *end_point_y);
//отрисовка
void Draw(Cell *array,int sizze);
void Draw2(Cell *array,int sizze, Cell *current);
// отследивание нажатий
void Update(Cell *array, Cell *current, Cell *end_cell, int sizze,int diff, int timmer, int ext_timmer);
//работа с файлами
void Save(Cell *array, int sizze,int diff,int timmer,int ext_timmer);
void Load(Cell *array, int *sizze,int *diff,int *ext_timmer);
//отладка
void Debugger (int i);
//string функции
int stringlength(char *string);
int stringcompare(char *string01,char *string02);
int stringswap(char *string01,char *string02);
int mysortstr01(char array[][81],int n);
int mysortstr02(char* array[],int n);
char* mygetstring();

//стек
struct stack_element {
        void *element;
        struct stack_element *prev;
};
struct _stack {
        int element_size;
        struct stack_element *top;
        void *buffer;
};
typedef struct _stack *stack;
stack create_stack (int _element_size);
int push(stack _stack, void *_element);
void * pop(stack _stack);
void delete_stack(stack _stack);
void print_stack(stack _stack,void (*print_head)(),void (*print_body)(void *_element),void (*print_foot)());
//доп функции
int ind(int i, int j, int sizze);
int mygetch( );
void SetCursor(int X,int Y);
void Pauza();
void Prt_time_spd(int timmer, int ext_timmer);
//главная программа
int main();
