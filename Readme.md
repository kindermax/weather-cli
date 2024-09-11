# Weather cli

This is a simple c++ cli which calls https://home.openweathermap api

## Build

```bash
cmake -S . -B build && cmake --build build
```

## Development

In order for nvim lsp to understand the project, you need to generate compile_commands.json file:

```bash 
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

## Run

```bash
export API_KEY=<key>

./build/weather_cli Kyiv
```

You will see something like:

```bash
The weather in Kyiv:
Temp: -1.73
Temp feels like: -1.73
Humidity:87
Wind: 0.45
```
