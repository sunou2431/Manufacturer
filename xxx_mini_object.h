#ifndef DEF_XXX_MINI_OBJECT_H
#define DEF_XXX_MINI_OBJECT_H

void hito_data(int *,int *,int *,bool);
int mini_map(int,int,int);
void mini_scroll(int *, int *, bool);

typedef struct room {
	int x1, y1,x2,y2;
}room;

void mini_room(int ,room *, bool);

void hito(int *, int *, int *,int *, bool);
void hito_atk(void);
void hito_damage(int, int);
void hito_status(int *,int *,int *,int *,bool);
void hito_sta_init(void);
void hito_sta_conv(void);

void enemy(int, int *, int *, int *,int *, bool);
void enemy_etc(int ,int *,int *,bool);
void enemy_atk(int,int,int);
void enemy_move(void);
int enemy_init(bool);


#endif // !DEF_XXX_MINI_OBJECT_H