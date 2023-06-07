#include <map>
#include <vector>

namespace WeatherForecast {

const int kDateI = 1;
const int kDateJ = 54;

const int kHoursInDay = 24;

const int kBlockPictureI = 4;
const int kBlocksPictureJ[4] = {1, 30, 59, 88};
const int kBlockPictureSizeI = 5;

const int kBlockInfoI = 4;
const int kBlocksInfoJ[4] = {15, 44, 73, 102};

const int kMaxNumDaysWeather = 16;

const std::vector<std::string> kWeatherMatrix = {
    "\n",
    "---------------------------------------------------------------------------------------------------------------------\n",
    "|           night            |           morning          |           afternoon        |           evening          |\n",
    "---------------------------------------------------------------------------------------------------------------------\n",
    "|                            |                            |                            |                            |\n",
    "|                            |                            |                            |                            |\n",
    "|                            |                            |                            |                            |\n",
    "|                            |                            |                            |                            |\n",
    "|                            |                            |                            |                            |\n",
    "---------------------------------------------------------------------------------------------------------------------\n"
};

std::string WindDirection(const int& degree) {
  if (337.5 <= degree or degree < 22.5) return "N";
  else if (22.5 <= degree and degree < 67.5) return "NE";
  else if (67.5 <= degree and degree < 112.5) return "E";
  else if (112.5 <= degree and degree < 157.5) return "SE";
  else if (157.5 <= degree and degree < 202.5) return "S";
  else if (202.5 <= degree and degree < 247.5) return "SW";
  else if (247.5 <= degree and degree < 292.5) return "W";
  else if (292.5 <= degree and degree < 337.5) return "NW";
  return {};
}

const std::unordered_map<int, std::string> kWMOCode = {
    {0, "Sunny"},
    {1, "PartlyCloudy"},
    {2, "PartlyCloudy"},
    {3, "Cloudy"},
    {3, "VeryCloudy"},
    {45, "Fog"},
    {48, "Fog"},
    {51, "LightRain"},
    {53, "HeavyRain"},
    {55, "HeavyRain"},
    {56, "HeavyRain"},
    {57, "HeavyRain"},
    {61, "LightRain"},
    {63, "HeavyRain"},
    {65, "HeavyRain"},
    {66, "LightSnowShowers"},
    {67, "HeavySnowShowers"},
    {71, "LightSnow"},
    {73, "HeavySnow"},
    {75, "HeavySnow"},
    {77, "ThunderySnowShowers"},
    {80, "LightRain"},
    {81, "HeavyRain"},
    {82, "HeavyRain"},
    {85, "LightSnowShowers"},
    {86, "HeavySnowShowers"},
    {95, "ThunderyHeavyRain"},
    {96, "ThunderyHeavyRain"},
    {99, "ThunderyHeavyRain"}
};

const std::unordered_map<std::string, std::vector<std::string>> kWeatherSymbolWEGO = {
    {"Sunny", {
        "     \\   /   ",
        "      .-.     ",
        " --- (   )=== ",
        "      `-`     ",
        "     /   \\   "}},
    {"PartlyCloudy", {
        "              ",
        "     .-.      ",
        "    (   ).    ",
        "   (___(__)   ",
        "              "}},
    {"Cloudy", {
        "              ",
        "     .--.     ",
        "  .-(    ).   ",
        " (___.__)__)  ",
        "              "}},
    {"VeryCloudy", {
        "              ",
        "     .--.     ",
        "  .-(    ).   ",
        " (___.__)__)  ",
        "              "}},
    {"LightShowers", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "    ' ' ' '   ",
        "   ' ' ' '    "}},
    {"HeavyShowers", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "   ‚'‚'‚'‚'   ",
        "   ‚'‚'‚'‚'   "}},
    {"LightSnowShowers", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "     *  *  *  ",
        "    *  *  *   "}},
    {"HeavySnowShowers", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "    * * * *   ",
        "   * * * *    "}},
    {"LightSleetShowers", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "    ' * ' *   ",
        "   * ' * '    "}},
    {"ThunderyShowers", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "    ⚡ '' ⚡''  ",
        "    ' ' ' '   "}},
    {"ThunderyHeavyRain", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "   '⚡ '‚ ⚡ '  ",
        "   ‚'‚'⚡'‚'   "}},
    {"ThunderySnowShowers", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "   * ⚡ * ⚡ *  ",
        "   *  *  *    "}},
    {"LightRain", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "    ` ` ` `   ",
        "   ` ` ` `    "}},
    {"HeavyRain", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "   ,`,`,`,`   ",
        "  ,`,`,`,`    "}},
    {"LightSnow", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "    *  *  *   ",
        "   *  *  *    "}},
    {"HeavySnow", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "    * * * *   ",
        "   * * * *    "}},
    {"LightSleet", {
        "      .-.     ",
        "     (   ).   ",
        "    (___(__)  ",
        "   '   '   *  ",
        "    * '  '    "}},
    {"Fog", {
        "              ",
        " _ - _ - _ -  ",
        "  _ - _ - _   ",
        " _ - _ - _ -  ",
        "              "}}
};

}