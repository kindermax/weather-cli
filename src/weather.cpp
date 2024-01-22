#include <iostream>
#include <cstdlib>

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

constexpr const char* const API_URL = "https://api.openweathermap.org/data/2.5/weather";

int main(int argc, char* argv[])
{
    const char* api_key = std::getenv("API_KEY");

    if (!api_key)
    {
        std::cout << "Set API_KEY environment variable" << std::endl;
        std::exit(1);
    }

    if (argc == 1)
    {
        std::cout << "Provide city" << std::endl;
        std::exit(1);
    }

    char* city = argv[1];

    cpr::Response r = cpr::Get(
        cpr::Url{API_URL},
        cpr::Parameters{
            {"q", city},
            {"APPID", api_key},
            {"units", "metric"}
        }
    );
    if (r.status_code == 401) {
        std::cout << "Invalid API_KEY: " << r.text << std::endl;
        std::exit(1);
    }

    json data = json::parse(r.text);

    std::cout << "The weather in " << city << std::endl;
    std::cout << "Temp: " << data["main"]["temp"] << std::endl;
    std::cout << "Temp feels like: " << data["main"]["feels_like"] << std::endl;
    std::cout << "Humidity:" << data["main"]["humidity"] << std::endl;
    std::cout << "Wind: " << data["wind"]["speed"] << std::endl;

    return 0;
}
