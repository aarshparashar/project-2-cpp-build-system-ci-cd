# Project 2 Retrospective — C++ Build System & CI/CD (NVK-inspired)

## What We Tried

**Week 1 — Foundation**
Built `libgpu_core`: a `Device` interface, a Vulkan-style `CommandBuffer` (record-then-submit), and a mock `ShaderIR`. Set up modern, target-scoped CMake (`target_include_directories`, `target_compile_features`) instead of global `include_directories`/`add_definitions`. Wired GoogleTest in via `FetchContent`. Ran the whole toolchain — GCC, CMake, Ninja, ccache — inside a real Ubuntu Linux VM using Apple's native `container` tool on Apple Silicon, so the Mac host stayed clean.

**Week 2 — Plugin architecture**
Turned `nvk_driver` into a real dynamically-loadable shared library (`libnvk_driver.so.0.1.0`, with the `.so.0`/`.so` symlinks a real driver ships), exporting a single C-linkage entry point so it can be `dlopen`'d/`dlsym`'d by name — the same pattern a real Vulkan ICD uses. Added `software_rasterizer` as the statically-linked CPU fallback, specifically to make the static-vs-dynamic-linking contrast concrete. Wrote a smoke test that actually `dlopen`s the built `.so` at test time, instead of just linking against it directly and calling that a test. Set up a GitHub Actions matrix (GCC/Clang × Debug/Release) plus a job that packages `nvk_driver` as its own versioned artifact, independent of the rest of the build.

**Week 3 — Hardening**
Added a dedicated ASan+UBSan sanitizer job — deliberately scoped to one leg (Debug, Clang) rather than the whole matrix, since sanitizer instrumentation is expensive and the bugs it catches don't depend on which compiler you used. Added `-Wall -Wextra -Werror` to our own targets only, explicitly excluding vendored GoogleTest. Also hit a real infrastructure snag: the local Linux VM's networking broke after a routine restart, so we made the call to trust GitHub Actions as the single source of truth going forward instead of chasing local reproduction — which turned out to be the more correct instinct for CI anyway.

**Week 4 — Build-time codegen, and a scope correction**
Built `shader_compiler` and wired it in via `add_custom_command`, so it compiles itself first, then runs against a sample shader as a genuine build-time codegen step, producing a real artifact. Started over-building this (a full mock IR parser/serializer) before catching it: the project is NVK-*inspired*, not real NVK, and the actual skill being practiced is the build orchestration, not the C++ itself. Right-sized `shader_compiler` down to ~15 lines once that was clear.

**Week 5 — Closing it out**
Auto-detected ccache in `CMakeLists.txt` itself, so it's not something you have to remember to pass as a flag. Added `scripts/report_build_times.sh`, parsing Ninja's build log to surface the slowest compile steps — and it correctly flagged GoogleTest's own source as the slowest thing in the build, real signal working as intended. Brought the README current with what the repo actually contains, and added an explicit "NVK-inspired, not real NVK" scope note so the framing stays honest.

## What We Learned

- Target-scoped CMake (`target_include_directories`/`target_link_libraries` with `PUBLIC`/`PRIVATE`/`INTERFACE`) vs global state, and why the latter stops scaling once you have more than one module.
- The real difference between static linking (compiled permanently into one binary) and dynamic loading (`dlopen`/`dlsym` by name, at runtime) — and why real driver ecosystems depend on the latter.
- The full userspace-driver-to-kernel-to-hardware chain (app → userspace driver → `ioctl` → kernel driver → GPU), and that this project deliberately stops before that last layer.
- Sanitizers are dynamic, runtime bug detectors (only catch what actually executes), fundamentally different from Rust's static, compile-time borrow checker — and why CI scopes sanitizer runs to one leg rather than the whole matrix.
- Build-time codegen (`add_custom_command`) requires explicit `DEPENDS` wiring, because CMake has no built-in notion that "run this program" secretly requires "that program to exist first."
- When to stop scoping up: catching ourselves over-engineering `shader_compiler` was as valuable a lesson as anything we built.
- Trust the pipeline over the local machine — when the local dev environment broke, the right move was leaning on CI as source of truth, not fighting the local setup.

## Plan For The Next Project

Project 2 is done: 6-job green CI (build matrix, sanitizers, artifact packaging, shader codegen verification), README matching reality, portfolio-ready.

Three projects remain: the GPU-aware Kubernetes cluster scheduler (Project 1), the observability platform (Project 3), and the distributed chaos-testing system (Project 4). Project 1 already has a small working Go control-plane skeleton from before this series started, giving it a head start, and it stays in the same "AI/GPU infra" niche this whole series is aimed at. Projects 3 and 4 are broader in scope (multiple correlated telemetry pipelines; multi-service resilience + chaos injection) and were ranked harder to finish cleanly.

Recommendation: pick up Project 1 next, for momentum and thematic continuity, then decide between Project 3 and 4 afterward based on how much runway is left.
