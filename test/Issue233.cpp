// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#include <ArduinoJson.h>
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

TEST(Issue233, ShouldNotCrash) {
  String jsonstring =
      "{\"plugins\":{\"ds18b20\":\"enables the use of DS18B20 "
      "sensor\",\"dht\":\"enables the use of DHT sensor\"}}";
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json =
      jsonBuffer.parseObject(const_cast<char*>(jsonstring.c_str()));

  std::ostringstream out;

  if (!json.success()) {
    out << "Failed to parse config file" << std::endl;
  } else {
    JsonObject& plugins = json["plugins"];
    for (JsonObject::iterator it = plugins.begin(); it != plugins.end(); ++it) {
      out << it->key << std::endl;
      out << it->value.asString() << std::endl;
    }
  }

  EXPECT_EQ(
      "ds18b20\n"
      "enables the use of DS18B20 sensor\n"
      "dht\n"
      "enables the use of DHT sensor\n",
      out.str());
}
