# include <iostream>
# include "HashTable.h"
# include <vector>

using namespace std;



HashTable::HashTable()
{
    for(int i = 0; i< TableSize; i++)
    {
        hashTable[i] = new Movie;
        hashTable[i]->year = NULL;
        hashTable[i]->title = "empty";
        hashTable[i]->next = NULL;
        hashTable[i]->genre = "empty";
    }

}

HashTable::~HashTable()
{
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
    int sum = 0;
    char letter;
    for(int i = 0;i<title.length();i++)
    {
        letter = title[i];
        sum = sum + (int)letter; //ascii value of ith character in the string
    }
    sum = sum % TableSize;
    return sum;
}

void HashTable::insertMovie(string in_title, int year, string in_genre, int in_rating, int in_quantity) // done
{
    bool check = true;
    int sum = hashSum(in_title);
    Movie *m = new Movie(in_title, year, in_genre, in_rating, in_quantity);
    Movie *x = new Movie;
    if(hashTable[sum]->title == "empty")
    {
        hashTable[sum]->title = in_title;
        hashTable[sum]->year = year;
        hashTable[sum]->genre = in_genre;
        hashTable[sum]->rating = in_rating;
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
        m->rating = hashTable[sum]->rating;
        m->quantity = hashTable[sum]->quantity;
        hashTable[sum]->next = m;
        hashTable[sum]->title = in_title;
        hashTable[sum]->year = year;
        hashTable[sum]->genre = in_genre;
        hashTable[sum]->rating = in_rating;
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

Movie* HashTable::findMovie(string title) // done
{
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
        cout<<"Rating: "<<hashTable[index]->rating<<endl;
        cout<<"Quantity: "<<hashTable[index]->quantity<<endl;
        //cout<<index<<":"<<title<<":"<<x->year<<endl
    }
    else if(hashTable[index]->title == "empty")
        cout<<"not found"<<endl;
}

void HashTable::deleteMovie(string in_title) // done
{
    int sum = hashSum(in_title);
    Movie* x = new Movie;
    bool found = true;
    x = hashTable[sum];
    Movie * prev = new Movie;

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
        while(x != NULL)
        {
            prev = x;
            x = x->next;
            if(x->title == in_title)
            {
                prev->next = x->next;
                break;
            }
        }
    }

}

void HashTable::printInventory()
{

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
            cout<<"Rating: "<<hashTable[i]->rating<<endl;
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
                cout<<"Rating: "<<temp->rating<<endl;
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


void HashTable::printOneGenre(string genre)
{
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
                cout<<"Rating: "<<hashTable[i]->rating<<endl;
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
                    cout<<"Rating: "<<temp->rating<<endl;
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

void HashTable::printTopRated()
{
     bool emp = true;
    int counter = 0;
    vector<Movie*> vect;
    int n = 0;
    for(int i = 0; i< TableSize; i++)
    {

        if(hashTable[i]->title != "empty")
        {
            emp = false;
            Movie* temp = hashTable[i]->next;
            temp->rating = hashTable[i]->next->rating;
            if(hashTable[i]->rating <= 10)
            {
                vect.push_back(hashTable[i]);
                counter++;
            }
            while(temp != NULL)
            {
                if(temp->rating <= 10)
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

    sortByRating(vect, vect.size());

    for(int i =0; i< vect.size(); i++)
    {
        Movie* temp = vect[i];
        cout<<"======================"<<endl;
        cout<<"Title: "<<temp->title<<endl;
        cout<<"Rating: "<<temp->rating<<endl;
        cout<<"======================"<<endl;
        cout<<endl;
    }
}

void HashTable::sortByRating(vector<Movie*> vect, int n)
{
    int minIndex;
    Movie* tmp;
    //vector<Movie*> vect2;
    for(int i = 0; i < n -1; i++)
    {
        minIndex = i;
        for(int j = i + 1; j < n; j++)
        {
            if(vect[j]->rating < vect[minIndex]->rating)
                minIndex = j;
        }
        if(minIndex != i)
        {
            //cout<<"in if"<<endl;
            swap(vect[i]->rating, vect[minIndex]->rating);
            swap(vect[i]->title, vect[minIndex]->title);
        }

    }
}
