#ifndef DEF_OBJECT_H
#define DEF_OBJECT_H

int map(int, int, int);
void palette(int *, int *, int *,int *,int *);
void scroll(double *);
void pal_num(int *);
void pal_col(int *,bool);
void name(char *,bool);
void select_box(int *,int *,bool);
void select_map(int *,int *,bool);
bool enter(bool,bool);
bool make_minmap(bool,bool);
bool make_help(bool,bool);
void obj_init(void);

#endif // !DEF_OBJECT_H

