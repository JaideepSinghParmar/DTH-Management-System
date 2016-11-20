#include<fstream>
#include<windows.h>
#include<stdio.h>
#include<iomanip>
#include<conio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
using namespace std;
class channel;
class pack;
class user;
class person;
class subscriber;
class distributer;
class dealer;
class date;
class address;
class recharge;
class on_demand;
class channel_on_demand;
class movies_on_demand;
class box;
class inter;



void gotoxy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//box class - contains row() & column() methods
class box{
int x_start;
int x_end;
int y_start;
int y_end;
public:
    //friend class interface;
    void draw_row(int x_start,int y_start,int len)
    {

        gotoxy(x_start,y_start);
        for(int i=0;i<len;i++)
        cout<<"_";
    }
    void draw_colomn(int x_start,int y_start,int len)
    {

        for(int i=0;i<len;i++)
           {
               gotoxy(x_start,y_start+i);
               cout<<(char)179;


           }
    }
    void draw_box(int x_start,int y_start,int w,int h)
    {
        gotoxy(x_start,y_start);
        cout<<(char)218;
        for(int i=0;i<w;i++)
        {

            cout<<(char)196;

        }
        cout<<(char)191;

        for(int i=1;i<h;i++)
           {
               gotoxy(x_start,y_start+i);
               cout<<(char)179;
               gotoxy(x_start+w+1,y_start+i);
               cout<<(char)179;


           }
        gotoxy(x_start,y_start+h);
        cout<<(char)192;
        for(int i=0;i<w;i++)
        {

            cout<<(char)196;

        }
        cout<<(char)217;



    }
};
// Creating Interface using box class
class inter{
    box ob;
public:
    void header()
    {
        ob.draw_row(0,4,170);
        gotoxy(70,2);
        cout<<"DTH SUBSCRIBER SYSTEM";
    }
    void draw_menu_bar()
     {
         gotoxy(30,4);
         ob.draw_colomn(30,5,50);
         gotoxy(10,6);
         cout<<"OPTIONS";
         ob.draw_row(0,7,30);
     }
    };
char catagory[12][25]={
                            "Hindi Movies",
                            "English Movies",
                            "Hindi News",
                            "English News",
                            "Sports",
                            "Music",
                            "Fasshion/LifeStyle",
                            "Kids",
                            "Bussiness News",
                            "Devotional",
                            "Education",
                            "Other Regional Language"
                            };
class channel{
short ch_code;
static int total;
char name[30];
int cat;
public:
    channel()
    {
    }
    void list_channels();
    void add_channels();
    int unique_code();
    //void del_channels();
    void show_1_channel();
    void particular_channel();
    void options();
    friend class pack;

};
int channel::total=0;
int channel::unique_code()
{

    fstream fp;
    fp.open("channel.txt",ios::in);
    int max=100;
    while(1)
    {
        fp.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(fp.eof())
            break;
        if(this->ch_code>max)
            max=this->ch_code;
    }
    fp.close();
    return max+1;


}
void channel::options()
{
    int ch;
    int code;
    char choice;
        inter i;
        box b;

    do{
            system("cls");
            i.header();
            i.draw_menu_bar();
            gotoxy(3,8);

    cout<<endl<<"1. Add channels";
    gotoxy(3,10);
    cout<<endl<<"2. List channels";
    gotoxy(3,12);
    //cout<<endl<<"Press 3 to delete channel";
    cout<<endl<<"3.Delete a channel";

    gotoxy(3,14);
    cout<<endl<<"4.Search a channel";
     gotoxy(3,16);
    cout<<endl<<"Your Choice:";
    cin>>ch;
    switch(ch)
    {
    case 1:
        add_channels();
        break;
    case 2:
        list_channels();
        break;
    case 3:
        //del_channels();
        break;
    case 4:
        particular_channel();
        break;
    default:
        cout<<"Chutiya hai kya??";
        break;
    }

    fflush(stdout);

    cout<<"\nAnything Else?<y/n>";
    cin>>choice;
    if(choice=='n'||choice=='N')
        break;
    }while(1);
}

void channel::particular_channel()
{
    int code;
    fstream fp;
    char ch;
    box b;

    fp.open("channel.txt",ios::in);
    bool exist;
    do{
            //system("cls");
        gotoxy(50,7);
    cout<<endl<<"Enter Channel code:";
    cin>>code;
    while(1)
    {
        fp.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(fp.eof())
            break;
        if(this->ch_code==code)
                {
                        cout.setf(ios::left);
                        gotoxy(50,9);
                        cout<<setw(12)<<"Code No."<<setw(25)<<"Name"<<setw(25)<<"Catagory"<<endl;
                        //gotoxy(50,10);
                        b.draw_row(50,10,50);
                    return ;
                }
    }
    if(this->ch_code!=code)
        cout<<"channel does not exist..";
        cout<<endl<<"Want to search another channel?<y/n>";
        cin>>ch;
        if(ch=='n'||ch=='N')
            break;

    }while(1);
}
void channel::add_channels()
{
    fstream fp;
    int n;
    int c;
    int i=0;
    int cat=0;
    char choice;
    channel ch;
fp.open("channel.txt",ios::app|ios::out);
    //do{}
            gotoxy(50,7);
    cout<<"Enter Channel name:";
    fflush(stdin);
    gets(ch.name);
    gotoxy(50,9);
    cout<<"SELECT CATAGORY:"<<endl;
    gotoxy(50,10);
    cout<<"________________________"<<endl;
    gotoxy(50,11);
    cout<<"CODE\tCATAGORY"<<endl;
    gotoxy(50,12);
    cout<<"________________________"<<endl;
    short k=13;
    for(i=0;i<12;i++)
    {

        gotoxy(50,k);
            if(i<9)
                cout<<"0"<<i<<"\t"<<catagory[i]<<endl;
            else
                cout<<i<<"\t"<<catagory[i]<<endl;
                k++;
    }
fflush(stdin);
gotoxy(50,k+1);
    cout<<"ENTER THE CATAGORY CODE:";
    cin>>cat;
    ch.cat=cat;
   ch.ch_code=unique_code();
   //cout<<"mhdf";
fp.write(reinterpret_cast<char*>(&ch),sizeof(ch));

     fp.close();
     fp.clear();

}
void channel::list_channels()
{
    fstream fp;
    box b;
   // remove("channel.txt");
    fp.open("channel.txt",ios::in);

    if(!fp.is_open())
        {
            cout<<"can not open file";
            return ;
        }

    channel c;
    int rec_len=sizeof(c);
    int cn=0;
    //cout<<rec_len;
    //gotoxy(30,7);
    //cout<<"_______________________________________________________________"<<endl;
    b.draw_row(31,7,90);
    cout.setf(ios::left);

    gotoxy(45,9);
    cout<<setw(12)<<"Code No."<<setw(25)<<"Name"<<setw(25)<<"Catagory"<<endl;
    gotoxy(45,12);
    b.draw_row(45,11,60);

    //cout<<"_______________________________________________________________"<<endl;
    short k=13;
   // b.draw_colomn(93,5,2);
    //gotoxy(93,8);
    //cout<<(char)180

    while(1)
    {

        fp.read(reinterpret_cast<char*>(&c),sizeof(c));
         if(fp.eof())
            break;
        //cn++;
        //cout<<cn;

gotoxy(45,k);
k++;
        cout.setf(ios::left);
    cout<<setw(12);
    cout<<c.ch_code;
    cout<<setw(25)<<c.name<<setw(25)<<catagory[c.cat]<<endl;
}
   b.draw_colomn(120,5,50);
    fp.close();
    fp.clear();
}
void channel::show_1_channel()
{
    cout.setf(ios::left);
    cout<<setw(12);
    cout<<ch_code;
    cout<<setw(25)<<name<<setw(25)<<catagory[this->cat]<<endl;

}

class pack{
int pack_code;
char name[30];
float price;
float st;
short channels[300];
short channel_count;

public:
    friend class user;
    pack(){}
    pack(char n[30],float p)
    {

        strcpy(name,n);
        price=p;
        st=price*11/100;

        channel_count=0;

    }


    ~pack(){}
    void options();
    float get_pack_price(int);
    int unique_id();
    void modification_options();
    void modify_pack();
    void add_pack();
    void remove_channels();
    void list_packs();
    void list_channels();
    void show_1_pack();
    void search_pack();
    void add_channel();
    bool pack_exist(int);
    void remove_pack();
    //void list_channels();
};
int pack::unique_id()
{

    fstream fp;
    fp.open("pack.txt",ios::in);
    int max=0;
    while(1)
    {
        fp.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(fp.eof())
            break;
        if(this->pack_code>max)
            max=this->pack_code;
    }
    fp.close();
    return max+1;


}
float pack::get_pack_price(int code)
{
    fstream fp;
     char ch;
     pack p;
        fp.open("pack.txt",ios::in);
        if(!fp.is_open())
           {
            cout<<endl<<"File Can not be opened..";

           }
           while(1)
        {
            fp.read(reinterpret_cast<char*>(&p),sizeof(p));
            if(fp.eof())
                break;
            if(p.pack_code==code)
            {
                return p.price+p.st;
            }
        }

}
void pack::options()
{
    int ch;
//    user u;
    char choice;
    inter i;
        box b;

    do{
            system("cls");
            i.header();
            i.draw_menu_bar();
            gotoxy(3,8);
    cout<<endl<<"1.Add a new pack";
    cout<<endl<<"2.List all packs";
    cout<<endl<<"3.Search a pack";
    cout<<endl<<"4.Modify a pack";
    cout<<endl<<"5.Remove a pack";
    cout<<endl<<"6.Go back";
    cout<<endl<<"7.Exit";
    cout<<endl<<"Your Choice:";
    cin>>ch;
    switch(ch)
    {
    case 1:
        add_pack();
        break;
    case 2:
        list_packs();
        break;
    case 3:
        search_pack();
        break;
    case 4:
        modify_pack();
        break;
    case 5:
        remove_pack();
        break;
    case 6:
        {
            return;

        }
        break;
    case 7:
        exit(0);
    default:
        cout<<"Wrong Choice";
        break;
    }
    gotoxy(3,40);
     cout<<"Anything Else?<y/n>";
     cin>>choice;
    if(choice=='n'||choice=='N')
        break;

    }while(1);
}
void pack::add_pack()
    {
        fstream fp;

        char ch;
        char name[30];
        float price;
        pack p;

        fp.open("pack.txt",ios::app|ios::out);
                gotoxy(45,9);
            cout<<"Pack name:";
            fflush(stdin);
            gets(p.name);
            gotoxy(45,11);
            cout<<"price:";
            fflush(stdin);
            cin>>p.price;
                p.pack_code=unique_id();
                p.channel_count=0;
           p.add_channel();
            fp.write(reinterpret_cast<char*>(&p),sizeof(p));
        fp.close();
        fp.clear();
    }
void pack::remove_pack()
{
    fstream fp1,fp2;
    int codes[10];
    int i;
    char ch;
    pack p;
    do{
        fp1.open("pack.txt",ios::in);
    if(!fp1)
    {
        cout<<endl<<"Can not open pack.txt"<<endl;
    }
    fp2.open("temp.txt",ios::out|ios::app);
    if(!fp2)
    {
        cout<<endl<<"Can not open temp.txt"<<endl;
    }
            system("cls");
    cout<<endl<<"____________________________________"<<endl;
          cout<<"|\tCurrently Available Packs\t|"<<endl;
          cout<<"____________________________________"<<endl;

    list_packs();
    //cout<<endl<<"Select Pack Codes you want delete(press -1 to stop input):"<<endl;
    i=0;
    for(i=0;i<10;i++)
    {
         cout<<"\t";
         cin>>codes[i];
         if(codes[i]==-1)
        break;
    }
    while(1)
    {
        fp1.read(reinterpret_cast<char*>(&p),sizeof(p));
        if(!fp1.eof())
            break;
            int flag=0;
        for(int j=0;j<i;j++)
        {
            if(p.pack_code==codes[j])
            {
                flag=1;
                break;
            }
        }
        cout<<"flag=="<<flag;
        getch();
        if(!flag)
            fp2.write(reinterpret_cast<char*>(&p),sizeof(p));


    }
    fp1.close();
    fp2.close();
    remove("pack.txt");
    rename("temp.txt","pack.txt");

    cout<<"Packs deleted successfully!!"<<endl;
    cout<<endl<<"Want to delete more packs?<y/n> ";
    cin>>ch;
    if(ch=='n'||ch=='N')
        break;
}while(1);
fp1.clear();
fp2.clear();
}

void pack::search_pack()
{
     fstream fp;
     int code;
     char ch;
        fp.open("pack.txt",ios::in);
        if(!fp.is_open())
           {
            cout<<endl<<"File Can not be opened..";
            return ;

           }
           gotoxy(45,9);
        cout<<"Enter the pack code:";
        cin>>code;
        pack p;
        box b;
        b.draw_row(31,7,90);
    cout.setf(ios::left);

    gotoxy(31,9);
    cout<<setw(12)<<"PACK_ID"<<setw(25)<<"PACK_NAME"<<setw(15)<<"NO_OF_CHANNELS"<<setw(10)<<"PRICE"<<setw(10)<<"ST"<<setw(10)<<"NET_RATE"<<endl;
    gotoxy(31,12);
    b.draw_row(31,11,90);
while(1)
        {
            fp.read(reinterpret_cast<char*>(&p),sizeof(p));
            if(fp.eof())
                break;
            if(p.pack_code==code)
            {
               cout.setf(ios::fixed);
        gotoxy(31,12);
        cout<<setw(12)<<p.pack_code<<setw(25)<<p.name<<setprecision(2)<<setw(15)<<p.channel_count<<setw(10)<<p.price<<setw(10)<<p.st<<setw(10)<<p.price+p.st<<endl;
                break;
            }
       }
      b.draw_colomn(120,5,50);
       gotoxy(125,15);
        cout<<"PRESS 'M' TO SEE CHANNEL DETAILS: ";
        cin>>ch;
        //cout<<endl;
        if(ch=='m'||ch=='M')
        {

      if(p.channel_count>0)
                 p.list_channels();
            else
                {   gotoxy(125,20);
                    cout<<"Currently there are no channels in this pack.."<<endl;
                }
        }

        else return ;
        fp.close();
}
void pack::show_1_pack()
    {
        cout.setf(ios::left);
        cout.setf(ios::fixed);
        cout<<setw(8)<<pack_code<<setw(25)<<name<<setprecision(2)<<setw(10)<<price<<setw(10)<<st<<setw(10)<<price+st<<endl;
    }
void pack::list_packs()
    {
        fstream fp;
        fp.open("pack.txt",ios::in);
        if(!fp.is_open())
           {
            cout<<endl<<"File Can not be opened..";
            return ;
            }

        pack p;
        box b;
        b.draw_row(31,7,90);
    cout.setf(ios::left);

    gotoxy(31,9);
    cout<<setw(12)<<"PACK_ID"<<setw(25)<<"PACK_NAME"<<setw(12)<<"NO_OF_CHANNELS"<<setw(10)<<"PRICE"<<setw(10)<<"ST"<<setw(10)<<"NET_RATE"<<endl;
    gotoxy(31,12);
    b.draw_row(31,11,90);
    b.draw_colomn(120,5,50);
    short k=12;
        while(1)
        {
            fp.read(reinterpret_cast<char*>(&p),sizeof(p));
            if(fp.eof())
                break;
            cout.setf(ios::left);
        cout.setf(ios::fixed);
        gotoxy(31,k);
        k++;
        cout<<setw(12)<<p.pack_code<<setw(25)<<p.name<<setprecision(2)<<setw(12)<<p.channel_count<<setw(10)<<p.price<<setw(10)<<p.st<<setw(10)<<p.price+p.st<<endl;


        }
        fp.close();
    }
void pack::list_channels()
    {
       fstream fp;
       channel c;
       int i=0;
       box b;
    fp.open("channel.txt",ios::in);
      b.draw_row(45,16,60);
    cout.setf(ios::left);
    gotoxy(45,17);
    cout<<setw(12)<<"Code No."<<setw(25)<<"Name"<<setw(25)<<"Catagory"<<endl;
    gotoxy(45,19);
    b.draw_row(45,19,60);
    short k=19;

       while(!fp.eof())
       {
           fp.read(reinterpret_cast<char*>(&c),sizeof(c));
           if(c.ch_code==this->channels[i]&&this->channels[i]!=-1)
           {
               gotoxy(45,k);
				k++;
        cout.setf(ios::left);
    cout<<setw(12);
    cout<<c.ch_code;
    cout<<setw(25)<<c.name<<setw(25)<<catagory[c.cat]<<endl;

            i++;
           }
       }
       fp.close();
    }

void pack::add_channel()
    {
        channel c;
gotoxy(45,9);

        c.list_channels();
        short code;
        short int exist=0;
        gotoxy(125,7);
        cout<<"Select channel codes(-1 to stop input):"<<endl;

        int k=9;
        while(1)
        {
             gotoxy(125,k);
                k++;
                cin>>code;
                if(code==-1)
                    break;
                if(code>=0&&code<c.total)
                        {
                            for(int j=0;j<channel_count;j++)
                            {
                                if(channels[j]==code)
                                {
                                    exist=1;
                                    cout<<"Channel Alrady Exist...";
                                    break;
                                }
                            }
                        }
                    if(!exist)
                    {this->channels[channel_count]=code;
                   channel_count++;
                    }


        }        //this->channel_count=i;
        //fp.close();

    }
void pack::remove_channels()
{
    channel c;
    box b;
    b.draw_row(31,7,89);
    cout.setf(ios::left);

    gotoxy(31,9);
    cout<<setw(12)<<"PACK_ID"<<setw(25)<<"PACK_NAME"<<setw(12)<<"NO_OF_CHANNELS"<<setw(10)<<"PRICE"<<setw(10)<<"ST"<<setw(10)<<"NET_RATE"<<endl;
    gotoxy(31,12);
    b.draw_row(31,11,89);
    cout.setf(ios::left);
        cout.setf(ios::fixed);
        gotoxy(31,12);
        cout<<setw(12)<<this->pack_code<<setw(25)<<this->name<<setprecision(2)<<setw(12)<<this->channel_count<<setw(10)<<this->price<<setw(10)<<this->st<<setw(10)<<this->price+this->st<<endl;
        //cout<<"CHANNELS IN THIS PACK"<<endl;
        this->list_channels();
        short code;
        short int exist=0;
        gotoxy(125,7);
        cout<<"Select channel codes(-1 to stop input):"<<endl;
        int k=9;
        do{
                 gotoxy(125,k);
                k++;
                cin>>code;

                            for(int j=0;j<channel_count;j++)
                            {
                                if(channels[j]==code)
                                {
                                    exist=1;
                                    this->channels[j]=-1;
                                    channel_count--;
                                    break;
                                }
                            }

                    if(!exist)
                    {
                        cout<<"Channel does not Exist...";
                    }


        }while(code!=-1);

}
void pack::modification_options()
{
    int ch;
    box b;
    char choice;
inter i;
    do{
            system("cls");
            i.header();
            i.draw_menu_bar();
            gotoxy(3,8);
    cout<<"1.Change pack name"<<endl;
    gotoxy(3,10);
    cout<<"2.Update price"<<endl;
    gotoxy(3,12);
    cout<<"3.Add channels"<<endl;
    gotoxy(3,14);
    cout<<"4.Remove channels"<<endl;
    gotoxy(3,16);
    cout<<"Your choice:";
    cin>>ch;
    b.draw_colomn(120,5,50);
    switch(ch)
    {
        case 1:
            gotoxy(3,25);
            cout<<"New Name:";
            fflush(stdin);
            cin>>name;

            break;
        case 2:
            gotoxy(3,30);
            cout<<"Revised Price:";
            fflush(stdin);
            cin>>price;
            break;
        case 3:
            add_channel();
            break;
        case 4:
            remove_channels();
            break;
        default:
            cout<<endl<<"Wrong Choice.....";

    }
    gotoxy(125,12);
    cout<<"Anything else?<y/n>";
    cin>>choice;
    if(choice=='n'||choice=='N')
        break;
    if(choice=='y'||choice=='N')
        continue;
        break;
    }while(1);

}
void pack::modify_pack()
{
        fstream fp;
char name[30];
        pack p;
        short flag=0;
        short code;
        p.list_packs();
        int ch,ch_code;
        bool exist;
        char choice;
        int rec_len;

            gotoxy(125,12);
        cout<<"Select Pack_code:";
        cin>>code;

        fp.open("pack.txt",ios::in|ios::out);
        if(!fp.is_open())

           {
            cout<<endl<<"File Can not be opened..";
            return ;
            }

        while(!fp.eof())
        {
            fp.read(reinterpret_cast<char*>(&p),sizeof(p));
            if(p.pack_code==code)
            {
                p.modification_options();
                 fp.seekg(-655,ios::cur);
                     fp.write(reinterpret_cast<char*>(&p),sizeof(p));
                break;
                fp.close();
                fp.clear();
                    }
        }
                return;
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
                                //date class//
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class date{
    public:
short dd;
short mm;
short yy;

   bool getdate()
    {
    char date[11];
    fflush(stdin);
    gets(date);


    dd=(date[0]-48)*10+date[1]-48;
    mm=(date[3]-48)*10+date[4]-48;
    yy=(date[6]-48)*1000+(date[7]-48)*100+(date[8]-48)*10+date[9]-48;

    //cout<<"dd="<<dd<<"-"<<"mm="<<mm<<"-"<<"yy="<<yy;
    //getch();

        try
        {
            if(dd<1||dd>31)
                throw 1;
            if(mm<1||mm>12)
                throw 2;
            if(yy<1900||yy>1995)
                throw 3;
            if(mm==2&&(yy%4!=0)&&dd>28)
                throw 4;

            if((mm==6||mm==11||mm==4||mm==9)&&dd>30)
                throw 5;
            if(mm==2&&(yy%4==0)&&dd>29)
                throw 6;
              return true;
        }
        catch(int c)
        {

            return false;

        }

    }
   friend ostream &operator<<(ostream &dout,date d)
    {
    dout<<d.dd<<"/"<<d.mm<<"/"<<d.yy;
    return dout;
    }
    bool operator<(date d)
    {
        if(yy<d.yy)
            return true;
        if(mm<d.mm)
            return true;
        if(dd<d.dd)
            return true;
        return false;
    }
date operator+(int d)
    {
        date temp;
        if(d==30)
        {
            if(mm==4||mm==6||mm==9||mm==11)
            {
                if((dd+30)%30==0)
                    temp.dd=30;
                else
                    temp.dd=(dd+30)%30;
                temp.yy=yy;
                temp.mm=mm+1;


            }
            else if(mm==2)
            {
                    if(dd>=1&&dd<=25)
                        temp.dd=(dd+30)%28;
                    else
                        temp.dd=dd;
                    temp.mm=mm+1;
                    temp.yy=yy;
            }
            else
            {
                if(dd==1)
                {
                    temp.dd=dd+30;
                    temp.mm=mm;
                    temp.yy=yy;

                }
                else if(dd>1)
                {
                    temp.dd=(dd+30)%31;
                    if(mm==12)
                        temp.mm=1;
                    temp.yy=yy+1;

                }
            }
        }
        return temp;
}

bool operator>(date &d)
{
    if(yy>d.yy)
        return true;
    if(mm>d.mm)
        return true;
    if(dd>d.dd)
        return true;
return false;
}
};
class address{
char h_no[4];
char area[20];
char city[20];
char state[20];
char PIN[6];

public:
    bool get_addr(int x,int y)
    {
        char ch;
        bool all_set=false;
        cout.setf(ios::left);
        gotoxy(x,y);
        cout<<"HOUSE NO.-";
        cin>>h_no;

        gotoxy(x+20,y);
        cout<<"AREA/STREET-";
        fflush(stdin);
        gets(area);
        gotoxy(x,y+1);
        cout<<"CITY-";
         fflush(stdin);
        gets(city);
        gotoxy(x+20,y+1);
        cout<<"STATE-";
        fflush(stdin);
        gets(state);
        gotoxy(x,y+2);
        cout<<"PIN-";
        fflush(stdin);
        gets(PIN);
        all_set=true;
        return all_set;
    }


};

class subscriber{
int id;
char f_name[15];
char m_name[15];
char l_name[15];
char email[40];
char mob[10];
int pack_code;
address p_addr;
address c_addr;
date DOB;
date connec_date;
bool sub_status;

public:
    int unique_id();
    void options();
    void add_subscriber();
    void delete_subscriber();
    void enable_subscription();
    void disable_subscription();
    void show_all_subscriber();
    //void show_profile();
    //void edit_profile();
    //bool validate_email();
    void update();//this funtion checks the subscription of every subscriber whether it is valid or not and updates it
    friend class user;
    friend class recharge;

};


int subscriber::unique_id()
{

    fstream fp;
    fp.open("subscriber.txt",ios::in);
    int max=0;
    subscriber s;
    while(1)
    {
        fp.read(reinterpret_cast<char*>(&s),sizeof(s));
        if(fp.eof())
            break;
        if(s.id>max)
            max=s.id;
    }
    fp.close();

    return max+1;
}
void subscriber::options()
{
    inter i;
   int ch;
   char choice;
    do{
              system("cls");
            i.header();
            i.draw_menu_bar();
            gotoxy(3,8);
        cout<<"1.Add subscriber"<<endl;
        gotoxy(3,10);
        cout<<"2.Delete subscriber"<<endl;
        gotoxy(3,12);
        cout<<"3.Enable subscriber"<<endl;
        gotoxy(3,14);
        cout<<"4.Disable subscriber"<<endl;
        gotoxy(3,16);
        cout<<"5.Show all subscriber"<<endl;
        gotoxy(3,18);
        cout<<"6.Show Profile"<<endl;
        gotoxy(3,20);
        cout<<"7.Edit Profile"<<endl;
        gotoxy(3,22);
        cout<<"8.Go back"<<endl;
        gotoxy(3,24);
        cout<<"9.Exit"<<endl;
        gotoxy(3,26);
        cout<<"Your Choice:";
        cin>>ch;
        switch(ch)
        {
        case 1:
            this->add_subscriber();
            break;
        case 2:
            this->delete_subscriber();
            break;
        case 3:
            this->enable_subscription();
            break;

        case 4:
            this->disable_subscription();
            break;
        case 5:
            this->show_all_subscriber();
            break;
        case 6:
            //this->show_profile();
            break;
        case 7:
            //this->edit_profile();
            break;
        case 8:
            {
               return ;
            }
            break;
        default:
            cout<<"Wrong choice";

        }
        gotoxy(3,40);
        cout<<"ANYTHING ELSE?<Y/N>";
        cin>>choice;
        if(choice=='y'||choice=='y')
            options();
        else
            break;
    }while(ch<=2);
}


void subscriber::add_subscriber()
{
    bool dob_set=true;
    bool connec_set=true;
    bool addr_set=true;
    subscriber s;
    int count=0;
    bool all_set=false;
    fstream fp;
    char ch;
    box b;
    fp.open("subscriber.txt",ios::out|ios::app|ios::binary);
    if(!fp)
        {cout<<"Error in opening file.";
        return;}
        do{
                    if(!dob_set)
                    {

                    }

        if(!addr_set)
            {   gotoxy(125,9);
                cout<<"Invalid address!!! Enter again"<<endl;
            }
        if(!connec_set)
        {
            gotoxy(125,11);
            cout<<"Invalid date !!! Enter the connection date again"<<endl;
        }

          b.draw_row(31,7,89);
    cout.setf(ios::left);
    gotoxy(60,6);
    cout<<"ENTER YOUR DETAILS";
    gotoxy(32,8);
    cout<<setw(30)<<"First Name:"<<setw(30)<<"Middle Name:"<<setw(30)<<"Last Name:";
    fflush(stdin);
s.id=unique_id();
cout<<"s.id="<<s.id<<endl;
int j=0;
    if(count==0)
    {   gotoxy(32,10);
        gets(s.f_name);
    }
    else
        {
            //gotoxy(32,10);
            //cout<<s.f_name<<endl;
        }
     fflush(stdin);
    if(count==0)
    {
        gotoxy(62,10);
        gets(s.m_name);
    }
    else
        {    //gotoxy(62,10);
            //cout<<s.m_name<<endl;
        }
     fflush(stdin);
   if(count==0)
    {
        gotoxy(92,10);
        gets(s.l_name);
    }
    else
     {
         //gotoxy(92,10);
       //cout<<s.l_name<<endl;
     }
    gotoxy(32,12);
    cout<<"EMAIL: ";
     fflush(stdin);
    if(count==0)
    {
         gotoxy(38,12);
        gets(s.email);
    }
    else
        {  //gotoxy(38,12);
           // cout<<s.email;
        }
    gotoxy(92,12);
    cout<<"DOB(dd/mm/yyyy):";
    fflush(stdin);
    dob_set=s.DOB.getdate();
   /* if(!dob_set)
    {
        gotoxy(125,7);
        cout<<"Invalid date !!! Enter the DOB again"<<endl;
        gotoxy(118,12);

    }*/
    gotoxy(32,14);
     cout<<"PERMANENT ADDRESS:";
     fflush(stdin);
     addr_set=s.p_addr.get_addr(52,15);
     if(!addr_set)
     {
         count++;
         continue;

     }

gotoxy(32,18);
    cout<<"CORRESSPONDENCE ADDRESS:";
    fflush(stdin);
    s.c_addr.get_addr(52,19);
all_set=true;
gotoxy(32,23);
        cout<<"MOBILE:";
    fflush(stdin);
    gets(s.mob);
    gotoxy(62,23);
    cout<<"DATE OF CONNECTION:";
    fflush(stdin);

   connec_set=s.connec_date.getdate();
   if(!connec_set)
    {
        count++;
        continue;
    }

    gotoxy(32,25);
    cout<<"CURRENT PACK CODE:";
    fflush(stdin);
    cin>>pack_code;

    //cout<<s.connec_date;
   s.sub_status=true;
   all_set==true;
   if(!dob_set)
    {
        gotoxy(125,7);
        cout<<"Invalid date !!! Enter the DOB again"<<endl;
        gotoxy(118,12);

    }


        }while(!all_set);
    gotoxy(125,7);
   cout<<"TO SAVE PRESS 'S' AND TO PRESS 'C' TO CANCEL: ";
   gotoxy(125,8);
   cin>>ch;
   if(ch=='c'||ch=='C')
    options();
   if(ch=='s'||ch=='S');
   {


       s.id=unique_id();
       fp.write(reinterpret_cast<char*>(&s),sizeof(s));
       gotoxy(125,9);
       cout<<"Record is saved successfully!!"<<endl;
      // getch();
   }

fp.close();
fp.clear();


}

void subscriber::show_all_subscriber()
{
    subscriber s;
    fstream fp;
    char name[40]="";
    fp.open("subscriber.txt",ios::in|ios::binary);
    if(!fp)
        cout<<"ERROR";

    cout.setf(ios::left);
    box b;
    b.draw_row(31,7,89);
    gotoxy(32,6);
    cout<<"ID NO."<<setw(40)<<"NAME"<<setw(10)<<"Subcription";
    int k=9;
   //b.draw_row(31,9,89);
    while(fp.read(reinterpret_cast<char*>(&s),sizeof(s)))
    {
    strcat(name,s.f_name);
    strcat(name," ");
    strcat(name,s.m_name);
    strcat(name," ");

    strcat(name,s.l_name);
gotoxy(32,k);
k++;
        cout<<setw(7)<<s.id<<setw(40)<<name<<setw(10);
        //cout<<s.sub_status;
        if(s.sub_status==true)
            cout<<"Enabled";
        else if(s.sub_status==0)
            {cout<<"Disabled";}
            strcpy(name,"\0");
    }
    fp.close();
    fp.clear();
}

void subscriber::delete_subscriber()
{
    fstream fp1,fp2;
    int i;
    int id;
    char ch;

    subscriber s;
    do{
        fp1.open("subscriber.txt",ios::in);
    if(!fp1)
    {
        cout<<"Can not open pack.txt";
    }
    fp2.open("temp.txt",ios::out|ios::app);
    if(!fp2)
    {
        cout<<"Can not open temp.txt";
    }

    show_all_subscriber();
    gotoxy(125,7);
    cout<<"Select subscriber IDs you want delete";
    gotoxy(125,8);
    cout<<"(press -1 to stop input):";
    gotoxy(125,9);
    cin>>id;
    i=0;
    while(1)
    {
fp1.read(reinterpret_cast<char*>(&s),sizeof(s));
        if(fp1.eof())
            break;
            int flag=0;
        if(s.id!=id)
            flag=1;

        if(flag)
           fp2.write(reinterpret_cast<char*>(&s),sizeof(s));

    }

    fp1.close();
    fp2.close();
    remove("subscriber.txt");
    rename("temp.txt","subscriber.txt");
    gotoxy(125,13);
    cout<<"Subscriber Record deleted successfully!!"<<endl;
    gotoxy(125,16);
    cout<<"Want to delete more subscribers?<y/n> ";
    cin>>ch;
    if(ch=='n'||ch=='N')
        break;
    if(ch=='y'||ch=='Y')
        options();
}while(1);
fp1.clear();
fp2.clear();
}
void subscriber::disable_subscription()
{
    fstream fp;
    int i;
    int id[10];
    char ch;
    int c;

    subscriber s;
    fp.open("subscriber.txt",ios::in|ios::out|ios::binary);
    show_all_subscriber();
    gotoxy(125,7);
    cout<<"select the subscriber ID u want to disable";
    gotoxy(125,9);
    cin>>c;
    //cout<<"(press -1 to stop )";
    /*int k=10;
    i=0;
    while(1)
    {
        gotoxy(125,k);
        k++;


        if(c==-1)
            break;
        id[i]=c;

i++;

    }*/
int flag;
    while(1)
    {

 flag=0;
     int rec_len=sizeof(s);

        fp.read(reinterpret_cast<char*>(&s),sizeof(s));
        flag=0;
            if(s.id==c)
        {flag=1;
        cout<<"true";
        s.sub_status=false;
         fp.seekg(-260,ios::cur);
         fp.write(reinterpret_cast<char*>(&s),sizeof(s));
                break;
        }
    }
    if(!flag)
    cout<<"no such subscriber.....!";
    fp.close();
                fp.clear();
                return ;
}
void subscriber::enable_subscription()
{
    fstream fp;
    int i;
    int id[10];
    char ch;
    int c;

    subscriber s;
    fp.open("subscriber.txt",ios::in|ios::out|ios::binary);
    show_all_subscriber();
    gotoxy(125,7);
    cout<<"select the subscriber IDs u want to enable";
    gotoxy(125,9);
    cout<<"(press -1 to stop )";
    int k=10;
    i=0;
    while(1)
    {
        gotoxy(125,k);
        k++;
        cin>>c;
        if(c==-1)
            break;
        id[i]=c;
        i++;
    }
    while(fp.read(reinterpret_cast<char*>(&s),sizeof(s)))
    {
            int flag=0;
        for(int j=0;j<i;j++)
        {
            if(s.id==id[j])
            {
                cout<<"true;";
                s.sub_status=true;
                  fp.seekg(-260,ios::cur);
         fp.write(reinterpret_cast<char*>(&s),sizeof(s));
                break;
            }
        }
    }
    fp.close();
    fp.clear();
}


class on_demand
{
protected:
int code;
int sub_id;
float price;
public:
    virtual void get_details()=0;
    virtual void show_all()=0;
    virtual void options()=0;
};

class channels_on_demand:public on_demand
{
char pack_name[25];
int validity;
int channel_count;
public:
     void get_details();
     void show_all();
     int unique_code();
     void options();

};
int channels_on_demand::unique_code()
{

    fstream fp;
    fp.open("channels_on_demand.txt",ios::in);
    int max=0;
    while(1)
    {
        fp.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(fp.eof())
            break;
        if(this->code>max)
            max=this->code;
    }
    fp.close();
    return max+1;


}
void channels_on_demand::options()
{
    int ch;
    char choice;
    inter i;
        box b;

    do{
            system("cls");
            i.header();
            i.draw_menu_bar();
            gotoxy(3,8);
    cout<<endl<<"1.Add a new pack"<<endl;
    cout<<endl<<"2.List all packs"<<endl;
    cout<<endl<<"6.Go back"<<endl;
    cout<<endl<<"7.Exit"<<endl;
    cout<<endl<<"Your Choice:";
    cin>>ch;
    switch(ch)
    {
    case 1:
        get_details();
        break;
    case 2:
        show_all();
        break;
    case 3:
        {
            return;

        }
        break;
    case 4:
        exit(0);
    default:
        cout<<"Wrong Choice";
        break;
    }
    gotoxy(3,40);
     cout<<"Anything Else?<y/n>";
     cin>>choice;
    if(choice=='n'||choice=='N')
        break;

    }while(1);
}
void channels_on_demand::get_details()
{
    fstream fp;

        char ch;
        char name[30];
        float price;
        //channels_on_demand c;

        fp.open("channels_on_demand.txt",ios::app|ios::out|ios::binary);
                gotoxy(45,9);
            cout<<"Pack name:";
            fflush(stdin);
            gets(pack_name);
            gotoxy(45,11);
            cout<<"price:";
            fflush(stdin);
            cin>>price;
                code=unique_code();
             //   cout<<code;
            gotoxy(45,13);
            cout<<"Channel count: ";
            fflush(stdin);
            cin>>channel_count;
             gotoxy(45,15);
            cout<<"VALIDITY: ";
            fflush(stdin);
            cin>>validity;

            fp.write(reinterpret_cast<char*>(this),sizeof(*this));
        fp.close();
        fp.clear();
}
void channels_on_demand::show_all()
{
    fstream fp;
        fp.open("channels_on_demand.txt",ios::in|ios::binary);
        if(!fp.is_open())
           {
            cout<<endl<<"File Can not be opened..";
            return ;
            }
cout<<"satyam";
    //channels_on_demand c;
        box b;
        b.draw_row(31,7,90);
    cout.setf(ios::left);

    gotoxy(31,9);
    cout<<setw(12)<<"PACK_ID"<<setw(15)<<"PACK_NAME"<<setw(15)<<"NO_OF_CHANNELS"<<setw(15)<<"VALIDITY"<<setw(15)<<"PRICE"<<endl;
    gotoxy(31,12);
    b.draw_row(31,11,90);
    b.draw_colomn(120,5,50);
    short k=12;
        while(1)
        {
            fp.read(reinterpret_cast<char*>(this),sizeof(*this));
            if(fp.eof())
                break;
            cout.setf(ios::left);
        cout.setf(ios::fixed);
        gotoxy(31,k);
        k++;
        cout<<setw(12)<<code<<setw(15)<<pack_name<<setprecision(2)<<setw(15)<<channel_count<<setw(15)<<validity<<setw(15)<<price<<endl;
        }
        fp.close();
}

/*void subscriber::show_profile()
{
    box b;
    fstream fp;
    fp.open("subscriber.txt",ios::in);
  show_all_subscriber();
  gotoxy(125,7);
  cout<<"SELECT THE SUBSCRIBER ID:";
  int id;

  cin>>id;
  subscriber s;
int flag=0;
  while(fp.read(reinterpret_cast<char*>(&s),sizeof(s)))
  {
    if(fp.eof())
        break;
    if(s.id==id)
        {flag=1;
            break;
        }
  }

  if(flag)
  {
     b.draw_row(31,7,90);
     gotoxy(60,6);
     cout<<"SUBSCRIBER NUMBER :: ";
     cout<<s.id;
      gotoxy(32,9);
     cout<<"NAME";gotoxy(52,9);cout<<s.f_name;
     gotoxy(32,11);cout<<"EMAIL";gotoxy(52,11);cout<<s.email;
     gotoxy(32,13);cout<<"DOB";gotoxy(52,13);cout<<s.DOB;
    /* gotoxy(32,15);cout<<"";gotoxy(52,11);cout<<s.email;
     gotoxy(32,11);cout<<"EMAIL";gotoxy(52,11);cout<<s.email;
     gotoxy(32,11);cout<<"EMAIL";gotoxy(52,11);cout<<s.email;
     toxy(32,11);cout<<"EMAIL";gotoxy(52,11);cout<<s.email;


  }*/
class recharge{
int recharge_no;
int pack_code;
int sub_id;
float amount;
date subs_start;
date subs_end;
int validity;
public:
    void options();
    void do_recharge();
    void show_all_recharge();
    int unique_code();
    void show_date_wise();
    friend class subscriber;
    void update();
};
void recharge::options()
{
    int ch;
    inter i;
    char choice;
    do{
//            gotoxy(4,5);
            system("cls");
            i.header();
            i.draw_menu_bar();
            gotoxy(3,8);

        cout<<"1.NEW RECHARGE";
         gotoxy(3,10);
        cout<<"2.SHOW ALL RECHARGE";
         gotoxy(3,12);
        cout<<"3.SHOW DATE WISE RECHARGE";
         gotoxy(3,14);
         cout<<"4.GO BACK";
         gotoxy(3,16);
         cout<<"5.EXIT";
         gotoxy(3,18);
         cout<<"YOUR CHOICE: ";
         cin>>ch;
         switch(ch)
         {
         case 1:
            do_recharge();
            break;
         case 2:
            show_all_recharge();
            break;
         case 3:
            show_date_wise();
            break;
         case 4:
            return ;
         default:
             gotoxy(3,40);
            cout<<"WRONG CHOICE";

         }
         gotoxy(3,40);
         cout<<"ANYTHING ELSE?";
         cin>>choice;
         if(choice=='y'||choice=='Y')
            options();
        else
            return ;
        }while(1);
}
void recharge::update()
{
    recharge r;
    subscriber s;
    fstream fp1,fp2;
    date today;
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    fp1.open("subscriber.txt",ios::in|ios::out|ios::binary);
    if(!fp1)
        {
            cout<<"CAN NOT OPEN FILE";
            return ;
        }
    fp2.open("recharge.txt",ios::in|ios::out|ios::binary);
    if(!fp2)
        {
            cout<<"CAN NOT OPEN FILE";
            return ;
        }

  today.yy=(now->tm_year + 1900);
  today.mm=(now->tm_mon + 1);
  today.dd=now->tm_mday;
  while(1)
  {
      fp2.read(reinterpret_cast<char*>(&r),sizeof(r));
      if(fp2.eof())
        break;
      if(today>r.subs_end)
      {
          while(1)
          {
              fp1.read(reinterpret_cast<char*>(&s),sizeof(s));
              if(fp1.eof())
                break;
              if(s.id==r.sub_id)
              {
                  s.sub_status=false;
                  fp1.seekg(0,ios::beg);
                  break;
              }


          }
      }
  }
}
int recharge::unique_code()
{

    fstream fp;
    fp.open("recharge.txt",ios::in);
    int max=0;
    while(1)
    {
        fp.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(fp.eof())
            break;
        if(this->recharge_no>max)
            max=this->recharge_no;
    }
    fp.close();
    return max+1;


}
void recharge::do_recharge()
{
   box b;
   pack p;
   recharge r;
   fstream fp;
   char ch;
   fp.open("recharge.txt",ios::app|ios::out);
   if(!fp)
    {
        gotoxy(3,17);
        cout<<"ERROR IN OPENING FILE!!!";
        return ;
    }

   time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    p.list_packs();
    r.recharge_no=unique_code();
    gotoxy(125,7);
    cout<<"ENTER SUBSCRIBER ID:";
    cin>>r.sub_id;
   gotoxy(125,10);
   cout<<"SELECT PACK CODE:";
   cin>>r.pack_code;
   gotoxy(125,13);
   cout<<"PACK PRICE:";

   r.amount=p.get_pack_price(r.pack_code);
   cout<<r.amount;
  r.subs_start.yy=(now->tm_year + 1900);
  r.subs_start.mm=(now->tm_mon + 1);
  r.subs_start.dd=now->tm_mday;
  if(r.subs_start.mm==12&&r.subs_start.dd>1)
  gotoxy(125,16);
  cout<<"SUBSCRIPTION START DATE";
  gotoxy(125,18);
  cout<<r.subs_start.dd<<"-"<<r.subs_start.mm<<"-"<<r.subs_start.yy;
  gotoxy(125,20);
  cout<<"SUBSCRIPTION END DATE";
  gotoxy(125,22);
  r.subs_end.dd=12;
  r.subs_end.mm=9;
  r.subs_end.yy=2013;
  //r.subs_end=r.subs_start+30;
  cout<<r.subs_end.dd<<"-"<<r.subs_end.mm<<"-"<<r.subs_end.yy;
  fp.write(reinterpret_cast<char*>(&r),sizeof(r));
  fp.close();
  fp.clear();
  gotoxy(125,25);
  cout<<"ANOTHER RECHARGE?";
  cin>>ch;
  if(ch=='y'||ch=='Y')
do_recharge();
else
    return ;
}
void recharge::show_all_recharge()
    {
        fstream fp;
        fp.open("recharge.txt",ios::in);
        if(!fp.is_open())
           {
            cout<<endl<<"File Can not be opened..";
            return ;
            }

        pack p;
        box b;
        b.draw_row(31,7,90);
    cout.setf(ios::left);

    gotoxy(31,9);
    cout<<setw(15)<<"RECH_NO."<<setw(15)<<"SUBS_ID"<<setw(15)<<"PACK"<<setw(15)<<"START_DATE"<<setw(15)<<"END_DATE"<<setw(15)<<"AMOUNT";
    gotoxy(31,12);
    b.draw_row(31,11,90);
    b.draw_colomn(120,5,50);
    recharge r;
    short k=12;
        while(1)
        {
            fp.read(reinterpret_cast<char*>(&r),sizeof(r));
            if(fp.eof())
                break;
            cout.setf(ios::left);
        cout.setf(ios::fixed);
        gotoxy(31,k);
        k++;

        cout<<setw(15)<<r.recharge_no<<setw(15)<<r.sub_id<<setw(15)<<r.pack_code;
        cout<<r.subs_start.dd<<"/"<<r.subs_start.mm<<"/"<<r.subs_start.yy;
        cout<<"\t  "<<r.subs_end.dd<<"/"<<r.subs_end.mm<<"/"<<r.subs_end.yy;
        cout<<"\t"<<setw(15)<<setprecision(2)<<r.amount;


        }
        fp.close();
    }
void recharge::show_date_wise()
{
    fstream fp;
        fp.open("recharge.txt",ios::in);
        if(!fp.is_open())
           {
            cout<<endl<<"File Can not be opened..";
            return ;
            }

        pack p;
        box b;
        date d;
        gotoxy(125,7);
    cout<<"ENTER THE DATE: ";
    fflush(stdin);
    d.getdate();
        b.draw_row(31,7,90);
    cout.setf(ios::left);

    gotoxy(31,9);
    cout<<setw(15)<<"RECH_NO."<<setw(15)<<"SUBS_ID"<<setw(15)<<"PACK"<<setw(15)<<"START_DATE"<<setw(15)<<"END_DATE"<<setw(15)<<"AMOUNT";
    gotoxy(31,12);
    b.draw_row(31,11,90);
    b.draw_colomn(120,5,50);
    recharge r;
    short k=12;

        while(1)
        {
            fp.read(reinterpret_cast<char*>(&r),sizeof(r));
            if(fp.eof())
                break;
            if(r.subs_start.dd==d.dd&&r.subs_start.mm==d.mm&&r.subs_start.yy==d.yy)
            {
            cout.setf(ios::left);
        cout.setf(ios::fixed);
        gotoxy(31,k);
        k++;

        cout<<setw(15)<<r.recharge_no<<setw(15)<<r.sub_id<<setw(15)<<r.pack_code;
        cout<<r.subs_start.dd<<"/"<<r.subs_start.mm<<"/"<<r.subs_start.yy;
        cout<<"\t  "<<r.subs_end.dd<<"/"<<r.subs_end.mm<<"/"<<r.subs_end.yy;
        cout<<"\t"<<setw(15)<<setprecision(2)<<r.amount;

            }
        }
        fp.close();
}
class user{
char id[10];
char pass[10];
public:
    void options();
    friend class subcriber;
    void get_details()
    {
        bool flag;
        gotoxy(65,22);
        cout<<"UUSER_ID: ";
        fflush(stdin);
        cin>>id;
        gotoxy(65,24);
        cout<<"UPassword:";
        fflush(stdin);
        cin>>pass;
        flag=authenticate();
        if(!flag)
        draw_login_window();
    }
    void draw_login_window()
    {
    	
        box b;
        inter i;
        static int c;
        system("cls");
        if(c>0)
        {
            gotoxy(62,18);
           cout<<"INVALID USER_ID/PASSWORD.!";
        }

        i.header();
        b.draw_box(60,20,30,10);
        c++;
        get_details();

    }
    void display()
    {
        cout<<id<<" "<<pass;
    }

int authenticate()

    {
       user t;
        int flag=0;
       fstream fp1;
        fp1.open("u1.txt",ios::in);

        if(!fp1.is_open())
        {
            cout<<"\nCan not open file!\n";
      }
    while(1)
        {
            fp1.read(reinterpret_cast<char*>(&t),sizeof(t));
            if(fp1.eof())
               break;

        if(strcmp(id,t.id)==0&&strcmp(pass,t.pass)==0)
            {flag=1;break;}
        }
        fp1.close();
        fp1.clear();

        if(flag)
            options();

       // if(!flag)
       //{
        //gotoxy(62,18);
        //get_details();
       //}

         return flag;



    }
    void change_password()
   {
         fstream fp;
         user t;
         char new_pass[10];
        fp.open("u1.txt",ios::in|ios::out);
        gotoxy(40,8);
         cout<<"New Password: ";
         cin>>new_pass;
       while(!fp.eof())
           {
            fp.read(reinterpret_cast<char*>(&t),sizeof(t));
           if(strcmp(t.id,id)==0&&strcmp(t.pass,pass)==0)
           {
               strcpy(t.pass,new_pass);
                int rec_len=sizeof(t);
            fp.seekg(-rec_len,ios::cur);
            fp.write(reinterpret_cast<char*>(&t),sizeof(t));
            break;
           }

    }

        fp.close();
           fp.clear();

    }
    void show_user()
    {
        fstream fp;
        user t;
        fp.open("u1.txt",ios::in);
        while(!fp.eof())
        {

        fp.read(reinterpret_cast<char*>(&t),sizeof(t));
        t.display();
        cout<<endl;

        }
        fp.close();
        fp.clear();
    }
    void create_user()
    {
        user temp;
        	bool flag;
        gotoxy(65,22);
        cout<<"USER_ID: ";
        fflush(stdin);
        cin>>temp.id;
        gotoxy(65,24);
        cout<<"PASSWORD:";
        fflush(stdin);
        cin>>temp.pass;
        temp.write();
    }
    void write()
    {
        fstream fp;

        fp.open("u1.txt",ios::out|ios::app);
        fp.write(reinterpret_cast<char*>(this),sizeof(*this));
        fp.close();
        fp.clear();

    }

    void read()
    {
    fstream fp;
        fp.open("u1.txt",ios::in);
        fp.read(reinterpret_cast<char*>(this),sizeof(*this));
        fp.close();
        fp.clear();
    }
    };
void user::options()
{
    int ch;
    inter i;
    do{
//            gotoxy(4,5);
            system("cls");
            i.header();
            i.draw_menu_bar();
            gotoxy(3,8);

        cout<<"1.Change Password"<<endl;
         gotoxy(3,9);
        cout<<"2.Create Users"<<endl;
         gotoxy(3,10);
        cout<<"3.Channels Info"<<endl;
         gotoxy(3,11);
        cout<<"4.Packs Details"<<endl;
         gotoxy(3,12);
        cout<<"5.Subscribers"<<endl;
         gotoxy(3,13);
        cout<<"6.channels ON demand"<<endl;
         gotoxy(3,14);
        cout<<"7.Movies on demand"<<endl;
         gotoxy(3,15);
        cout<<"8.Recharge"<<endl;
         gotoxy(3,16);
        cout<<"9.Exit"<<endl;
         gotoxy(3,17);
        cout<<"Your Choice:";
        cin>>ch;
        switch(ch)
        {
        case 1:
            this->change_password();
            break;
        case 2:
            this->create_user();
            break;
        case 3:
            {
			channel c;
            c.options();
            options();
            }break;

        case 4:
            {
			pack p;
            p.options();
            options();
            }
            break;
        case 5:
            {
                subscriber s;
                s.options();
                options();
            }
            break;
        case 6:
            {
                channels_on_demand c;
                c.options();
                options();
            }
        case 8:
            {
                recharge r;
                r.options();
                options();
            }
        default:
            cout<<"Wrong choice";

        }
    }while(ch<=2);
}
int main()
    {
        user admin;
        box b;
        inter i;
        i.header();
        gotoxy(0,0);
       // b.draw_box(40,20,20,10);
    admin.get_details();
    admin.write();
       int flag=0;

        int ch;
        do{
date d;
date p;
d.dd=12;
d.mm=1;
d.yy=2013;
p.dd=7;
p.mm=8;
p.yy=2013;
//cout<<(d>p);
getche();
  //  admin.create_user();
        admin.draw_login_window();
        flag=admin.authenticate();
        }while(!flag);
recharge r;
r.update();
///////////////////////////////////////////////////////////////////
if(flag==1)
    admin.options();

        getch();
        return 0;
    }

