// Word Search Solver.cpp : Application to solve word searches. requires some clumsy manual input due to c++ array restrictions
//also because I don't know how to use a vector. maybe one day.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Solver class: see constructor for parameters
 * members: wordSearch - string array, size 24 | word - keyword to search for | rowDir & colDir - determine what direction to search in
 * output contained within solve class
 */
class Solver {
private:
    //member variables
    string wordSearch[24];
    string word;
    int rowDir=0, colDir=0; //these two members prevent the recursive algorithm from finding wiggly words

    /* solve function: no paramaters
    * Iterates through 2d array using nested for loops to find first letters.
    * Produces and prints output.
    * Calls on check function
    */
    void solve() {
        bool done = false;
        for (int i = 0; i < wordSearch->size(); i++) {
            for (int j = 0; j < wordSearch[i].size(); j++) {
                done = check(i, j);
                if (done) {
                    string output = "Word found at (" + to_string(i + 1) + "," + to_string(j + 1) + ")."; // plus one to fix index positioning
                    cout << output;
                    return;
                }
            }
        }
        cout << "Word not found";
    }
    /* check function: 2 paramaters - row & col: 2d location of current iteration
     * checks first letter against keyword.
     * calls line function in every possible direction, first checking if the word can fit in each direction
     * returns boolean value of line function
     * NOTE: there's some complicated logic in the if statements in this section. most of it is checking if the word would fit
     * in the boundaries in the direction it wants to check.
     */
    bool check(int row, int col) {
        int depth = 0; // variable to keep track of where in the keyword we are checking.
        bool found = false;
        if (wordSearch[row][col] == word[depth]) {
            if (row >= word.size()) { // checks to the north
                rowDir = -1;
                colDir = 0;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            if (row >= word.size() && col < (wordSearch[row].size() - word.size()) && !found) { // checks to the northeast
                rowDir = -1;
                colDir = 1;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            if (col < (wordSearch[row].size() - word.size()) && !found) { // checks to the east
                rowDir = 0;
                colDir = 1;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            if (row < (wordSearch->size() - word.size()) && col < (wordSearch[row].size() - word.size()) && !found) { // checks to the southeast
                rowDir = 1;
                colDir = 1;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            if (row < (wordSearch->size() - word.size()) && !found) { // checks to the south
                rowDir = 1;
                colDir = 0;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            if (row < (wordSearch->size() - word.size()) && col >= word.size() && !found) { // checks to the southwest
                rowDir = 1;
                colDir = -1;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            if (col >= word.size() && !found) { // checks to the west
                rowDir = 0;
                colDir = -1;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            if (row >= word.size() && col >= word.size() && !found) { // checks to the northwest
                rowDir = -1;
                colDir = -1;
                found = line(row + rowDir, col + colDir, depth + 1); // function call to line
            }
            return found; // return value of repeated line calls to solve function to continue algorithm
        }
        return false; // return false if first letter is not a match
    }

public:
   /* Constructor: 2 parameters - puzzle
    * Accepts input from main, sets member values
    * Calls on solve function
    */
    Solver(string puzzle[], string input) {
        word = input;
        for (int i = 0; i < 24; i++) {
            wordSearch[i] = puzzle[i];
        }
        solve();
    }

   /* line function: 3 parameters - row & col: 2d location of current recursion, depth: point in keyword to search for
    * checks if end of word has been reached. if we have gotten this far without a false return, we have found the word. returns true
    * otherwise, checks next letter, increments depth, and recurs. returns false if letter does not match.
    */
    bool line(int row, int col, int depth) {
        if (depth >= word.size()) {
            return true;
        }
        if (wordSearch[row][col] == word[depth]) {
            return line(row+rowDir, col+colDir, depth+1);
        }
        else {
            return false;
        }

    }

};

int main()
{
    ifstream file;
    try {
        file.open("wordSearch.txt");
    }
    catch (exception E) {
        cout << "exception";
    }
    string wordSearch[24];
    for (int i = 0; getline(file, wordSearch[i]); i++) {}
    file.close();
    string word;
    cout << "What word are you looking for?" << endl;
    getline(cin, word);
    Solver solver(wordSearch, word);
}
