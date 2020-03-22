#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "Command.hpp"

class backSpace : public Command {

    public:
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;

    private:
        char undoChar;

        int prevCol;
        // int prevLine;
        // int prevCount;

};

#endif