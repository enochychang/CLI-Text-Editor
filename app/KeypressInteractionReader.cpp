// KeypressInteractionReader.cpp
//
// ICS 45C Fall 2019
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE

#include "KeypressInteractionReader.hpp"

#include "cursorRight.hpp"
#include "cursorLeft.hpp"
#include "insertChar.hpp"
#include "backSpace.hpp"
#include "deleteLine.hpp"
#include "newLine.hpp"
#include "cursorUp.hpp"
#include "cursorDown.hpp"
#include "cursorHome.hpp"
#include "cursorEnd.hpp"
// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.

Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();

        Command* cmmd = nullptr;

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            switch (keypress.code())
            {
                case 'X':
                    return Interaction::quit();
                case 'O':
                    cmmd = new cursorRight();
                    break;
                case 'U':
                    cmmd = new cursorLeft();
                    break;
                case 'Z':
                    return Interaction::undo();
                case 'A':
                    return Interaction::redo();
                case 'H':
                    cmmd = new backSpace();
                    break;
                case 'D':
                    cmmd = new deleteLine();
                    break;
                case 'M': case 'J':
                    cmmd = new newLine();
                    break;
                case 'I':
                    cmmd = new cursorUp();
                    break;
                case 'K':
                    cmmd = new cursorDown();
                    break;
                case 'Y':
                    cmmd = new cursorHome();
                    break;
                case 'P':
                    cmmd = new cursorEnd();
                    break;
                default:
                    break;
            }      

            //returns to interactionprocessor.cpp
            return Interaction::command(cmmd);
        }
        else
        {
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly

            //this is where insert characters implemented
            cmmd = new insertChar{keypress.code()};
            return Interaction::command(cmmd);
        }
    }
}

