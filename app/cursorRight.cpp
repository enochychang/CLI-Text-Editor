#include "cursorRight.hpp"

//Moves the cursor right one cell (i.e., to the next column 
//on the same line). If the cursor is just beyond the end of 
//a line already, it instead moves to the beginning of the 
//next line instead. If the cursor is just beyond the end of 
//the last line, this command fails and an error message is 
//displayed.
void cursorRight::execute(EditorModel& model) {
    model.moveCol(model.cursorColumn() + 1);
}

void cursorRight::undo(EditorModel& model) {
    model.moveCol(model.cursorColumn() - 1);
}