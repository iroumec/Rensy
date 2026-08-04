module;

#include <iostream>
#include <string_view>

export module renderer:logging.level;

// ============================================================================
// Declarations
// ============================================================================

/**
 * Level explanation:
 * - TRACE: Most detailed level. Execution line per line.
 * - DEBUG: Useful information for the programmer (me) during development.
 * - INFO: General information about the program working.
 * - WARNING: Something unexpected happened, but the program can continue.
 * - ERROR: Something failed and, probably, the result will be incorrect.
 */
export enum class LogLevel {
    Error,
    Warning,
    Info,
    Debug,
    Trace,
};

// ============================================================================
// EOF
// ============================================================================