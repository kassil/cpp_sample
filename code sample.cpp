#include <iostream>
#include <functional>
#include <map>

using namespace std;

// Define the possible states
enum State
{
    STOP,
    RUN,
    PAUSE
};

// Name strings for display
const std::map<enum State, std::string> state_names = {
    {STOP,  "Stopped"},
    {RUN,   "Running"},
    {PAUSE, "Paused"},
};

// The StateMachine class defines states, events to transition between
// states, and allows the user to inject a handler for every state.
class StateMachine
{
public:
    typedef std::function<void(StateMachine&)> function_type;

    StateMachine(
        function_type onStop,
        function_type onRun,
        function_type onPause)
    :
        onStop(onStop), onRun(onRun), onPause(onPause), state(RUN)
    {
        // Null check
        if (!onStop || !onRun || !onPause)
        {
            throw std::runtime_error("Empty function pointer");
        }
    }

    // Define the events that trigger state transitions
    void start() { state = RUN; }
    void stop() { state = STOP; }
    void pause() { state = PAUSE; }
    void resume() { state = RUN; }

    // Define the state machine's main loop
    void run()
    {
        while (true)
        {
            // Display name
            auto state_name = state_names.find(state);
            if (state_name != state_names.end())
            {
                cout << "In " << state_name->second << " state" << endl;
            }
            switch (state)
            {
            case STOP:
                onStop(*this);
                // Exit the function here
                return;
            case RUN:
                onRun(*this);
                break;
            case PAUSE:
                onPause(*this);
                break;
            default:
                // Should never happen
                throw std::runtime_error("Invalid state!");
            }
        }
    }

private:
    function_type onStop;
    function_type onRun;
    function_type onPause;
    State state;
};

int main()
{
    // Define the state transition functions
    auto onStop = [](StateMachine& machine)
    {
        // Perform actions for the stop state
        cout << "Clean up in Stop state before we exit" << endl;
    };

    auto onRun = [](StateMachine& machine)
    {
        // Perform actions for the run state
        cout << "Pause event" << endl;
        machine.pause();
    };

    auto onPause = [](StateMachine& machine)
    {
        // Perform actions for the pause state
        cout << "Stop event" << endl;
        machine.stop();
    };
    
    try
    {
        StateMachine stateMachine(onStop, onRun, onPause);
        stateMachine.run();
    }
    catch(std::exception& e)
    {
        // Handle unexpected problems
        cerr << "Unexpected: " << e.what() << endl;
    }
    return 0;
}

