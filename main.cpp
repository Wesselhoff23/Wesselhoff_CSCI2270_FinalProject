# include <iostream>
# include "fstream"
# include "HashTable.h"
//#include <windows.h>


using namespace std;

void PrintMenu()
{
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Insert a movie"<<endl;
    cout<<"2. Delete a movie"<<endl;
    cout<<"3. Search"<<endl;
    cout<<"4. Search by genre"<<endl;
    cout<<"5. Top Ranked"<<endl;
    cout<<"6. Print All Movies"<<endl;
    cout<<"7. Quit"<<endl;
}

int main()
{

    ifstream in;
    in.open("Movies.txt");
    string line;
    HashTable* hashTable = new HashTable;
    while(getline(in, line))
    {
            int index_comma = line.find(",");
            // newItem;
            string number = line.substr(0,index_comma);
            string parts = line.substr(index_comma+1, line.length()-1);
            int index_comma2 = parts.find(",");
            string name = parts.substr(0,index_comma2);
            string parts2 = parts.substr(index_comma2+1, parts.length()-1);
            int index_comma3 = parts2.find(",");
            string year = parts2.substr(0, index_comma3);
            string parts3 = parts2.substr(index_comma3+1, parts2.length()-1);
            int index_comma4 = parts3.find(",");
            string quan = parts3.substr(0, index_comma4);
            string genre = parts3.substr(index_comma4+1, parts3.length()-1);
            int quant = atoi(quan.c_str());
            int numb = atoi(number.c_str());
            int yr = atoi(year.c_str());

            //Movie(name, yr);
            hashTable->insertMovie(name, yr, genre, numb, quant);


    }
    in.close();

    string input;
    while(input != "7")
    {
        PrintMenu();

        getline(cin, input);
        if(input == "1")
        {
            cout<<"Enter title:"<<endl;
            string ins;
            string years;
            string genres;
            string rank;
            string quant;
            getline(cin, ins);
            cout<<"Enter year:"<<endl;
            getline(cin, years);
            cout<<"Enter genre:"<<endl;
            getline(cin, genres);
            cout<<"Enter ranking"<<endl;
            getline(cin, rank);
            cout<<"Enter quantity"<<endl;
            getline(cin, quant);
            int yrs = atoi(years.c_str());
            int ranks = atoi(rank.c_str());
            int quants = atoi(quant.c_str());
            hashTable->insertMovie(ins, yrs, genres, ranks, quants);

        }
        else if(input == "2")
        {
            cout<<"Enter title:"<<endl;
            string del;
            getline(cin, del);
            hashTable->deleteMovie(del);
        }
        else if(input == "3")
        {
            cout<<"Enter title:"<<endl;
            string toFind;
            getline(cin, toFind);
            Movie* found = hashTable->findMovie(toFind);
        }
        else if(input == "4")
        {
            hashTable->printExistingGenres();
            cout<<"Enter genre:"<<endl;
            string gen;
            getline(cin, gen);
            cout<<"======Results======"<<endl;
            cout<<endl;
            hashTable->printOneGenre(gen);
        }
        else if(input == "5")
        {
            hashTable->printTopRanked();

        }
        else if(input == "6")
        {
            hashTable->printInventory();
        }
        else if(input == "7")
        {
            cout<<"Goodbye!"<<endl;
        }
    }

}
