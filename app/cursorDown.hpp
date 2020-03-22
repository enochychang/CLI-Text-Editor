#ifndef CURSORDOWN_HPP
#define CURSORDOWN_HPP

#include "Command.hpp"

class cursorDown: public Command {

    public:
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;

    private:
        int prevCol;
        int prevLine;

};

#endif
