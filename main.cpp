#include "AudioManager.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "Демонстрация AudioManager\n\n";

    AudioManager& audio = AudioManager::getInstance();

    audio.loadSound("explosion", "sounds/explosion.wav");
    audio.loadSound("background", "sounds/bg_music.mp3");
    audio.loadSound("shot", "sounds/shot.wav");

    audio.setMasterVolume(0.8f);
    audio.setVolume("background", 0.5f);

    audio.playSound("background");
    audio.playSound("shot");

    std::cout << "\nbackground играет? " << (audio.isPlaying("background") ? "Да" : "Нет") << "\n";
    std::cout << "explosion играет? " << (audio.isPlaying("explosion") ? "Да" : "Нет") << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    audio.pauseAll();

    audio.playSound("explosion");

    audio.resumeAll();
    audio.playSound("explosion");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    audio.stopSound("shot");

    audio.listTracks();

    AudioManager& anotherRef = AudioManager::getInstance();
    std::cout << "\nАдрес первого экземпляра: " << &audio << "\n";
    std::cout << "Адрес второго экземпляра: " << &anotherRef << " (тот же!)\n";

    return 0;
}