#ifndef HASHTABLE_H
#define HASHTABLE_H
# include <vector>

struct Movie{
    std::string title;
    std::string genre;
    int year;
    int ranking;
    int quantity;
    Movie *next;
    //Movie *previous;

    Movie()
    {
        title = "empty";
        year = NULL;
        genre = "empty";
        next = NULL;
        ranking = NULL;
        quantity = NULL;
    };

    Movie(std::string in_title, int in_year, std::string in_genre, int in_ranking, int in_quantity)
    {
        title = in_title;
        year = in_year;
        genre = in_genre;
        ranking = in_ranking;
        quantity = in_quantity;

    }

};

class HashTable
{
    public:
        HashTable();
        ~HashTable();
        void insertMovie(std::string in_title, int year, std::string in_genre, int in_ranking, int in_quantity);
        Movie* findMovie(std::string in_title);
        void deleteMovie(std::string in_title);
        void printInventory();
        int hashSum(std::string title);
        void printOneGenre(std::string genre);
        void printTopRanked();
        void sortByRanking(std::vector<Movie*> vect, int n);
        void genreCheck(std::string);
        void printExistingGenres();
    protected:
    private:
        static const int TableSize = 10;
        Movie *hashTable[TableSize];
        int moviesDeleted;
        std::vector<std::string> genreTable;
        //Movie *topRankedHash[10];


};

#endif // HASHTABLE_H
