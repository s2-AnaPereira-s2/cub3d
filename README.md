*This project has been created as part of the 42 curriculum by ana-pdos, thtinner.*

# cub3d

## Description

`cub3d` is a small 3D game engine inspired by early raycasting games (such as Wolfenstein 3D), built in C with MiniLibX.

The goal of the project is to:

- Parse and validate a `.cub` configuration/map file.
- Render a pseudo-3D scene in real time using raycasting.
- Handle player movement/rotation.
- Display textures, floor/ceiling colors.

This project focuses on low-level graphics programming, input handling, and map parsing.

## Features

- `.cub` file parsing (textures, colors, map)
- Map format and enclosure checks
- Real-time raycasting renderer
- Wall texture loading (`.xpm`)
- Keyboard movement and camera rotation
- Minimap and player indicator

## Instructions

### Requirements

- Linux environment
- `cc` compiler
- `make`
- X11 development libraries (for MiniLibX Linux build)

### Build

```bash
make
```

### Run

```bash
./cub3d maps/easy.cub
```

You can also run another map, for example:

```bash
./cub3d maps/doom.cub
```

### Common Make Targets

```bash
make        # build if needed
make clean  # remove object files
make fclean # remove objects + binary
make re     # full rebuild
```

## Controls

- `W` / `A` / `S` / `D`: move player
- Left / Right arrows: rotate camera
- `ESC`: exit

## Project Structure

- `include/`: headers
- `src/`: source files (parsing, rendering, movement, cleanup)
- `maps/`: sample `.cub` maps
- `textures/`: wall textures
- `libft/`: local libft dependency

## Resources

Classic references used for learning and implementation:

- MiniLibX documentation and project examples
- 42 project subject for `cub3d`
- https://www.youtube.com/watch?v=G9i78WoBBIU
- https://www.youtube.com/watch?v=NbSee-XM7WA&t=89s

### AI Usage

AI was used for:

- Explaining and reviewing concepts and existing code
- Style-oriented cleanup suggestions
- Drafting the project documentation (this README).
