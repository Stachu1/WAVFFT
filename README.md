# WAVE File FFT Visualizer

## 📘 Overview

This is a simple C project designed to help understand how to:
- **Read and parse WAVE audio files**
- **Compute the Fast Fourier Transform (FFT)** of audio data
- **Visualize frequency content** of audio in the terminal using text-based bars

The program reads a file named `f.wav` from the current working directory, displays its header information, and prints a simple FFT-based frequency visualization in the console.


---

## ▶️ How It Works

1. **Loads and prints** WAV header info using `wav_test`.
2. Waits for 3 seconds before starting FFT processing.
3. Reads short chunks of samples (32 samples at a time) from the file.
4. Applies an FFT to each chunk.
5. Uses a simple smoothing filter to stabilize the visualization.
6. Prints a bar chart representing the frequency bin magnitudes.

---


## ✅ Requirements

- C compiler (e.g., `gcc`)
- A mono 16-bit PCM `.wav` file named `f.wav` in the same directory
