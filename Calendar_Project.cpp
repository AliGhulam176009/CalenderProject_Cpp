#include<iostream>
#include<windows.h>       //header file for gotoxy position
#include<conio.h>       //getch (predefined function) header file
using namespace std;

class Calendar{
	public:
		int d;     //date
		int m;    //month
		int y;   //year

		bool check_leap_year(int year);
		void increase_month(int *m,int *y);
		void decrease_month(int *m,int *y);
		int get_number_of_days(int m,int y);
		string get_name(int day);
		void print_date(int mm,int yy);
		int get_day_number(int d,int m,int y);    //d=day   m=month  y=year
		string get_day(int d,int m,int y);
		//void print_month(int d,int m, int y);
		void print_month(int mon,int year,int x,int y);
		//
		void SetColor(int ForgC);
		void ClearColor();
		
};


//gotoxy function
COORD xy = {0, 0};    //declared in windows,h

void gotoxy (int x, int y) 
{
        xy.X = x; xy.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

//cheack leap year
bool Calendar::check_leap_year(int year){
					if (year%100==0 && year%400==0){
						//cout << year << " is the Leap Year "<< endl;
						return true;
					}
					return false;
	
}


//This will set the forground color for printing in a console window.
void Calendar::SetColor(int ForgC)
{
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


//clearcolor
void Calendar::ClearColor(){
    SetColor(7);
}


//increase month function
void Calendar::increase_month(int *m,  int *y){ //increase the month by one
    ++*m;
    if(*m > 12){
        ++*y;
        *m = *m - 12;
    }
}

//decrease month function
void Calendar::decrease_month(int *m,int *y){
					--*m;
					if (*m < 1){
						--*y;
						if (*y<1600){
							 cout << ("No record available");
							  return;
						}
						
						
					*m = *m + 12;
					//return;
}
}
 
 
//return the number of days in given  month and  year.
int Calendar::get_number_of_days(int m,int y){ 
	switch (m){
		case 1:
			return 31;
											
		case 2:
			if (check_leap_year(y)==true)
			{
				return 29;
			}
			return 28;
		case 3:
			return 31;
		case 4:
			return 30;
		case 5:
			return 31;
		case 6:
			return 30;
		case 7:
			return 31;
		case 8:
			return 31;
		case 9:
			return 30;
		case 10:
			return 31;
		case 11:
			return 30;
		case 12:
			return 31;		
		default:
			return -1;				
	}
	
	return 0;
}


//returns the name of the day(week name)
string Calendar::get_name(int day){
	switch(day){
		case 0:
			return ("Sunday");
		case 1:
			return ("Monday");
		case 2:
			return ("Tusday");
		case 3:
			return ("Wednesday");
		 case 4:
			return ("Thursday");
		case 5:
			return ("Friday");
		case 6:
			return ("Saturday");
		default:
			return ("Invalid argument passed");
	
	}
					
}
  
//print month and year
//print_date   
void Calendar::print_date(int mm,int yy){
	gotoxy(20,5);
    cout << "========================="<<endl;
	gotoxy(24,6);
    
	switch(mm){
        case 1: 
			cout<<"January";
			break;
        case 2: 
			cout<<"February"; 
			break;
        case 3: 
			cout<<"March"; 
			break;
        case 4: 
			cout<<"April"; 
			break;
        case 5: 
			cout<<"May"; 
			break;
        case 6:
			cout<<"June"; 
			break;
        case 7: 
			cout<<"July"; 
			break;
        case 8: 
			cout<<"August"; 
			break;
        case 9: 
			cout<<"September"; 
			break;
        case 10: 
			cout<<"October"; 
			break;
        case 11: 
			cout<<"November"; 
			break;
        case 12: 
			cout<<"December"; 
			break;
								
	}
					
	cout<< " , "<< yy<<endl;
	gotoxy(20,7);
	cout << "========================="<<endl;
}
	
	
//get_day_number	
int Calendar::get_day_number(int d, int m,int yy){
	int res = 0, t1, t2, y = yy;
    yy = yy - 1600;
    while(yy >= 100){
        res = res + 5;
        yy = yy - 100;
    }
    res = (res % 7);
    t1 = ((yy - 1) / 4);
    t2 = (yy-1)-t1;
    t1 = (t1*2)+t2;
    t1 = (t1%7);
    res = res + t1;
    res = res%7;
    t2 = 0;
    for(t1 = 1;t1 < m; t1++){
        t2 += get_number_of_days(t1,y);
    }
    t2 = t2 + d;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if(y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}

//get_day
string Calendar::get_day(int d,int m,int y){
	 int day;
    if(!(m>=1 && m<=12)){
        return ("Invalid month value");
    }
    if(!(d>=1 && d<=get_number_of_days(m,y))){
        return("Invalid date");
    }
    if(y>=1600){
        day = get_day_number(d, m,y);
        day = day%7;
        return(get_name(day));
    }else{
        return("Please give year more than 1600");
    }
}
	
	

//void print_month function  //prints the month with all days
void Calendar::print_month(int mon,int year,int x,int y){ 
    int nod, day, cnt, d = 1, x1 = x, y1 = y, isNote = 0;
    if(!(mon>=1 && mon<=12)){
        printf("INVALID MONTH");
        getch();
        return;
    }
    if(!(year>=1600)){
        cout << ("INVALID YEAR");
        getch();
        return;
    }
    gotoxy(20,y);
    print_date(mon,year);
    y += 3;
    gotoxy(x,y);
    cout << ("S   M   T   W   T   F   S   ");
    cout << endl;
    y++;
    nod = this->get_number_of_days(mon,year);
    day = this->get_day_number(d,mon,year);
    switch(day){     //locates the starting day in calender
        case 0 :
            x=x;
            cnt=1;
            break;
        case 1 :
            x=x+4;
            cnt=2;
            break;
        case 2 :
            x=x+8;
            cnt=3;
            break;
        case 3 :
            x=x+12;
            cnt=4;
            break;
        case 4 :
            x=x+16;
            cnt=5;
            break;
        case 5 :
            x=x+20;
            cnt=6;
            break;
        case 6 :
            x=x+24;
            cnt=7;
            break;
        default :
            cout << "INVALID DATA FROM THE getOddNumber()MODULE";
            return;
    }
    gotoxy(x,y);
    
    if(cnt == 1){
        SetColor(12);
    }
    cout << ("%02d",d);

    for(d=2;d<=nod;d++){
        if(cnt%7==0){
            y++;
            cnt=0;
            x=x1-4;
        }
        x = x+4;
        cnt++;
        gotoxy(x,y);
        if(cnt==1){   //sunday column assign red color
            SetColor(12);
        }
		else{
            ClearColor();
        }
        
        cout << ("%02d",d);
    }
    gotoxy(8, y+5);
    ClearColor();
    printf("Press 'n'  to Next, Press 'p' to Previous and 'q' to Quit");


}


/*A Function that returns the index of the day 
  of the date- day/month/year 
  For e.g- 
  
  Index     Day 
  0         Sunday 
  1         Monday 
  2         Tuesday 
  3         Wednesday 
  4         Thursday 
  5         Friday 
  6         Saturday*/
int dayNumber(int day, int month, int year) 
{ 
  
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 
                       4, 6, 2, 4 }; 
    year -= month < 3; 
    return ( year + year/4 - year/100 + 
             year/400 + t[month-1] + day) % 7; 
} 
  
/* 
  A Function that returns the name of the month 
  with a given month number 
  
  Month Number     Name 
  0                January 
  1                February 
  2                March 
  3                April 
  4                May 
  5                June 
  6                July 
  7                August 
  8                September 
  9                October 
  10               November 
  11               December */
string getMonthName(int monthNumber) 
{ 
    string months[] = {"January", "February", "March", 
                       "April", "May", "June", 
                       "July", "August", "September", 
                       "October", "November", "December"
                      }; 
  
    return (months[monthNumber]); 
} 
  
/* A Function to return the number of days in 
   a month 
  
  Month Number     Name        Number of Days 
  0                January     31 
  1                February    28 (non-leap) / 29 (leap) 
  2                March       31 
  3                April       30 
  4                May         31 
  5                June        30 
  6                July        31 
  7                August      31 
  8                September   30 
  9                October     31 
  10               November    30 
  11               December    31 
  
*/
int numberOfDays (int monthNumber, int year) 
{ 
    // January 
    if (monthNumber == 0) 
        return (31); 
  
    // February 
    if (monthNumber == 1) 
    { 
        // If the year is leap then February has 
        // 29 days 
        if (year % 400 == 0 || 
                (year % 4 == 0 && year % 100 != 0)) 
            return (29); 
        else
            return (28); 
    } 
  
    // March 
    if (monthNumber == 2) 
        return (31); 
  
    // April 
    if (monthNumber == 3) 
        return (30); 
  
    // May 
    if (monthNumber == 4) 
        return (31); 
  
    // June 
    if (monthNumber == 5) 
        return (30); 
  
    // July 
    if (monthNumber == 6) 
        return (31); 
  
    // August 
    if (monthNumber == 7) 
        return (31); 
  
    // September 
    if (monthNumber == 8) 
        return (30); 
  
    // October 
    if (monthNumber == 9) 
        return (31); 
  
    // November 
    if (monthNumber == 10) 
        return (30); 
  
    // December 
    if (monthNumber == 11) 
        return (31); 
} 
  
// Function to print the calendar of the given year 
void printCalendar(int year) 
{ 
    printf ("         Calendar - %d", year); 
    int days; 
  
    // Index of the day from 0 to 6 
    int current = dayNumber (1, 1, year); 
  
    // i --> Iterate through all the months 
    // j --> Iterate through all the days of the 
    //       month - i 
    for (int i = 0; i < 12; i++) 
    { 
        days = numberOfDays (i, year); 
  
        // Print the current month name 
        printf("\n  ------------%s-------------\n", 
               getMonthName (i).c_str()); 
  
        // Print the columns 
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n"); 
  
        // Print appropriate spaces 
        int k; 
        for (k = 0; k < current; k++) 
            printf("     "); 
  
        for (int j = 1; j <= days; j++) 
        { 
            printf("%5d", j); 
  
            if (++k > 6) 
            { 
                k = 0; 
                printf("\n"); 
            } 
        } 
  
        if (k) 
            printf("\n"); 
  
        current = k; 
    } 
  
    return; 
} 

//
	
int main(){
	
	Calendar c;
	int year;
	system("color A");
	
	int choice;
    char ch = 'a';
    while(1){
    	
	    
		system("cls");   //clear the screen,predefined function header file (iostream)
		gotoxy(41,0);
		cout <<"**********************" <<endl;
		gotoxy(41,1);
		Sleep(1000);
		cout <<"|| PROJECT CALENDAR ||"<<endl<<endl;
		gotoxy(41,2);
		cout <<"**********************" <<endl<<endl;
		Sleep(1000);
		gotoxy(41,4);
		cout << "Project Developers  "<<endl;
		Sleep(1000);
		gotoxy(37,5);
		cout<<"ALI GHULAM & MALIK ADNAN "<<endl<<endl;
		Sleep(1000);
		gotoxy(35,7);
        cout << ("1.Find Out the Day\n");
        Sleep(1000);
        gotoxy(35,8);
        cout << ("2.Print all the day of month\n");
        Sleep(1000);
        gotoxy(35,9);
        cout << "3.Enter your desired year (print one year calender)\n";
        Sleep(1000);
        gotoxy(35,10);
		cout << ("4.EXIT\n");
        Sleep(1000);
        gotoxy(35,11);
        cout << ("ENTER YOUR CHOICE : ");
        Sleep(1000);
        cin  >> choice;
        
        system("cls");
        system("color 7");    //white color
        switch(choice){
            case 1:
                cout << "Enter date then month then year : " << endl;
                cin >> c.d;
                cin >> c.m;
                cin >> c.y;
                
                cout << "Day is : " << c.get_day(c.d, c.m, c.y);

                getch();
                break;
            case 2 :
                cout << ("Enter month and year (MM - YYYY) : ");                
                cin >> c.m;
                cin >> c.y;
                system("cls");
                while(ch!='q'){
                    c.print_month(c.m,c.y,20,5);     
                    
                    ch = getch();
                    if(ch == 'n'){
                    	
                        c.increase_month(&c.m,&c.y);
                        system("cls");
                        c.print_month(c.m,c.y,20,5);
                    }
					else if(ch == 'p'){
                        c.decrease_month(&c.m,&c.y);
                        system("cls");
                        c.print_month(c.m,c.y,20,5);
                    }
                }
                break;
            case 3 :
            	system("color 3F");
            	cout << "Enter Year to print one year calender : " ;
				cin  >> year;
				cout<<endl<<endl;
                printCalendar(year); 
                getch();
                c.ClearColor();
				break;
            case 4 :
                exit(0);
        }
    }
    return 0;
		
		
}
