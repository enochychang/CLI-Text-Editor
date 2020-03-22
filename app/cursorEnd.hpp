#ifndef CURSOREND_HPP
#define CURSOREND_HPP

#include "Command.hpp"

class cursorEnd : public Command {

    public:
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
        int prevCol;
        int prevLine;
};

#endif