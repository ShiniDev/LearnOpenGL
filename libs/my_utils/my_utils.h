#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

namespace my_utils {

    inline std::string get_exec_path();
    inline std::string get_exec_dir();
    inline std::string join(const std::vector<std::string> &, std::string);
    inline std::string read_f(std::string);
    template <typename T>
    inline void print_vec(const std::vector<T> &);

    inline std::string get_exec_path()
    {
        std::string path{std::filesystem::canonical("/proc/self/exe")};
        return path;
    }

    inline std::string get_exec_dir()
    {
        std::stringstream ss;
        ss.str(get_exec_path());
        std::string segment;
        std::vector<std::string> seglist;

        while (std::getline(ss, segment, '/')) {
            seglist.push_back(segment);
        }
        seglist.erase(seglist.begin());
        seglist.erase(seglist.end());
        std::string dir{my_utils::join(seglist, "/")};
        return "/" + dir + "/";
    }

    template <typename T>
    inline void print_vec(const std::vector<T> &v)
    {
        std::cout << "[";
        for (int i = 0, s = v.size(); i < s; ++i) {
            if (i + 1 < s) {
                std::cout << v[i] << ", ";
            } else {
                std::cout << v[i] << "]" << std::endl;
            }
        }
    }

    inline std::string join(const std::vector<std::string> &v, std::string sep = "")
    {
        std::string s;
        for (int i = 0, sz = v.size(); i < sz; ++i) {
            s += v[i];
            if (i + 1 < sz) {
                s += sep;
            }
        }
        return s;
    }

    inline std::string read_f(std::string path)
    {
        std::ifstream f(path);
        std::stringstream ss;
        ss << f.rdbuf();
        return ss.str();
    }

} // namespace my_utils

#endif