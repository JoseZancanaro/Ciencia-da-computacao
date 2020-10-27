#include <string>
#include <sstream>
#include <random>

struct Reading
{
    std::string zone;
    int temp;
    int wave_height;
};

auto serialize(Reading const& reading) -> std::string
{
    return reading.zone + " " + std::to_string(reading.temp) + " " + std::to_string(reading.wave_height);
}

auto deserialize(std::string const& input) -> Reading
{
    auto ss = std::istringstream(input);

    auto reading = Reading();
    ss >> reading.zone >> reading.temp >> reading.wave_height;

    return reading;
};

auto make_random_reading(std::string const& zone) -> Reading
{
    std::random_device rd;
    auto gen = std::mt19937(rd());

    auto temp_distribution = std::uniform_int_distribution<>(10, 30);
    auto wave_distribution = std::uniform_int_distribution<>(2, 12);

    return Reading{zone, temp_distribution(gen), wave_distribution(gen)};
}