# Applies strict warnings-as-errors to a target. Deliberately PRIVATE and
# applied per-target (never globally) so third-party code we pull in via
# FetchContent (e.g. GoogleTest) is never held to our own warning bar.
function(gpu_driver_stack_enable_warnings target)
    target_compile_options(${target} PRIVATE -Wall -Wextra -Werror)
endfunction()
