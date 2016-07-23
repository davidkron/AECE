//
// Created by david on 2016-07-02.
//
#include <typedefs.h>
#include <AefFile.h>
#include <AudioEvent.hpp>
#include <PatternRenderer.hpp>
#include <yaml-cpp/yaml.h>

int main(){
    AECE::RenderedAefEvents events;
    unsigned long long int first;
    auto parsedFile = AefFile::FromString(
"Tempo: 90\n"
"Instruments: \n"
"- Name: Somename\n"
"  Patterns: \n"
"  - Type: Hit\n"
"    OccoursOn: [1,2,3,4]\n"
"    HitsPerBar: 4\n"
"    Offset: 32\n"
"    BarsToRepeatAfter: 1\n"
"    BarsToRepeat: 1");

    AECE::PatternRenderer renderer(AECE::Precision::Micro);
    int Length = 500;
    renderer.RenderPattern(parsedFile.Instruments[0].Patterns[0], 0, 0, 1, Length, &events);


    first = 4 * 32 * AECE::Precision::Micro;
    return 0;
}