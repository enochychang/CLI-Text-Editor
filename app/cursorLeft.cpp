#include "cursorLeft.hpp"

//Moves the cursor left one cell (i.e., to the previous column on 
//the same line). If the cursor is at the beginning of a line 
//already, it instead moves just beyond the end of the previous 
//line instead. If the cursor is at the beginning of line 1, 
//this command fails and an error message is displayed.
void cursorLeft::execute(EditorModel& model) {
    model.moveCol(model.cursorColumn() - 1);
}

void cursorLeft::undo(EditorModel& model) {
    model.moveCol(model.cursorColumn() + 1);
}