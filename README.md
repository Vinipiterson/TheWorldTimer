# The World Timer

The plugin contains 1 main class and a function library. The timer can be used for any purpose (match timer, for example) and is completely replicated.

## How to use:
1 - Drag a world timer to your level and set it's default properties.

2 - Get a reference for the timer on any blueprint you want to use it (GameMode, PlayerController or UI, for example) using "GetWorldTimer" on blueprints, or `UWorldTimerFunctionLibrary::GetWorldTimer(WORLDCONTEXTOBJECT);` passing a WorldContextObject as a parameter in c++.

3 - Bind events to the delegates you need and add your logic.

## Callable functions
- GetWorldTimer - returns a reference for the timer present on the current level
- SetTimerPaused - pause/unpause the timer (Can be used for activating the timer as well)
- SetTotalTime - no description needed
- ResetTimer - no description needed as well

## Delegates
- OnTimerUpdated
- OnTimerPaused
- OnTimerEnded
- OnTimerReset
