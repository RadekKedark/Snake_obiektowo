#include <iostream>

#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
#include <cstdlib>
#include <ctime>



using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Ksztalt
{
private:
    int x;
    int y;
    void Draw(char a)
    {
        gotoxy(x,y);
        cout<<a<<endl;
    }
    void Draw_jedzenie()
    {
        gotoxy(x,y);
        cout<<"J"<<endl;
    }

    void Usun()
        {
        gotoxy(x,y);
        cout<<" "<<endl;
        }

    friend class Rysuj;
public:
      Ksztalt (int x=5, int y=5)
    {
        this -> x = x;
        this -> y = y;
    }

    void ustaw_punkt (int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }

    int GetX()
    {
        return x;
    }

    int GetY()
    {
        return y;
    }

        void W_Prawo()
    {
        if(x==48)
        {
            x=1;
        }
        else
        {
            x++;
        }
    }
        void W_Lewo()
    {
        if(x==1)
        {
            x=48;
        }
        else
        {
            x--;
        }
    }
        void Do_Gory()
    {
        if(y==1)
        {
            y=20;
        }
        else
        {
            y--;
        }
    }
        void W_Dol()
    {
        if(y==20)
        {
            y=1;
        }
        else
        {
            y++;
        }
    }
    void kopiuj(Ksztalt*p)
    {
        p->x = x;
        p->y = y;
    }

};

class Rysuj
{
private:
    Ksztalt *k[50];
    Ksztalt jedzenie;
    Ksztalt *ramka[50][50];
    int size=0;
public:
    Rysuj()
    {
        k[0]=new Ksztalt(5,8);
        for(int i=1; i<50;i++)
        {
        k[i] = NULL;
        }

        for(int i=0; i<50;i++)
        {
        ramka[i][0] = new Ksztalt(i,0);
        ramka[i][0] ->Draw('b');
        ramka[i][21] = new Ksztalt(i,21);
        ramka[i][21] ->Draw('b');
        }

        for(int j=0; j<22;j++)
        {
        ramka[0][j] = new Ksztalt(0,j);
        ramka[0][j] ->Draw('b');
        ramka[49][j] = new Ksztalt(49,j);
        ramka[49][j] ->Draw('b');
        }

    }

    void Turn_Right()
    {
        k[0]->W_Prawo();
    }
        void Turn_Left()
    {
        k[0]->W_Lewo();
    }
        void Turn_Up()
    {
        k[0]->Do_Gory();
    }
        void Turn_Down()
    {
        k[0]->W_Dol();
    }

        void dodaj_weza(int x, int y)
    {
        k[size]=new Ksztalt(x,y);
    }

    char kolizja(char &a)
    {
         for(int i=1; i<size; i++)
            {
            if(k[0]->GetX()==k[i]->GetX()&&k[0]->GetY()==k[i]->GetY())
            {
                a='1';
            }
            }
    }

    void kolizja_jedzenie()
    {
        if (jedzenie.GetX()==k[0]->GetX()&&jedzenie.GetY()==k[0]->GetY())
        {
            int a=k[size]->GetX();
            int b=k[size]->GetY();
            size++;
            dodaj_weza(a,b);
            jedzenie.ustaw_punkt(((rand()%47)+1),((rand()%19)+1));
        }
    }

    char Move(char &a)
    {
        kolizja(a);
        kolizja_jedzenie();
        jedzenie.Draw_jedzenie();

                if (size==49)
        {
            a='1';
        }

        for(int i=0; i<size+1;i++)
        {
        k[i] ->Draw('s');
        }

        Sleep(200);

        for(int i=0; i<size+1;i++)
        {
        k[i] ->Usun();
        }

        for(int i=size; i>0; i--)
        {
            k[i-1]->kopiuj(k[i]);
        }

        return a;
    }
     void koniec_gry()
    {

    gotoxy(15,9);
    cout<<"zdobyles: "<<size<<" punktow"<<endl;
    gotoxy(15,10);
    cout<<"koniec gry"<<endl;
    getch();
    }
};

int main()
{
    srand( time( NULL ) );
    char a='2';
    char dir;
    Rysuj rysuj;
    do{
        if(kbhit())
        {
            a=getch();
        }
        if(a=='d'||a=='D')
        {
           if (dir == 2)
           {
               dir=2;
           }
           else
            {
            dir = 1;
            }
        }
        if(a=='a'||a=='A')
        {
           if (dir == 1)
           {
               dir=1;
           }
           else
            {
            dir = 2;
            }
        }
        if(a=='w'||a=='W')
        {
           if (dir == 4)
           {
               dir=4;
           }
           else
            {
            dir = 3;
            }
        }
        if(a=='s'||a=='S')
        {
           if (dir == 3)
           {
               dir=3;
           }
           else
            {
            dir = 4;
            }
        }
        switch(dir)
        {
            case 1:
                rysuj.Turn_Right();
                break;
            case 2:
                rysuj.Turn_Left();
                break;
            case 3:
                rysuj.Turn_Up();
                break;
            case 4:
                rysuj.Turn_Down();
                break;
        }
        rysuj.Move(a);
    }
    while(a != '1');
    rysuj.koniec_gry();
    return 0;
}

