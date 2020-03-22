#ifndef CURSORHOME_HPP
#define CURSORHOME_HPP

#include "Command.hpp"

class cursorHome : public Command {

    public:
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
        int prevCol;
        int prevLine;
};

#endif