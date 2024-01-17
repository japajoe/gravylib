#ifndef GRAVY_SIGNAL_HPP
#define GRAVY_SIGNAL_HPP

#include <functional>
#include <signal.h>

namespace Gravy::System
{
    typedef void (*signal_handler_t)(int);

#ifdef _WIN32
    enum class SignalType : int
    {
        SigInt = SIGINT,
        SigIll = SIGILL,
        SigAbrtCompat = SIGABRT_COMPAT,
        SigFpe = SIGFPE,
        SigSegv = SIGSEGV,
        SigTerm = SIGTERM,
        SigBreak = SIGBREAK,
        SigAbrt = SIGABRT,
        SigAbrt2 = SIGABRT2
    };
#else
    enum class SignalType : int
    {
        SigInt = SIGINT,
        SigIll = SIGILL,
        SigAbrt = SIGABRT,
        SigFpe = SIGFPE,
        SigSegv = SIGSEGV,
        SigTerm = SIGTERM,
        SigHup = SIGHUP,
        SigQuit = SIGQUIT,
        SigTrap = SIGTRAP,
        SigKill = SIGKILL,
        SigBus = SIGBUS,
        SigSys = SIGSYS,
        SigPipe = SIGPIPE,
        SigAlrm = SIGALRM,
        SigUrg = SIGURG,
        SigStop = SIGSTOP,
        SigTstp = SIGTSTP,
        SigCont = SIGCONT,
        SigChld = SIGCHLD,
        SigTtin = SIGTTIN,
        SigTtou = SIGTTOU,
        SigPoll = SIGPOLL,
        SigXcpu = SIGXCPU,
        SigXfsz = SIGXFSZ,
        SigVtalrm = SIGVTALRM,
        SigProf = SIGPROF,
        SigUsr1 = SIGUSR1,
        SigUsr2 = SIGUSR2,
        SigWinch = SIGWINCH,
        SigIo = SIGIO,
        SigIot = SIGIOT,
        SigCld = SIGCLD,
        SigRtmin = __SIGRTMIN,
        SigRtmax = __SIGRTMAX
    };
#endif
    
    class Signal
    {
    public:
        static void Register(SignalType signalType, signal_handler_t handler);
    };
};
#endif