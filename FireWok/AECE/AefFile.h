#include <vector>
#include <string>
#include <algorithm>
#include <yaml-cpp\yaml.h>
#include <memory>

#pragma once

/*template <typename T>
int indexOf(std::vector<T> ts,T item){
    return std::find(ts.begin(),ts.end(),item) - ts.begin();
}*/

struct BasicPattern {
    virtual int CrotchetTillFirstEvent() const = 0;
    virtual bool IndexIsLastHit(int index) const = 0;
    virtual int GetEventAfter(int currentEvent) const = 0;
};

class PositionalPattern : public BasicPattern {
    std::map<int, int> LocationPattern;
public:
    PositionalPattern(std::map<int, int> locationPattern) : LocationPattern(locationPattern) { }

    int GetLocation(int index) {
        return LocationPattern[index];
    }

    virtual int CrotchetTillFirstEvent() const {
        return LocationPattern.begin()->first - 1;
    }

    virtual bool IndexIsLastHit(int index) const {
        return index == LocationPattern.rbegin()->first;
    }

    virtual int GetEventAfter(int currentEvent) const {
        auto prevItemIterator = LocationPattern.find(currentEvent);
        return std::next(prevItemIterator)->first;
    }
};

class HitPattern : public BasicPattern {
    std::vector<int> OccoursOn;
public:
    HitPattern(std::vector<int> occoursOn) : OccoursOn(occoursOn) { }

    int CrotchetTillFirstEvent() const {
        return OccoursOn[0] - 1;
    }

    bool IndexIsLastHit(int index) const {
        return index == OccoursOn[OccoursOn.size()];
    }

    int GetEventAfter(int currentEvent) const {
        return std::next(std::find(OccoursOn.begin(), OccoursOn.end(), currentEvent)) - OccoursOn.begin();
    }
};


struct Pattern {
    enum Types {
        IntensityIncrease, Hit, Positional
    };
    std::shared_ptr<BasicPattern> base;
    Types Type;
    int BarsToRepeatAfter;
    int HitsPerBar;
    int Offset;
    int index = 0;

    bool ShouldRepeat() {
        return BarsToRepeatAfter > 0;
    }

    int TimeTillNextEvent();

    int Progress() {

    }

    int CrotchetTillFirstEvent() const {
        return base->CrotchetTillFirstEvent();
    }

    int TotalHits() {
        return HitsPerBar * BarsToRepeatAfter;
    }

public:
    template<typename T>
    T *As() const {
        return dynamic_cast<T *>(base.get());
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
            rhs.Patterns = std::move(node["Patterns"].as<std::vector<Pattern>>());
            return true;
        }
    };

#include <memory>

    template<>
    struct convert<Pattern> {
        static bool decode(const Node& node, Pattern& rhs) {

            rhs.Type = node["Type"].as<Pattern::Types>();

            switch (rhs.Type) {
                case Pattern::Types::Positional: {
                    auto map = node["LocationPattern"].as<std::map<int, int>>();
                    rhs.base.reset(new PositionalPattern(map));
                    break;
                }
                case Pattern::Types::Hit:
                case Pattern::Types::IntensityIncrease: {
                    auto patternVector = node["OccoursOn"].as<std::vector<int>>();
                    rhs.base.reset(new HitPattern(patternVector));
                    break;
                }
            }

            rhs.BarsToRepeatAfter = node["BarsToRepeatAfter"].as<int>();
            rhs.HitsPerBar = node["HitsPerBar"].as<int>();
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
		static Node encode(const Pattern::Types& rhs) {
			Node n;
			if (rhs == Pattern::Types::IntensityIncrease) n = "IntensityIncrease";
			if (rhs == Pattern::Types::Hit ) n = "Hit";
			if (rhs == Pattern::Types::Positional) n = "Positional";
			return n;
		}
    };
}


