#ifndef CURSORRIGHT_HPP
#define CURSORRIGHT_HPP

#include "Command.hpp"

class cursorRight : public Command {

    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
};

#endif