// InteractionProcessor.cpp
//
// ICS 45C Fall 2019
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"

#include <stack>

// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    view.refresh();

    //use pointer?
    std::stack<Command*> allCommands;
    std::stack<Command*> redoStack;
    
    std::stack<Command*> deleteStack;

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            while(deleteStack.size() != 0) {
                delete deleteStack.top();
                deleteStack.pop();
            }

            break;
        }
        //Reverts the previously-executed command, putting the editor 
        //back into the state it was in before that command was executed. 
        //All commands listed above are "undoable", including cursor 
        //movements and text changes, and individual commands are 
        //undone individually (i.e., each "undo" command undoes a 
        //single cursor movement, a single character inserted, a 
        //single line deleted, etc.).
        else if (interaction.type() == InteractionType::undo)
        {
            if (!allCommands.empty()) {

                allCommands.top()->undo(model);
                redoStack.push(allCommands.top());
                allCommands.pop();
                
            }
            view.refresh();

        }
        //Re-executes the most-recently-undone command. Note that 
        //Undo/Redo work the way that Back and Forward buttons 
        //have traditionally worked in a web browser; once you 
        //execute a command other than Undo or Redo successfully, 
        //there are no commands available to be redone until a 
        //command is subsequently undone.
        else if (interaction.type() == InteractionType::redo)
        {
            if (!redoStack.empty()) {

                redoStack.top()->execute(model);
                allCommands.push(redoStack.top());
                redoStack.pop();

            }
            view.refresh();
        }
        else if (interaction.type() == InteractionType::command)
        {
            //why is this dynamic allocation
                //commands dynam allocated in keypressinteractionreader
                //need to delete them
            Command* command = interaction.command();
            
            //store all commands and delete them when quit
            deleteStack.push(command);

            try
            {
                //where is model from
                command->execute(model);
                model.clearErrorMessage();

                allCommands.push(command);
                //once you execute a command other than Undo or Redo successfully, 
                //there are no commands available to be redone until a 
                //command is subsequently undone.
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
            }

            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.

            //delete command;
        }
    }
}

