# include <iostream>
# include "HashTable.h"
# include <vector>

using namespace std;



HashTable::HashTable()
{
     /*
-    Prototype: Hashtable::HashTable();
-    Description: This is the constructor method for the HashTable. It sets all the items in the hashtable to NULL or "empty"
-    How to Call: this method is called when the class is created
-    pre-conditions: none
-    post-conditions: none
-    */
    for(int i = 0; i< TableSize; i++)
    {
        hashTable[i] = new Movie;
        hashTable[i]->year = 0;
        hashTable[i]->title = "empty";
        hashTable[i]->next = NULL;
        hashTable[i]->genre = "empty";
        moviesDeleted = 0;
    }
}

HashTable::~HashTable()
{
     /*
-    Prototype:Thashtable:: ~HashTable();
-    Description: This is the destructor
-    How to Call: N/A
-    pre-conditions: Must have a hashtable built
-    post-conditions:every hash value of the hashtable will be deleted from the table
-    */
    for(int i = 0; i< TableSize; i++)
    {
        Movie* temp = hashTable[i]->next;
        deleteMovie(hashTable[i]->title);
        while(temp != NULL)
        {
            deleteMovie(temp->title);
        }
    }
}

int HashTable::hashSum(string title)
{
     /*
-    Prototype: int Hashtable::hashSum(string);
-    Description: Will take the titles of each movie and convert them into a hash value, then insert them into the hashtable based on that value
-    Example: HashTable ht;
              ht.hashSum("Shawshank Redemption");
-    pre-conditions: must have a text file or movie name to input into the function
-    post-conditions: will take the title as an input and insert it into the hashtable based on it's hash value
-    */
    int sum = 0;
    char letter;
    for(unsigned int i = 0;i<title.length();i++)
    {
        letter = title[i];
        sum = sum + (int)letter; //ascii value of ith character in the string
    }
    sum = sum % TableSize;
    return sum;
}

void HashTable::genreCheck(string genre)
{
    /*Function to check if the genre already exists in the vector of genres and if it doesnt it inserts the genre*/
    bool inTable = false;
    for(vector<string>::iterator it = genreTable.begin(); it != genreTable.end(); ++it){
        if(*it == genre){
            inTable = true;
            break;
        }
    }
    if(!inTable)
        genreTable.push_back(genre);
}

void HashTable::insertMovie(string in_title, int year, string in_genre, int in_ranking, int in_quantity) // done
{
     /*
-    Prototype: void Hashtable::insertMovie(string, int, string, int, int);
-    Description: This method is used to create the hashTable and insert values into the already created table. It also sorts the nodes in the linked lists.
-    Example: HashTable ht;
              ht.insertMovie("Ted", 2014, Comedy, 1, 100,000,000)
-    pre-conditions: insertMovie(string, int, string, int, int), takes in only this order.
-    post-conditions: inserts the newly created node into the hashtable in the proper place
-    */
    bool check = true;
    int sum = hashSum(in_title);
    Movie *m = new Movie(in_title, year, in_genre, in_ranking, in_quantity);
    Movie *x = new Movie;

    //check if genre already exists and if not insert it into the table
    genreCheck(in_genre);

    if(hashTable[sum]->title == "empty")
    {
        hashTable[sum]->title = in_title;
        hashTable[sum]->year = year;
        hashTable[sum]->genre = in_genre;
        hashTable[sum]->ranking = in_ranking;
        hashTable[sum]->quantity = in_quantity;
        hashTable[sum]->next = NULL;
        check = false;

    }

    else if(hashTable[sum]->title.compare(in_title) > 0)

    {
        m->title = hashTable[sum]->title;
        m->year = hashTable[sum]->year;
        m->next = hashTable[sum]->next;
        m->genre = hashTable[sum]->genre;
        m->ranking = hashTable[sum]->ranking;
        m->quantity = hashTable[sum]->quantity;
        hashTable[sum]->next = m;
        hashTable[sum]->title = in_title;
        hashTable[sum]->year = year;
        hashTable[sum]->genre = in_genre;
        hashTable[sum]->ranking = in_ranking;
        hashTable[sum]->quantity = in_quantity;
        check = false;

    }
    x = hashTable[sum];
    Movie *temp = new Movie();
    while(check == true)
    {
		if(x->next == NULL)
		{
			x->next = m;
            m->next = NULL;
			check = false;
		}
		else{
            temp=x;
            x=x->next;
            //cout<<x->title<<"comparing with"<<in_title<<endl;
                if(x->title.compare(in_title) > 0) // x->title > in_title
                {
                    //cout<<"in if"<<endl;
                    m->next = x;
                    temp->next = m;
                    //x->next = NULL;
                    check = false;
                }
		}
	}
}

void HashTable::findMovie(string title) // done
{
     /*
-    Prototype: Movie* Hashtable::findMovie(string);
-    Description: This method finds the hashsum for the input string, and searches through the linked list for the hashsum value and
     if the value is found, it returns the key info
-    Example: HashTable ht;
	      ht.findMovie("Ted")
-    pre-conditions: takes only  string as  parameter
-    post-conditions: returns the key associated with the string
-    */
    int index = hashSum(title);
    Movie *x = new Movie;
    bool found = true;
    x = hashTable[index];
    while(x->title != title)
    {
        if(x->next != NULL)
            x = x->next;
        else{
            cout<<"not found"<<endl;
            found = false;
            break;
        }
    }
    if((found == true) && (hashTable[index]->title != "empty"))
    {
        cout<<endl;
        cout<<"Title: "<<hashTable[index]->title<<endl;
        cout<<"Year: "<<hashTable[index]->year<<endl;
        cout<<"Genre: "<<hashTable[index]->genre<<endl;
        cout<<"Ranking: "<<hashTable[index]->ranking<<endl;
        cout<<"Quantity: "<<hashTable[index]->quantity<<endl;
        //cout<<index<<":"<<title<<":"<<x->year<<endl
    }
    else if(hashTable[index]->title == "empty")
        cout<<"not found"<<endl;
}

void HashTable::deleteMovie(string in_title) // done
{
     /*
-    Prototype: void Hashtable::deleteMovie(string);
-    Description:This method finds the hashsum for the input string, and searches through the linked list for the hashsum value and
     if the value is found, it deletes the key info
-    Example: HashTable ht;
	      ht.deleteMovie("Ted")
-    pre-conditions: Takes in the desired string to delete in the created hashtable
-    post-conditions: Deletes the selected node and frees up that section of the memory
-    */
    int sum = hashSum(in_title);
    Movie* x = new Movie;
	x = hashTable[sum];
    moviesDeleted++;
    if((in_title == x->title) && (x->next != NULL))
    {
        hashTable[sum] = x->next;
    }
    else if(in_title == x->title)
    {
        hashTable[sum]->title = "empty";
    }
    else
    {
		Movie* prev = new Movie;
        while(x != NULL)
        {
            prev = x;
            x = x->next;
            if(x->title == in_title)
            {
                prev->next = x->next;
                delete x;
                break;
            }
        }
		delete prev;
    }
}

void HashTable::printInventory()
{
     /*
-    Prototype: void Hashtable::printInventory()
-    Description:prints all the movies in the hashtable
-    Example:HashTable ht;
	     ht.printInventory()
-    pre-conditions:already has a created hashtable
-    post-conditions:will print out every node of the hashtable
-    */
    bool emp = true;
    int counter = 0;
    int counter2 = 0;
    for(int i = 0; i< TableSize; i++)
    {

        if(hashTable[i]->title != "empty")
        {
            emp = false;
            Movie* temp = hashTable[i]->next;
            cout<<"======================"<<endl;
            cout<<"Title: "<<hashTable[i]->title<<endl;
            cout<<"Year: "<<hashTable[i]->year<<endl;
            cout<<"Genre: "<<hashTable[i]->genre<<endl;
            cout<<"Ranking: "<<hashTable[i]->ranking<<endl;
            cout<<"Quantity: "<<hashTable[i]->quantity<<endl;
            cout<<"======================"<<endl;
            cout<<endl;
            counter2++;
            //cout<<hashTable[i]->next->next->title<<" "<<hashTable[i]->next->next->genre<<endl;
            while(temp != NULL)
            {
                cout<<"======================"<<endl;
                cout<<"Title: "<<temp->title<<endl;
                cout<<"Year: "<<temp->year<<endl;
                cout<<"Genre: "<<temp->genre<<endl;
                cout<<"Ranking: "<<temp->ranking<<endl;
                cout<<"Quantity: "<<temp->quantity<<endl;
                cout<<"======================"<<endl;
                cout<<endl;
                temp = temp->next;
                counter++;
            }

        }
    }
    //cout<<(counter+counter2)<<endl;
    if(emp == true)
        cout<<"empty"<<endl;
}

void HashTable::printExistingGenres()
{
    cout<<"Existing genres are: ";
    for(vector<string>::iterator it = genreTable.begin(); it != genreTable.end(); ++it)
        cout<<*it<<", ";
    cout<<endl;
}
void HashTable::printOneGenre(string genre)
{
     /*
-    Prototype: void Hashtable::printOneGenre(string genre)
-    Description:Prints only selected movies of the desired genre
-    Example: HashTable ht;
	     ht.PrintOneGenre("Action")
-    pre-conditions:hashtable with movies that have genres, parameter of desired genre
-    post-conditions: Will print out movies of the desired genre
-    */
    bool emp = true;
    int counter = 0;
    for(int i = 0; i< TableSize; i++)
    {
        if(hashTable[i]->title != "empty")
        {
            emp = false;
            Movie* temp = hashTable[i]->next;
            if(hashTable[i]->genre == genre)
            {
                //emp = false;
                cout<<"======================"<<endl;
                cout<<"Title: "<<hashTable[i]->title<<endl;
                cout<<"Year: "<<hashTable[i]->year<<endl;
                cout<<"Genre: "<<hashTable[i]->genre<<endl;
                cout<<"Ranking: "<<hashTable[i]->ranking<<endl;
                cout<<"Quantity: "<<hashTable[i]->quantity<<endl;
                cout<<"======================"<<endl;
                cout<<endl;
                counter++;
            }
            while(temp != NULL)
            {
                if(temp->genre == genre)
                {
                    cout<<"======================"<<endl;
                    cout<<"Title: "<<temp->title<<endl;
                    cout<<"Year: "<<temp->year<<endl;
                    cout<<"Genre: "<<temp->genre<<endl;
                    cout<<"Ranking: "<<temp->ranking<<endl;
                    cout<<"Quantity: "<<temp->quantity<<endl;
                    cout<<"======================"<<endl;
                    cout<<endl;
                    counter++;
                }
                temp = temp->next;
            }
        }
    }
    if(counter == 0)
        cout<<"Genre not found!"<<endl;
    if(emp == true)
        cout<<"empty"<<endl;
}

void HashTable::printTopRanked()
{
     /*
-    Prototype: void Hashtable::printTopRanked()
-    Description:will print out the top 10 ranked movies in the hashtable
-    Example: HashTable ht;
	      ht.printTopRanked()
-    pre-conditions: created hash table with movies that have been ranked
-    post-conditions: wll print out the top 10 ranked movies in the hashtable
-    */
     bool emp = true;
    int counter = 0;
    vector<Movie*> vect;
    for(int i = 0; i< TableSize; i++)
    {

        if(hashTable[i]->title != "empty")
        {
            emp = false;
            Movie* temp = hashTable[i]->next;

            temp->ranking = hashTable[i]->next->ranking;
            if(hashTable[i]->ranking <= 10)
            {
                vect.push_back(hashTable[i]);
                counter++;
            }
            while(temp != NULL)
            {
                if(temp->ranking <= 10 + moviesDeleted)
                {
                    vect.push_back(temp);

                    counter++;
                }
                temp = temp->next;
            }

        }
    }
    //cout<<counter<<endl;
    cout<<endl;
    if(emp == true)
        cout<<"empty"<<endl;

    sortByRanking(vect, vect.size());

    for(int i =0; i < 10; i++)
    {
        Movie* temp = vect[i];
        cout<<"======================"<<endl;
        cout<<"Title: "<<temp->title<<endl;
        cout<<"Ranking: "<<temp->ranking<<endl;
        cout<<"======================"<<endl;
        cout<<endl;
    }
}

void HashTable::sortByRanking(vector<Movie*> vect, int n)
{

     /*Prototype: void Hashtable::sortByRanking(vector<Movie*> vect, int n)
-    Description: Takes in a vector containing the top 10 movies and will sort them into 1-10
-    Example: sortByRanking(<vector>, int)
-    pre-conditions: Called in the printtopRanked function
-    post-conditions: sorts vector into numerical order
-    */
    int minIndex;
    //vector<Movie*> vect2;
    for(int i = 0; i < n -1; i++)
    {
        minIndex = i;
        for(int j = i + 1; j < n; j++)
        {
            if(vect[j]->ranking < vect[minIndex]->ranking)
                minIndex = j;
        }
        if(minIndex != i)
        {
            //cout<<"in if"<<endl;
            swap(vect[i]->ranking, vect[minIndex]->ranking);
            swap(vect[i]->title, vect[minIndex]->title);
        }

    }
}
