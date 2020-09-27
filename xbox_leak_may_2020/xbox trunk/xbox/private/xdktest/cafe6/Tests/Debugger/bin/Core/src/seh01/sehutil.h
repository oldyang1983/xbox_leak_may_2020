//
//	Use counter for tracing execution/setting breakpoints
//
#include <wtypes.h>

extern int counter;

//	Functions for causing exceptions.

void RaiseNoException();
void RaiseIntDivideByZero();
void RaiseControlC();
void IntDivideByZero();


//	Functions used for filter-expressions.

LONG ContinueExecution();
LONG ExecuteHandler();
LONG ContinueSearch();