#include<iostream>
#include<mysql.h>
#include<sstream>
#include<string>

using namespace std;

MYSQL* conn;

namespace Database
{
    class Response_db{
    public:
        bool connectDatabase()
        {
            const char* hostname= "localhost";
            const char* username= "root";
            const char* password= "";
            const char* database = "movieticketbooking_db";
            unsigned int port = 3306;
            const char* unixsocket = NULL;
            unsigned long clientflag = 0;

            conn = mysql_init(NULL);
            if (mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag))
            {
                cout<<"connected to database" << endl;
                return true;
            }
            else
            {
                cout<<"Fai1ed to connect to database" <<endl;
                return false;
            }
        }
    };

    void pushOnlyQueryWithoutMSG(string query)
    {
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
    }

    void pushOnlyQuery(string query, string suc_msg, string error_msg)
    {
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "\n" << suc_msg << endl <<endl;
        }
        else
        {
            cout << error_msg << ": " << mysql_errno(conn) << endl;
        }
    }


    MYSQL_RES* execute_query(string query)
    {
        MYSQL_RES* res;
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
        if(!qstate)
        {
            res= mysql_store_result(conn);
            return res;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
    }
}

