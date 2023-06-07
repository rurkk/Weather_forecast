#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "WeatherConstants.h"

namespace WeatherForecast {

struct BlockWeatherData {
  int weather_code_;
  float temperature_;
  int wind_direction_;
  float wind_speed_;
  int surface_pressure_;
  float precipitation_;
  int precipitation_probability_;
};

struct DayWeatherData {
  std::vector<BlockWeatherData> blocks_data_;
  std::vector<std::string> weather_matrix_;

  DayWeatherData(const nlohmann::json& weather_json, int day_index) {
    weather_matrix_ = kWeatherMatrix;
    std::string str;
    // date
    str = (static_cast<std::string>(weather_json["hourly"]["time"][day_index * kHoursInDay])).erase(10, 6);
    StringWriter(str, kDateI, kDateJ);
    // filling the one-day blocks
    int time_code;
    time_code = 0;
    for (int i_hour = 3; i_hour < kHoursInDay; i_hour += 6) {
      BlockWeatherData block{};
      // weather condition
      block.weather_code_ = weather_json["hourly"]["weathercode"][day_index * kHoursInDay + i_hour];
      str = kWMOCode.find(block.weather_code_)->second;
      StringWriter(str, kBlockInfoI, kBlocksInfoJ[time_code]);
      // picture
      for (int j = 0; j < kBlockPictureSizeI; j++) {
        StringWriter((kWeatherSymbolWEGO.find(str)->second).at(j), kBlockPictureI + j, kBlocksPictureJ[time_code]);
      }
      // temperature
      block.temperature_ = weather_json["hourly"]["temperature_2m"][day_index * kHoursInDay + i_hour];
      str = std::to_string(block.temperature_).substr(0, 4) + " C";
      StringWriter(str, kBlockInfoI + 1, kBlocksInfoJ[time_code]);
      // direction and speed of wind
      block.wind_direction_ = weather_json["hourly"]["winddirection_10m"][day_index * kHoursInDay + i_hour];
      block.wind_speed_ = weather_json["hourly"]["windspeed_10m"][day_index * kHoursInDay + i_hour];
      str = WindDirection(block.wind_direction_) + " | " + std::to_string(block.wind_speed_).substr(0, 4) + " km/h";
      StringWriter(str, kBlockInfoI + 2, kBlocksInfoJ[time_code]);
      // pressure
      block.surface_pressure_ = weather_json["hourly"]["surface_pressure"][day_index * kHoursInDay + i_hour];
      str = std::to_string(block.surface_pressure_) + " hPa";
      StringWriter(str, kBlockInfoI + 3, kBlocksInfoJ[time_code]);
      // precipitations
      block.precipitation_ = weather_json["hourly"]["precipitation"][day_index * kHoursInDay + i_hour];
      if ((weather_json["hourly"]["precipitation_probability"][day_index * kHoursInDay + i_hour]) == nullptr) {
        block.precipitation_probability_ = -1;
      } else {
        block.precipitation_probability_ =
            weather_json["hourly"]["precipitation_probability"][day_index * kHoursInDay + i_hour];
      }
      str = std::to_string(block.precipitation_).substr(0, 3) + " mm | "
          + std::to_string(block.precipitation_probability_) + " %";
      StringWriter(str, kBlockInfoI + 4, kBlocksInfoJ[time_code]);

      blocks_data_.push_back(block);
      time_code++;
    }
  }

  void StringWriter(const std::string& str, int I, int J) {
    for (int i = 0; i < str.size(); i++) {
      weather_matrix_[I][J + i] = str[i];
    }
  }

  void PrintDayWeather() {
    for (auto& i : weather_matrix_) {
      std::cout << i;
    }
  }

  ~DayWeatherData() = default;
};

struct CityWeatherData {
  std::vector<DayWeatherData> days_data_;
  std::string city_;

  explicit CityWeatherData(std::string city) : city_(city) {
    //coordinates
    cpr::Response coordinates_response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                                  cpr::Parameters{{"name", city}},
                                                  cpr::Header{
                                                      {"X-Api-Key", "hLMAVxkFaCcNIHDGYMWzDg==eN0sjXQ8bljRs5CZ"}});
    if (coordinates_response.error.code != cpr::ErrorCode::OK) {
      throw std::invalid_argument(coordinates_response.error.message);
    }
    nlohmann::json coordinates_json = nlohmann::json::parse(coordinates_response.text);
    std::string latitude = std::to_string(static_cast<double>(coordinates_json[0]["latitude"]));
    std::string longitude = std::to_string(static_cast<double>(coordinates_json[0]["longitude"]));
    //weather json
    cpr::Response weather_response = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                              cpr::Parameters{{"latitude", latitude},
                                                              {"longitude", longitude},
                                                              {"hourly",
                                                               "temperature_2m,relativehumidity_2m,"
                                                               "precipitation_probability,precipitation,weathercode,"
                                                               "surface_pressure,windspeed_10m,winddirection_10m"},
                                                              {"forecast_days", "16"},
                                                              {"timezone", "auto"}});
    if (weather_response.error.code != cpr::ErrorCode::OK) {
      throw std::invalid_argument(weather_response.error.message);
    }
    nlohmann::json weather_json = nlohmann::json::parse(weather_response.text);
    //parse json
    for (int i = 0; i < kMaxNumDaysWeather; i++) {
      days_data_.emplace_back(DayWeatherData(weather_json, i));
    }
  }

  void PrintWeather(int cnt_days) {
    std::cout << "Weather forecast: " << city_ << '\n';
    for (int i = 0; i < cnt_days; i++) {
      days_data_[i].PrintDayWeather();
    }
  }

  void PrintDayWeather(int day) {
    days_data_[day].PrintDayWeather();
  }

  ~CityWeatherData() = default;
};

struct Parser {
  int days_;
  int frequency_;
  std::vector<std::string> cities_;
  explicit Parser(const std::string& path) {
    std::ifstream config_file(path);
    nlohmann::json config_json = nlohmann::json::parse(config_file);
    days_ = config_json["days"];
    frequency_ = config_json["frequency"];
    cities_ = config_json["cities"];
  }
};

struct ConfigWeatherData {
  std::vector<CityWeatherData> cities_weather_;
  Parser parser_;
  explicit ConfigWeatherData(const Parser& parser) : parser_(parser) {
    for (auto& city : parser.cities_) {
      cities_weather_.emplace_back(WeatherForecast::CityWeatherData(city));
    }
  }
  void PrintCityWeather(int city_ind, int n_days) {
    cities_weather_[city_ind].PrintWeather(n_days);
  };
  void PrintDayCityWeather(int city_ind, int n_day) {
    cities_weather_[city_ind].PrintDayWeather(n_day);
  };
  void UpdateWeatherData() {
    cities_weather_.clear();
    for (auto& city : parser_.cities_) {
      cities_weather_.emplace_back(WeatherForecast::CityWeatherData(city));
    }
  }
};

}
