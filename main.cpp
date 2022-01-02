#include <iostream>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;



class user{
  public :
  char username [20] ;
  int id , seat ;

};

set<int> s;


    void Register(){

    fstream out("user.txt" , ios::out | ios :: app) ;
    user u1;
    char c;
    bool fid = true, fseat = true;
    do{
        cout << "Enter your name : " ;   cin >> u1.username ;
        do{

            cout << "Enter your ID : " ;     cin >> u1.id;
            if(u1.id <= 0){
                cout << "Invalid ID\n";
                fid = false;
            }else{
                fid = true;
            }
        }while(!fid);
        do{
            cout << "Enter your seat (you can choose a seat from to 40000) : " ;   cin >> u1.seat;
            if(u1.seat <= 0 || u1.seat > 40000){
                cout << "invalid seat number\n";
                fseat = false;
            }else if(!s.count(u1.seat)){
                cout << "This seat is booked\n";
                fseat = false;
            }else{
                s.erase(u1.seat);
                fseat = true;
            }
        }while(!fseat);
        out.write((char*) &u1, sizeof(u1));
        cout << "your registration is done\n";
        cout << "Do you want register a new user?(y/n):  ";
        cin >> c;

    }while(c == 'y' || c == 'Y');
    out.close();
}

void read_all_user(){
    fstream input("user.txt") ;
    user u;
    if(input.is_open()){
        input.read((char*) &u, sizeof(u));
        cout << "Name\t\tID\t\tSeat\n";

        while(!input.eof()) {

            cout << u.username << "\t\t" << u.id<< "\t\t" << u.seat<< "\n" ;
            input.read((char*) &u, sizeof(u));
        }

        input.close();
    }else{
         cout << "Cannot open the specified file ....!\n";
    }
}



void searchUser(){

    fstream input("user.txt") ;
    user u;

    if(input.is_open()){
        input.read((char*) &u, sizeof(u));
        bool found = false ;

        cout << "What do you want to search by?\n1. Search by name\n2. Search by ID\n3. Search by seat\nEnter the number of the kind of search you want: ";
        int a; cin>> a;

        switch(a){

            case 1 :

                cout << "Enter name to search it: ";
                char NewName[20]; cin >> NewName;

                while(!input.eof()) {
                    if( strcmp(NewName,u.username) == 0){
                        cout << "Name\t\tID\t\tSeat\n";
                        cout << u.username << "\t\t" <<u.id << "\t\t" << u.seat << "\n" ;
                        found = true ;
                    }
                    input.read((char*) &u, sizeof(u));
                }
                break;


            case 2:

                cout << "Enter ID to search it: ";
                int Id ; cin >> Id;

                while(!input.eof()) {
                    if( Id == u.id){
                        cout << "Name\t\tID\t\tSeat\n";
                        cout << u.username << "\t\t" <<u.id << "\t\t" << u.seat << "\n" ;
                        found = true;
                        break;
                    }
                    input.read((char*) &u, sizeof(u));
                }
                break;
            case 3:

                cout << "Enter seat to search it : ";
                int Seat ; cin >> Seat ;

                while(!input.eof()) {
                    if( Seat == u.seat){
                    cout << "Name\t\tID\t\tSeat\n";
                    cout << u.username << "\t\t" <<u.id << "\t\t" << u.seat << "\n" ;
                    found = true ;
                    }
                    input.read((char*) &u, sizeof(u));
                }
                break;
        }

        if (!found)  cout << "User not found\n";
        input.close();
    }else
         cout << "Cannot open the specified file ....!\n";
}

void deleteUser(){

    fstream input("user.txt") ;
    ofstream output("temp.txt") ;
    user u ;


    cout << "What do you want to delete by?\n1. Delete by name\n2. Delete by ID\n3. Delete by seat\nEnter the number of the kind of delete you want: ";
    int a; cin>> a;

    switch(a){

        case 1 : {
            cout << "Enter name to delete it\n";
            string NewName; cin >> NewName;
            input.read((char*) &u, sizeof(u));
            while(!input.eof()) {
                if(NewName != u.username)
                    output.write((char*) &u, sizeof(u));
                else
                    s.insert(u.seat);
            input.read((char*) &u, sizeof(u));
            }
            input.close();
            output.close();
            remove("user.txt");
            rename("temp.txt" , "user.txt") ;
            break;
        }

        case 2 :

            cout << "Enter Id to delete it\n";
            int __id ; cin >> __id;
            input.read((char*) &u, sizeof(u));
            while(!input.eof()) {
                if( __id != u.id)
                    output.write((char*) &u, sizeof(u));
                else
                    s.insert(u.seat);
                input.read((char*) &u, sizeof(u));
            }
            input.close();
            output.close();
            remove("user.txt");
            rename("temp.txt" , "user.txt") ;
            break;


        case 3 :

            cout << "Enter seat to delete it\n";
            int _seat ; cin >> _seat ;
            input.read((char*) &u, sizeof(u));
            while(!input.eof()) {
                if( _seat != u.seat)
                    output.write((char*) &u, sizeof(u));
                else
                    s.insert(u.seat);
                input.read((char*) &u, sizeof(u));
            }
            input.close();
            output.close();
            remove("user.txt");
            rename("temp.txt" , "user.txt");
            break ;

     }
}

void update (){

    fstream input("user.txt") ;
    user u ;
    if(input.is_open()){
        input.read((char*) &u, sizeof(u));
        bool found = false ;
        cout << "What do you want to update?\n1. update your name\n2. update your ID\n3. Update your seat\n4. Update all the info\nEnter the number of the kind of update you want: ";
        int a; cin>> a;

        switch(a){

            case 1 : {

                cout << "Enter name to update it\n";
                char NewName[20]; cin >> NewName;
                while(!input.eof()) {
                    if( strcmp(NewName ,u.username) == 0) {
                        cout << "Enter the new name for " << u.username << " " ;
                        cin >> u.username ;
                        input.seekp(input.tellg() -  sizeof(u) , ios :: beg);
                        input.write((char*) &u, sizeof(u));
                        cout << u.username << "\t\t" <<u.id << "\t\t" << u.seat << "\n " ;
                        found = true ;
                        break;
                    }
                    input.read((char*) &u, sizeof(u));
                }
            break ;
        }

            case 2 : {

                cout << "Enter ID to update it\n";
                int __id ; cin >> __id;
                while(!input.eof()) {
                    if( __id == u.id){
                        cout << "Enter the new ID for " << u.username << " and ID " << u.id << " : " ;
                        cin >> u.id ;
                        input.seekp(input.tellg() -  sizeof(u) , ios :: beg);
                        input.write((char*) &u, sizeof(u));
                        cout << u.username << "\t\t" <<u.id << "\t\t" << u.seat << "\n " ;
                        found = true ;
                        break;
                    }
                    input.read((char*) &u, sizeof(u));
                }
            break ;
       }

       case 3 : {

            cout << "Enter seat to update it\n";
            int __seat, ss; cin >> __seat ;
            bool fseat;
            while(!input.eof()) {
                if( __seat == u.seat){
                    cout << "Enter the new seat for " << u.username << " and ID " << u.id << " : " ;
                    do{
                        cin >> ss;
                        if(ss <= 0 || ss > 40000){
                            cout << "invalid seat number\n";
                            fseat = false;
                        }else if(!s.count(ss)){
                            cout << "This seat is booked\n";
                            fseat = false;
                        }else{
                            s.erase(ss);
                            s.insert(u.seat);
                            u.seat = ss;
                            fseat = true;
                        }
                    }while(!fseat);
                    input.seekp(input.tellg() -  sizeof(u) , ios :: beg);
                    input.write((char*) &u, sizeof(u));
                    cout << u.username << "\t\t" <<u.id << "\t\t" << u.seat << "\n " ;
                    found = true ;
                    break;
             }
              input.read((char*) &u, sizeof(u));
        }
            break ;
       }
       case 4 : {

            cout << "Enter name to search it\n";
            char NewName[20]; cin >> NewName;
            bool fid,fseat;
            int ss;
            while(!input.eof()) {
                if( strcmp(NewName,u.username) == 0){
                    cout << "Enter the new record for " << u.username << " and ID " << u.id << " and Seat " << u.seat << "\n" ;
                    cin >> u.username;
                     do{
                        cout << "Enter new ID : " ;     cin >> u.id;
                        if(u.id <= 0){
                            cout << "Invalid ID\n";
                            fid = false;
                        }else{
                            fid = true;
                        }
                    }while(!fid);
                    do{
                        cout << "Enter the new seat: ";
                        cin >> ss;
                        if(ss <= 0 || ss > 40000){
                            cout << "invalid seat number\n";
                            fseat = false;
                        }else if(!s.count(ss)){
                            cout << "This seat is booked\n";
                            fseat = false;
                        }else{
                            s.erase(ss);
                            s.insert(u.seat);
                            u.seat = ss;
                            fseat = true;
                        }
                    }while(!fseat);
                    input.seekp(input.tellg() -  sizeof(u) , ios :: beg);
                    input.write((char*) &u, sizeof(u));
                    cout << u.username << "\t\t" <<u.id << "\t\t" << u.seat << "\n " ;
                    found = true;
                    break;
                }
                input.read((char*) &u, sizeof(u));
            }
            break ;
        }
     }

        if (!found)  cout << "NOT Found\n";

    } else
         cout << "Cannot Open The Specified File ....!\n";
    input.close();

}

void deletebooked(){

    fstream input("user.txt") ;
    user u;
    if(input.is_open()){
        input.read((char*) &u, sizeof(u));
        while(!input.eof()) {
            s.erase(u.seat);
            input.read((char*) &u, sizeof(u));
        }
        input.close();
    }
}



int main(){

    for(int i = 1; i <= 40000; i++){
        s.insert(i);
    }
    deletebooked();





    cout << "\n\n\t\t\t\tWelcome to our stadium reservation system\n\n";
    int n;
    char x;
    bool flag;
    do{
        flag = false;
        cout << "Choose which process from the next five you want do:\n1. Book a seat for the next match.\n"
             << "2. Update your data.\n"
             << "3. delete your data.\n"
             << "4. Search for any record you want.\n"
             << "5. Print the booked seats and who booked them data.   ";
        cin >> n;
        if(n == 1)
            Register();
        else if (n == 2)
            update();
        else if (n == 3)
            deleteUser();
        else if (n == 4)
            searchUser();
        else if (n == 5)
            read_all_user();
        else{
            cout << "Invalid answer\n";
            flag = true;
        }
        if(!flag){
            cout << "Do you want to do another process? (y/n) "; cin >> x;
        }

    }while(flag || x == 'y' || x == 'Y');


    cout << "\n\n\tThank you for using our system :)\n\n";
    return 0;
}
