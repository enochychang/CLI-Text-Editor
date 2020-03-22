#include "deleteLine.hpp"

//Deletes the entire current line of text, with all subsequent lines 
//moving up to fill the empty space. The cursor remains in its 
//current location unless the cursor would be beyond the end of 
//the line of text that now occupies the cursor's line number, 
//in which case the cursor is placed just beyond the end of that 
//line of text instead. If there is only one line of text, it is 
//cleared and the cursor is placed at line 1 column 1. 
//(In other words, the editor must always have at least one line 
//of text, even if it's empty.)
void deleteLine::execute(EditorModel& model) {

    model.deleteLine();
    prevLine = model.prevLineUDL();
    prevRow = model.prevRowUDL();
    prevCol = model.prevColUDL();

}

void deleteLine::undo(EditorModel& model) {
    model.undeleteLine(prevLine, prevRow, prevCol);
}