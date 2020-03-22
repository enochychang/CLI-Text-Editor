#include "backSpace.hpp"

//Deletes the character to the left of the current cursor position, 
//sliding subsqeuent characters backward to fill the empty space. 
//Moves the cursor one character to the left. If the cursor is 
//already in column 1, the entire current line of text is instead 
//moved to the end of the previous line and the cursor is placed 
//at the beginning of that moved text. If the cursor is already 
//on line 1 column 1, this command fails and an error message is 
//displayed.
void backSpace::execute(EditorModel& model) {
    
    model.backSpace();
    undoChar = model.prevChar();
    prevCol = model.prevColUDL();
    // prevLine = model.prevRowUDL();
    // prevCount = model.prevLineCountUBS();
}

void backSpace::undo(EditorModel& model) {

    // if (model.lineCount() < prevCount) {

    //     model.addVecLine();
    //     model.setCursorCol(prevCol);
    //     model.setCursorLine(prevLine);
    //     model.setLineCount(prevCount);
    // }

    if (prevCol == 1) {
        model.newLine();
    }
    else {
        model.insertChar(undoChar);
    }
}

