//
// Created by tywael on 1/16/23.
//

#include "../inc/Location.hpp"
#include <map>
#include <iostream>

Location &check_location(const std::map<std::string, Location*> &locations, std::string uri)
{
    while (uri.size() > 1) {
        if (locations.find(uri) != locations.end())
            return(*(locations.find(uri)->second));
        uri = uri.substr(0, uri.rfind("/"));
    }
    if (locations.find("/") != locations.end())
        return(*(locations.find("/")->second));
    return (*locations.begin()->second);
}
