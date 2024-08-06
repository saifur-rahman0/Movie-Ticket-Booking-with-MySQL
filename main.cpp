#include<iostream>
#include<sstream>
#include<string>
#include<windows.h>
#include<cstdlib>
#include<conio.h>

#include "InterectToDB.h"

using namespace std;
using namespace Database;


void welcome();
void bookTicket();
void showMyTicket();
void availableSeats();
void addNewMovie();
void editMovieDeatails();
void deleteMovie();
void showMovieList();

void exitMenu(string fun_point, int again_ack_p);
void exitProgram();

bool terminator;

int main()
{
    system("title Movie Ticket Booking System");
    system("color FD");

    Database::Response_db r;
    terminator= r.connectDatabase();

    while(terminator)
    {
        system("cls");
        welcome();
        int menu;

        cout << "1. Show Movie List" << endl;
        cout << "2. Available Seats" << endl;
        cout << "3. Book Ticket" << endl;
        cout << "4. Show My Ticket" << endl;
        cout << "5. Add New Movie" << endl;
        cout << "6. Edit Movie Details" << endl;
        cout << "7. Delete Movie" << endl;
        cout << "0. Exit" << endl;
        cout << "\nChoose any option: "<< endl;

        cin >> menu;
        switch(menu)
        {
        case 1:
            showMovieList();
            break;

        case 2:
            availableSeats();
            break;

        case 3:
            bookTicket();
            break;

        case 4:
            system("cls");
            showMyTicket();
            break;

        case 5:
            addNewMovie();
            break;

        case 6:
            editMovieDeatails();
            break;

        case 7:
            deleteMovie();
            break;

        case 0:
            exitProgram();
            break;

        default:
            cout << "Please choose between 1 - 7. Press Enter To Continue...";
            getch();
            system("cls");
            main();
            break;

        }
    }
}

void welcome() {
    cout << "\t\t\t\tMovie Ticket Booking System" << endl << endl;
    cout << "Menu:" << endl;
}

void bookTicket()
{
    system("cls");
    int again_ack_point= 1;

    cout << "\t\t\t\t\tBooking Ticket" << endl;

    string c_name = "";
    string c_phone = "";
    string c_seat = "";
    string getId = "";
    float totalPrice = 0.0;
    bool itemFalse = false;

    string query= "";
    string storeId[5000];
    string storeid = "";
    string storename = "";
    string storegenre = "";
    string storeformat = "";
    string storeshowDate = "";
    string storeshowTime = "";
    string storeticketPrice = "";
    string storeseat = "";
    int storeIndex = 0, storeIndexN = 0;
    MYSQL_RES* res;
    MYSQL_ROW row;
    bool exitcode;

    query= "select * from movie_tb";
    res = Database::execute_query(query);
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-15s | %-7s | %-15s | %-15s | %-10s | %-5s |\n", "Column Id", "Name", "Format", "Show Date", "Show Time", "Price", "Seat");
    while ((row = mysql_fetch_row(res)))
    {

        if (atoi(row[7]) > 0)
        {
            printf("| %-10s | %-15s | %-7s | %-15s | %-15s | %-10s | %-5s |\n", row[0], row[1], row[3], row[4], row[5], row[6], row[7]);
            storeId[storeIndex] = row[0];
            storeIndex++;
        }

    }
    printf("---------------------------------------------------------------------------------------------------\n");

    itemFalse = true;
    for (;;)
    {
        cout << "\nEnter a Movie ID's (q to quite booking): ";
        cin >> getId;

        if (getId == "q") {
            exitcode = true;
            break;
        }

        for(int i = 0; i < storeIndex; i++)
        {
            if (getId == storeId[i])
            {
                itemFalse = false;
                break;
            }
        }
        if (itemFalse)
        {
            cout << "Enter a valid number." << endl;
            itemFalse = true;
        }
        else
        {
            break;
        }
    }

    if (!exitcode)
    {
        cout << "Enter Customer Name: ";
        cin >> c_name;
        cout << "Enter Customer Phone: ";
        cin >> c_phone;
        cout << "Book Seat: ";
        cin >> c_seat;

        query= "select * from movie_tb where m_id = '"+getId+"'";
        res = Database::execute_query(query);
        printf("--------------------------------------------------------------------\n");
        printf("| %-10s | %-15s | %-15s | %-15s |\n", "Column Id", "Name", "Format", "Price");
        while ((row = mysql_fetch_row(res)))
        {
            if (atoi(row[7]) > 0)
            {
                printf("| %-10s | %-15s | %-15s | %-15s |\n", row[0], row[1], row[3], row[6]);
                storeid = row[0];
                storename = row[1];
                storegenre = row[2];
                storeformat = row[3];
                storeshowDate = row[4];
                storeshowTime = row[5];
                storeticketPrice = row[6];
                storeseat = row[7];
            }

        }
        printf("--------------------------------------------------------------------\n");

        query= "update movie_tb set m_seat = m_seat - '"+c_seat+"' where m_id = '" +getId+ "'";
        Database::pushOnlyQueryWithoutMSG(query);

        totalPrice = strtof((storeticketPrice).c_str(), 0) * strtof((c_seat).c_str(), 0);
        string tPrice = to_string(totalPrice);

        query= "insert into customer_tb (name, phone, movie, format, seat, price, showdate, showtime) values ('"+c_name+"','"+c_phone+"','"+storename+"', '"+storeformat+"', '"+c_seat+"', '"+tPrice+"', '"+storeshowDate+"', '"+storeshowTime+"')";
        Database::pushOnlyQuery(query, "Purchase Successfully Done.", "Query Execution Problem! ");
        cout << "Total Price: " << totalPrice << endl;
    }


    exitMenu("bookTicket", again_ack_point);
}

void showMyTicket()
{

    int again_ack_p= 0;

    cout << "\t\t\tShow My Tickets" << endl;

    int c= 0;
    string input;
    MYSQL_RES* res;
    MYSQL_ROW row;
    string query= "";

    cin.ignore(1, '\n');
    cout << "Enter Your Id Or Name: ";
    getline(cin, input);

    query= "select * from  customer_tb where id = '"+input+"' or name = '"+input+"'";
    res= Database::execute_query(query);
    cout << endl;

    while ((row = mysql_fetch_row(res)))
    {
        cout << "ID: " << row[0] << "\nName: " << row[1] << "\nPhone: " << row[2] << "\nMovie: " << row[3] << "\nFormat: " << row[4] << "\nSeat: " << row[5] << "\nPrice: " << row[6] << "\nShow Date: " << row[7] << "\nShow Time: " << row[8] << endl << endl;
        c++;
    }

    if (c == 0)
    {
        cout << "No ticket with this input" << endl;
    }

    exitMenu("showMyTicket", again_ack_p);
}

void availableSeats()
{
    system("cls");
    int again_ack_p = 1;

    MYSQL_RES* res;
    MYSQL_ROW row;

    cout << "\t\tAvailable Seats" <<endl;

    string query= "select * from  movie_tb";

    res= Database::execute_query(query);
    printf("-------------------------------------\n");
    printf("| %-15s | %-15s |\n", "Name", "Seat");
    while ((row = mysql_fetch_row(res)))
    {
        printf("| %-15s | %-15s |\n", row[1], row[7]);
    }
    printf("-------------------------------------\n");

    exitMenu("availableSeats", again_ack_p);
}


void addNewMovie()
{
    system("cls");
    int again_ack_p=0;
    string name = "";
    string genre = "";
    string format = "";
    string showDate = "";
    string showTime = "";
    string ticketPrice = "";
    string seat = "";

    cout << "\t\t\tAdd New Movie" << endl;

    cin.ignore(1, '\n');
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Genre: ";
    getline(cin, genre);
    cout << "Enter format: ";
    getline(cin, format);
    cout << "Enter Show Date (dd-mm-yyyy): ";
    getline(cin, showDate);
    cout << "Enter Show Time: ";
    getline(cin, showTime);
    cout << "Enter Ticket Price: ";
    getline(cin, ticketPrice);
    cout << "Enter Seat: ";
    getline(cin, seat);

    string query = "insert into movie_tb (m_name, m_genre, m_format, m_showdate, m_showtime, m_ticketprice, m_seat) values ('"+name+"','"+genre+"','"+format+"',STR_TO_DATE('"+showDate+"', '%d-%m-%Y'),'"+showTime+"','"+ticketPrice+"', '"+seat+"')";
    Database::pushOnlyQuery(query, "Successfully added in database.", "Query Execution Problem!");

    exitMenu("addNewMovie", again_ack_p);

}

void editMovieDeatails()
{
    system("cls");
    int again_ack_p= 0;

    string name = "";
    string genre = "";
    string format = "";
    string showDate = "";
    string showTime = "";
    string ticketPrice = "";
    string seat = "";
    string items[5000];
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    string storeid = "";
    string storename = "";
    string storegenre = "";
    string storeformat = "";
    string storeshowDate = "";
    string storeshowTime = "";
    string storeticketPrice = "";
    string storeseat = "";

    MYSQL_RES* res;
    MYSQL_ROW row;
    string query;

    cout << "\t Edit Movie Details" << endl;

    query= "select m_id, m_name from movie_tb";
    res= Database::execute_query(query);
    printf("-------------------------------------\n");
    printf("| %-10s | %-20s |\n", "Column Id", "Name");
    while ((row = mysql_fetch_row(res)))
    {
        printf("| %-10s | %-20s |\n", row[0], row[1]);
        items[indexForId] = row[0];
        indexForId++;
    }
    printf("-------------------------------------\n");

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        exitMenu("editMovieDeatails", again_ack_p);
    }

    if (HaveException == false)
    {
        string strID = to_string(itemId);

        for (int i = 0; i < indexForId; i++)
        {
            if (strID != items[i])
            {
                NotInDatabase = true;
            }
            else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            query= "select * from movie_tb where m_id = '"+strID+"'";
            res= Database::execute_query(query);
            while (row = mysql_fetch_row(res))
            {
                cout << "Column ID: " << row[0] <<
                "\nName: "<< row[1] <<
                "\nGenre: " << row[2] <<
                "\nFormat: " << row[3] <<
                "\nShow Date: " << row[4] <<
                "\nShow Time: " << row[5] <<
                "\nTicket Price: " << row[6] <<
                "\nSeat: " << row[7] << endl << endl;

                storeid = row[0];
                storename = row[1];
                storegenre = row[2];
                storeformat = row[3];
                storeshowDate = row[4];
                storeshowTime = row[5];
                storeticketPrice = row[6];
                storeseat = row[7];
            }

            cin.ignore(1, '\n');
            string defaultString = "xN";
            cout << "Enter Name (" << defaultString << "  to not change): ";
            getline(cin, name);
            if (name == defaultString)
            {
                name = storename;
            }
            cout << "Enter Genre (" << defaultString << "  to not change): ";
            getline(cin, genre);
            if (genre == defaultString)
            {
                genre = storegenre;
            }
            cout << "Enter Format (" << defaultString << "  to not change): ";
            getline(cin, format);
            if (format == defaultString)
            {
                format = storeformat;
            }
            cout << "Enter Show Date (" << defaultString << "  to not change): ";
            getline(cin, showDate);
            if (showDate == defaultString)
            {
                showDate = storeshowDate;
            }
            cout << "Enter Show Time (" << defaultString << "  to not change): ";
            getline(cin, showTime);
            if (showTime == defaultString)
            {
                showTime = storeshowTime;
            }
            cout << "Enter Ticket Price (" << defaultString << "  to not change): ";
            cin >> ticketPrice;
            if (ticketPrice == defaultString)
            {
                ticketPrice = storeticketPrice;
            }
            cout << "Enter Seat (" << defaultString << "  to not change): ";
            cin >> storeseat;
            if (seat == defaultString)
            {
                seat = storeseat;
            }

            query= "update movie_tb set m_name = '"+name+"', m_genre = '"+genre+"', m_format = '"+format+"', m_showdate = '"+showDate+"', m_showtime = '"+showTime+"', m_ticketprice = '"+ticketPrice+"', m_seat = '"+seat+"' where m_id = '"+strID+"'";
            Database::pushOnlyQuery(query, "Successfully Saved In Database.", "Failed To Update!" );

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }

    }

    exitMenu("editMovieDeatails", again_ack_p);
}

void deleteMovie()
{
    system("cls");
    int again_ack_p= 0;

    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    MYSQL_RES* res;
    MYSQL_ROW row;

    cout << "\t\t\tDelete Movie" << endl;

    res = Database::execute_query("select * from movie_tb");

    printf("-------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-15s |\n", "Column Id", "Name", "Price");
    printf("-------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res)))
    {
        printf("| %-10s | %-20s | %-15s |\n", row[0], row[1], row[6]);
        items[indexForId] = row[0];
        indexForId++;
    }
    printf("-------------------------------------------------------\n");

    if(indexForId<1)
    {
        cout << "There no movie items. Please insert first.\n" << endl;
        goto ExitMenu;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }
            else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string query = "delete from movie_tb where m_id = '"+strid+"'";
            Database::pushOnlyQuery(query,"Successfully Deleted.", "Failed To Delete!");
        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }
    ExitMenu:
    exitMenu("deleteMovie", again_ack_p);
}

void showMovieList()
{
    system("cls");
    int again_ack_p=1;

    cout << "\t\t\t\t\t\tMovie List" << endl;

    MYSQL_RES* res;
    res= Database::execute_query("select * from movie_tb");

    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Name", "Genre", "Format", "Show Date", "Show Time", "Price");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)))
    {
        printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
    }
    printf("-------------------------------------------------------------------------------------------------------------\n");

    exitMenu("ShowMovieList", again_ack_p);

}

void exitMenu(string fun_point, int again_ack_p)
    {
    chooseAgain:
        char choose;
        if(again_ack_p == 0)
        {
            cout << "\nPress 'm/M' to Menu and 'a/A' to Again and 'e/E' to exit: ";
            cin >> choose;
            if (choose == 'm' || choose == 'M')
            {
                main();
            }
            else if (choose == 'a' || choose == 'A')
            {
                if(fun_point == "addNewMovie")
                {
                    addNewMovie();
                }
                else if(fun_point == "ShowMovieList")
                {
                    showMovieList();
                }
                else if(fun_point == "deleteMovie")
                {
                    deleteMovie();
                }
    //            else if(fun_point == "checkSeat")
    //            {
    //                checkSeat();
    //            }
                else if(fun_point == "editMovieDeatails")
                {
                    editMovieDeatails();
                }
                else if(fun_point == "showMyTicket")
                {
                    showMyTicket();
                }
            }
            else if(choose == 'e' || choose == 'E')
            {
                exitProgram();
            }
            else
            {
                cout << "\nNext time to choose after clearly read the corresponding line.\n" << endl;
                goto chooseAgain;
            }
        }
        else
        {
        chooseAgain_:
                cout << "\nPress 'm/M' to Menu and 'e/E' to Exit: ";
                cin >> choose;
                if (choose == 'm' || choose == 'M')
                {
                    main();
                }
                else if(choose == 'e' || choose == 'E')
                {
                    exitProgram();
                }
                else
                {
                    cout << "\nNext time to choose after clearly read the corresponding line.\n" << endl;
                    goto chooseAgain_;
                }
        }
    }

    void exitProgram()
    {
    ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        char permission;
        cin >> permission;
        if (permission == 'y' || permission == 'Y')
        {
            terminator= false;
        }
        else if (permission == 'n' || permission == 'N')
        {
            system("cls");
            main();
        }
        else
        {
            cout << "\nNext time to choose after clearly read the corresponding line.\n" << endl;
            goto ExitProgram;
        }
    }
