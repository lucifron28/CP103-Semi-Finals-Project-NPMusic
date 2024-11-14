# Music Player Application

## Overview

This project is a Music Player Application that demonstrates the use of stacks and queues. It allows users to manage a playlist and track recently played songs using a graphical user interface (GUI).

## Features

- **Stack Operations**:
  - **Push**: Adds a recently played song to the stack.
  - **Pop**: Removes the most recently played song from the stack.
  - **Peek**: Views the most recently played song without removing it from the stack.

- **Queue Operations**:
  - **Enqueue**: Adds a song to the playlist queue.
  - **Dequeue**: Removes the next song from the playlist queue.
  - **Peek**: Views the next song in the playlist queue without removing it.

- **Graphical User Interface (GUI)**:
  - **Buttons for Each Operation**: Users can interact with the application using buttons for push, pop, enqueue, and dequeue operations.
  - **Display Current States**: The GUI displays the current states of the stack and queue, allowing users to see the songs in the stack and the playlist queue.

## Installation Guide

### Prerequisites

- Windows OS

### Steps

1. **Download the Released Version**:
   - Go to the [Release](https://github.com/lucifron28/CP103-Semi-Finals-Project-NPMusic/blob/main/build/Desktop_Qt_6_7_2_MinGW_64_bit-Release/release/) page of the repository.
   - Download the latest release zip file.

2. **Extract the Zip File**:
   - Extract the contents of the zip file to a desired location on your computer.

3. **Run the Application**:
   - Navigate to the extracted folder.
   - Double-click on the executable file `CP103_Semi-Finals_Project.exe` to run the application.

### Development Setup

If you want to build the project from source, follow these steps:

#### Prerequisites

- Qt 6.0 or higher
- C++17 compatible compiler

#### Steps

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/lucifron28/CP103-Semi-Finals-Project-NPMusic.git
   cd CP103-Semi-Finals-Project-NPMusic
   ```

2. **Open the Project in Qt Creator**:
   - Launch Qt Creator.
   - Open the project by selecting the `.pro` file in the cloned repository.

3. **Configure the Project**:
   - Ensure that the correct Qt version and compiler are selected.
   - Configure the build settings as needed.

4. **Build the Project**:
   - Click on the "Build" button or press `Ctrl+B` to build the project.

5. **Run the Project**:
   - Click on the "Run" button or press `Ctrl+R` to run the application.

### Usage

- **Add Songs to Queue**: Double-click on a song in the list to add it to the queue.
- **Play Next Song in Queue**: Click the "Play" button to play the next song in the queue.
- **View Recently Played Songs**: The history tab shows the list of recently played songs.

