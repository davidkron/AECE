//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include <AefFile.h>

TEST(basic_check, test_eq) {
    auto parsedFile = AefFile::FromString(
"Tempo: 90\n"
"Instruments: \n"
"- Name: HighPitchGlider\n"
"  Patterns: \n"
"  - Type: Positional\n"
"    LocationPattern: \n"
"    - {Index: 1, Value: 1}\n"
"    - {Index: 4, Value: 2}\n"
"    - {Index: 5, Value: 3}\n"
"    - {Index: 8, Value: 4}\n"
"    #- {Index: 9, Value: 5}\n"
"    - {Index: 13, Value: 0}\n"
"    HitsPerBar: 4\n"
"    Offset: 16\n"
"    BarsToRepeatAfter: 4\n"
"  - Type: Hit\n"
"    OccoursOn: [1,2,3,4]\n"
"    HitsPerBar: 4\n"
"    Offset: 32\n"
"    BarsToRepeatAfter: 1\n"
"- Name: HighPitchBam\n"
"  Patterns: \n"
"  - Type: Hit\n"
"    OccoursOn: [9]\n"
"    HitsPerBar: 4\n"
"    Offset: 16\n"
"    BarsToRepeatAfter: 4\n"
"- Name: Balls\n"
"  Patterns: \n"
"  - Type: Positional\n"
"    LocationPattern: \n"
"    - {Index: 1, Value: -1}\n"
"    - {Index: 2, Value: -1}\n"
"    - {Index: 3, Value: 1}\n"
"    - {Index: 4, Value: 1}\n"
"    - {Index: 5, Value: -1}\n"
"    - {Index: 6, Value: -1}\n"
"    - {Index: 7, Value: 1}\n"
"    - {Index: 8, Value: 1}\n"
"    HitsPerBar: 8\n"
"    Offset: 0\n"
"    BarsToRepeatAfter: 1\n"
"- Name: IntensityIncrease\n"
"  Patterns: \n"
"  - Type: IntensityIncrease\n"
"    OccoursOn: [1]\n"
"    HitsPerBar: 4\n"
"    Offset: 32 \n"
"    BarsToRepeatAfter: 4\n"
"- Name: Kling\n"
"  Patterns:  \n"
"  - Type: Hit\n"
"    OccoursOn: [2,6,8,10,12,14,16]\n"
"    HitsPerBar: 4\n"
"    Offset: 32\n"
"    BarsToRepeatAfter: 4\n"
"    \n"
"    #9  > Sprid (32)\n"
"    #13 > Upp (48)\n"
"    #17 > runt (64)\n"
"    #21 spräng (80)");
EXPECT_EQ(1, 0);
}

TEST(basic_check, test_neq) {
EXPECT_NE(1, 0);
}