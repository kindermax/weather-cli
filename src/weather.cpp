#include <cpr/cpr.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

constexpr const char *const API_URL =
    "https://api.openweathermap.org/data/2.5/weather";

class WeatherInfo {
 public:
  std::string city;
  std::float_t temperature;
  std::float_t temperature_feels_like;
  std::int16_t humidity;
  std::float_t wind_speed;

  static std::shared_ptr<WeatherInfo> parse_json(std::string city, json data) {
    auto info = std::make_shared<WeatherInfo>();

    info->city = city;
    info->temperature = data["main"]["temp"];
    info->temperature_feels_like = data["main"]["feels_like"];
    info->humidity = data["main"]["humidity"];
    info->wind_speed = data["wind"]["speed"];

    return std::move(info);
  }
};

void print_weather_info(std::shared_ptr<WeatherInfo> info) {
  std::cout << "The weather in " << info->city << std::endl;
  std::cout << "Temp: " << info->temperature << std::endl;
  std::cout << "Temp feels like: " << info->temperature_feels_like << std::endl;
  std::cout << "Humidity: " << info->humidity << std::endl;
  std::cout << "Wind: " << info->wind_speed << std::endl;
}

int main(int argc, char *argv[]) {
  const char *api_key = std::getenv("API_KEY");

  if (!api_key) {
    std::cout << "Set API_KEY environment variable" << std::endl;
    std::exit(1);
  }

  if (argc == 1) {
    std::cout << "Provide city" << std::endl;
    std::exit(1);
  }

  char *city = argv[1];

  cpr::Response r = cpr::Get(
      cpr::Url{API_URL},
      cpr::Parameters{{"q", city}, {"APPID", api_key}, {"units", "metric"}});

  if (r.status_code == 401) {
    std::cout << "Invalid API_KEY: " << r.text << std::endl;
    std::exit(1);
  }

  json data = json::parse(r.text);

  std::shared_ptr<WeatherInfo> info =
      WeatherInfo::parse_json(std::string{city}, data);
  print_weather_info(info);

  return 0;
}
