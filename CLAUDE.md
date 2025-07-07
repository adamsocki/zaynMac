# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a macOS Metal-based graphics application called "zaynMac" built using C++ and Apple's metal-cpp bindings. The project is a custom game engine or graphics framework that uses Metal for GPU rendering.

## Build System

- **Xcode Project**: Use Xcode to build the application
- **Target**: zaynMac executable (builds to a command-line tool)
- **Build Command**: `xcode-build` or build through Xcode IDE
- **Frameworks**: Foundation, Metal, MetalKit, QuartzCore, AppKit

## Architecture

### Core Components

- **ZaynMemory**: Central memory management structure containing camera, input, time systems
- **Camera System**: 3D camera with data stored in `CameraData*` 
- **Input Management**: `InputManager` with keyboard device support
- **Time System**: `ZaynTime` for frame timing and delta calculations
- **Memory Arenas**: Separate permanent and frame memory arenas for efficient allocation

### Rendering Pipeline

- **Renderer**: Metal-based renderer with compute and graphics pipelines
- **MTKView Integration**: Uses MetalKit view delegate pattern
- **Frame Management**: Supports up to 3 frames in flight (`kMaxFramesInFlight`)
- **Instanced Rendering**: Configured for 10x10x10 instance grid (1000 instances)

### Directory Structure

- `zaynMac/`: Main source code
  - `mac/`: macOS-specific app delegate and view classes
  - `render/`: Rendering system (renderer, mesh)
  - `math/`: Math utilities (vector, matrix, quaternion, scalar)
- `metal-cpp/`: Apple's metal-cpp C++ bindings
- `metal-cpp-extensions/`: Additional AppKit and MetalKit C++ bindings

## Metal-cpp Usage

This project uses Apple's metal-cpp for C++ Metal integration:
- Manual memory management required (no ARC)
- Call `release()` on objects when done
- Use `NS::AutoreleasePool` for temporary objects
- Include pattern: `#define NS_PRIVATE_IMPLEMENTATION` etc. in main.cpp

## Key Classes

- `ZaynAppDelegate`: Main application delegate inheriting from `NS::ApplicationDelegate`
- `MyMTKViewDelegate`: Metal view delegate for rendering
- `Renderer`: Core Metal rendering class
- `ZaynMemory`: Global state container

## Memory Management

- Uses custom memory arenas (`MemoryArena`) for efficient allocation
- Global `ZaynMemory* Zayn` pointer for engine state
- Metal-cpp objects require manual reference counting