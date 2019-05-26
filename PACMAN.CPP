#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<fstream.h>
#include<process.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>


#define up 72
#define dn 80
#define rt 77
#define lt 75
#define esc 27
#define abc 0


char ghost_dir[]={'u','u','u','u'};
int ghost_status[]={0,0,0,0};
int Ghost_count=0;
int play_again=0;
int life=3;
int out=0;
int level=0;
int nextlevel=0;
int choice=-1;
int xcomp_food=0;
int ycomp_food=0;
int xcomp[200];
int ycomp[200];
int flag[200];
float score=0;
char j='1';

int rando(int u,int l){
   time_t t;
   srand(time(&t));
   return rand()%u+l;
}

void GrInput(int x, int y, char Input[]){
    setcolor(3);
    settextstyle(2, HORIZ_DIR, 15);

    for(int ptr=0;;){
	char c;
	c = getch();
	if(c == 13 && ptr!=0 ){
	    break;
	}

	if(c == 8){
	    if(ptr!=0){
	       ptr --;
	       setfillstyle(1,BLACK);
	       bar(x,y+10,x+300,y+50);
	       Input[ptr] = '\0';
	    }
	}
	else{
	    Input[ptr] = c;
	    Input[ptr+1] = '\0';
	    ptr++;
	}
	outtextxy(x,y,Input);
	outtextxy(x+1,y,Input);
    }
}

class DATA{
   char name[20];
   int clas;
   float hscore;
   int lev;

public:

   static int count;
   friend void GrInput(int x, int y, char Input[])

   float rets(){
      return hscore;
   }

   DATA(){
      name[0]='\0';
      hscore=0;
      lev=0;
      count=0;
   }

   void in(){
      hscore=score;
      char cls[4];
      cleardevice();
      setcolor(9);
      settextstyle(0,0,5);
      outtextxy(65,30,"-------------");
      outtextxy(65,60,"ENTER DETAILS");
      outtextxy(65,90,"-------------");
      setcolor(3);
      settextstyle(2,0,15);
      outtextxy(66,150,"NAME :");
      outtextxy(65,150,"NAME :");
      outtextxy(66,230,"CLASS:");
      outtextxy(65,230,"CLASS:");
      setcolor(4);
      setfillstyle(1,4);
      bar(55,171,45,175);
      GrInput(200,150,name);
      setcolor(0);
      setfillstyle(1,0);
      bar(55,171,45,175);
      setcolor(4);
      setfillstyle(1,4);
      bar(55,258,45,262);
      GrInput(200,230,cls);
      clas = atoi(cls);
   }

   void dis(){
     count++;
     if( count==1)
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
     cout<<"\n\n POS   : "<<count;
     cout<<"\n NAME  : "<<name;
     cout<<"\n CLASS : "<<clas;
     cout<<"\n SCORE : "<<hscore;
   }
};

int DATA :: count;

void hiscore(){
   DATA s1,s2;
   s1.in();
   int flag=0;
   ifstream oldf("pscore.dat",  ios::binary );
   ofstream newf("temp.dat", ios::app | ios::binary );

   while(oldf.read((char*)&s2, sizeof(s2))){
      if( s1.rets() > s2.rets() && flag == 0 ){
	 newf.write( (char*)&s1 , sizeof(DATA) ) ;
	 flag=1;
      }
      newf.write((char*)&s2,sizeof(s2));
   }

   if( flag == 0 )
      newf.write((char*)&s1,sizeof(s1));

   oldf.close();
   newf.close();
   remove("pscore.dat");
   rename("temp.dat","pscore.dat");

   int k=0;
   cleardevice();
   setcolor(1);
   setfillstyle(1,8);
   settextstyle(0,0,6);
   outtextxy(10,30,"HIGH SCORES ");
   ifstream x("pscore.dat",  ios::binary );

   while( !x.eof() && k<3){

      x.read((char*)&s2, sizeof(s2));
      s2.dis();
      k++;
   }
   getch();
}


void food(){
   int i,check=0;
   int h=getmaxx()/2, k=getmaxy()/2;
   int x=getmaxx(), y=getmaxy();

   for( i=0; i<200; i++ )
      flag[i]=0;

   //ROWS

   for(i=0;i<290;i+=27){                       //1st line

      putpixel(25+i,40,15);
      xcomp[xcomp_food]=25+i;
      ycomp[xcomp_food]=40;
      xcomp_food++;
      ycomp_food++;
   }

   for(i=0;i<290;i+=27){
      putpixel(x-25-i,40,15);
      xcomp[xcomp_food]=x-25-i;
      ycomp[ycomp_food]=40;
      xcomp_food++;
      ycomp_food++;
   }

   for(i=0;i<h;i+=27){                         //2nd line
      for(int j=-1;j<2;j++){
	 if( getpixel(25+i+j,72) == 1 )
	    check=1;
      }

      if( check == 0 ){
	 putpixel(25+i,72,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=72;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<300;i+=27){
      for(int j=-1;j<2;j++)
	 if( getpixel(x-25-i-j,72) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(x-25-i,72,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=72;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }


   for(i=0;i<290;i+=27){                       //3rd line
      if(getpixel(25+i,105)==1)
	 continue;

      else{
	 putpixel(25+i,105,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=105;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<290;i+=27){
      if(getpixel(x-25-i,105)==1)
	 continue;

      else{
	 putpixel(x-25-i,105,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=105;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<300;i+=27){                       //4th line
      for(int j=-1;j<2;j++)
	 if( getpixel(25+i+j,142) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(25+i,142,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=142;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<300;i+=27){
      for(int j=-1;j<2;j++)
	 if( getpixel(x-25-i-j,142) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(x-25-i,142,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=142;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<h;i+=27){                         //5th line
      for(int j=-1;j<2;j++)
	 if( getpixel(25+i+j,168) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(25+i,168,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=168;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<h;i+=27){
      for(int j=-1;j<2;j++)
	 if( getpixel(x-25-i-j,168) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(x-25-i,168,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=168;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<220;i+=26){                       //5th line
      if(getpixel(h-104+i,k-51)==1)
	 continue;

      else if( i!=104 ){
	 putpixel(h-104+i,k-51,15);
	 xcomp[xcomp_food]=h-104+i;
	 ycomp[ycomp_food]=k-51;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<220;i+=26){
      if(getpixel(h-104+i,y-k+51)==1)
	 continue;

      else if( i!=104 ){
	 putpixel(h-104+i,y-k+51,15);
	 xcomp[xcomp_food]=h-104+i;
	 ycomp[ycomp_food]=y-k+51;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<200;i+=27){                       //mid line
      if(getpixel(25+i,k)==1)
	 continue;

      else{
	 putpixel(25+i,k,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=k;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<200;i+=27){
      if(getpixel(x-25-i,k)==1)
	 continue;

      else{
	 putpixel(x-25-i,k,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=k;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<h-100;i+=27){                     //6th line
      for(int j=-1;j<2;j++)
	 if( getpixel(25+i+j,y-170) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(25+i,y-170,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=y-170;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<h-100;i+=27){
      for(int j=-1;j<2;j++)
	 if( getpixel(x-25-i-j,y-170) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(x-25-i,y-170,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=y-170;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<h;i+=27){                         //7th line
      for(int j=-1;j<2;j++)
	 if( getpixel(25+i+j,y-143) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(25+i,y-143,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=y-143;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<h;i+=27){
      for(int j=-1;j<2;j++)
	 if( getpixel(x-25-i-j,y-143) == 1 )
	    check=1;

      if( check == 0 ){
	 putpixel(x-25-i,y-143,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=y-143;
	 xcomp_food++;
	 ycomp_food++;
      }
      check=0;
   }

   for(i=0;i<20;i+=35){                        //8(a) line
      if(getpixel(25+i,y-116)==1)
	 continue;

      else{
	 putpixel(25+i,y-116,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=y-116;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<10;i+=35){
      if(getpixel(x-25-i,y-116)==1)
	 continue;

      else{
	 putpixel(x-25-i,y-116,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=y-116;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=81;i<h;i+=27){                        //8(b) line
      if(getpixel(25+i,y-106)==1)
	 continue;

      else{
	 putpixel(25+i,y-106,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=y-106;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=81;i<h;i+=27){
      if(getpixel(x-25-i,y-106)==1)
	 continue;

      else{
	 putpixel(x-25-i,y-106,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=y-106;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<h-200;i+=27){                     //9th line
      if(getpixel(25+i,y-79)==1)
	 continue;

      else{
	 putpixel(25+i,y-79,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=y-79;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<h-200;i+=27){
      if(getpixel(x-25-i,y-79)==1)
	 continue;

      else{
	 putpixel(x-25-i,y-79,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=y-79;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<h-27;i+=27){                      //last line
      if(getpixel(25+i,y-41)==1)
	 continue;

      else{
	 putpixel(25+i,y-41,15);
	 xcomp[xcomp_food]=25+i;
	 ycomp[ycomp_food]=y-41;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<h-27;i+=27){
      if(getpixel(x-25-i,y-41)==1)
	 continue;

      else{
	 putpixel(x-25-i,y-41,15);
	 xcomp[xcomp_food]=x-25-i;
	 ycomp[ycomp_food]=y-41;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

//Special cases.

   for(i=0;i<170;i+=156){
      if(getpixel(h-77+i,y-83)==1)
	 continue;

      else{
	 putpixel(h-77+i,y-83,15);
	 xcomp[xcomp_food]=h-77+i;
	 ycomp[ycomp_food]=y-83;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<170;i+=156){
      if(getpixel(h-77+i,y-62)==1)
	 continue;

      else{
	 putpixel(h-77+i,y-62,15);
	 xcomp[xcomp_food]=h-77+i;
	 ycomp[ycomp_food]=y-62;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<211;i+=210){
      if(getpixel(h-105+i,k-24)==1)
	 continue;

      else{
	 putpixel(h-105+i,k-24,15);
	 xcomp[xcomp_food]=h-105+i;
	 ycomp[ycomp_food]=k-24;
	 xcomp_food++;
	 ycomp_food++;

	 putpixel(h-105+i,k+24,15);
	 xcomp[xcomp_food]=h-105+i;
	 ycomp[ycomp_food]=k+24;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

   for(i=0;i<375;i+=372){
      if(getpixel(h-186+i,k-34)==1)
	 continue;

      else{
	 putpixel(h-186+i,k-34,15);
	 xcomp[xcomp_food]=h-186+i;
	 ycomp[ycomp_food]=k-34;
	 xcomp_food++;
	 ycomp_food++;

	 putpixel(h-186+i,k+34,15);
	 xcomp[xcomp_food]=h-186+i;
	 ycomp[ycomp_food]=k+34;
	 xcomp_food++;
	 ycomp_food++;
      }
   }

//Fruits.

   setcolor(GREEN);
   setfillstyle(1,GREEN);
   bar(h-1,y-37,h+1,y-48);
   bar(h-1,109,h+1,98);

   setcolor(RED);
   setfillstyle(1,RED);
   sector(h,y-37,0,360,5,5);
   sector(h,109,0,360,5,5);
}

void structure(int style){
   setcolor(BLUE);
   setfillstyle(style,BLUE);
   int h=getmaxx()/2, k=getmaxy()/2;
   int x=getmaxx(), y=getmaxy();
   bar(0,15,10,k-50);                          // left column
   bar(0,k+50,10,y-15);

   bar( 0, k-53,h-200,k-47);                   // up
   bar(h-200,k-50,h-205,k-20);
   bar(h-200,k-23,0,k-17);

   bar( 0, k+53,h-200,k+47);                   // down
   bar(h-200,k+50,h-205,k+20);
   bar(h-200,k+20,0,k+13);

   bar(x-10,15,x,k-50);                        // right column
   bar(x-10,k+50,x,y-15);

   bar(x, k-53,x-h+200,k-47);                  // up
   bar(x-h+200,k-50,x-h+205,k-20);
   bar(x-h+200,k-23,x,k-17);

   bar( x, k+53,x-h+200,k+47);                 // down
   bar(x-h+200,k+50,x-h+205,k+20);
   bar(x-h+200,k+19,x,k+13);

   bar(0,15,x,25);                             // top and bottom
   bar(0,y-25,x,y-15);

   bar(h-280,k-184,h-200,k-150);               // left side
   bar(h-280,k-120,h-200,k-83);
   bar(h-170,k-184,h-35,k-150);

   bar(x-h+280,k-184,x-h+200,k-150);           // right side
   bar(x-h+280,k-120,x-h+200,k-83);
   bar(x-h+170,k-184,x-h+35,k-150);

   bar(h-5,15,h+6,k-150);                      // top

   bar(h-90 ,k-120,h+90,k-110);		       // middle; top
   bar(h-5,k-120,h+6,k-68);
//****
   bar(h-170 , k-120 ,h-120 ,k-83);            // middle; top-left
   bar(h-170 , k-53 ,h-120 ,k-17);             // middle; top-left
   bar(h-90 , k-80  ,h-35 ,k-67);

   bar(x-h+170 , k-120 ,x-h+120 ,k-83);        // middle; top-right
   bar(x-h+170 , k-53 ,x-h+120 ,k-17);         // middle; top-right
   bar(x-h+90 , k-80  ,x-h+35 ,k-67);

   bar(h-170 ,y-k+120 ,h-120 ,y-k+83);         // middle; top-left
   bar(h-170 , y-k+53 ,h-120 ,y-k+17);         // middle; top-left
   bar(h-90 ,y-k+80  ,h-35 ,y-k+67);

   bar(x-h+170 ,y-k+120 ,x-h+120 ,y-k+83);     // middle; top-right
   bar(x-h+170 ,y-k+53 ,x-h+120 ,y-k+17);      // middle; top-right
   bar(x-h+90 , y-k+80  ,x-h+35 ,y-k+67);

   bar(h-90,y-k+120,h+90,y-k+110);	       // middle; bottom
   bar(h-5,y-k+120,h+6,y-k+67);

   //bottom half

   bar(h-280,y-55,h-90,y-65);                  // lower-left
   bar(h-170,y-55,230,y-90);

   bar(40,y-95, 118 ,k+83);                    // bottom left corner

   bar(x-40,y-55,x-h+90,y-65);                 // lower-right
   bar(x-150,y-55,x-230,y-90);

   bar(x-40,y-95,x-118,k+83);                  // bottom right corner

   bar(h-60,y-90,h+60,y-55);                   // middle

   bar(h-90,k-37,h+90,k+37);                   // ghost strt pt

   setfillstyle(2,BLACK);
   setcolor(BLACK);
   bar(h-73,k-23,h+73,k+23);                   // ghost strt pt
   bar(h-20,k-23,h+20,k-39);

   setcolor(15);
   settextstyle(2,0,5);
   outtextxy(0,0,"LIVES :");

   setcolor(YELLOW);
   if( life == 3 ){
      pieslice(100,8,45,315,6);
      pieslice(80,8,45,315,6);
      pieslice(60,8,45,315,6);
   }

   if( life == 2 ){
      pieslice(80,8,45,315,6);
      pieslice(60,8,45,315,6);
   }

   if( life == 1 ){
      pieslice(60,8,45,315,6);
   }

   setcolor(15);
   settextstyle(2,0,5);
   outtextxy(280,0,"LEVEL :");
   char *scr;
   scr=&j;
   outtextxy(340,0,scr);
}

void developers(int x){
   setcolor(x);
   setfillstyle(1,x);

   cleardevice();
   settextstyle(0,0,5);
   outtextxy(80,130,"DEVELOPED BY");
   outtextxy(160,180,"HARIVIND");
   delay(2000);

   cleardevice();
   settextstyle(0,0,5);
   outtextxy(125,140,"THE H-TEAM");
   outtextxy(125,190,"PRODUCTION");
   outtextxy(165,240,"PRESENTS");
   delay(2000);

}

void intro(){
   developers(8);
   cleardevice();

   int col;
   int r1=rando(3,1);

   if(r1==1)
      col=6;

   else
      if(r1==2)
	 col=8;

   else
      col=14;

   setcolor(col);
   setfillstyle(1,col);
   settextstyle(0,0,10);
   outtextxy(80,90,"PACMAN");
   delay(100);

   setcolor(WHITE);
   setfillstyle(1,WHITE);

   for( int i=50; i<getmaxx()-50; i+=50)
      fillellipse( 50+i, 300, 3, 3 );

   for( i=0; i<getmaxx()+5; i++){
      setcolor(YELLOW);                        //pacman
      setfillstyle(1,YELLOW);
      sector(50+i,300,30,330,50,50);

      setcolor(BLACK);                         //eye
      setfillstyle(1,BLACK);
      fillellipse(55+i,270,5,5);

      circle (50+i,300,50);
   }
   delay(500);
}


void clearmove(int x,int y){
   setcolor(BLACK);
   setfillstyle(1,BLACK);
   circle(x,y,12);
}

void score_inc(){
   for(int i=0;i<192;i++){
      int colx=getpixel(xcomp[i],ycomp[i]);

      if((flag[i]!=1) && (colx==YELLOW ) ){
	 flag[i]=1;
	 score+=50;
      }

      if( (colx!=WHITE) && (flag[i]==0) ){
	 putpixel(xcomp[i],ycomp[i],15);
      }
   }

   for( i=0; i<190; i++){
      if( flag[i] == 1)
	 level++;
   }

   if( level > 184 )
      nextlevel=1;

   else
      level=0;
}

void move(int x,int y, int color){             //MOVING FN-GHOST
   setcolor(color);
   setfillstyle(1,color);
   fillellipse(x,y,12,12);
   clearmove(x,y);
}

int stop=0;

void ghost(int &x,int &y,int w,int c=0){
   int y_y=getmaxy()/2, x_x=getmaxx()/2;
   if(  ghost_status[w] == 0 ){
      ghost_status[w]=1;
   }

   if(stop==0){
      setcolor(1);
      setfillstyle(1,1);
      line(x_x-5,y_y-36,x_x+5,y_y-36);
   }

   if( getpixel(x_x,y_y-25)!=0 ){
      setcolor(0);
      setfillstyle(1,0);
      line(x_x-5,y_y-36,x_x+5,y_y-36);
   }

   int r=rando(2,1) ;
   int i=0,j=0,k=0,l=0;
   float m,v,pix;


   for( m=y-12; m<=y+12; m+=1.5){              //right
      for(  v=x+12; v<x+18; v+=1){
	 pix=getpixel(v,m);

	 if( pix == 1 ){
	    i=1;
	    break;
	 }

	 else
	    i=pix;
      }

      if( i == 1 || i == 14 )
	 break;
   }

   for( m=y-12; m<=y+12; m+=1.5){              //left
      for( v=x-12; v>x-18; v-=1){
	 pix=getpixel(v,m);

	 if( pix == 1 ){
	    k=1;
	    break;
	 }

	 else
	    k=pix;
      }
	 if( k == 1 || k == 14 )
	    break;
   }

   for( m=x-12; m<=x+12; m+=1.5){              //up
      for( v=y-12; v>y-18; v-=1){
	 pix=getpixel(m,v);

	 if( pix == 1 ){
	    j=1;
	    break;
	 }

	 else
	    j=pix;
      }

      if( j == 1 || j == 14 )
	 break;
   }

   for( m=x-12; m<=x+12; m+=1.5){              //down
      for(  v=y+12; v<y+18; v+=1){
	 pix=getpixel(m,v);

	 if( pix == 1 ){
	    l=1;
	    break;
	 }

	 else
	    l=pix;
      }
      if( l == 1 || l == 14 )
	 break;
   }

//conditions for out

   if((i==YELLOW)||(j==YELLOW)||(k==YELLOW)||(l==YELLOW)){
      out=1;
   }


   if( i==1 || j==1 || k==1 || l==1 ){
      //condition for two
      if((i==1)&&(j==1)&&(k!=1)&&(l!=1)){      //left or down
	 if(ghost_dir[w]=='u'){                //left
	    ghost_dir[w]='l';
	    move (--x,y,c);
	 }

	 if(ghost_dir[w]=='r'){                //down
	    ghost_dir[w]='d';
	    move (x,++y,c);
	 }
      }

      else
      if((i!=1)&&(j==1)&&(k==1)&&(l!=1)){      //down or right
	 if(ghost_dir[w]=='u'){                //right
	    ghost_dir[w]='r';
	    move (++x,y,c);
	 }

	 if(ghost_dir[w]=='l'){                //down
	    ghost_dir[w]='d';
	    move (x,++y,c);
	 }
      }

      else
      if((i!=1)&&(j!=1)&&(k==1)&&(l==1)){      // up or right
	 if(ghost_dir[w]=='d'){                //right
	    ghost_dir[w]='r';
	    move (++x,y,c);
	 }

	 if(ghost_dir[w]=='l'){                //up
	    ghost_dir[w]='u';
	    move (x,--y,c);
	 }
      }

      else
      if((i==1)&&(j!=1)&&(k!=1)&&(l==1)){      // top or left
	 if(ghost_dir[w]=='d'){                //left
	    ghost_dir[w]='l';
	    move (--x,y,c);
	 }

	 if(ghost_dir[w]=='r'){                //up
	    ghost_dir[w]='u';
	    move (x,--y,c);
	 }
      }

      //conditions for three

      if((i!=1)&&(j!=1)&&(k!=1)&&(l==1)){      //-|- no down
	 if(ghost_dir[w]=='r'){
	    if( r==1 ){
	       ghost_dir[w]='r';
	       move(++x,y,c);                  //right
	    }

	    if(r==2){
	       ghost_dir[w]='u';
	       move(x,--y,c);                  //up
	    }
	 }

	 if(ghost_dir[w]=='l'){
	    if( r==1 ){
	       ghost_dir[w]='l';
	       move(--x,y,c);                  //left
	    }

	    if(r==2){
	       ghost_dir[w]='u';
	       move(x,--y,c);                  //up
	    }
	 }

	 if(ghost_dir[w]=='d'){
	    if( r==1 ){
	       ghost_dir[w]='r';
	       move(++x,y,c);                  //right
	    }

	    if(r==2){
	       ghost_dir[w]='l';
	       move(--x,y,c);                  //up
	    }
	 }
      }

      else
      if((i!=1)&&(j==1)&&(k!=1)&&(l!=1)){      //-|- no up
	 if(ghost_dir[w]=='r'){                //case1
	    if( r==1 ){
	       ghost_dir[w]='r';
	       move(++x,y,c);                  //right
	    }

	    if(r==2){
	       ghost_dir[w]='d';
	       move(x,++y,c);                  //down
	    }
	 }

	 if(ghost_dir[w]=='l'){                //case2
	    if( r==1 ){
	       ghost_dir[w]='l';
	       move(--x,y,c);                  //left
	    }

	    if(r==2){
	       ghost_dir[w]='d';
	       move(x,++y,c);                  //down
	    }
	 }

	 if(ghost_dir[w]=='u'){                //case3
	    if( r==1 ){
	       ghost_dir[w]='r';
	       move(++x,y,c);                  //right
	    }

	    if(r==2){
	       ghost_dir[w]='l';
	       move(--x,y,c);                  //left
	    }
	 }
      }

      else
      if((i!=1)&&(j!=1)&&(k==1)&&(l!=1)){      //-|- no left
	 if(ghost_dir[w]=='l'){                //case1
	    if( r==1 ){
	       ghost_dir[w]='u';
	       move(x,--y,c);                  //up
	    }

	    if(r==2){
	       ghost_dir[w]='d';
	       move(x,++y,c);                  //down
	    }
	 }

	 if(ghost_dir[w]=='u'){                //case2
	    if( r==1 ){
	       ghost_dir[w]='r';
	       move(++x,y,c);                  //right
	    }

	    if(r==2){
	       ghost_dir[w]='u';
	       move(x,--y,c);                  //up
	    }
	 }

	 if(ghost_dir[w]=='d'){                //case3
	    if( r==1 ){
	       ghost_dir[w]='r';
	       move(++x,y,c);                  //right
	    }

	    if(r==2){
	       ghost_dir[w]='d';
	       move(x,++y,c);                  //down
	    }
	 }
      }

      else
      if((i==1)&&(j!=1)&&(k!=1)&&(l!=1)){      //-|- no right
	 if(ghost_dir[w]=='r'){                //case1
	    if( r==1 ){
	       ghost_dir[w]='u';
	       move(x,--y,c);                  //up
	    }

	    if(r==2){
	       ghost_dir[w]='d';
	       move(x,++y,c);                  //down
	    }
	 }

	 if(ghost_dir[w]=='u'){                //case2
	    if( r==1 ){
	       ghost_dir[w]='l';
	       move(--x,y,c);                  //left
	    }

	    if(r==2){
	       ghost_dir[w]='u';
	       move(x,--y,c);                  //up
	    }
	 }

	 if(ghost_dir[w]=='d'){                //case3
	    if( r==1 ){
	       ghost_dir[w]='l';
	       move(--x,y,c);                  //left
	    }

	    if(r==2){
	       ghost_dir[w]='d';
	       move(x,++y,c);                  //down
	    }
	 }
      }
   }

   if(ghost_dir[w]=='u')      //if moving up, continue moving up
      move(x,--y,c);

   else
   if(ghost_dir[w]=='d')      //if moving down ,continue moving down
      move(x,++y,c);

   else
   if(ghost_dir[w]=='r')      //if moving right, continue moving right
      move(++x,y,c);

   else
   if(ghost_dir[w]=='l')      //if moving left ,continue moving left
      move(--x,y,c);

   if( x == getmaxx()+12 )
      x=0;

   if( x == -12 )
      x=getmaxx();
}

void PacRight(int x, int y){
    setcolor(YELLOW);
    setfillstyle(1,YELLOW);
    pieslice(x,y,45,315,10);
}

void PacLeft(int x, int y){
    setcolor(YELLOW);
    setfillstyle(1,YELLOW);
    pieslice(x,y,0,135,10);
    pieslice(x,y,225,360,10);
}

void PacUp(int x, int y){
    setcolor(YELLOW);
    setfillstyle(1,YELLOW);
    pieslice(x,y,0,45,10);
    pieslice(x,y,135,360,10);
}

void PacDown(int x, int y){
    setcolor(YELLOW);
    setfillstyle(1,YELLOW);
    pieslice(x,y,0,225,10);
    pieslice(x,y,315,360,10);
}

void pacman(){
   int a=up;
   float Pacx=getmaxx()/2;
   float Pacy=getmaxy()/2;
   float tx,ty;
   Pacy=Pacy+136;

   float temp_x=Pacx;
   float temp_y=Pacy;

   int Ghost_x1= getmaxx()/2;
   int Ghost_y1=getmaxy()/2;

   int Ghost_x2=getmaxx()/2;
   int Ghost_y2=getmaxy()/2;

   int Ghost_x3=getmaxx()/2;
   int Ghost_y3=getmaxy()/2;

   int Ghost_x4=getmaxx()/2;
   int Ghost_y4=getmaxy()/2;
   int tempo = 0, tempg = 0;

   for(;;){
      ghost(Ghost_x1,Ghost_y1,0,3);

      if(Ghost_count<1553)
	 Ghost_count++;

      if(Ghost_count>500)
	 ghost(Ghost_x2,Ghost_y2,1,5);

      if(Ghost_count<500)
	 move(Ghost_x2,Ghost_y2,5);

      if(Ghost_count>900)
	 ghost(Ghost_x3,Ghost_y3,2,4);

      if(Ghost_count<900 && Ghost_count>500)
	 move(Ghost_x3,Ghost_y3,4);

      if(Ghost_count>1300)
	 ghost(Ghost_x4,Ghost_y4,3,6);

      if(Ghost_count<1300 && Ghost_count>900)
	 move(Ghost_x4,Ghost_y4,6);

      if(Ghost_count>1550 && stop==0){
	 stop=1;
	 int h=getmaxx()/2, k=getmaxy()/2, y=getmaxy();
	 setcolor(0);
	 setfillstyle(1,0);
	 bar(h-90,k-37,h+90,k+37);
	 bar(h-5,y-k+120,h+6,y-k+120);
	 bar(h-5,k-120,h+6,k-68);

	 setcolor(1);
	 setfillstyle(1,1);
	 bar(h-90,k-37,h-35,k+37);

	 bar(h+35,k-37,h+90,k+37);
	 bar(h-90,k-7 ,h+90,k+7 );

	 bar(h-5,y-k+120,h+6,y-k+38);
	 bar(h-5,k-120,h+6,k-38);
      }

      if(out==1){
	 setcolor(BLACK);
	 setfillstyle(1,BLACK);
	 sector(temp_x,temp_y,0,360,11,11);
	 sector(temp_x+1,temp_y+1,0,360,11,11);
	 sector(temp_x,temp_y+1,0,360,11,11);
	 sector(temp_x+1,temp_y,0,360,11,11);
	 sector(temp_x,temp_y,0,360,11,11);
	 sector(temp_x-1,temp_y-1,0,360,11,11);
	 sector(temp_x,temp_y-1,0,360,11,11);
	 sector(temp_x-1,temp_y,0,360,11,11);

	 a=up;
	 Pacx=getmaxx()/2;
	 Pacy=getmaxy()/2+136;
	 out=0;
	 life--;

	 if(life==2){
	    setcolor(BLACK);
	    setfillstyle(1,BLACK);
	    pieslice(100,8,45,315,6);
	 }

	 if(life==1){
	    setcolor(BLACK);
	    setfillstyle(1,BLACK);
	    pieslice(80,8,45,315,6);
	 }

	 if(life==0){
	    setcolor(BLACK);
	    setfillstyle(1,BLACK);
	    pieslice(60,8,45,315,6);

	    getch();
	    cleardevice();

	    life=-2;
	    break;
	 }
      }

      if(a==up){
	 PacUp(Pacx,Pacy);
	 tx=Pacx;
	 ty=Pacy;
	 int x=getpixel(Pacx,Pacy-16);
	 int y=getpixel(Pacx+11,Pacy-16);
	 int z=getpixel(Pacx-11,Pacy-16);

	 if( (x!=1)&&(y!=1)&&(z!=1) )
	    Pacy-=2;
      }

      else
      if(a==dn){
	 PacDown(Pacx,Pacy);
	 tx=Pacx;
	 ty=Pacy;
	 int x=getpixel(Pacx-11,Pacy+16);
	 int y=getpixel(Pacx+11,Pacy+16);
	 int z=getpixel(Pacx,Pacy+16);

	 if((x!=1)&&(y!=1)&&(z!=1))
	    Pacy+=2;
	}

      else
      if(a==rt){
	 PacRight(Pacx,Pacy);
	 tx=Pacx;
	 ty=Pacy;
	 int x=getpixel(Pacx+16,Pacy-11);
	 int y=getpixel(Pacx+16,Pacy+11);
	 int z=getpixel(Pacx+16,Pacy);

	 if((x!=1)&&(y!=1)&&(z!=1))
	    Pacx+=2;
      }

      else
      if(a==lt){
	 PacLeft(Pacx,Pacy);
	 tx=Pacx;
	 ty=Pacy;
	 int x=getpixel(Pacx-16,Pacy);
	 int y=getpixel(Pacx-16,Pacy+11);
	 int z=getpixel(Pacx-16,Pacy-11);

	 if((x!=1)&&(y!=1)&&(z!=1))
	    Pacx-=2;
	}

      int ul=getpixel(Pacx-13,Pacy-18);
      int ur=getpixel(Pacx+13,Pacy-18);
      int dl=getpixel(Pacx-13,Pacy+18);
      int dr=getpixel(Pacx+13,Pacy+18);

      int lu=getpixel(Pacx-18,Pacy-13);
      int ru=getpixel(Pacx+18,Pacy-13);
      int ld=getpixel(Pacx-18,Pacy+13);
      int rd=getpixel(Pacx+18,Pacy+13);

      int u=getpixel(Pacx,Pacy-17);
      int r=getpixel(Pacx+17,Pacy);
      int l=getpixel(Pacx-17,Pacy);
      int d=getpixel(Pacx,Pacy+17);

	if(u == BLACK && ur==BLACK && ul == BLACK && tempo == up){
	      a = up;
	      tempg = 1;
	      tempo = 0;
	  }
	  else if(l == BLACK && ld==BLACK && lu == BLACK&& tempo == lt){
	      a = lt;
	      tempg = 1;
	      tempo = -0;
	  }
	  else if(d == BLACK && dr==BLACK && dl == BLACK&& tempo == dn){
	      a = dn;
	      tempg = 1;
	      tempo = -0;
	  }
	  else if(r == BLACK && rd==BLACK && ru == BLACK&& tempo == rt){
	      a = rt;
	      tempg = 1;
	      tempo = 0;
	  }

      int stor = a;
      if(kbhit()){

	  if(tempg != 1)
	      a = getch();
	  if(a == 0 && tempg != 1)
	      a = getch();

	  if(a == esc){
	      exit(0);
	  }

	  if(a == up)
	      if(stor != up)
		  if(u != BLACK){
		      tempo = a;
		      a = stor;
		  }
	  if(a == lt)
	      if(stor != lt)
		  if(l != BLACK){
		      tempo = a;
		      a = stor;
		  }
	  if(a == rt)
	      if(stor != rt)
		  if(r != BLACK){
		      tempo = a;
		      a = stor;
		  }
	  if(a == dn)
	      if(stor != dn)
		  if(d != BLACK){
		      tempo = a;
		      a = stor;
		  }
      }
	   tempg = 0;

      gotoxy(581,1);
      cout<<"SCORE :"<<score;

      setcolor(BLACK);
      setfillstyle(1,BLACK);
      circle(tx+1,ty+1,11);
      circle(tx+1,ty,11);
      circle(tx,ty+1,11);
      circle(tx,ty,11);

      if(Pacx == getmaxx()+12)
	 Pacx=0;

      else
      if( Pacx == -12)
	 Pacx=getmaxx();

      score_inc();

      if(nextlevel==1)
	 break;
   }
}

void main(){
   clrscr();
   int gm,gd=DETECT;
   initgraph(&gd,&gm,"c://turboc3//bgi");
   char play='0';
   intro();
   do{
      startagain:
      cleardevice();
      setcolor(1);
      settextstyle(0,0,10);
      outtextxy(80,90,"PACMAN");
      setcolor(8);
      settextstyle(0,0,5);
      outtextxy(190,220,"1.PLAY");
      outtextxy(190,280,"2.HELP");
      outtextxy(190,340,"3.EXIT");
      choice=getch();

      if( choice == '3')
	 exit(0);

      else
      if( choice == '2' ){
	 char help[100];
	 cleardevice();
	 setcolor(1);
	 settextstyle(0,0,10);
	 outtextxy(80,60,"PACMAN");
	 ifstream fin( "PACHELP.txt", ios::in);
	 int k=0;
	 setcolor(2);
	 settextstyle(2,0,5);
	 while ( !fin.eof() ){
	    fin.getline( help, 90 , '\n');
	    outtextxy(5,180+(20*k),help);
	    k++;
	 }
	 getch();
	 goto startagain;
      }

      else if ( choice == '1' ){
	 cleardevice();
	 if( j > '1' & play_again == 0 ){
	    setcolor(6);
	    settextstyle(0,0,100);
	    outtextxy(160,200,"NEXT LEVEL!");
	    delay(1000);
	 }

	 if( play_again != 0 ){
	    play_again=0;
	    score =0;
	    stop=0;
	    life =3;
	    Ghost_count=0;
	    j='1';
	 }

	 stop=0;
	 nextlevel=0;
	 level=0;
	 Ghost_count=0;

	 for(int u=0; u<4 ; u++){
	    ghost_dir[u]='u';
	    ghost_status[u]=0;
	 }

	 xcomp_food=ycomp_food=0;

	 for(int i=0;i<192;i++)
	    flag[i]=0;

	 cleardevice();
	 structure(1);
	 food();
	 pacman();

	 settextstyle(3,0,2);

	 if(life <= 0){
	    char *str;
	    int dec, sign;
	    str = fcvt(score, 0, &dec, &sign);

	    cleardevice();
	    setcolor(1);
	    settextstyle(0,0,8);
	    outtextxy(getmaxx()/4+45,80,"GAME");
	    outtextxy(getmaxx()/4+30,160,"OVER!");
	    setcolor(5);
	    settextstyle(0,0,7);
	    outtextxy(30,260,"SCORE:");
	    outtextxy(350,260, str);
	    getch();
	    getch();
	    cleardevice();
	    hiscore();
	    cleardevice();
	    settextstyle(0,0,8);
	    setcolor(6);
	    outtextxy(getmaxx()/4-25,100," PLAY ");
	    outtextxy(getmaxx()/4-76,175," AGAIN?");
	    outtextxy(getmaxx()/4-60,250," [y/n]");

	    play=getch();
	    if(play == 89 || play == 121 )
	       play_again=1;
	 }
	 j++;
      }
      else
	 goto startagain;
   }

   while(  nextlevel == 1 || play == 89 || play == 121 );
   cleardevice();
}