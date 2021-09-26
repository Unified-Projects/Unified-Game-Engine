#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
namespace UnifiedEngine{
    namespace Console{
        #include <Windows.h>

        //Hides Console
        void HideConsole()
        {
            UnifiedEngine::Console::ShowWindow(UnifiedEngine::Console::GetConsoleWindow(), SW_HIDE);
        }
        
        //Show Console
        void ShowConsole()
        {
            UnifiedEngine::Console::ShowWindow(UnifiedEngine::Console::GetConsoleWindow(), SW_SHOW);
        }

        //Reaturns a bool if it is visible or not
        bool IsConsoleVisible()
        {
            return UnifiedEngine::Console::IsWindowVisible(UnifiedEngine::Console::GetConsoleWindow()) != FALSE;
        }
    }
}
#endif
