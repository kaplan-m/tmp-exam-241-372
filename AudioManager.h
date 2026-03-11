#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

struct AudioTrack {
    std::string name;
    std::string path;
    bool isPlaying;
    float volume;
};

class AudioManager {
private:
    AudioManager() : masterVolume(1.0f), paused(false) {}

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    std::map<std::string, AudioTrack> tracks;
    float masterVolume;
    bool paused;

public:
    static AudioManager& getInstance() {
        static AudioManager instance;
        return instance;
    }

    void loadSound(const std::string& name, const std::string& path) {
        if (tracks.find(name) != tracks.end()) {
            std::cout << "Звук '" << name << "' уже загружен. Перезаписываем.\n";
        }
        tracks[name] = { name, path, false, 1.0f };
        std::cout << "Звук '" << name << "' загружен из '" << path << "'\n";
    }

    void playSound(const std::string& name) {
        if (paused) {
            std::cout << "Система на паузе. Сначала вызовите resumeAll().\n";
            return;
        }

        auto it = tracks.find(name);
        if (it != tracks.end()) {
            it->second.isPlaying = true;
            std::cout << "▶ Воспроизводится: '" << name << "' (громкость: "
                << it->second.volume * masterVolume << ")\n";
        }
        else {
            std::cout << "Ошибка: звук '" << name << "' не загружен.\n";
        }
    }

    void stopSound(const std::string& name) {
        auto it = tracks.find(name);
        if (it != tracks.end()) {
            it->second.isPlaying = false;
            std::cout << "⏹ Остановлен: '" << name << "'\n";
        }
        else {
            std::cout << "Ошибка: звук '" << name << "' не найден.\n";
        }
    }

    void setVolume(const std::string& name, float volume) {
        if (volume < 0.0f) volume = 0.0f;
        if (volume > 1.0f) volume = 1.0f;

        auto it = tracks.find(name);
        if (it != tracks.end()) {
            it->second.volume = volume;
            std::cout << "Громкость для '" << name << "' установлена на " << volume << "\n";
        }
        else {
            std::cout << "Ошибка: звук '" << name << "' не найден.\n";
        }
    }

    void setMasterVolume(float volume) {
        if (volume < 0.0f) volume = 0.0f;
        if (volume > 1.0f) volume = 1.0f;
        masterVolume = volume;
        std::cout << "Общая громкость установлена на " << masterVolume << "\n";
    }

    void pauseAll() {
        paused = true;
        std::cout << "⏸ Все звуки на паузе.\n";
    }

    void resumeAll() {
        paused = false;
        std::cout << "▶ Воспроизведение возобновлено.\n";
    }

    bool isPlaying(const std::string& name) const {
        auto it = tracks.find(name);
        if (it != tracks.end()) {
            return it->second.isPlaying && !paused;
        }
        return false;
    }

    void listTracks() const {
        std::cout << "\n=== Загруженные звуки ===\n";
        for (const auto& pair : tracks) {
            std::cout << " - " << pair.second.name << " [" << pair.second.path << "] "
                << (pair.second.isPlaying ? "(играет)" : "(остановлен)") << "\n";
        }
        std::cout << "========================\n";
    }
};

#endif