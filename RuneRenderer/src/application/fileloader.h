#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class FileLoader 
{
private:
    static inline std::map<std::string, std::string> added_files = { };
    
    static void RegisterFoundFile(char* filepath) {

    }

    static std::string GetAssetFolderPath() {
        return "C:\\Users\\ivans\\Desktop\\Projetos\\Rune-Engine\\RuneRenderer\\resources";
    }

    static void RegisterAssetFiles() {
        std::string valid_extensions[] = {
            ".png",
            ".jpg",
            ".glsl"
        };

        std::string folder = GetAssetFolderPath();
        size_t path_length = folder.length() + 1;

        try {
            for (auto& path : fs::recursive_directory_iterator(folder)) 
            {
                if(path.is_directory())
                    continue;

                std::string abs_path = path.path().u8string();
                std::string relative_path = abs_path.substr(path_length, abs_path.length() - path_length);
                FileLoader::added_files[relative_path] = abs_path;
            }
        }
        catch(std::filesystem::filesystem_error e) {
            std::cout << "Error: " << e.what() << "\n"; 
        } 
    }

public:
    static void Init() 
    {
        FileLoader::added_files.clear();
        RegisterAssetFiles();

        for(const auto &[key, val] : added_files) {
            std::cout << "Registered File: " << key << "\n";
        }
    }

    static const char* GetFile(const char* rel_path) { 
        if(added_files.find(rel_path) == added_files.end())
            return nullptr;

        return added_files[rel_path].c_str();
    }

    static unsigned char* ReadFile(const char* rel_path)
    {
        if(added_files.find(rel_path) == added_files.end())
            return nullptr;

        const char* file_path = added_files[rel_path].c_str();

        std::ifstream input(file_path, std::ios::binary);
        std::vector<char> bytes((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
        input.close();

        unsigned char* out = new unsigned char[bytes.size()];
        memcpy(out, &bytes[0], bytes.size());
        out[bytes.size()-1] = 0;

        return out;
    }

    void LoadImage(char* image_id) {
    
    }
};