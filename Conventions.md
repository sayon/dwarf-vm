# DWARF: coding conventions

Please read this document before making any changes to the source code.

## Naming

- All types are to be prefixed by `vm_`.
- All functions operating on a certain struct instances are to be prefixed with this struct's name.
- No global mutable variables are allowed.
- No typedefs hiding `struct`, `union` etc.
- Following POSIX, no `_t` suffix in type names.


## Documenting
- The documentation format is Doxygen.
- Use `@` for Doxygen commands, not `\\`.
- All functions are documented in header files, all static functions are documented in sources.

## Macros
- Macros are OK as long as they are simple and local to one source file.
