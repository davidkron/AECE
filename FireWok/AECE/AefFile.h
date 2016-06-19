#include <vector>
#include <string>
#include <algorithm>
#include <yaml-cpp/yaml.h>

#pragma once


struct Location
{
    int Index;
    int Value;
    bool operator ==(const Location& other) const
    {
            return other.Index == Index && other.Value == Value;
    }
};


struct Pattern{
    enum Types{
        IntensityIncrease,Hit,Positional
    };

    Types Type;
    int HitsPerBar;
    int BarsToRepeatAfter;
    std::vector<int> OccoursOn;
    int Offset;
    std::vector<Location> LocationPattern;

    bool ShouldRepeat(){
      return BarsToRepeatAfter > 0;
    }

    int TotalHits(){
      return HitsPerBar * BarsToRepeatAfter;
    }

    int CrotchetTillFirstEvent()
    {
        switch (Type)
        {
            case IntensityIncrease:
            case Hit:
                return OccoursOn[0] -1;
            case Positional:
                return LocationPattern[0].Index - 1;
        }
    }

    bool IndexIsLastHit(int index)
    {
        switch (Type)
        {
            case IntensityIncrease:
            case Hit:
                return index == OccoursOn[OccoursOn.size()];
            case Positional:
                return index == LocationPattern[LocationPattern.size()].Index;
        }
    }

    int GetEventAfter(int currentEvent)
    {
        switch (Type)
        {
            case IntensityIncrease:
            case Hit:
            {
                int prevItemPos = indexOf(OccoursOn,currentEvent);
                auto nextItem = OccoursOn[prevItemPos + 1];
                return nextItem;
            }
            case Positional:
            {
                auto prevItem2 = *std::find_if(LocationPattern.begin(),LocationPattern.end(), [&currentEvent](Location x){
                    return x.Index == currentEvent;
                });
                auto prevItemPos2 = indexOf(LocationPattern,prevItem2);
                auto nextItem2 = LocationPattern[prevItemPos2 + 1];
                return nextItem2.Index;
            }
        }
    }

    template <typename T>
    int indexOf(std::vector<T> ts,T item){
        return std::find(ts.begin(),ts.end(),item) - ts.begin();
    }
};

struct Instrument{
    std::string Name;
    std::vector<Pattern> Patterns;
};

struct AefFile {
public:
    int Tempo;
    std::vector<Instrument> Instruments;

    static AefFile FromFile(std::string path)
    {
        return YAML::LoadFile(path).as<AefFile>();
    }

    static AefFile FromString(std::string contents)
    {
        return YAML::Load(contents).as<AefFile>();
    }
};

namespace YAML {
    template<>
    struct convert<AefFile> {
        static bool decode(const Node& node, AefFile& rhs) {
            rhs.Tempo = node["Tempo"].as<int>();
            rhs.Instruments = node["Instruments"].as<std::vector<Instrument>>();
            return true;
        }
    };

    template<>
    struct convert<Instrument> {
        static bool decode(const Node& node, Instrument& rhs) {
            rhs.Name = node["Name"].as<std::string>();
            rhs.Patterns = node["Patterns"].as<std::vector<Pattern>>();
            return true;
        }
    };

    template<>
    struct convert<Pattern> {
        static bool decode(const Node& node, Pattern& rhs) {
            rhs.BarsToRepeatAfter = node["BarsToRepeatAfter"].as<int>();
            rhs.HitsPerBar = node["HitsPerBar"].as<int>();
            rhs.Type = node["Type"].as<Pattern::Types>();

            if(rhs.Type == Pattern::Types::Hit || rhs.Type == Pattern::Types::IntensityIncrease)
                rhs.OccoursOn = node["OccoursOn"].as<std::vector<int>>();

            if(rhs.Type == Pattern::Types::Positional)
                rhs.LocationPattern = node["LocationPattern"].as<std::vector<Location>>();

            rhs.Offset = node["Offset"].as<int>();
            return true;
        }
    };

    template<>
    struct convert<Pattern::Types> {
        static bool decode(const Node& node, Pattern::Types& rhs) {
            auto str = node.as<std::string>();
            if(str == "IntensityIncrease") rhs = Pattern::Types::IntensityIncrease;
            if(str == "Hit") rhs = Pattern::Types::Hit;
            if(str == "Positional") rhs = Pattern::Types::Positional;
            return true;
        }
    };
    template<>
    struct convert<Location> {
        static bool decode(const Node& node, Location& rhs) {
            rhs.Index = node["Index"].as<int>();
            rhs.Value = node["Value"].as<int>();
            return true;
        }
    };
}


