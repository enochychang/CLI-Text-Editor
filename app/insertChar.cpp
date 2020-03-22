#include "insertChar.hpp"

//Inserts a character where the cursor is currently positioned. 
//Any characters at or beyond the cursor on the same line are 
//shifted to the right. The cursor moves one cell to the right 
//afterward.
void insertChar::execute(EditorModel& model) {
    model.insertChar(x);
}

void insertChar::undo(EditorModel& model) {
    model.backSpace();
}