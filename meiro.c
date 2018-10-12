#include <stdio.h>
#define MAZE_row    8  // 行数
#define MAZE_column 8  // 列数

// プレイヤー
typedef struct{
	int row;    // プレイヤー位置(行)
	int column; // プレイヤー位置(例)
}MazePlayer;

// 迷路のブロック
enum MazeKind {path, wall, start, goal}; // ブロックの種類(道,壁,スタート,ゴール)
enum MazeFlag {false, true};            // ブロックが判明してるか

typedef struct{
	enum MazeKind kind;
	enum MazeFlag flag;
} MazeBlock;

// プレイヤーの初期化
int MazePlayerInit(int *playerRow,int *playerColumn,MazeBlock maze[MAZE_row][MAZE_column]){
	int i,j; 
	for(i=0; i<MAZE_row; i++){
		for(j=0; j<MAZE_column; j++){
			if(maze[i][j].kind==start){ //スタート地点ならプレイヤーの位置に設定
				*playerRow = i;
				*playerColumn = j;
				return 0;
			}
		}
	}
	printf("スタートがないです\n");
	return -1;
}


// 迷路表示
void MazeDraw(int playerRow,int playerColumn,MazeBlock maze[MAZE_row][MAZE_column]){
	int i,j;
	for(i=0; i<MAZE_row; i++){
		for(j=0; j<MAZE_column; j++){
			if(i==playerRow && j==playerColumn){ //プレイヤー位置
				printf("Ｐ");
			}else if(maze[i][j].flag==false){ // ブロックがわからないとき
				printf("？");
			}else{
				if(maze[i][j].kind==wall){
					printf("壁"); // 壁
				}else if(maze[i][j].kind==goal){
					printf("Ｇ"); // ゴール
				}else{
					printf("　"); // 道、スタート
				}
			}
		}
		printf("\n");
	}
} 

//方向
enum MazeDirection{up,down,left,right,Invalid};

//プレイヤー移動
void MazePlayerMove(int *playerRow,int *playerColumn,MazeBlock maze[MAZE_row][MAZE_column]){
	char buf[100];
	int direction=-1;
	printf("%d:上\n",up);
	printf("%d:下\n",down);
	printf("%d:左\n",left);
	printf("%d:右\n",right);
	printf("数字を入力してください。:");

	fgets(buf,sizeof(buf),stdin);
	sscanf(buf,"%d",&direction);
	while(direction<0 && direction>(Invalid-1)){
		printf("正しく入力してください:");
		fgets(buf,sizeof(buf),stdin);
		sscanf(buf,"%d",&direction);
	}
//上移動
if(direction==up){
	if(*playerRow-1>=0){  //迷路の範囲外でないように
		maze[*playerRow-1][*playerColumn].flag=true;
		if(maze[*playerRow-1][*playerColumn].kind!=wall){
			*playerRow-=1;
			printf("\n上に移動しました\n");
		}else{
			printf("\n壁です\n");
		}
	}else{
		printf("\n範囲外です\n");
	}
//下移動
}else if(direction==down){
	if(*playerRow+1<MAZE_row){
		maze[*playerRow+1][*playerColumn].flag=true;
		if(maze[*playerRow+1][*playerColumn].kind!=wall){
			*playerRow+=1;
			printf("\n下に移動しました\n");
		}else{
			printf("\n壁です\n");
		}
	}else{
		printf("\n範囲外です\n");
	}
//左移動
}else if(direction==left){
	if(*playerColumn-1>=0){
		maze[*playerRow][*playerColumn-1].flag=true;
		if(maze[*playerRow][*playerColumn-1].kind!=wall){
			*playerColumn-=1;
			printf("\n左に移動しました\n");
		}else{
			printf("\n壁です\n");
		}
	}else{
		printf("\n範囲外です\n");
	}
//右移動
}else if(direction==right){
	if(*playerColumn+1<MAZE_column){
		maze[*playerRow][*playerColumn+1].flag=true;
		if(maze[*playerRow][*playerColumn+1].kind!=wall){
			*playerColumn+=1;
			printf("\n右に移動しました\n");
		}else{
			printf("\n壁です\n");
		}
	}else{
		printf("\n範囲外です\n");
	}
}
}
//ゴール判定
int MazeGoalCheck(int playerRow,int playerColumn,MazeBlock maze[MAZE_row][MAZE_column]){
	if(maze[playerRow][playerColumn].kind==goal){
		printf("ゴール\n");
		return 1;
	}
	return 0;
}

int main(void){
// プレイヤー
MazePlayer player;

// 迷路
MazeBlock maze[MAZE_row][MAZE_column] = {
{ {start,true},{wall,false},{path,false},{path,false},{path,false},{path,false},{path,false},{path,false} },
{ {path,false},{wall,false},{wall,false},{path,false},{wall,false},{path,false},{wall,false},{path,false} },
{ {path,false},{wall,false},{path,false},{path,false},{wall,false},{path,false},{wall,false},{path,false} },
{ {path,false},{path,false},{path,false},{wall,false},{path,false},{path,false},{wall,false},{path,false} },
{ {path,false},{wall,false},{wall,false},{path,false},{wall,false},{path,false},{path,false},{wall,false} },
{ {path,false},{wall,false},{path,false},{path,false},{path,false},{wall,false},{path,false},{path,false} },
{ {path,false},{wall,false},{wall,false},{wall,false},{path,false},{wall,false},{path,false},{wall,false} },
{ {path,false},{path,false},{path,false},{path,false},{path,false},{wall,false},{path,false},{goal,true } },
};

	// プレイヤー初期化
	if(MazePlayerInit(&player.row,&player.column,maze)==-1){
	return 0;
	}

	while(MazeGoalCheck(player.row, player.column, maze)!=1){
		//迷路表示
		MazeDraw(player.row, player.column, maze);
		MazePlayerMove(&player.row, &player.column, maze);
	}

//迷路最終結果表示
MazeDraw(player.row,player.column,maze);
return 0;
}