#ifndef INSERTCHAR_HPP
#define INSERTCHAR_HPP

#include "Command.hpp"

class insertChar : public Command {

    public: 
        insertChar(char x) : x(x) {};
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;

    private:
        char x;
};

#endif