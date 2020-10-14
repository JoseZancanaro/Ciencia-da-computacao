#include "Domain.hpp"

namespace gamequery {

auto readCollection(std::string const& filename) -> GameDataCollection {
    GameDataCollection collection {};

    auto csvBase = util::readFromCSV(filename);

    std::for_each(std::begin(csvBase) + 1, std::end(csvBase), [&collection](auto const& data) {
        collection.push_back({
            data.at(0),
            data.at(1),
            data.at(2),
            data.at(4),
            data.at(5),
            util::split(data.at(6)),
            data.at(7),
            util::split(data.at(8)),
            util::split(data.at(9)),
            util::split(data.at(10)),
            data.at(11),
            data.at(12),
            data.at(13),
            data.at(14),
            data.at(16),
            data.at(17)
        });
    });

    return collection;
}

auto readWeightsConfiguration(std::string const& filename, std::size_t count) -> BaseAttributesWeights {
    BaseAttributesWeights base {};

    std::ifstream file (filename);
    std::string buffer {};
    std::size_t attributeCount {};

    if (file.is_open()) {
        while (attributeCount < count) {
            std::string line {};
            std::getline(file, line);

            auto values = util::split(line, ",");

            auto attribute = values.front();
            auto weight = std::stod(values.at(1));

            if (attribute == "developer") {
                base.developer = weight;
            } else if (attribute == "publisher") {
                base.publisher = weight;
            } else if (attribute == "platform") {
                base.platform = weight;
            } else if (attribute == "required_age") {
                base.requiredAge = weight;
            } else if (attribute == "resource") {
                base.resource = weight;
            } else if (attribute == "genre") {
                base.genre = weight;
            } else if (attribute == "tag") {
                base.tag = weight;
            } else if (attribute == "achievements") {
                base.achievements = weight;
            } else if (attribute == "positive_rating") {
                base.positiveRating = weight;
            } else if (attribute == "negative_rating") {
                base.negativeRating = weight;
            } else if (attribute == "average_playtime") {
                base.averagePlaytime = weight;
            } else if (attribute == "owners") {
                base.owners = weight;
            } else if (attribute == "price") {
                base.price = weight;
            }

            ++attributeCount;
        }
    }

    return base;
}

auto readCityBlockFile(std::string const& filename, std::size_t count) -> std::vector<CityBlock> {
    std::vector<CityBlock> cityBlock;

    std::ifstream file (filename);

    if (file.is_open()) {
        std::size_t valueCount {};

        while (valueCount < count) {
            std::string buffer {};
            std::getline(file, buffer);

            auto cb = util::split(buffer, ",");
            cityBlock.push_back({ cb.front(), std::stod(cb.back()) });

            ++valueCount;
        }
    }

    return cityBlock;
}

auto readMatrixFile(std::string const& filename, std::size_t count) -> std::pair<std::vector<std::string>, std::vector<std::vector<double>>> {
    std::vector<std::string> genreNames;
    std::vector<std::vector<double>> matrix (count, std::vector<double>(count));

    std::ifstream file (filename);

    genreNames.reserve(count);

    if (file.is_open()) {
        std::size_t valueCount {};

        while (valueCount < count) {
            std::string buffer {};
            std::getline(file, buffer);
            genreNames.push_back(buffer);
            ++valueCount;
        }

        valueCount = 0;

        while (valueCount < count) {
            std::string buffer {};
            std::getline(file, buffer);

            auto weights = util::split(buffer, ",");

            std::size_t column = 0;
            for (auto const& weight : weights) {
                auto cast = std::stod(weight);
                matrix[valueCount][column] = cast;
                matrix[column][valueCount] = cast;
                ++column;
            }

            ++valueCount;
        }
    }

    return { genreNames, matrix };
}

auto readBaseConfiguration(std::string const& storePath) -> BaseAttributesWeights {
    auto base = readWeightsConfiguration(storePath + "attributes.txt", 13);

    base.cbRequiredAge = readCityBlockFile(storePath + "required_age.txt", 6);
    base.cbAchievements = readCityBlockFile(storePath + "achievements.txt", 8);
    base.cbPositiveRating = readCityBlockFile(storePath + "positive_rating.txt", 7);
    base.cbNegativeRating = readCityBlockFile(storePath + "negative_rating.txt", 6);
    base.cbAveragePlaytime = readCityBlockFile(storePath + "average_playtime.txt", 9);
    base.cbOwners = readCityBlockFile(storePath + "owners.txt", 13);
    base.cbPrice = readCityBlockFile(storePath + "price.txt", 8);

    auto [ genre, matrix ] = readMatrixFile(storePath + "genre.txt", 19);
    base.genreNames = genre;
    base.genreSimilarity = matrix;

    return base;
}

auto calculateCityBlockSimilarity(std::vector<CityBlock> const& cityBlocks, std::string const& input, std::string const& base) -> double {
    auto findCity = [&cityBlocks](std::string const& city) {
        return std::distance(std::begin(cityBlocks), std::find_if(std::begin(cityBlocks), std::end(cityBlocks), [&city](auto const& cityBlock) {
                                 return cityBlock.first == city;
                             }));
    };

    return 1.0 - (std::fabs(findCity(input) - findCity(base)) / static_cast<double>(cityBlocks.size()));
}

auto calculateMatrixSimilarity(BaseAttributesWeights const& weights,
                               GameData const& inputCase, GameData const& baseCase) -> double {
    auto itInputCase = std::find(std::begin(weights.genreNames), std::end(weights.genreNames),
                                 inputCase.genre.front());
    auto itBaseCase = std::find(std::begin(weights.genreNames), std::end(weights.genreNames),
                                baseCase.genre.front());

    auto i = std::distance(std::begin(weights.genreNames), itInputCase);
    auto j = std::distance(std::begin(weights.genreNames), itBaseCase);

    return weights.genreSimilarity.at(i).at(j);
}

auto calculateSimilarity(BaseAttributesWeights const& weights,
                         GameData const& inputCase, GameData const& baseCase) -> double {
    std::string const indif = "Indiferente";

    auto developer = guardSimilarity(indif, inputCase.developer, [&](){
        if (inputCase.developer == baseCase.developer) {
            return 1.0;
        } else {
            return 0.0;
        }
    }) * weights.developer;

    auto publisher = guardSimilarity(indif, inputCase.publisher, [&](){
        if (inputCase.publisher == baseCase.publisher) {
            return 1.0;
        } else {
            return 0.0;
        }
    }) * weights.publisher;

    auto platform = guardSimilarity(indif, inputCase.platform.front(), [&](){
        if (inputCase.platform.front() == baseCase.platform.front()) {
            return 1.0;
        } else {
            return 0.0;
        }
    }) * weights.platform;

    auto resource = guardSimilarity(indif, inputCase.resource.front(), [&](){
        if (inputCase.resource.front() == baseCase.resource.front()) {
            return 1.0;
        } else {
            return 0.0;
        }
    }) * weights.resource;

    auto tag = guardSimilarity(indif, inputCase.tag.front(), [&](){
        if (inputCase.tag.front() == baseCase.tag.front()) {
            return 1.0;
        } else {
            return 0.0;
        }
    }) * weights.tag;

    auto genre = guardSimilarity(indif, inputCase.genre.front(), [&]() {
        return calculateMatrixSimilarity(weights, inputCase, baseCase);
    }) * weights.genre;

    auto requiredAge = guardSimilarity(indif, inputCase.requiredAge, [&]() {
        return calculateCityBlockSimilarity(weights.cbRequiredAge, inputCase.requiredAge, baseCase.requiredAge);
    }) * weights.requiredAge;

    auto achievements = guardSimilarity(indif, inputCase.achievements, [&]() {
        return calculateCityBlockSimilarity(weights.cbAchievements, inputCase.achievements, baseCase.achievements);
    }) * weights.achievements;

    auto positiveRating = guardSimilarity(indif, inputCase.positiveRating, [&]() {
        return calculateCityBlockSimilarity(weights.cbPositiveRating,  inputCase.positiveRating, baseCase.positiveRating);
    }) * weights.positiveRating;

    auto negativeRating = guardSimilarity(indif, inputCase.negativeRating, [&]() {
        return calculateCityBlockSimilarity(weights.cbNegativeRating, inputCase.negativeRating, baseCase.negativeRating);
    }) * weights.negativeRating;

    auto averagePlaytime = guardSimilarity(indif, inputCase.averagePlaytime, [&]() {
        return calculateCityBlockSimilarity(weights.cbAveragePlaytime, inputCase.averagePlaytime, baseCase.averagePlaytime);
    }) * weights.averagePlaytime;

    auto owners = guardSimilarity(indif, inputCase.owners, [&]() {
        return calculateCityBlockSimilarity(weights.cbOwners, inputCase.owners, baseCase.owners);
    }) * weights.owners;

    auto price = guardSimilarity(indif, inputCase.price, [&]() {
        return calculateCityBlockSimilarity(weights.cbPrice, inputCase.price, baseCase.price);
    }) * weights.price;

    auto similaritySum = developer + publisher + platform + requiredAge
                         + resource + genre + tag + achievements
                         + positiveRating + negativeRating + averagePlaytime
                         + owners + price;

    auto weightSum = weights.developer + weights.publisher + weights.platform + weights.requiredAge
                     + weights.resource + weights.genre + weights.tag + weights.achievements
                     + weights.positiveRating + weights.negativeRating + weights.averagePlaytime
                     + weights.owners + weights.price;

    return similaritySum / weightSum;
};

auto calculateAll(GameQuery const& query, GameData const& inputCase) -> GameDataSimilarityCollection {
    GameDataSimilarityCollection collection {};
    collection.reserve(query.collection.size());

    for (auto const& baseCase : query.collection) {
        collection.push_back({
            baseCase,
            calculateSimilarity(query.base, inputCase, baseCase)
        });
    }

    std::stable_sort(std::begin(collection), std::end(collection), [](auto const& l, auto const& r) {
        return r.second < l.second;
    });

    return collection;
}

}
