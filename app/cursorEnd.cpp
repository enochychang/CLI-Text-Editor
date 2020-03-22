#include "cursorEnd.hpp"

//Moves the cursor just beyond the end of the current line. 
//No error message is shown if the cursor is already at the 
//end of the current line.
void cursorEnd::execute(EditorModel& model) {
    model.cursorEnd();
    prevCol = model.prevColUCU();
    prevLine = model.prevLineUCU();
}

void cursorEnd::undo(EditorModel& model) {
    model.setCursorCol(prevCol);
    model.setCursorLine(prevLine);
}