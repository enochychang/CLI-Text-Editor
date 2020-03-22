#ifndef CURSORUP_HPP
#define CURSORUP_HPP

#include "Command.hpp"

class cursorUp: public Command {

    public:
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;

    private:
        int prevCol;
        int prevLine;

};

#endif