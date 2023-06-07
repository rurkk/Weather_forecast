#include "WeatherForecast.h"
#include <conio.h>


int main() {
  std::string path = R"(C:\Users\raulm\labwork-10-rurkk\config.json)";
  WeatherForecast::Parser parser(path);

  const int max_city_ind = parser.cities_.size() - 1;
  int cur_city_ind = 0;
  const int max_n_days = WeatherForecast::kMaxNumDaysWeather;
  const int default_n_days = parser.days_;
  int cur_n_days = default_n_days;
  const int update_freq = parser.frequency_;

  WeatherForecast::ConfigWeatherData config_weather(parser);
  config_weather.PrintCityWeather(cur_city_ind, cur_n_days);

  size_t start_clock = clock();
  size_t end_clock = start_clock + update_freq;

  int key;
  while (true) {
    start_clock = clock();
    if (start_clock >= end_clock) {
      config_weather.UpdateWeatherData();
      system("cls");
      config_weather.PrintCityWeather(cur_city_ind, cur_n_days);
      start_clock = clock();
      end_clock = start_clock + update_freq;
    }
    if (_kbhit()) {  // Check if a key is pressed
      key = _getch();
      if (key == 27) { // esc
        break;
      } else if (key == 43 || key == 45 || key == 61) { // + and -
        if (key == 43 || key == 61) {
          if (cur_n_days < max_n_days) {
            cur_n_days++;
            config_weather.PrintDayCityWeather(cur_city_ind, cur_n_days - 1);
          }
        } else {
          if (cur_n_days > 0) {
            cur_n_days--;
            system("cls");
            config_weather.PrintCityWeather(cur_city_ind, cur_n_days);
          }
        }
      } else if (key == 110 || key == 112) { // n and p
        if (key == 110) {
          if (cur_city_ind > 0) {
            cur_city_ind--;
            system("cls");
            config_weather.PrintCityWeather(cur_city_ind, cur_n_days);
          }
        } else {
          if (cur_city_ind < max_city_ind) {
            cur_city_ind++;
            system("cls");
            config_weather.PrintCityWeather(cur_city_ind, cur_n_days);
          }
        }
      }
    }
  }
  return 0;
}