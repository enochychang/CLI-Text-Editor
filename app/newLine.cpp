#include "newLine.hpp"

//Creates a new line just under the current line. 
//Any text at or after the cursor on the current line 
//is moved to the beginning of the new line. 
//The cursor is moved to the beginning of the new line. 
//(Note that there are two different keys that are 
//interpreted the same way; either Ctrl+J or Ctrl+M b
//ehaves this way.)
void newLine::execute(EditorModel& model) {
    prevColNL = model.cursorColumn();
    model.newLine();
}
void newLine::undo(EditorModel& model) {
    model.setCursorCol(prevColNL);
    model.unnewLine();
}