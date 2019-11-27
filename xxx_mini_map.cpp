#include "DxLib.h"
#include "xxx_mini.h"
#include "xxx_mini_object.h"
#include "xxx_mini_class.h"


void map_init(void)
{

	static int r[5], rp[8], max = 75;
	static room room[5];
	int scr_x, scr_x2, scr_y, scr_y2, scr_num;
	int kai_x,kai_y,kai_num;
	int hito_x = 0,hito_y = 0, hito_way=0;
	int hito_x2 = 50*(16/2-1),hito_y2 = -20+50 * (12 / 2-1);

	r[0] = GetRand(max - 40) + 20;
	r[1] = GetRand(max - 40) + 20;
	if (r[0] > max / 2)r[2] = GetRand(r[0] - 40) + 20;
	else r[2] = GetRand(max - r[0] - 40) + r[0] + 20;
	if (r[1] > max / 2)r[3] = GetRand(r[1] -40) +20;
	else r[3] = GetRand(max - r[1] - 40) + r[1] + 20;

	for (int i = 0; i < max; i++)for (int j = 0; j < max - 1; j++) mini_map(i, j, 1);

	if (r[0]>max / 2) {

		room[0].x1 = GetRand((max - r[0]) / 2 - 8) + r[0] + 2;
		room[0].x2 = GetRand((max - r[0]) / 2 - 8) + (max - r[0]) / 2 + r[0] + 6;
		room[0].y1 = GetRand(max / 2 - 8) + 2;
		room[0].y2 = GetRand(max / 2 - 8) + max / 2 + 6;

		rp[0] = GetRand(room[0].y2 - room[0].y1 - 4) + room[0].y1 + 2;
		for (int i = r[0]; i < room[0].x1; i++) mini_map(i, rp[0], 0);

		if (r[1]>max / 2) {

			room[1].x1 = GetRand(r[0] / 2 - 8) + 2;
			room[1].x2 = GetRand(r[0] / 2 - 8) + r[0] / 2 + 6;
			room[1].y1 = GetRand((max - r[1]) / 2 - 8) + r[1] + 2;
			room[1].y2 = GetRand((max - r[1]) / 2 - 8) + (max - r[1]) / 2 + r[1] + 6;

			rp[1] = GetRand(room[1].y2 - room[1].y1 - 4) + room[1].y1 + 2;
			for (int i = room[1].x2; i < r[0]; i++) mini_map(i, rp[1], 0);

			rp[2] = GetRand(room[1].x2 - room[1].x1 - 4) + room[1].x1 + 2;
			for (int i = r[1]; i < room[1].y2; i++) mini_map(rp[2], i, 0);

			if (r[2]>r[0] / 2) {

				room[2].x1 = GetRand((r[0] - r[2]) / 2 - 8) + r[2] + 2;
				room[2].x2 = GetRand((r[0] - r[2]) / 2 - 8) + (r[0] - r[2]) / 2 + r[2] + 6;
				room[2].y1 = GetRand(r[1] / 2 - 8) + 2;
				room[2].y2 = GetRand(r[1] / 2 - 8) + r[1] / 2 + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = room[2].y2; i < r[1]; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = r[2]; i <room[2].x1 ; i++) mini_map(i, rp[4], 0);

				room[3].x1 = GetRand(r[2] / 2 - 8) + 2;
				room[3].x2 = GetRand(r[2] / 2 - 8) + r[2] / 2 + 6;
				room[3].y1 = GetRand(r[3] / 2 - 8) + 2;
				room[3].y2 = GetRand(r[3] / 2 - 8) + r[3] / 2 + 6;
	
				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = room[3].x1; i <r[2]; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);
				
				room[4].x1 = GetRand(r[2] / 2 - 8) + 2;
				room[4].x2 = GetRand(r[2] / 2 - 8) + r[2] / 2 + 6;
				room[4].y1 = GetRand((r[1] - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((r[1] - r[3]) / 2 - 8) + (r[1] - r[3]) / 2 + r[3] + 6;
		
				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i =  r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
			else {

				room[2].x1 = GetRand(r[2] / 2 - 8) + 2;
				room[2].x2 = GetRand(r[2] / 2 - 8) + r[2] / 2 + 6;
				room[2].y1 = GetRand(r[1] / 2 - 8) + 2;
				room[2].y2 = GetRand(r[1] / 2 - 8) + r[1] / 2 + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = room[2].y2; i < r[1]; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = room[2].x2; i < r[2]; i++) mini_map(i, rp[4], 0);
				
				room[3].x1 = GetRand((r[0] - r[2]) / 2 - 8) + r[2] + 2;
				room[3].x2 = GetRand((r[0] - r[2]) / 2 - 8) + (r[0] - r[2]) / 2 + r[2] + 6;
				room[3].y1 = GetRand(r[3] / 2 - 8) + 2;
				room[3].y2 = GetRand(r[3] / 2 - 8) + r[3] / 2 + 6;

				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = r[2]; i <room[3].x1; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);

				room[4].x1 = GetRand((r[0] - r[2]) / 2 - 8) + r[2] + 2;
				room[4].x2 = GetRand((r[0] - r[2]) / 2 - 8) + (r[0] - r[2]) / 2 + r[2] + 6;
				room[4].y1 = GetRand((r[1] - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((r[1] - r[3]) / 2 - 8) + (r[1] - r[3]) / 2 + r[3] + 6;

				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i = r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
		}
		else {
			room[1].x1 = GetRand(r[0] / 2 - 8) + 2;
			room[1].x2 = GetRand(r[0] / 2 - 8) + r[0] / 2 + 6;
			room[1].y1 = GetRand(r[1] / 2 - 8) + 2;
			room[1].y2 = GetRand(r[1] / 2 - 8) + r[1] / 2 + 6;

			rp[1] = GetRand(room[1].y2 - room[1].y1 - 4) + room[1].y1 + 2;
			for (int i = room[1].x2; i < r[0]; i++) mini_map(i, rp[1], 0);

			rp[2] = GetRand(room[1].x2 - room[1].x1 - 4) + room[1].x1 + 2;
			for (int i = room[1].y1; i < r[1]; i++) mini_map(rp[2], i, 0);

			if (r[2]>r[0] / 2) {

				room[2].x1 = GetRand((r[0] - r[2]) / 2 - 8) + r[2] + 2;
				room[2].x2 = GetRand((r[0] - r[2]) / 2 - 8) + (r[0] - r[2]) / 2 + r[2] + 6;
				room[2].y1 = GetRand((max - r[1]) / 2 - 8) + r[1] + 2;
				room[2].y2 = GetRand((max - r[1]) / 2 - 8) + (max - r[1]) / 2 + r[1] + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = r[1]; i < room[2].y1; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = r[2]; i <room[2].x1; i++) mini_map(i, rp[4], 0);
				
				room[3].x1 = GetRand(r[2] / 2 - 8) + 2;
				room[3].x2 = GetRand(r[2] / 2 - 8) + r[2] / 2 + 6;
				room[3].y1 = GetRand((r[3] - r[1]) / 2 - 8) + r[1] + 2;
				room[3].y2 = GetRand((r[3] - r[1]) / 2 - 8) + (r[3] - r[1]) / 2 + r[1] + 6;

				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = room[3].x1; i <r[2]; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);

				room[4].x1 = GetRand(r[2] / 2 - 8) + 2;
				room[4].x2 = GetRand(r[2] / 2 - 8) + r[2] / 2 + 6;
				room[4].y1 = GetRand((max - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((max - r[3]) / 2 - 8) + (max - r[3]) / 2 + r[3] + 6;

				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i = r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
			else {

				room[2].x1 = GetRand(r[2] / 2 - 8) + 2;
				room[2].x2 = GetRand(r[2] / 2 - 8) + r[2] / 2 + 6;
				room[2].y1 = GetRand((max - r[1]) / 2 - 8) + r[1] + 2;
				room[2].y2 = GetRand((max - r[1]) / 2 - 8) + (max - r[1]) / 2 + r[1] + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = r[1]; i < room[2].y1; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = room[2].x2; i < r[2]; i++) mini_map(i, rp[4], 0);

				room[3].x1 = GetRand((r[0] - r[2]) / 2 - 8) + r[2] + 2;
				room[3].x2 = GetRand((r[0] - r[2]) / 2 - 8) + (r[0] - r[2]) / 2 + r[2] + 6;
				room[3].y1 = GetRand((r[3] - r[1]) / 2 - 8) + r[1] + 2;
				room[3].y2 = GetRand((r[3] - r[1]) / 2 - 8) + (r[3] - r[1]) / 2 + r[1] + 6;

				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = r[2]; i <room[3].x1; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);

				room[4].x1 = GetRand((r[0] - r[2]) / 2 - 8) + r[2] + 2;
				room[4].x2 = GetRand((r[0] - r[2]) / 2 - 8) + (r[0] - r[2]) / 2 + r[2] + 6;
				room[4].y1 = GetRand((max - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((max - r[3]) / 2 - 8) + (max - r[3]) / 2 + r[3] + 6;

				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i = r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
		}
	}
	else {

		room[0].x1 = GetRand(r[0] / 2 - 8) + 2;
		room[0].x2 = GetRand(r[0] / 2 - 8) + r[0] / 2 + 6;
		room[0].y1 = GetRand(max / 2 - 8) + 2;
		room[0].y2 = GetRand(max / 2 - 8) + max / 2 + 6;

		rp[0] = GetRand(room[0].y2 - room[0].y1 - 4) + room[0].y1 + 2;
		for (int i = room[0].x2; i < r[0]; i++) mini_map(i, rp[0], 0);

		if (r[1]>max / 2) {

			room[1].x1 = GetRand((max - r[0]) / 2 - 8) + r[0] + 2;
			room[1].x2 = GetRand((max - r[0]) / 2 - 8) + (max - r[0]) / 2 + r[0] + 6;
			room[1].y1 = GetRand((max - r[1]) / 2 - 8) + r[1] + 2;
			room[1].y2 = GetRand((max - r[1]) / 2 - 8) + (max - r[1]) / 2 + r[1] + 6;

			rp[1] = GetRand(room[1].y2 - room[1].y1 - 4) + room[1].y1 + 2;
			for (int i = r[0]; i < room[1].x1; i++) mini_map(i, rp[1], 0);

			rp[2] = GetRand(room[1].x2 - room[1].x1 - 4) + room[1].x1 + 2;
			for (int i = r[1]; i < room[1].y2; i++) mini_map(rp[2], i, 0);

			if (r[2] - r[0]>(max - r[0]) / 2) {

				room[2].x1 = GetRand((max - r[2]) / 2 - 8) + r[2] + 2;
				room[2].x2 = GetRand((max - r[2]) / 2 - 8) + (max - r[2]) / 2 + r[2] + 6;
				room[2].y1 = GetRand(r[1] / 2 - 8) + 2;
				room[2].y2 = GetRand(r[1] / 2 - 8) + r[1] / 2 + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = room[2].y2; i < r[1]; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = r[2]; i <room[2].x1; i++) mini_map(i, rp[4], 0);

				room[3].x1 = GetRand((r[2] - r[0]) / 2 - 8) + r[0] + 2;
				room[3].x2 = GetRand((r[2] - r[0]) / 2 - 8) + (r[2] - r[0]) / 2 + r[0] + 6;
				room[3].y1 = GetRand(r[3] / 2 - 8) + 2;
				room[3].y2 = GetRand(r[3] / 2 - 8) + r[3] / 2 + 6;

				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = room[3].x1; i <r[2]; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);

				room[4].x1 = GetRand((r[2] - r[0]) / 2 - 8) + r[0] + 2;
				room[4].x2 = GetRand((r[2] - r[0]) / 2 - 8) + (r[2] - r[0]) / 2 + r[0] + 6;
				room[4].y1 = GetRand((r[1] - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((r[1] - r[3]) / 2 - 8) + (r[1] - r[3]) / 2 + r[3] + 6;

				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i = r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
			else {

				room[2].x1 = GetRand((r[2] - r[0]) / 2 - 8) + r[0] + 2;
				room[2].x2 = GetRand((r[2] - r[0]) / 2 - 8) + (r[2] - r[0]) / 2 + r[0] + 6;
				room[2].y1 = GetRand(r[1] / 2 - 8) + 2;
				room[2].y2 = GetRand(r[1] / 2 - 8) + r[1] / 2 + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = room[2].y2; i < r[1]; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = room[2].x2; i < r[2]; i++) mini_map(i, rp[4], 0);

				room[3].x1 = GetRand((max - r[2]) / 2 - 8) + r[2] + 2;
				room[3].x2 = GetRand((max - r[2]) / 2 - 8) + (max - r[2]) / 2 + r[2] + 6;
				room[3].y1 = GetRand(r[3] / 2 - 8) + 2;
				room[3].y2 = GetRand(r[3] / 2 - 8) + r[3] / 2 + 6;

				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = r[2]; i <room[3].x1; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);

				room[4].x1 = GetRand((max - r[2]) / 2 - 8) + r[2] + 2;
				room[4].x2 = GetRand((max - r[2]) / 2 - 8) + (max - r[2]) / 2 + r[2] + 6;
				room[4].y1 = GetRand((r[1] - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((r[1] - r[3]) / 2 - 8) + (r[1] - r[3]) / 2 + r[3] + 6;

				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i = r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
		}
		else {
			room[1].y1 = GetRand(r[1] / 2 - 8) + 2;
			room[1].y2 = GetRand(r[1] / 2 - 8) + r[1] / 2 + 6;
			room[1].x1 = GetRand((max - r[0]) / 2 - 8) + r[0] + 2;
			room[1].x2 = GetRand((max - r[0]) / 2 - 8) + (max - r[0]) / 2 + r[0] + 6;

			rp[1] = GetRand(room[1].y2 - room[1].y1 - 4) + room[1].y1 + 2;
			for (int i = r[0]; i < room[1].x1; i++) mini_map(i, rp[1], 0);

			rp[2] = GetRand(room[1].x2 - room[1].x1 - 4) + room[1].x1 + 2;
			for (int i = room[1].y1; i < r[1]; i++) mini_map(rp[2], i, 0);

			if (r[2] - r[0]>(max - r[0]) / 2) {

				room[2].x1 = GetRand((max - r[2]) / 2 - 8) + r[2] + 2;
				room[2].x2 = GetRand((max - r[2]) / 2 - 8) + (max - r[2]) / 2 + r[2] + 6;
				room[2].y1 = GetRand((max - r[1]) / 2 - 8) + r[1] + 2;
				room[2].y2 = GetRand((max - r[1]) / 2 - 8) + (max - r[1]) / 2 + r[1] + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = r[1]; i < room[2].y1; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = r[2]; i <room[2].x1; i++) mini_map(i, rp[4], 0);

				room[3].x1 = GetRand((r[2] - r[0]) / 2 - 8) + r[0] + 2;
				room[3].x2 = GetRand((r[2] - r[0]) / 2 - 8) + (r[2] - r[0]) / 2 + r[0] + 6;
				room[3].y1 = GetRand((r[3] - r[1]) / 2 - 8) + r[1] + 2;
				room[3].y2 = GetRand((r[3] - r[1]) / 2 - 8) + (r[3] - r[1]) / 2 + r[1] + 6;

				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = room[3].x1; i <r[2]; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);

				room[4].x1 = GetRand((r[2] - r[0]) / 2 - 8) + r[0] + 2;
				room[4].x2 = GetRand((r[2] - r[0]) / 2 - 8) + (r[2] - r[0]) / 2 + r[0] + 6;
				room[4].y1 = GetRand((max - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((max - r[3]) / 2 - 8) + (max - r[3]) / 2 + r[3] + 6;

				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i = r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
			else {

				room[2].x1 = GetRand((r[2] - r[0]) / 2 - 8) + r[0] + 2;
				room[2].x2 = GetRand((r[2] - r[0]) / 2 - 8) + (r[2] - r[0]) / 2 + r[0] + 6;
				room[2].y1 = GetRand((max - r[1]) / 2 - 8) + r[1] + 2;
				room[2].y2 = GetRand((max - r[1]) / 2 - 8) + (max - r[1]) / 2 + r[1] + 6;

				rp[3] = GetRand(room[2].x2 - room[2].x1 - 4) + room[2].x1 + 2;
				for (int i = r[1]; i < room[2].y1; i++) mini_map(rp[3], i, 0);

				rp[4] = GetRand(room[2].y2 - room[2].y1 - 4) + room[2].y1 + 2;
				for (int i = room[2].x2; i < r[2]; i++) mini_map(i, rp[4], 0);

				room[3].x1 = GetRand((max - r[2]) / 2 - 8) + r[2] + 2;
				room[3].x2 = GetRand((max - r[2]) / 2 - 8) + (max - r[2]) / 2 + r[2] + 6;
				room[3].y1 = GetRand((r[3] - r[1]) / 2 - 8) + r[1] + 2;
				room[3].y2 = GetRand((r[3] - r[1]) / 2 - 8) + (r[3] - r[1]) / 2 + r[1] + 6;

				rp[5] = GetRand(room[3].y2 - room[3].y1 - 4) + room[3].y1 + 2;
				for (int i = r[2]; i <room[3].x1; i++) mini_map(i, rp[5], 0);

				rp[6] = GetRand(room[3].x2 - room[3].x1 - 4) + room[3].x1 + 2;
				for (int i = room[3].y2; i < r[3]; i++) mini_map(rp[6], i, 0);

				room[4].x1 = GetRand((max - r[2]) / 2 - 8) + r[2] + 2;
				room[4].x2 = GetRand((max - r[2]) / 2 - 8) + (max - r[2]) / 2 + r[2] + 6;
				room[4].y1 = GetRand((max - r[3]) / 2 - 8) + r[3] + 2;
				room[4].y2 = GetRand((max - r[3]) / 2 - 8) + (max - r[3]) / 2 + r[3] + 6;

				rp[7] = GetRand(room[4].x2 - room[4].x1 - 4) + room[4].x1 + 2;
				for (int i = r[3]; i <room[4].y2; i++) mini_map(rp[7], i, 0);

			}
		}
	}

	if (rp[0] < rp[1]) for (int i = rp[0]; i<rp[1] + 1; i++)mini_map(r[0], i, 0);
	else for (int i = rp[1]; i<rp[0] + 1; i++)mini_map(r[0], i, 0);
	if (rp[2] < rp[3]) for (int i = rp[2]; i<rp[3] + 1; i++)mini_map(i, r[1], 0);
	else for (int i = rp[3]; i<rp[2] + 1; i++)mini_map(i, r[1], 0);
	if (rp[4] < rp[5]) for (int i = rp[4]; i<rp[5] + 1; i++)mini_map(r[2], i, 0);
	else for (int i = rp[5]; i<rp[4] + 1; i++)mini_map(r[2], i, 0);
	if (rp[6] < rp[7]) for (int i = rp[6]; i<rp[7] + 1; i++)mini_map(i, r[3], 0);
	else for (int i = rp[7]; i<rp[6] + 1; i++)mini_map(i, r[3], 0);

	for (int j = 0; j<5; j++)
		for (int i = room[j].x1; i < room[j].x2; i++)
			for (int k = room[j].y1; k < room[j].y2; k++) mini_map(i, k, 0);

	do {
		scr_num = GetRand(5);
		scr_x = (room[scr_num].x2 - room[scr_num].x1) / 2 + room[scr_num].x1 - 7;
		scr_y = (room[scr_num].y2 - room[scr_num].y1) / 2 + room[scr_num].y1 - 5;
	} while (mini_map(scr_x + 7, scr_y + 5, -1) != 0);

	mini_scroll(&scr_x2, &scr_y2, true);
	scr_x -= scr_x2;
	scr_y -= scr_y2;
	mini_scroll(&scr_x, &scr_y, false);

	hito_way = -100;
	hito_data(&hito_x, &hito_y, &hito_way,true);
	hito_way=0;
	hito_x2-=hito_x;
	hito_y2-=hito_y;
	hito_data(&hito_x2, &hito_y2, &hito_way, false);

	for (int i = 0; i < 5; i++)mini_room(i, &room[i], false);

	do {
		kai_num = GetRand(4);
		kai_x = GetRand(room[kai_num].x2 - room[kai_num].x1-10) + room[kai_num].x1+5;
		kai_y = GetRand(room[kai_num].y2 - room[kai_num].y1-10) + room[kai_num].y1+5;
	} while (mini_map(kai_x, kai_y, -1) != 0 || scr_num == kai_num || scr_num+1 == kai_num || scr_num-1 == kai_num);
	mini_map(kai_x, kai_y, 75);

}
