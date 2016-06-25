//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include <AefFile.h>
#include <PatternRenderer.hpp>

TEST(units, units_test_renderSimpleHit_Test) {
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

    AECE::RenderedAefEvents events;
    AECE::PatternRenderer renderer(AECE::Precision::Micro);
    int Length = 500;
    renderer.RenderPattern(parsedFile.Instruments[0].Patterns[0], 0, 0, 1, Length, &events);
    auto first = 4 * 32 * AECE::Precision::Micro;
    EXPECT_EQ(events.begin()->first, first);
    EXPECT_FALSE(events[first + AECE::Precision::Micro].empty());

}

TEST(basic_check, test_neq) {
EXPECT_NE(1, 0);
}