#include "cursorDown.hpp"

//Moves the cursor down one cell (i.e., to the same column 
//on the next line). If the previous line is so long that 
//this would place the cursor beyond the end of the next line, 
//the cursor is placed in the column just beyond the end of 
//the next line instead. If the cursor is already on the last 
//line, there is no cell below, so this command fails and an 
//error message is displayed.
void cursorDown::execute(EditorModel& model) {
    model.cursorDown();
    prevCol = model.prevColUCU();
    prevLine = model.prevLineUCU();
}

void cursorDown::undo(EditorModel& model) {
    model.setCursorCol(prevCol);
    model.setCursorLine(prevLine);
}