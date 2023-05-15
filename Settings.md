# Tooling

## Compiler

Any GCC, Clang or MSVC compiler

## IDE: Visual Studio Code

- [Visual Studio Code](https://code.visualstudio.com/)

### VSCode Extensions

- Coding Tools Extension Pack (franneck94)
- C/C++ Extension Pack (franneck94)

### Extra settings (for local .vscode/settings.json file)

```json
  "C_Cpp_Runner.includePaths": [
    "${workspaceFolder}/utils/"
  ],
  // Linux only
  "C_Cpp_Runner.linkerArgs": [
      "-lm"
  ],
  "C_Cpp_Runner.excludeSearch": [
      "**/scripts/"
  ],
```
