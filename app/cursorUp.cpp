#include "cursorUp.hpp"

//Moves the cursor up one cell (i.e., to the same column on the 
//previous line). If the previous line is so short that this 
//would place the cursor beyond the end of the previous line, 
//the cursor is placed in the column just beyond the end of the 
//previous line instead. If the cursor is already on line 1, 
//there is no cell above, so this command fails and an error 
//message is displayed.
void cursorUp::execute(EditorModel& model)
{
    model.cursorUp();
    prevCol = model.prevColUCU();
    prevLine = model.prevLineUCU();
}

void cursorUp::undo(EditorModel& model) {
    model.setCursorCol(prevCol);
    model.setCursorLine(prevLine);
}