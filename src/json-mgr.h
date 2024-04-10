// Copyright 2024 Dogan Torosdagli
#pragma once
#include <string>
#include <vector>
#include <boost/json.hpp>

enum class InteractionSeverity {
    UNKNOWN,
    MODERATE,
    MINOR,
    MAJOR
};

struct DrugInfo {
    std::string name;
    std::string ingredients;
    std::vector<std::string> brandNames;
    std::vector<std::string> Generics;
};

struct InteractionDesc {
    std::string name;
    std::string type;
    InteractionSeverity severity;
};

boost::json::array jsonize(const std::vector<std::string>& vec) {
    boost::json::array arr;
    for (const auto& str : vec) {
        arr.push_back(str);
    }
    return arr;
}

boost::json::object jsonize(const InteractionDesc interaction) {
    boost::json::object obj;
    obj["name"] = interaction.name;
    obj["type"] = interaction.type;
}

std::string DrugSerializer(const DrugInfo drug, const std::vector<InteractionDesc> &interactionList) {
    boost::json::object response;
    response["drugName"] = drug.name;
    response["ingredients"] = drug.ingredients;
    response["brandNames"] = jsonize(drug.brandNames);
    response["generics"] = jsonize(drug.Generics);

    boost::json::object interactions;
    boost::json::array majorList, moderateList, minorList, unknownList;
    for (const auto& interaction : interactionList) {
        switch (interaction.severity) {
            case InteractionSeverity::MAJOR:
                majorList.push_back(jsonize(interaction));
                break;
            case InteractionSeverity::MODERATE:
                moderateList.push_back(jsonize(interaction));
                break;
            case InteractionSeverity::MINOR:
                minorList.push_back(jsonize(interaction));
                break;
            case InteractionSeverity::UNKNOWN:
                unknownList.push_back(jsonize(interaction));
        }
    }
    interactions["major"] = majorList;
    interactions["moderate"] = moderateList;
    interactions["minor"] = minorList;
    interactions["unknown"] = unknownList;

    response["interactions"] = interactions;

    return boost::json::serialize(response);
}
