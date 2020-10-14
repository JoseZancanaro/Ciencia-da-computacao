#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include "StringManip.hpp"

namespace gamequery {

struct GameData {
    std::string appId;
    std::string name;
    std::string releaseDate;
    std::string developer;
    std::string publisher;
    std::vector<std::string> platform;
    std::string requiredAge;
    std::vector<std::string> resource;
    std::vector<std::string> genre;
    std::vector<std::string> tag;
    std::string achievements;
    std::string positiveRating;
    std::string negativeRating;
    std::string averagePlaytime;
    std::string owners;
    std::string price;
};

using GameDataCollection = std::vector<GameData>;
using GameDataSimilarity = std::pair<GameData, double>;
using GameDataSimilarityCollection = std::vector<GameDataSimilarity>;

using CityBlock = std::pair<std::string, double>;

struct BaseAttributesWeights {
    double developer {};
    double publisher {};
    double platform {};
    double requiredAge {};
    double resource {};
    double genre {};
    double tag {};
    double achievements {};
    double positiveRating {};
    double negativeRating {};
    double averagePlaytime {};
    double owners {};
    double price {};

    std::vector<std::string> genreNames {};
    std::vector<std::vector<double>> genreSimilarity {};

    std::vector<CityBlock> cbRequiredAge {};
    std::vector<CityBlock> cbAchievements {};
    std::vector<CityBlock> cbPositiveRating {};
    std::vector<CityBlock> cbNegativeRating {};
    std::vector<CityBlock> cbAveragePlaytime {};
    std::vector<CityBlock> cbOwners {};
    std::vector<CityBlock> cbPrice {};
};

struct GameQuery {
    GameDataCollection collection {};
    BaseAttributesWeights base {};
};

auto readCollection(std::string const& filename) -> GameDataCollection;

auto readWeightsConfiguration(std::string const& filename, std::size_t count) -> BaseAttributesWeights;

auto readCityBlockFile(std::string const& filename, std::size_t count) -> std::vector<CityBlock>;

auto readMatrixFile(std::string const& filename, std::size_t count)
    -> std::pair<std::vector<std::string>, std::vector<std::vector<double>>>;

auto readBaseConfiguration(std::string const& storePath) -> BaseAttributesWeights;

auto calculateCityBlockSimilarity(std::vector<CityBlock> const& cityBlocks,
                                  std::string const& input, std::string const& base) -> double;

auto calculateMatrixSimilarity(BaseAttributesWeights const& weights,
                               GameData const& inputCase, GameData const& baseCase) -> double;

auto calculateSimilarity(BaseAttributesWeights const& weights,
                         GameData const& inputCase, GameData const& baseCase) -> double;

template <typename Callable>
auto guardSimilarity(std::string const& expected, std::string const& input, Callable callable) -> double {
    if (expected == input) {
        return 1.0;
    } else {
        return callable();
    }
}

auto calculateAll(GameQuery const& query, GameData const& inputCase) -> GameDataSimilarityCollection;

}

#endif // DOMAIN_HPP
