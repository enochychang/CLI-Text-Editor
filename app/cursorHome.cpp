#include "cursorHome.hpp"

//Moves the cursor to the beginning of the current line. 
//No error message is shown if the cursor is already at the 
//beginning of the current line.
void cursorHome::execute(EditorModel& model) {
    model.cursorHome();
    prevCol = model.prevColUCU();
    prevLine = model.prevLineUCU();
}

void cursorHome::undo(EditorModel& model) {
    model.setCursorCol(prevCol);
    model.setCursorLine(prevLine);
}