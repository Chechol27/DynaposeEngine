#pragma once

namespace Utils
{
    ///<summary>
    ///a std::vector wrapper to facilitate Edit vs Play modes in diverse parts of the engine,
    ///when a scene is in "Edit mode" this container will prioritize pointer stability over memory contiguity, that
    ///way a scene that only needs to be played will run much faster
    ///</summary>
    template <typename T>
    class EditableContainer
    {

    };
}