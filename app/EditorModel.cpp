// EditorModel.cpp
//
// ICS 45C Fall 2019
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"

EditorModel::EditorModel()
{
    currLine = 1;
    currCol = 1;
    numLine = 1;
    errorMsg = "";
    //will run into seg fault at line func otherwise
    lines.push_back(""); 
}

int EditorModel::cursorLine() const
{
    return currLine;
}

int EditorModel::cursorColumn() const
{
    return currCol;
}

int EditorModel::lineCount() const
{
    return numLine;
}

void EditorModel::setCursorLine(int line)
{
	currLine = line; //Set cursor y-coordinate
}

void EditorModel::setCursorCol(int col)
{ 
	currCol = col; //Set cursor x-coordinate
}

void EditorModel::setLineCount(int count)
{
	numLine = count; //Set current max number of lines
}

const std::string& EditorModel::line(int lineNumber) const
{
    return lines.at(lineNumber - 1);
}

const std::string& EditorModel::currentErrorMessage() const
{
    return errorMsg;
}

void EditorModel::setErrorMessage(const std::string& errorMessage)
{
    errorMsg = errorMessage;
}

void EditorModel::clearErrorMessage()
{
    errorMsg = "";
}


void EditorModel::moveCol(int col) {

    if (col > line(currLine).size() + 1) {
        if (currLine + 1 > lineCount()) {
            throw EditorException("Already at beginning");
        }
        currLine++;
        currCol = 1;
    }
    else if (col < 1) {
        if (currLine == 1) {
            throw EditorException("Already at end");
        }
        currLine--;
        currCol = line(currLine).size() + 1;
    }
    else {
        currCol = col;
    }

}

void EditorModel::insertChar(char x) {
    //vector . at gives a string then . insert
    //we need a iterator for insert because the signature is
    //iterator insert (const_iterator p, char c);
    //Inserts additional characters into the string right before the character indicated by pos (or p):
    //using .begin we get Returns an iterator pointing to the first character of the string.
    //currLine - 1 because vector goes from 0, 1, 2, ...etc so 0 is actually line 1
    //Inserts a character where the cursor is currently positioned.
    lines.at(currLine - 1).insert(lines.at(currLine - 1).begin() + currCol - 1, x);
    //update the current column we are at after inserting the character
    currCol++;
}

void EditorModel::backSpace() {

    prevLineCountBS = numLine;
    prevColDL = currCol;
    prevLineDL = currLine;
    
    //If the cursor is 
    //already in column 1, the entire current line of text is instead 
    //moved to the end of the previous line and the cursor is placed 
    //at the beginning of that moved text. 
    if (currCol == 1) {
        //If the cursor is already 
        //on line 1 column 1, this command fails and an error message is 
        //displayed.
        if (currLine == 1) {
            throw EditorException("Already at end");
        }
        else {

            //don't need
            // prevCharBS = lines.at(currLine - 1).at(currCol - 1 - 1);

            //the line before currLine - 1 gets appended the line currLine - 1
            lines.at(currLine - 1 - 1) += lines.at(currLine - 1);
            lines.at(currLine - 1) = "";
            
            //update vals
            //cursor is placed 
            //at the beginning of that moved text. 
            currCol = lines.at(currLine - 1 - 1).size() + 1;
            numLine--;
            currLine--;

        }
    }
    //Deletes the character to the left of the current cursor position, 
    //sliding subsqeuent characters backward to fill the empty space. 
    //Moves the cursor one character to the left. 
    else {
        
        prevCharBS = lines.at(currLine - 1).at(currCol - 1 - 1);

        //lines . at gets string . erase on string
        //string . erase
        //iterator erase (const_iterator p);
        //Erases the character pointed by p.
        //Deletes the character to the left of the current cursor position, 
        //which is (currCol - 1) - 1
        lines.at(currLine - 1).erase(lines.at(currLine - 1).begin() + (currCol - 1) - 1);
        currCol--;
    }
}

char EditorModel::prevChar() {
    return prevCharBS;
}

void EditorModel::deleteLine() {

    //update prevLine, prevRow, prevCol for undo
    prevLineDL = lines.at(currLine - 1);
    prevColDL = currCol;
    prevRowDL = currLine;

    //special case
    if (currLine == 1) {
        //lines.erase(lines.begin());
        //lines.push_back("");

        lines.at(0) = "";
        //(In other words, the editor must always have at least 
        //one line of text, even if it's empty.)
        
    }
    else {
        //.erase()
        //Removes from the vector either a single element (position) 
        //or a range of elements ([first,last)).
            //Member types iterator and const_iterator
        lines.erase(lines.begin() + currLine - 1);
        //lines vector should be updated to a smaller size, shifted
    }
    //the cursor remains in its current location unless 
    //the cursor would be beyond the end of 
    //the line of text that now occupies the cursor's line number, 
    //in which case the cursor is placed just beyond the end of that 
    //line of text instead. 
    
    if (currLine == 1) {
        currCol = 1;
        //return;
    }
    //since currLine is now representing a diff line bc vec shrink
    //unless currLine == numLine
    else if (currCol > line(currLine - 1).size()) {
        //If there is only one line of text, it is 
        //cleared and the cursor is placed at line 1 column 1. 
        

        //if (currLine == numLine) {
            numLine--;
            currLine--;
        //}
        currCol = line(currLine).size() + 1;
    }
    else {
        numLine--;
        currLine--;
    }

}

std::string EditorModel::prevLineUDL() {
    return prevLineDL;
}
int EditorModel::prevColUDL() {
    return prevColDL;
}
int EditorModel::prevRowUDL() {
    return prevRowDL;
}

void EditorModel::undeleteLine(std::string prevLine, int prevRow, int prevCol) {

    //lines.erase(lines.begin() + currLine - 1);

    if (lines.size() == 1 && lines.at(0) == "") {
        lines.at(0) = prevLine;
    }
    else {
        if (currLine == lines.size()) {
            lines.push_back(prevLine);
        }
        else {
            lines.insert(lines.begin() + currLine, prevLine);
        }
        numLine++;
    }

    currCol = prevCol;
    currLine = prevRow;
    
}

//Creates a new line just under the current line. 
//Any text at or after the cursor on the current line 
//is moved to the beginning of the new line. 
void EditorModel::newLine() {
    
    // prevColNL = currCol;

    int strSize = lines.at(currLine - 1).size();

    //Returns a newly constructed string object with its value 
    //initialized to a copy of a substring of this object.
    //portion of the object that starts at character position 
    //pos and spans len characters 
    prevStrNL = "";
    //note curCol always atleast 1
    // if (strSize == 0) {
        
    // }
    // else {
        prevStrNL = lines.at(currLine - 1).substr(currCol - 1, strSize - currCol + 1);
    //}

    //Erases part of the string, reducing its length
    lines.at(currLine - 1).erase(currCol - 1, strSize - currCol + 1);

    numLine++;
    currLine++;
    //The cursor is moved to the beginning of the new line. 
    currCol = 1;

    //The vector is extended by inserting new elements before the 
    //element at the specified position, effectively increasing 
    //the container size by the number of elements inserted.
    lines.insert(lines.begin() + currLine - 1, prevStrNL);

}

void EditorModel::unnewLine() {
    //can't unnewline at first row
    if (currLine != 1) {
        lines.erase(lines.begin() + currLine - 1);

        lines.at(currLine - 1 - 1) += prevStrNL;
        // currCol = prevColNL;
        numLine--;
        currLine--;
        
    }
}

//Moves the cursor up one cell (i.e., to the same column on the 
//previous line). 
void EditorModel::cursorUp() {

    prevColCU = currCol;
    prevLineCU = currLine;

    //If the cursor is already on line 1, 
    //there is no cell above, so this command fails and an error 
    //message is displayed.
    if (currLine == 1) {
        throw EditorException("Already at top");
    }
    //If the previous line is so short that this 
    //would place the cursor beyond the end of the previous line, 
    //the cursor is placed in the column just beyond the end of the 
    //previous line instead. 
    else if (lines.at(currLine - 1 - 1).size() < currCol) {
        currCol = lines.at(currLine - 1 - 1).size() + 1;
    }

    currLine--;

}

int EditorModel::prevColUCU() {
    return prevColCU;
}

int EditorModel::prevLineUCU() {
    return prevLineCU;
}

//Moves the cursor down one cell (i.e., to the same column 
//on the next line). 
void EditorModel::cursorDown() {

    prevColCU = currCol;
    prevLineCU = currLine;

    //If the cursor is already on the last 
    //line, there is no cell below, so this command fails and an 
    //error message is displayed.
    if (currLine == lines.size()) {
        throw EditorException("Already at bottom");
    }
    //If the previous line is so long that 
    //this would place the cursor beyond the end of the next line, 
    //the cursor is placed in the column just beyond the end of 
    //the next line instead. 
    else if (lines.at(currLine).size() < currCol) {
        currCol = lines.at(currLine).size() + 1;
    }

    currLine++;

}

//Moves the cursor to the beginning of the current line. 
void EditorModel::cursorHome() {

    prevColCU = currCol;
    prevLineCU = currLine;

    //No error message is shown if the cursor is already at the 
    //beginning of the current line.
    if (currCol != 1) {
        currCol = 1;
    }
}

//Moves the cursor just beyond the end of the current line. 
void EditorModel::cursorEnd() {

    prevColCU = currCol;
    prevLineCU = currLine;

    //No error message is shown if the cursor is already at the 
    //end of the current line.
    if (currCol != lines.at(currLine - 1).size() + 1) {
        currCol = lines.at(currLine - 1).size() + 1;
    }
}