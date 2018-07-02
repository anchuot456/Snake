#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<cstdlib>

#include"Console.h"

#define ConsoleWidth 120
#define ConsoleHeight 30
#define GameCreenWidth 60
#define GameCreenHeight 30

enum TrangThai{Up,Down,Left,Right};

struct toado{
	int x, y;
};
struct diem{
	int n;
	toado td;
};
struct snake{
	toado dot[50];
	int n;
	TrangThai tt;
	int score;
};
struct buffer{//bộ nhớ đệm
	char kitu;
	int mau;
};
struct bonus{
	toado td;
	int n;
};
struct wall{
	int n,t;
	toado td;
};
struct vien{
	toado td;
};
struct gach{
	vien vien[10];
	int tt,n;
};

buffer gamecreen[GameCreenHeight][GameCreenWidth];

//các hàm khởi tạo game
void khoitao(snake &snake,diem &diem){
	snake.score = 0;
	snake.n = 2;
	snake.tt = Right;
	snake.dot[0].x = GameCreenWidth / 2;
	snake.dot[0].y = GameCreenHeight / 2;
	snake.dot[1].x = GameCreenWidth / 2 - 1;
	snake.dot[1].y = GameCreenHeight / 2;
	diem.td.x = rand() % (GameCreenWidth-1);
	diem.td.y = rand() % (GameCreenHeight-1);
	diem.n = 1;
	if (diem.td.x == 0)
		diem.td.x++;
	if (diem.td.y == 0)
		diem.td.y++;
	for (int i = 0; i < GameCreenHeight; i++){
		for (int j = 0; j < GameCreenWidth; j++){
			gamecreen[i][j].kitu = ' ';
			gamecreen[i][j].mau = 7;
		}
	}
}

void VeMotO(int i, int j, char kitu, int mau = 7){
	gamecreen[i][j].kitu = kitu;
	gamecreen[i][j].mau = mau;
}

//các hàm chức năng game trong vòng lặp
void hienthi(snake &snake,diem &o,gach&gach){
	for (int i = 0; i < GameCreenHeight-1; i++){//vẽ khung
		VeMotO(i,0,219);
		VeMotO(i, GameCreenWidth-1,219);
	}
	for (int j = 0; j < GameCreenWidth; j++){
		VeMotO(0,j,219);
		VeMotO(GameCreenHeight-1,j,219);
	}
	for (int i = 0; i < snake.n; i++){// snake
		gotoxy(snake.dot[i].x, snake.dot[i].y);
		if (i == 0){
			VeMotO(snake.dot[i].y, snake.dot[i].x,'*',14);
		}
		else{
			VeMotO(snake.dot[i].y, snake.dot[i].x,'*');
		}
	}
	//điểm ăn
	VeMotO(o.td.y, o.td.x, '0');
	gotoxy(0, 0);
	//vẽ gamecreen
	for (int i = 0; i < GameCreenHeight; i++){
		for (int j = 0; j < GameCreenWidth; j++){
			gotoxy(j, i);
			setcolor(gamecreen[i][j].mau);
			putchar(gamecreen[i][j].kitu);
			if (gamecreen[i][j].kitu != -37)
				gamecreen[i][j].kitu = ' ';
		}
	}
	gotoxy(ConsoleWidth / 2 + 20, ConsoleHeight / 2);// khung ghi điểm
	printf("your score: %d", snake.score);
	gotoxy(ConsoleWidth / 2 + 20, ConsoleHeight / 2 + 1);
}
int  dieukhienchuyendong(snake &snake){
	char key;
	//truyền vị trí cho đốt sau
	for (int i = snake.n - 1; i > 0; i--){
		snake.dot[i] = snake.dot[i - 1];
	}
	//điều khiển
	if (_kbhit()){//nếu phát hiện phím nhấn
		key = _getch();
		if (key == 'A' || key == 'a'){
			if (snake.tt != Right)
				snake.tt = Left;
		}
		else if (key == 'D' || key == 'd'){
			if (snake.tt != Left)
				snake.tt = Right;
		}
		else if (key == 'W' || key == 'w'){
			if (snake.tt != Down)
				snake.tt = Up;
		}
		else if (key == 'S' || key == 's'){
			if (snake.tt != Up)
				snake.tt = Down;
		}
	}
	//Đốt đầu di chuyển
	if (snake.tt == Up)
		snake.dot[0].y--;
	else if (snake.tt == Down)
		snake.dot[0].y++;
	else if (snake.tt == Left)
		snake.dot[0].x--;
	else if (snake.tt == Right)
		snake.dot[0].x++;
	if (gamecreen[snake.dot[0].y][snake.dot[0].x].kitu==-37)//điều kiện thua
		return 0;
	for (int i = 1; i < snake.n; i++){
		if (snake.dot[0].x == snake.dot[i].x&&snake.dot[0].y == snake.dot[i].y)
			return 0;
	}
	return 1;
}
void an(snake &snake, diem &o,int &j,int&dem,int&t,int&u,int&k,int&demxoay){//ăn điểm
	if (snake.dot[0].x == o.td.x && snake.dot[0].y == o.td.y){//ăn được
		snake.n++;
		for (int i = snake.n; i > 0; i--){
			snake.dot[i] = snake.dot[i - 1];
		}
		if (snake.tt == Up)//hướng của đầu
			snake.dot[0].y--;
		else if (snake.tt == Down)
			snake.dot[0].y++;
		else if (snake.tt == Left)
			snake.dot[0].x--;
		else if (snake.tt == Right)
			snake.dot[0].x++;
		do{
			o.td.x = rand() % (GameCreenWidth - 1);//vị trí của điểm 
			o.td.y = rand() % (GameCreenHeight - 1);
			if (o.td.x == 0)
				o.td.x++;
			if (o.td.y == 0)
				o.td.y++;
		} while (gamecreen[o.td.y][o.td.x].kitu != ' ');
		//cộng điểm
		snake.score += o.n;
		if (snake.score % 5 == 0)j = 0;
		if (snake.score % 7 == 0)j = 0;
		if (snake.score % 12 == 0)j = 0;
		//xuất hiện bonus
		if (snake.score % 10 == 0 && snake.score >= 10)dem = t = 0;
		if (snake.score % 6 == 0 && snake.score > 10)dem = t = k = 0;
		if (snake.score % 4 == 0 && snake.score > 10)dem = t = u =0;
		if (snake.score % 3 == 0 && snake.score>10)dem = t = u = 0;
		if (snake.score % 5 == 0 && snake.score >= 10)dem = t = u = 0;
		if (snake.score % 9 == 0)demxoay = 0;
	}
}
void an(snake &snake, bonus &tocdo,int &k, int &dem,int &t){//ăn bonus
	if (snake.dot[0].x == tocdo.td.x&&snake.dot[0].y == tocdo.td.y){
		k = tocdo.n;
		VeMotO(tocdo.td.y, tocdo.td.x, ' ');
		gotoxy(tocdo.td.x, tocdo.td.y);
		setcolor(gamecreen[tocdo.td.y][tocdo.td.x].mau);
		putchar(gamecreen[tocdo.td.y][tocdo.td.y].kitu);
		dem++;
		t++;
	}
}
void an(snake &snake, wall &tuong,gach &gach,int&t){
	if (snake.dot[0].x == tuong.td.x&&snake.dot[0].y == tuong.td.y){
		gach.vien[0].td.x = rand()% (GameCreenWidth - 6);
		gach.vien[0].td.y = rand() % (GameCreenHeight - 6);
		gach.n = tuong.n;
		t++;
		if (tuong.t == 1){//tường dọc
			for (int j = 1; j < tuong.n; j++){
					gach.vien[j].td.x = gach.vien[j - 1].td.x;
					gach.vien[j].td.y = gach.vien[j - 1].td.y+1;
				}
			for (int i = 0; i<tuong.n; i++){
				VeMotO(gach.vien[i].td.y, gach.vien[i].td.x, 219);
			}
		}
		if (tuong.t == 2){//tường ngang
			for (int j = 1; j < tuong.n; j++){
				gach.vien[j].td.x = gach.vien[j - 1].td.x+1;
				gach.vien[j].td.y = gach.vien[j - 1].td.y;
			}
			for (int i = 0; i<tuong.n; i++)
				VeMotO(gach.vien[i].td.y, gach.vien[i].td.x, 219);
		}
		if (tuong.t == 3){//tường vuông góc
			for (int j = 1; j < tuong.n; j++){
				if (j < (tuong.n / 2)+1){
					gach.vien[j].td.x = gach.vien[j - 1].td.x + 1;
					gach.vien[j].td.y = gach.vien[j - 1].td.y;
				}
				else{
					gach.vien[j].td.x = gach.vien[j - 1].td.x;
					gach.vien[j].td.y = gach.vien[j - 1].td.y+1;
				}
			}
			for (int i = 0; i<tuong.n; i++)
				VeMotO(gach.vien[i].td.y, gach.vien[i].td.x, 219);
		}
		if (tuong.t == 4){//tường sole
			for (int j = 1; j < tuong.n; j++){
				gach.vien[j].td.x = gach.vien[j - 1].td.x + 2;
				gach.vien[j].td.y = gach.vien[j - 1].td.y;
			}
			for (int i = 0; i<tuong.n; i++)
				VeMotO(gach.vien[i].td.y, gach.vien[i].td.x, 219);
		}

		tuong.td.x == NULL;
		tuong.td.y == NULL;
		tuong.n = NULL;
		tuong.t = NULL;
	}
}
void an(snake&snake, toado& gate1, toado&gate2,int&n){
	if (snake.dot[0].x == gate1.x&&snake.dot[0].y == gate1.y){//nếu ăn
		snake.dot[0] = gate2;//xuất hiện ở cổng 2
		int i = rand() % 4;//random trạng thái của rắn
		if (i == 0)snake.tt = Left;
		else if (i == 1)snake.tt = Right;
		else if (i == 2)snake.tt = Up;
		else if (i == 3)snake.tt = Down;
		n++;
		gate1.x = gate1.y = gate2.x = gate2.y = NULL;
	}
	if (snake.dot[0].x == gate2.x&&snake.dot[0].y == gate2.y){//nếu ăn
		snake.dot[0] = gate1;//xuất hiện ở cổng 1
		int i = rand() % 4;//random trạng thái của rắn
		if (i == 0)snake.tt = Left;
		else if (i == 1)snake.tt = Right;
		else if (i == 2)snake.tt = Up;
		else if (i == 3)snake.tt = Down;
		n++;
		gate1.x = gate1.y = gate2.x = gate2.y = NULL;
	}
}
void an(snake&snake, toado&xoay, int&demxoay){
	if (snake.dot[0].x == xoay.x&&snake.dot[0].y == xoay.y){//ăn được
		for (int i = 0; i<snake.n / 2; i++){
			int x, y;
			x = snake.dot[i].x;
			y = snake.dot[i].y;
			snake.dot[i] = snake.dot[snake.n - i-1];
			snake.dot[snake.n - i-1].x = x;
			snake.dot[snake.n - i-1].y = y;
		}
		if (snake.dot[0].x - snake.dot[1].x == -1)snake.tt = Left;
		else if (snake.dot[0].x - snake.dot[1].x == 1)snake.tt = Right;
		else if (snake.dot[0].y - snake.dot[1].y == -1)snake.tt = Up;
		else if (snake.dot[0].y - snake.dot[1].y == 1)snake.tt = Down;
		demxoay++;
		xoay.x = xoay.y = NULL;
	}
}
void xuathien(snake &snake,diem &a, diem&b, diem&s,int &j){
	if (snake.score % 5 == 0 && snake.score>0){//điểm thưởng cấp B
		if (snake.score % 7 != 0&& snake.score%12!=0){
			if (j == 0){
					do{
						a.td.x = rand() % (GameCreenWidth - 1);
						a.td.y = rand() % (GameCreenHeight - 1);
						if (a.td.x == 0)a.td.x++;
						if (a.td.y == 0)a.td.y++;
					} while (gamecreen[a.td.y][a.td.x].kitu != ' ');
			}
			if (j < 50){
				a.n = 3;
				VeMotO(a.td.y, a.td.x, 'B', 8);
				gotoxy(a.td.x, a.td.y);
				setcolor(gamecreen[a.td.y][a.td.x].mau);
				putchar(gamecreen[a.td.y][a.td.x].kitu);
				j++;
			}
		}
	}
	if ((snake.score % 7) == 0 && snake.score>0){//điểm thưởng cấp A
		if (snake.score % 12 != 0){
			if (j == 0){
					do{
						b.td.x = rand() % (GameCreenWidth - 1);
						b.td.y = rand() % (GameCreenHeight - 1);
						if (b.td.x == 0)b.td.x++;
						if (b.td.y == 0)b.td.y++;
					} while (gamecreen[b.td.y][b.td.x].kitu != ' ');
			}
			if (j < 45){
				b.n = 5;
				VeMotO(b.td.y, b.td.x, 'A', 10);
				gotoxy(b.td.x, b.td.y);
				setcolor(gamecreen[b.td.y][b.td.x].mau);
				putchar(gamecreen[b.td.y][b.td.x].kitu);
				j++;
			}
		}
	}
	if ((snake.score % 12) == 0 && snake.score>0){//điểm thưởng cấp S
		if (j == 0){
				do{
					s.td.x = rand() % (GameCreenWidth - 1);
					s.td.y = rand() % (GameCreenHeight - 1);
					if (s.td.x == 0)s.td.x++;
					if (s.td.y == 0)s.td.y++;
				} while (gamecreen[s.td.y][s.td.x].kitu != ' ');
		}
		if (j < 40){
			s.n = 10;
			VeMotO(s.td.y, s.td.x, 'S', 14);
			gotoxy(s.td.x, s.td.y);
			setcolor(gamecreen[s.td.y][s.td.x].mau);
			putchar(gamecreen[s.td.y][s.td.x].kitu);
			j++;
		}
	}
}
void xuathienhieuung(snake &snake, bonus &tocdo, int &dem, int &t){//xuất hiện những điểm ăn có bonus
	if (t == 0){
		if (snake.score % 10 == 0 && snake.score >= 10){
			if (dem == 0){//biến đếm bằng 0 thì lặp vô hạn
				do{
					tocdo.td.y = rand() % (GameCreenHeight - 1);//y là trục tung
					tocdo.td.x = rand() % (GameCreenWidth - 1);//x là trục hoành
					if (tocdo.td.y == 0)tocdo.td.y++;
					if (tocdo.td.x == 0)tocdo.td.x++;
				} while (gamecreen[tocdo.td.y][tocdo.td.x].kitu != ' ');
			}
			if (dem < 60){
				tocdo.n = -50;
				VeMotO(tocdo.td.y, tocdo.td.x, 'C', 8);
				gotoxy(tocdo.td.x, tocdo.td.y);
				setcolor(gamecreen[tocdo.td.y][tocdo.td.x].mau);
				putchar(gamecreen[tocdo.td.y][tocdo.td.x].kitu);
				dem++;
			}
			else{
				tocdo.n = NULL;
				tocdo.td.x = tocdo.td.y = NULL;
			}
		}
		if (snake.score % 4 == 0 && snake.score>10){//tăng tốc độ
			if (dem == 0){//biến đếm bằng 0 thì lặp vô hạn
				do{
					tocdo.td.y = rand() % (GameCreenHeight - 1);//y là trục tung
					tocdo.td.x = rand() % (GameCreenWidth - 1);//x là trục hoành
					if (tocdo.td.y == 0)tocdo.td.y++;
					if (tocdo.td.x == 0)tocdo.td.x++;
				} while (gamecreen[tocdo.td.y][tocdo.td.x].kitu != ' ');
			}
			if (dem < 60){
				tocdo.n = 25;
				VeMotO(tocdo.td.y, tocdo.td.x, 'N', 8);
				gotoxy(tocdo.td.x, tocdo.td.y);
				setcolor(gamecreen[tocdo.td.y][tocdo.td.x].mau);
				putchar(gamecreen[tocdo.td.y][tocdo.td.x].kitu);
				dem++;
			}
			else{
				tocdo.n = NULL;
				tocdo.td.x = tocdo.td.y = NULL;
			}
		}
		if (snake.score % 6 == 0 && snake.score>10){//tăng tốc dộ siêu nhanh
			if (dem == 0){//biến đếm bằng 0 thì lặp vô hạn
				do{
					tocdo.td.y = rand() % (GameCreenHeight - 1);//y là trục tung
					tocdo.td.x = rand() % (GameCreenWidth - 1);//x là trục hoành
					if (tocdo.td.y == 0)tocdo.td.y++;
					if (tocdo.td.x == 0)tocdo.td.x++;
				} while (gamecreen[tocdo.td.y][tocdo.td.x].kitu != ' ');
			}
			if (dem < 60){
				tocdo.n = 50;
				VeMotO(tocdo.td.y, tocdo.td.x, 'N', 14);
				gotoxy(tocdo.td.x, tocdo.td.y);
				setcolor(gamecreen[tocdo.td.y][tocdo.td.x].mau);
				putchar(gamecreen[tocdo.td.y][tocdo.td.x].kitu);
				dem++;
			}
			else{
				tocdo.n = NULL;
				tocdo.td.x = tocdo.td.y = NULL;
			}
		}
	}
}
void xuathientuong(snake &snake, wall&tuong, int &u, int &t){
	if (t == 0){
		if (snake.score % 3 == 0 && snake.score > 10){
			if (snake.score % 4 != 0 && snake.score % 5 != 0&&snake.score%7!=0){
				if (u == 0){
					do{
					tuong.td.x = rand() % (GameCreenWidth - 1);
					tuong.td.y = rand() % (GameCreenHeight - 1);
					if (tuong.td.x == 0)tuong.td.x++;
					if (tuong.td.y == 0)tuong.td.y++;
					} while (gamecreen[tuong.td.y][tuong.td.x].kitu != ' ');
				}
				if (u < 40){//tường dọc
					tuong.t = 1;
					tuong.n = 5;
					VeMotO(tuong.td.y, tuong.td.x, 'W');
					u++;
				}
				else{
					tuong.n = tuong.t = tuong.td.x = tuong.td.y = NULL;
				}
			}
		}
		if (snake.score % 4 == 0 && snake.score>10){
			if (snake.score % 5 != 0&&snake.score%7!=0){
				if (u == 0){
					do{
					tuong.td.x = rand() % (GameCreenWidth - 1);
					tuong.td.y = rand() % (GameCreenHeight - 1);
					if (tuong.td.x == 0)tuong.td.x++;
					if (tuong.td.y == 0)tuong.td.y++;
					} while (gamecreen[tuong.td.y][tuong.td.x].kitu != ' ');
				}
				if (u < 50){//tường ngang
					tuong.t = 2;
					tuong.n = 5;
					VeMotO(tuong.td.y, tuong.td.x, 'W', 9);
					u++;
				}
				else{
					tuong.n = tuong.t = tuong.td.x = tuong.td.y = NULL;
				}
			}
		}
		if (snake.score % 5 == 0 && snake.score >= 10){
			if (snake.score % 7 != 0){
				if (u == 0){
					do{
					tuong.td.x = rand() % (GameCreenWidth - 1);
					tuong.td.y = rand() % (GameCreenHeight - 1);
					if (tuong.td.x == 0)tuong.td.x++;
					if (tuong.td.y == 0)tuong.td.y++;
					} while (gamecreen[tuong.td.y][tuong.td.x].kitu != ' ');
				}
				if (u < 60){//tường góc vuông
					tuong.t = 3;
					tuong.n = 5;
					VeMotO(tuong.td.y, tuong.td.x, 'W', 14);
					u++;
				}
				else{
					tuong.n = tuong.t = tuong.td.x = tuong.td.y = NULL;
				}
			}
		}
		if (snake.score % 7 == 0 && snake.score>10){
				if (u == 0){
					do{
					tuong.td.x = rand() % (GameCreenWidth - 1);
					tuong.td.y = rand() % (GameCreenHeight - 1);
					if (tuong.td.x == 0)tuong.td.x++;
					if (tuong.td.y == 0)tuong.td.y++;
					} while (gamecreen[tuong.td.y][tuong.td.x].kitu != ' ');
				}
				if (u < 50){//tường ngang
					tuong.t = 4;
					tuong.n = 5;
					VeMotO(tuong.td.y, tuong.td.x, 'W', 5);
					u++;
				}
				else{
					tuong.n = tuong.t = tuong.td.x = tuong.td.y = NULL;
				}
			}
		}
	}
void xuathiencong(snake&snake, toado&gate1, toado&gate2,int &t){
	if ((snake.score-10) % 6 == 0 && snake.score > 10){
		if (t == 0){
			do{
				gate1.x = rand() % (GameCreenWidth - 1);
				gate1.y = rand() % (GameCreenHeight - 1);
				if (gate1.x == 0)gate1.x++;
				if (gate1.y == 0)gate1.y++;
			} while (gamecreen[gate1.y][gate1.x].kitu != ' ');
			do{
				gate2.x = rand() % (GameCreenWidth - 1);
				gate2.y = rand() % (GameCreenHeight - 1);
				if (gate2.x == 0)gate2.x++;
				if (gate2.y == 0)gate2.y++;
			} while (gamecreen[gate2.y][gate2.x].kitu != ' ');
		}
		if (t < 60){
			VeMotO(gate1.y, gate1.x, 'G');
			VeMotO(gate2.y, gate2.x, 'G');
			t++;
		}
		else{
			gate1.x = gate1.y = gate2.x = gate2.y = NULL;
		}
	}
}
void xuathienxoaydau(snake&snake, toado&xoay, int&demxoay){
	if (snake.score % 9 == 0 && snake.score > 0){
		if (demxoay == 0){
			do{
				xoay.x = rand() % (GameCreenWidth - 1);
				xoay.y = rand() % (GameCreenHeight - 1);
				if (xoay.x == 0)xoay.x++;
				if (xoay.y == 0)xoay.y++;
			} while (gamecreen[xoay.y][xoay.x].kitu != ' ');
		}
		if (demxoay < 60){
				VeMotO(xoay.y, xoay.x, 'X');
				demxoay++;
		}
		else xoay.x = xoay.y = NULL;
	}
}

void main(){
	//khởi tạo game
	int i, j,dem,k,t,u,n,demxoay;
	i = j = dem = k = t = u = n = demxoay = 0;
	bonus tocdo;
	wall tuong;
	gach gach;
	tocdo.n = 0;
	snake snake;
	diem diem,a,b,s;
	toado gate1, gate2, xoay;
	srand(time(NULL));//khởi tạo bộ sinh  số ngẫu nhiên
	khoitao(snake,diem);
	ShowCur(0);
	while (1){
		//hiển thị
		xuathien(snake, a, b, s, j);
		//dieukienbonus(snake, dem, t, u);
		xuathienhieuung(snake, tocdo, dem, t);
		xuathientuong(snake, tuong, u, t);
		xuathiencong(snake, gate1, gate2, n);
		xuathienxoaydau(snake, xoay, demxoay);
		hienthi(snake,diem,gach);
		//chuyển động và điều khiển
		i = dieukhienchuyendong(snake);
		//điều kiện thắng thua
		an(snake, diem,j,dem,t,u,n,demxoay);//cộng điểm
		an(snake, a, j,dem,t,u,n,demxoay);
		an(snake, b, j,dem,t,u,n,demxoay);
		an(snake, s, j,dem,t,u,n,demxoay);
		an(snake, tocdo, k, dem,t);//bonus
		an(snake, tuong, gach,t);
		an(snake, gate1, gate2, n);
		an(snake, xoay, demxoay);
		if (i == 0)break;
		//nhịp game
		Sleep(50-k);
	}
	system("pause");
}