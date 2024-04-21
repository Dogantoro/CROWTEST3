// Copyright 2024 Dogan Torosdagli
#pragma once
#include <string>
#include <vector>
#include <boost/json/src.hpp>

// Enum of levels of drug interactions
enum class InteractionSeverity {
    UNKNOWN,
    MODERATE,
    MINOR,
    MAJOR,
    NONE
};

// Record of a single drug interaction
struct InteractionDesc {
    std::string name;
    InteractionSeverity severity;
};

// Complete drug information
struct DrugInfo {
    std::string name;
    std::string ingredients;
    std::vector<std::string> brandNames;
    std::vector<std::string> Generics;
    std::vector<InteractionDesc> interactions;
};

// converts string to correct interaction severity enum
InteractionSeverity convert(std::string inter) {
    if (inter == "Moderate")    return InteractionSeverity::MODERATE;
    if (inter == "Minor")       return InteractionSeverity::MINOR;
    if (inter == "Major")       return InteractionSeverity::MAJOR;
    if (inter == "Unknown")     return InteractionSeverity::UNKNOWN;
    return InteractionSeverity::NONE;
}

// converts a C++ string vector into a JSON string array
boost::json::array jsonize(const std::vector<std::string>& vec) {
    boost::json::array arr;
    for (const auto& str : vec) {
        arr.emplace_back(str);
    }
    return arr;
}

// Converts Drug + List of its interactions into a single JSON file
std::string DrugSerializer(const DrugInfo drug) {
    std::vector<InteractionDesc> interactionList = drug.interactions;
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
                majorList.emplace_back(interaction.name);
                break;
            case InteractionSeverity::MODERATE:
                moderateList.emplace_back(interaction.name);
                break;
            case InteractionSeverity::MINOR:
                minorList.emplace_back(interaction.name);
                break;
            default:
                unknownList.emplace_back(interaction.name);
        }
    }
    interactions["major"] = majorList;
    interactions["moderate"] = moderateList;
    interactions["minor"] = minorList;
    interactions["unknown"] = unknownList;

    response["interactions"] = interactions;

    return boost::json::serialize(response);
}

