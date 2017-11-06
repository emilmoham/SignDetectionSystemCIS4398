#pragma once
enum InputMode { Camera, VideoFile };

int openImage(char* path);
int readFromCamera();
int readFromVideoFile(char* path);
