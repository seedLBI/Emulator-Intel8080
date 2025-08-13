#include "Unicode.h"


const std::vector<UnicodeRanges> UnicodeBlocks = {
    UnicodeRanges{0x0000, 0x007f},
UnicodeRanges{0x0080, 0x00ff},
UnicodeRanges{0x0100, 0x017f},
UnicodeRanges{0x0180, 0x024f},
UnicodeRanges{0x0250, 0x02af},
UnicodeRanges{0x02b0, 0x02ff},
UnicodeRanges{0x0300, 0x036f},
UnicodeRanges{0x0370, 0x03ff},
UnicodeRanges{0x0400, 0x04ff},
UnicodeRanges{0x0500, 0x052f},
UnicodeRanges{0x0530, 0x058f},
UnicodeRanges{0x0590, 0x05ff},
UnicodeRanges{0x0600, 0x06ff},
UnicodeRanges{0x0700, 0x074f},
UnicodeRanges{0x0750, 0x077f},
UnicodeRanges{0x0780, 0x07bf},
UnicodeRanges{0x07c0, 0x07ff},
UnicodeRanges{0x0800, 0x083f},
UnicodeRanges{0x0840, 0x085f},
UnicodeRanges{0x0860, 0x086f},
UnicodeRanges{0x0870, 0x089f},
UnicodeRanges{0x08a0, 0x08ff},
UnicodeRanges{0x0900, 0x097f},
UnicodeRanges{0x0980, 0x09ff},
UnicodeRanges{0x0a00, 0x0a7f},
UnicodeRanges{0x0a80, 0x0aff},
UnicodeRanges{0x0b00, 0x0b7f},
UnicodeRanges{0x0b80, 0x0bff},
UnicodeRanges{0x0c00, 0x0c7f},
UnicodeRanges{0x0c80, 0x0cff},
UnicodeRanges{0x0d00, 0x0d7f},
UnicodeRanges{0x0d80, 0x0dff},
UnicodeRanges{0x0e00, 0x0e7f},
UnicodeRanges{0x0e80, 0x0eff},
UnicodeRanges{0x0f00, 0x0fff},
UnicodeRanges{0x1000, 0x109f},
UnicodeRanges{0x10a0, 0x10ff},
UnicodeRanges{0x1100, 0x11ff},
UnicodeRanges{0x1200, 0x137f},
UnicodeRanges{0x1380, 0x139f},
UnicodeRanges{0x13a0, 0x13ff},
UnicodeRanges{0x1400, 0x167f},
UnicodeRanges{0x1680, 0x169f},
UnicodeRanges{0x16a0, 0x16ff},
UnicodeRanges{0x1700, 0x171f},
UnicodeRanges{0x1720, 0x173f},
UnicodeRanges{0x1740, 0x175f},
UnicodeRanges{0x1760, 0x177f},
UnicodeRanges{0x1780, 0x17ff},
UnicodeRanges{0x1800, 0x18af},
UnicodeRanges{0x18b0, 0x18ff},
UnicodeRanges{0x1900, 0x194f},
UnicodeRanges{0x1950, 0x197f},
UnicodeRanges{0x1980, 0x19df},
UnicodeRanges{0x19e0, 0x19ff},
UnicodeRanges{0x1a00, 0x1a1f},
UnicodeRanges{0x1a20, 0x1aaf},
UnicodeRanges{0x1ab0, 0x1aff},
UnicodeRanges{0x1b00, 0x1b7f},
UnicodeRanges{0x1b80, 0x1bbf},
UnicodeRanges{0x1bc0, 0x1bff},
UnicodeRanges{0x1c00, 0x1c4f},
UnicodeRanges{0x1c50, 0x1c7f},
UnicodeRanges{0x1c80, 0x1c8f},
UnicodeRanges{0x1c90, 0x1cbf},
UnicodeRanges{0x1cc0, 0x1ccf},
UnicodeRanges{0x1cd0, 0x1cff},
UnicodeRanges{0x1d00, 0x1d7f},
UnicodeRanges{0x1d80, 0x1dbf},
UnicodeRanges{0x1dc0, 0x1dff},
UnicodeRanges{0x1e00, 0x1eff},
UnicodeRanges{0x1f00, 0x1fff},
UnicodeRanges{0x2000, 0x206f},
UnicodeRanges{0x2070, 0x209f},
UnicodeRanges{0x20a0, 0x20cf},
UnicodeRanges{0x20d0, 0x20ff},
UnicodeRanges{0x2100, 0x214f},
UnicodeRanges{0x2150, 0x218f},
UnicodeRanges{0x2190, 0x21ff},
UnicodeRanges{0x2200, 0x22ff},
UnicodeRanges{0x2300, 0x23ff},
UnicodeRanges{0x2400, 0x243f},
UnicodeRanges{0x2440, 0x245f},
UnicodeRanges{0x2460, 0x24ff},
UnicodeRanges{0x2500, 0x257f},
UnicodeRanges{0x2580, 0x259f},
UnicodeRanges{0x25a0, 0x25ff},
UnicodeRanges{0x2600, 0x26ff},
UnicodeRanges{0x2700, 0x27bf},
UnicodeRanges{0x27c0, 0x27ef},
UnicodeRanges{0x27f0, 0x27ff},
UnicodeRanges{0x2800, 0x28ff},
UnicodeRanges{0x2900, 0x297f},
UnicodeRanges{0x2980, 0x29ff},
UnicodeRanges{0x2a00, 0x2aff},
UnicodeRanges{0x2b00, 0x2bff},
UnicodeRanges{0x2c00, 0x2c5f},
UnicodeRanges{0x2c60, 0x2c7f},
UnicodeRanges{0x2c80, 0x2cff},
UnicodeRanges{0x2d00, 0x2d2f},
UnicodeRanges{0x2d30, 0x2d7f},
UnicodeRanges{0x2d80, 0x2ddf},
UnicodeRanges{0x2de0, 0x2dff},
UnicodeRanges{0x2e00, 0x2e7f},
UnicodeRanges{0x2e80, 0x2eff},
UnicodeRanges{0x2f00, 0x2fef},
UnicodeRanges{0x2ff0, 0x2fff},
UnicodeRanges{0x3000, 0x303f},
UnicodeRanges{0x3040, 0x309f},
UnicodeRanges{0x30a0, 0x30ff},
UnicodeRanges{0x3100, 0x312f},
UnicodeRanges{0x3130, 0x318f},
UnicodeRanges{0x3190, 0x319f},
UnicodeRanges{0x31a0, 0x31bf},
UnicodeRanges{0x31c0, 0x31ef},
UnicodeRanges{0x31f0, 0x31ff},
UnicodeRanges{0x3200, 0x32ff},
UnicodeRanges{0x3300, 0x33ff},
UnicodeRanges{0x3400, 0x4dbf},
UnicodeRanges{0x4dc0, 0x4dff},
UnicodeRanges{0x4e00, 0x9fff},
UnicodeRanges{0xa000, 0xa48f},
UnicodeRanges{0xa490, 0xa4cf},
UnicodeRanges{0xa4d0, 0xa4ff},
UnicodeRanges{0xa500, 0xa63f},
UnicodeRanges{0xa640, 0xa69f},
UnicodeRanges{0xa6a0, 0xa6ff},
UnicodeRanges{0xa700, 0xa71f},
UnicodeRanges{0xa720, 0xa7ff},
UnicodeRanges{0xa800, 0xa82f},
UnicodeRanges{0xa830, 0xa83f},
UnicodeRanges{0xa840, 0xa87f},
UnicodeRanges{0xa880, 0xa8df},
UnicodeRanges{0xa8e0, 0xa8ff},
UnicodeRanges{0xa900, 0xa92f},
UnicodeRanges{0xa930, 0xa95f},
UnicodeRanges{0xa960, 0xa97f},
UnicodeRanges{0xa980, 0xa9df},
UnicodeRanges{0xa9e0, 0xa9ff},
UnicodeRanges{0xaa00, 0xaa5f},
UnicodeRanges{0xaa60, 0xaa7f},
UnicodeRanges{0xaa80, 0xaadf},
UnicodeRanges{0xaae0, 0xaaff},
UnicodeRanges{0xab00, 0xab2f},
UnicodeRanges{0xab30, 0xab6f},
UnicodeRanges{0xab70, 0xabbf},
UnicodeRanges{0xabc0, 0xabff},
UnicodeRanges{0xac00, 0xd7af},
UnicodeRanges{0xd7b0, 0xd7ff},
UnicodeRanges{0xd800, 0xdb7f},
UnicodeRanges{0xdb80, 0xdbff},
UnicodeRanges{0xdc00, 0xdfff},
UnicodeRanges{0xe000, 0xf8ff},
UnicodeRanges{0xf900, 0xfaff},
UnicodeRanges{0xfb00, 0xfb4f},
UnicodeRanges{0xfb50, 0xfdff},
UnicodeRanges{0xfe00, 0xfe0f},
UnicodeRanges{0xfe10, 0xfe1f},
UnicodeRanges{0xfe20, 0xfe2f},
UnicodeRanges{0xfe30, 0xfe4f},
UnicodeRanges{0xfe50, 0xfe6f},
UnicodeRanges{0xfe70, 0xfeff},
UnicodeRanges{0xff00, 0xffef},
UnicodeRanges{0xfff0, 0xffff}
};




uint64_t strUTF8Symbol_to_UnicodeValue(const std::string& UTF8Symbol) {
    uint64_t result = 0;
    if (UTF8Symbol.empty())
        return result;
    if (UTF8Symbol.size() == 1)
        result = UTF8Symbol[0] & 0b01111111;
    else if (UTF8Symbol.size() == 2) {
        uint64_t first = UTF8Symbol[1] & 0b00111111;
        uint64_t second = (static_cast<uint64_t>(UTF8Symbol[0] & 0b00011111)) << 6;

        result = first + second;
    }
    else if (UTF8Symbol.size() == 3) {
        uint64_t first = UTF8Symbol[2] & 0b00111111;
        uint64_t second = (static_cast<uint64_t>(UTF8Symbol[1] & 0b00111111)) << 6;
        uint64_t third = (static_cast<uint64_t>(UTF8Symbol[0] & 0b00001111)) << 12;

        result = first + second + third;
    }
    else if (UTF8Symbol.size() == 4) {
        uint64_t first = UTF8Symbol[3] & 0b00111111;
        uint64_t second = (static_cast<uint64_t>(UTF8Symbol[2] & 0b00111111)) << 6;
        uint64_t third = (static_cast<uint64_t>(UTF8Symbol[1] & 0b00111111)) << 12;
        uint64_t fourth = (static_cast<uint64_t>(UTF8Symbol[0] & 0b00000111)) << 18;

        result = first + second + third + fourth;
    }
    return result;
}

std::string         Translate_enumUNICODE_BLOCK_NAMES_to_str(const UNICODE_BLOCK_NAMES& BlockIndex) {
    std::unordered_map<UNICODE_BLOCK_NAMES, std::string> mapTranslation = {
        { UNICODE_BLOCK_NAMES::Basic_Latin,"Basic Latin"},
{ UNICODE_BLOCK_NAMES::Latin_1_Supplement,"Latin-1 Supplement"},
{ UNICODE_BLOCK_NAMES::Latin_Extended_A,"Latin Extended-A"},
{ UNICODE_BLOCK_NAMES::Latin_Extended_B,"Latin Extended-B"},
{ UNICODE_BLOCK_NAMES::IPA_Extensions,"IPA Extensions"},
{ UNICODE_BLOCK_NAMES::Spacing_Modifier_Letters,"Spacing Modifier Letters"},
{ UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks,"Combining Diacritical Marks"},
{ UNICODE_BLOCK_NAMES::Greek_and_Coptic,"Greek and Coptic"},
{ UNICODE_BLOCK_NAMES::Cyrillic,"Cyrillic"},
{ UNICODE_BLOCK_NAMES::Cyrillic_Supplement,"Cyrillic Supplement"},
{ UNICODE_BLOCK_NAMES::Armenian,"Armenian"},
{ UNICODE_BLOCK_NAMES::Hebrew,"Hebrew"},
{ UNICODE_BLOCK_NAMES::Arabic,"Arabic"},
{ UNICODE_BLOCK_NAMES::Syriac,"Syriac"},
{ UNICODE_BLOCK_NAMES::Arabic_Supplement,"Arabic Supplement"},
{ UNICODE_BLOCK_NAMES::Thaana,"Thaana"},
{ UNICODE_BLOCK_NAMES::NKo,"NKo"},
{ UNICODE_BLOCK_NAMES::Samaritan,"Samaritan"},
{ UNICODE_BLOCK_NAMES::Mandaic,"Mandaic"},
{ UNICODE_BLOCK_NAMES::Syriac_Supplement,"Syriac Supplement"},
{ UNICODE_BLOCK_NAMES::Arabic_Extended_B,"Arabic Extended-B"},
{ UNICODE_BLOCK_NAMES::Arabic_Extended_A,"Arabic Extended-A"},
{ UNICODE_BLOCK_NAMES::Devanagari,"Devanagari"},
{ UNICODE_BLOCK_NAMES::Bengali,"Bengali"},
{ UNICODE_BLOCK_NAMES::Gurmukhi,"Gurmukhi"},
{ UNICODE_BLOCK_NAMES::Gujarati,"Gujarati"},
{ UNICODE_BLOCK_NAMES::Oriya,"Oriya"},
{ UNICODE_BLOCK_NAMES::Tamil,"Tamil"},
{ UNICODE_BLOCK_NAMES::Telugu,"Telugu"},
{ UNICODE_BLOCK_NAMES::Kannada,"Kannada"},
{ UNICODE_BLOCK_NAMES::Malayalam,"Malayalam"},
{ UNICODE_BLOCK_NAMES::Sinhala,"Sinhala"},
{ UNICODE_BLOCK_NAMES::Thai,"Thai"},
{ UNICODE_BLOCK_NAMES::Lao,"Lao"},
{ UNICODE_BLOCK_NAMES::Tibetan,"Tibetan"},
{ UNICODE_BLOCK_NAMES::Myanmar,"Myanmar"},
{ UNICODE_BLOCK_NAMES::Georgian,"Georgian"},
{ UNICODE_BLOCK_NAMES::Hangul_Jamo,"Hangul Jamo"},
{ UNICODE_BLOCK_NAMES::Ethiopic,"Ethiopic"},
{ UNICODE_BLOCK_NAMES::Ethiopic_Supplement,"Ethiopic Supplement"},
{ UNICODE_BLOCK_NAMES::Cherokee,"Cherokee"},
{ UNICODE_BLOCK_NAMES::Unified_Canadian_Aboriginal_Syllabics,"Unified Canadian Aboriginal Syllabics"},
{ UNICODE_BLOCK_NAMES::Ogham,"Ogham"},
{ UNICODE_BLOCK_NAMES::Runic,"Runic"},
{ UNICODE_BLOCK_NAMES::Tagalog,"Tagalog"},
{ UNICODE_BLOCK_NAMES::Hanunoo,"Hanunoo"},
{ UNICODE_BLOCK_NAMES::Buhid,"Buhid"},
{ UNICODE_BLOCK_NAMES::Tagbanwa,"Tagbanwa"},
{ UNICODE_BLOCK_NAMES::Khmer,"Khmer"},
{ UNICODE_BLOCK_NAMES::Mongolian,"Mongolian"},
{ UNICODE_BLOCK_NAMES::Unified_Canadian_Aboriginal_Syllabics_Extended,"Unified Canadian Aboriginal Syllabics Extended"},
{ UNICODE_BLOCK_NAMES::Limbu,"Limbu"},
{ UNICODE_BLOCK_NAMES::Tai_Le,"Tai Le"},
{ UNICODE_BLOCK_NAMES::New_Tai_Lue,"New Tai Lue"},
{ UNICODE_BLOCK_NAMES::Khmer_Symbols,"Khmer Symbols"},
{ UNICODE_BLOCK_NAMES::Buginese,"Buginese"},
{ UNICODE_BLOCK_NAMES::Tai_Tham,"Tai Tham"},
{ UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks_Extended,"Combining Diacritical Marks Extended"},
{ UNICODE_BLOCK_NAMES::Balinese,"Balinese"},
{ UNICODE_BLOCK_NAMES::Sundanese,"Sundanese"},
{ UNICODE_BLOCK_NAMES::Batak,"Batak"},
{ UNICODE_BLOCK_NAMES::Lepcha,"Lepcha"},
{ UNICODE_BLOCK_NAMES::Ol_Chiki,"Ol Chiki"},
{ UNICODE_BLOCK_NAMES::Cyrillic_Extended_C,"Cyrillic Extended C"},
{ UNICODE_BLOCK_NAMES::Georgian_Extended,"Georgian Extended"},
{ UNICODE_BLOCK_NAMES::Sundanese_Supplement,"Sundanese Supplement"},
{ UNICODE_BLOCK_NAMES::Vedic_Extensions,"Vedic Extensions"},
{ UNICODE_BLOCK_NAMES::Phonetic_Extensions,"Phonetic Extensions"},
{ UNICODE_BLOCK_NAMES::Phonetic_Extensions_Supplement,"Phonetic Extensions Supplement"},
{ UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks_Supplement,"Combining Diacritical Marks Supplement"},
{ UNICODE_BLOCK_NAMES::Latin_Extended_Additional,"Latin Extended Additional"},
{ UNICODE_BLOCK_NAMES::Greek_Extended,"Greek Extended"},
{ UNICODE_BLOCK_NAMES::General_Punctuation,"General Punctuation"},
{ UNICODE_BLOCK_NAMES::Superscripts_and_Subscripts,"Superscripts and Subscripts"},
{ UNICODE_BLOCK_NAMES::Currency_Symbols,"Currency Symbols"},
{ UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks_for_Symbols,"Combining Diacritical Marks for Symbols"},
{ UNICODE_BLOCK_NAMES::Letterlike_Symbols,"Letterlike Symbols"},
{ UNICODE_BLOCK_NAMES::Number_Forms,"Number Forms"},
{ UNICODE_BLOCK_NAMES::Arrows,"Arrows"},
{ UNICODE_BLOCK_NAMES::Mathematical_Operators,"Mathematical Operators"},
{ UNICODE_BLOCK_NAMES::Miscellaneous_Technical,"Miscellaneous Technical"},
{ UNICODE_BLOCK_NAMES::Control_Pictures,"Control Pictures"},
{ UNICODE_BLOCK_NAMES::Optical_Character_Recognition,"Optical Character Recognition"},
{ UNICODE_BLOCK_NAMES::Enclosed_Alphanumerics,"Enclosed Alphanumerics"},
{ UNICODE_BLOCK_NAMES::Box_Drawing,"Box Drawing"},
{ UNICODE_BLOCK_NAMES::Block_Elements,"Block Elements"},
{ UNICODE_BLOCK_NAMES::Geometric_Shapes,"Geometric Shapes"},
{ UNICODE_BLOCK_NAMES::Miscellaneous_Symbols,"Miscellaneous Symbols"},
{ UNICODE_BLOCK_NAMES::Dingbats,"Dingbats"},
{ UNICODE_BLOCK_NAMES::Miscellaneous_Mathematical_Symbols_A,"Miscellaneous Mathematical Symbols-A"},
{ UNICODE_BLOCK_NAMES::Supplemental_Arrows_A,"Supplemental Arrows-A"},
{ UNICODE_BLOCK_NAMES::Braille_Patterns,"Braille Patterns"},
{ UNICODE_BLOCK_NAMES::Supplemental_Arrows_B,"Supplemental Arrows-B"},
{ UNICODE_BLOCK_NAMES::Miscellaneous_Mathematical_Symbols_B,"Miscellaneous Mathematical Symbols-B"},
{ UNICODE_BLOCK_NAMES::Supplemental_Mathematical_Operators,"Supplemental Mathematical Operators"},
{ UNICODE_BLOCK_NAMES::Miscellaneous_Symbols_and_Arrows,"Miscellaneous Symbols and Arrows"},
{ UNICODE_BLOCK_NAMES::Glagolitic,"Glagolitic"},
{ UNICODE_BLOCK_NAMES::Latin_Extended_C,"Latin Extended-C"},
{ UNICODE_BLOCK_NAMES::Coptic,"Coptic"},
{ UNICODE_BLOCK_NAMES::Georgian_Supplement,"Georgian Supplement"},
{ UNICODE_BLOCK_NAMES::Tifinagh,"Tifinagh"},
{ UNICODE_BLOCK_NAMES::Ethiopic_Extended,"Ethiopic Extended"},
{ UNICODE_BLOCK_NAMES::Cyrillic_Extended_A,"Cyrillic Extended-A"},
{ UNICODE_BLOCK_NAMES::Supplemental_Punctuation,"Supplemental Punctuation"},
{ UNICODE_BLOCK_NAMES::CJK_Radicals_Supplement,"CJK Radicals Supplement"},
{ UNICODE_BLOCK_NAMES::Kangxi_Radicals,"Kangxi Radicals"},
{ UNICODE_BLOCK_NAMES::Ideographic_Description_Characters,"Ideographic Description Characters"},
{ UNICODE_BLOCK_NAMES::CJK_Symbols_and_Punctuation,"CJK Symbols and Punctuation"},
{ UNICODE_BLOCK_NAMES::Hiragana,"Hiragana"},
{ UNICODE_BLOCK_NAMES::Katakana,"Katakana"},
{ UNICODE_BLOCK_NAMES::Bopomofo,"Bopomofo"},
{ UNICODE_BLOCK_NAMES::Hangul_Compatibility_Jamo,"Hangul Compatibility Jamo"},
{ UNICODE_BLOCK_NAMES::Kanbun,"Kanbun"},
{ UNICODE_BLOCK_NAMES::Bopomofo_Extended,"Bopomofo Extended"},
{ UNICODE_BLOCK_NAMES::CJK_Strokes,"CJK Strokes"},
{ UNICODE_BLOCK_NAMES::Katakana_Phonetic_Extensions,"Katakana Phonetic Extensions"},
{ UNICODE_BLOCK_NAMES::Enclosed_CJK_Letters_and_Months,"Enclosed CJK Letters and Months"},
{ UNICODE_BLOCK_NAMES::CJK_Compatibility,"CJK Compatibility"},
{ UNICODE_BLOCK_NAMES::CJK_Unified_Ideographs_Extension_A,"CJK Unified Ideographs Extension A"},
{ UNICODE_BLOCK_NAMES::Yijing_Hexagram_Symbols,"Yijing Hexagram Symbols"},
{ UNICODE_BLOCK_NAMES::CJK_Unified_Ideographs,"CJK Unified Ideographs"},
{ UNICODE_BLOCK_NAMES::Yi_Syllables,"Yi Syllables"},
{ UNICODE_BLOCK_NAMES::Yi_Radicals,"Yi Radicals"},
{ UNICODE_BLOCK_NAMES::Lisu,"Lisu"},
{ UNICODE_BLOCK_NAMES::Vai,"Vai"},
{ UNICODE_BLOCK_NAMES::Cyrillic_Extended_B,"Cyrillic Extended-B"},
{ UNICODE_BLOCK_NAMES::Bamum,"Bamum"},
{ UNICODE_BLOCK_NAMES::Modifier_Tone_Letters,"Modifier Tone Letters"},
{ UNICODE_BLOCK_NAMES::Latin_Extended_D,"Latin Extended-D"},
{ UNICODE_BLOCK_NAMES::Syloti_Nagri,"Syloti Nagri"},
{ UNICODE_BLOCK_NAMES::Common_Indic_Number_Forms,"Common Indic Number Forms"},
{ UNICODE_BLOCK_NAMES::Phags_pa,"Phags-pa"},
{ UNICODE_BLOCK_NAMES::Saurashtra,"Saurashtra"},
{ UNICODE_BLOCK_NAMES::Devanagari_Extended,"Devanagari Extended"},
{ UNICODE_BLOCK_NAMES::Kayah_Li,"Kayah Li"},
{ UNICODE_BLOCK_NAMES::Rejang,"Rejang"},
{ UNICODE_BLOCK_NAMES::Hangul_Jamo_Extended_A,"Hangul Jamo Extended-A"},
{ UNICODE_BLOCK_NAMES::Javanese,"Javanese"},
{ UNICODE_BLOCK_NAMES::Myanmar_Extended_B,"Myanmar Extended-B"},
{ UNICODE_BLOCK_NAMES::Cham,"Cham"},
{ UNICODE_BLOCK_NAMES::Myanmar_Extended_A,"Myanmar Extended-A"},
{ UNICODE_BLOCK_NAMES::Tai_Viet,"Tai Viet"},
{ UNICODE_BLOCK_NAMES::Meetei_Mayek_Extensions,"Meetei Mayek Extensions"},
{ UNICODE_BLOCK_NAMES::Ethiopic_Extended_A,"Ethiopic Extended-A"},
{ UNICODE_BLOCK_NAMES::Latin_Extended_E,"Latin Extended-E"},
{ UNICODE_BLOCK_NAMES::Cherokee_Supplement,"Cherokee Supplement"},
{ UNICODE_BLOCK_NAMES::Meetei_Mayek,"Meetei Mayek"},
{ UNICODE_BLOCK_NAMES::Hangul_Syllables,"Hangul Syllables"},
{ UNICODE_BLOCK_NAMES::Hangul_Jamo_Extended_B,"Hangul Jamo Extended-B"},
{ UNICODE_BLOCK_NAMES::High_Surrogates,"High Surrogates"},
{ UNICODE_BLOCK_NAMES::High_Private_Use_Surrogates,"High Private Use Surrogates"},
{ UNICODE_BLOCK_NAMES::Low_Surrogates,"Low Surrogates"},
{ UNICODE_BLOCK_NAMES::Private_Use_Area,"Private Use Area"},
{ UNICODE_BLOCK_NAMES::CJK_Compatibility_Ideographs,"CJK Compatibility Ideographs"},
{ UNICODE_BLOCK_NAMES::Alphabetic_Presentation_Forms,"Alphabetic Presentation Forms"},
{ UNICODE_BLOCK_NAMES::Arabic_Presentation_Forms_A,"Arabic Presentation Forms-A"},
{ UNICODE_BLOCK_NAMES::Variation_Selectors,"Variation Selectors"},
{ UNICODE_BLOCK_NAMES::Vertical_Forms,"Vertical Forms"},
{ UNICODE_BLOCK_NAMES::Combining_Half_Marks,"Combining Half Marks"},
{ UNICODE_BLOCK_NAMES::CJK_Compatibility_Forms,"CJK Compatibility Forms"},
{ UNICODE_BLOCK_NAMES::Small_Form_Variants,"Small Form Variants"},
{ UNICODE_BLOCK_NAMES::Arabic_Presentation_Forms_B,"Arabic Presentation Forms-B"},
{ UNICODE_BLOCK_NAMES::Halfwidth_and_Fullwidth_Forms,"Halfwidth and Fullwidth Forms"},
{ UNICODE_BLOCK_NAMES::Specials,"Specials"},
        { UNICODE_BLOCK_NAMES::UNKNOWN, "UNKNOWN"}
    };
    return mapTranslation[BlockIndex];
}
UNICODE_BLOCK_NAMES Translate_str_to_enumUNICODE_BLOCK_NAMES(const std::string& NameBlock) {
    std::unordered_map<std::string, UNICODE_BLOCK_NAMES> mapTranslation = {
        { "Basic Latin", UNICODE_BLOCK_NAMES::Basic_Latin},
{ "Latin-1 Supplement", UNICODE_BLOCK_NAMES::Latin_1_Supplement},
{ "Latin Extended-A", UNICODE_BLOCK_NAMES::Latin_Extended_A},
{ "Latin Extended-B", UNICODE_BLOCK_NAMES::Latin_Extended_B},
{ "IPA Extensions", UNICODE_BLOCK_NAMES::IPA_Extensions},
{ "Spacing Modifier Letters", UNICODE_BLOCK_NAMES::Spacing_Modifier_Letters},
{ "Combining Diacritical Marks", UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks},
{ "Greek and Coptic", UNICODE_BLOCK_NAMES::Greek_and_Coptic},
{ "Cyrillic", UNICODE_BLOCK_NAMES::Cyrillic},
{ "Cyrillic Supplement", UNICODE_BLOCK_NAMES::Cyrillic_Supplement},
{ "Armenian", UNICODE_BLOCK_NAMES::Armenian},
{ "Hebrew", UNICODE_BLOCK_NAMES::Hebrew},
{ "Arabic", UNICODE_BLOCK_NAMES::Arabic},
{ "Syriac", UNICODE_BLOCK_NAMES::Syriac},
{ "Arabic Supplement", UNICODE_BLOCK_NAMES::Arabic_Supplement},
{ "Thaana", UNICODE_BLOCK_NAMES::Thaana},
{ "NKo", UNICODE_BLOCK_NAMES::NKo},
{ "Samaritan", UNICODE_BLOCK_NAMES::Samaritan},
{ "Mandaic", UNICODE_BLOCK_NAMES::Mandaic},
{ "Syriac Supplement", UNICODE_BLOCK_NAMES::Syriac_Supplement},
{ "Arabic Extended-B", UNICODE_BLOCK_NAMES::Arabic_Extended_B},
{ "Arabic Extended-A", UNICODE_BLOCK_NAMES::Arabic_Extended_A},
{ "Devanagari", UNICODE_BLOCK_NAMES::Devanagari},
{ "Bengali", UNICODE_BLOCK_NAMES::Bengali},
{ "Gurmukhi", UNICODE_BLOCK_NAMES::Gurmukhi},
{ "Gujarati", UNICODE_BLOCK_NAMES::Gujarati},
{ "Oriya", UNICODE_BLOCK_NAMES::Oriya},
{ "Tamil", UNICODE_BLOCK_NAMES::Tamil},
{ "Telugu", UNICODE_BLOCK_NAMES::Telugu},
{ "Kannada", UNICODE_BLOCK_NAMES::Kannada},
{ "Malayalam", UNICODE_BLOCK_NAMES::Malayalam},
{ "Sinhala", UNICODE_BLOCK_NAMES::Sinhala},
{ "Thai", UNICODE_BLOCK_NAMES::Thai},
{ "Lao", UNICODE_BLOCK_NAMES::Lao},
{ "Tibetan", UNICODE_BLOCK_NAMES::Tibetan},
{ "Myanmar", UNICODE_BLOCK_NAMES::Myanmar},
{ "Georgian", UNICODE_BLOCK_NAMES::Georgian},
{ "Hangul Jamo", UNICODE_BLOCK_NAMES::Hangul_Jamo},
{ "Ethiopic", UNICODE_BLOCK_NAMES::Ethiopic},
{ "Ethiopic Supplement", UNICODE_BLOCK_NAMES::Ethiopic_Supplement},
{ "Cherokee", UNICODE_BLOCK_NAMES::Cherokee},
{ "Unified Canadian Aboriginal Syllabics", UNICODE_BLOCK_NAMES::Unified_Canadian_Aboriginal_Syllabics},
{ "Ogham", UNICODE_BLOCK_NAMES::Ogham},
{ "Runic", UNICODE_BLOCK_NAMES::Runic},
{ "Tagalog", UNICODE_BLOCK_NAMES::Tagalog},
{ "Hanunoo", UNICODE_BLOCK_NAMES::Hanunoo},
{ "Buhid", UNICODE_BLOCK_NAMES::Buhid},
{ "Tagbanwa", UNICODE_BLOCK_NAMES::Tagbanwa},
{ "Khmer", UNICODE_BLOCK_NAMES::Khmer},
{ "Mongolian", UNICODE_BLOCK_NAMES::Mongolian},
{ "Unified Canadian Aboriginal Syllabics Extended", UNICODE_BLOCK_NAMES::Unified_Canadian_Aboriginal_Syllabics_Extended},
{ "Limbu", UNICODE_BLOCK_NAMES::Limbu},
{ "Tai Le", UNICODE_BLOCK_NAMES::Tai_Le},
{ "New Tai Lue", UNICODE_BLOCK_NAMES::New_Tai_Lue},
{ "Khmer Symbols", UNICODE_BLOCK_NAMES::Khmer_Symbols},
{ "Buginese", UNICODE_BLOCK_NAMES::Buginese},
{ "Tai Tham", UNICODE_BLOCK_NAMES::Tai_Tham},
{ "Combining Diacritical Marks Extended", UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks_Extended},
{ "Balinese", UNICODE_BLOCK_NAMES::Balinese},
{ "Sundanese", UNICODE_BLOCK_NAMES::Sundanese},
{ "Batak", UNICODE_BLOCK_NAMES::Batak},
{ "Lepcha", UNICODE_BLOCK_NAMES::Lepcha},
{ "Ol Chiki", UNICODE_BLOCK_NAMES::Ol_Chiki},
{ "Cyrillic Extended C", UNICODE_BLOCK_NAMES::Cyrillic_Extended_C},
{ "Georgian Extended", UNICODE_BLOCK_NAMES::Georgian_Extended},
{ "Sundanese Supplement", UNICODE_BLOCK_NAMES::Sundanese_Supplement},
{ "Vedic Extensions", UNICODE_BLOCK_NAMES::Vedic_Extensions},
{ "Phonetic Extensions", UNICODE_BLOCK_NAMES::Phonetic_Extensions},
{ "Phonetic Extensions Supplement", UNICODE_BLOCK_NAMES::Phonetic_Extensions_Supplement},
{ "Combining Diacritical Marks Supplement", UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks_Supplement},
{ "Latin Extended Additional", UNICODE_BLOCK_NAMES::Latin_Extended_Additional},
{ "Greek Extended", UNICODE_BLOCK_NAMES::Greek_Extended},
{ "General Punctuation", UNICODE_BLOCK_NAMES::General_Punctuation},
{ "Superscripts and Subscripts", UNICODE_BLOCK_NAMES::Superscripts_and_Subscripts},
{ "Currency Symbols", UNICODE_BLOCK_NAMES::Currency_Symbols},
{ "Combining Diacritical Marks for Symbols", UNICODE_BLOCK_NAMES::Combining_Diacritical_Marks_for_Symbols},
{ "Letterlike Symbols", UNICODE_BLOCK_NAMES::Letterlike_Symbols},
{ "Number Forms", UNICODE_BLOCK_NAMES::Number_Forms},
{ "Arrows", UNICODE_BLOCK_NAMES::Arrows},
{ "Mathematical Operators", UNICODE_BLOCK_NAMES::Mathematical_Operators},
{ "Miscellaneous Technical", UNICODE_BLOCK_NAMES::Miscellaneous_Technical},
{ "Control Pictures", UNICODE_BLOCK_NAMES::Control_Pictures},
{ "Optical Character Recognition", UNICODE_BLOCK_NAMES::Optical_Character_Recognition},
{ "Enclosed Alphanumerics", UNICODE_BLOCK_NAMES::Enclosed_Alphanumerics},
{ "Box Drawing", UNICODE_BLOCK_NAMES::Box_Drawing},
{ "Block Elements", UNICODE_BLOCK_NAMES::Block_Elements},
{ "Geometric Shapes", UNICODE_BLOCK_NAMES::Geometric_Shapes},
{ "Miscellaneous Symbols", UNICODE_BLOCK_NAMES::Miscellaneous_Symbols},
{ "Dingbats", UNICODE_BLOCK_NAMES::Dingbats},
{ "Miscellaneous Mathematical Symbols-A", UNICODE_BLOCK_NAMES::Miscellaneous_Mathematical_Symbols_A},
{ "Supplemental Arrows-A", UNICODE_BLOCK_NAMES::Supplemental_Arrows_A},
{ "Braille Patterns", UNICODE_BLOCK_NAMES::Braille_Patterns},
{ "Supplemental Arrows-B", UNICODE_BLOCK_NAMES::Supplemental_Arrows_B},
{ "Miscellaneous Mathematical Symbols-B", UNICODE_BLOCK_NAMES::Miscellaneous_Mathematical_Symbols_B},
{ "Supplemental Mathematical Operators", UNICODE_BLOCK_NAMES::Supplemental_Mathematical_Operators},
{ "Miscellaneous Symbols and Arrows", UNICODE_BLOCK_NAMES::Miscellaneous_Symbols_and_Arrows},
{ "Glagolitic", UNICODE_BLOCK_NAMES::Glagolitic},
{ "Latin Extended-C", UNICODE_BLOCK_NAMES::Latin_Extended_C},
{ "Coptic", UNICODE_BLOCK_NAMES::Coptic},
{ "Georgian Supplement", UNICODE_BLOCK_NAMES::Georgian_Supplement},
{ "Tifinagh", UNICODE_BLOCK_NAMES::Tifinagh},
{ "Ethiopic Extended", UNICODE_BLOCK_NAMES::Ethiopic_Extended},
{ "Cyrillic Extended-A", UNICODE_BLOCK_NAMES::Cyrillic_Extended_A},
{ "Supplemental Punctuation", UNICODE_BLOCK_NAMES::Supplemental_Punctuation},
{ "CJK Radicals Supplement", UNICODE_BLOCK_NAMES::CJK_Radicals_Supplement},
{ "Kangxi Radicals", UNICODE_BLOCK_NAMES::Kangxi_Radicals},
{ "Ideographic Description Characters", UNICODE_BLOCK_NAMES::Ideographic_Description_Characters},
{ "CJK Symbols and Punctuation", UNICODE_BLOCK_NAMES::CJK_Symbols_and_Punctuation},
{ "Hiragana", UNICODE_BLOCK_NAMES::Hiragana},
{ "Katakana", UNICODE_BLOCK_NAMES::Katakana},
{ "Bopomofo", UNICODE_BLOCK_NAMES::Bopomofo},
{ "Hangul Compatibility Jamo", UNICODE_BLOCK_NAMES::Hangul_Compatibility_Jamo},
{ "Kanbun", UNICODE_BLOCK_NAMES::Kanbun},
{ "Bopomofo Extended", UNICODE_BLOCK_NAMES::Bopomofo_Extended},
{ "CJK Strokes", UNICODE_BLOCK_NAMES::CJK_Strokes},
{ "Katakana Phonetic Extensions", UNICODE_BLOCK_NAMES::Katakana_Phonetic_Extensions},
{ "Enclosed CJK Letters and Months", UNICODE_BLOCK_NAMES::Enclosed_CJK_Letters_and_Months},
{ "CJK Compatibility", UNICODE_BLOCK_NAMES::CJK_Compatibility},
{ "CJK Unified Ideographs Extension A", UNICODE_BLOCK_NAMES::CJK_Unified_Ideographs_Extension_A},
{ "Yijing Hexagram Symbols", UNICODE_BLOCK_NAMES::Yijing_Hexagram_Symbols},
{ "CJK Unified Ideographs", UNICODE_BLOCK_NAMES::CJK_Unified_Ideographs},
{ "Yi Syllables", UNICODE_BLOCK_NAMES::Yi_Syllables},
{ "Yi Radicals", UNICODE_BLOCK_NAMES::Yi_Radicals},
{ "Lisu", UNICODE_BLOCK_NAMES::Lisu},
{ "Vai", UNICODE_BLOCK_NAMES::Vai},
{ "Cyrillic Extended-B", UNICODE_BLOCK_NAMES::Cyrillic_Extended_B},
{ "Bamum", UNICODE_BLOCK_NAMES::Bamum},
{ "Modifier Tone Letters", UNICODE_BLOCK_NAMES::Modifier_Tone_Letters},
{ "Latin Extended-D", UNICODE_BLOCK_NAMES::Latin_Extended_D},
{ "Syloti Nagri", UNICODE_BLOCK_NAMES::Syloti_Nagri},
{ "Common Indic Number Forms", UNICODE_BLOCK_NAMES::Common_Indic_Number_Forms},
{ "Phags-pa", UNICODE_BLOCK_NAMES::Phags_pa},
{ "Saurashtra", UNICODE_BLOCK_NAMES::Saurashtra},
{ "Devanagari Extended", UNICODE_BLOCK_NAMES::Devanagari_Extended},
{ "Kayah Li", UNICODE_BLOCK_NAMES::Kayah_Li},
{ "Rejang", UNICODE_BLOCK_NAMES::Rejang},
{ "Hangul Jamo Extended-A", UNICODE_BLOCK_NAMES::Hangul_Jamo_Extended_A},
{ "Javanese", UNICODE_BLOCK_NAMES::Javanese},
{ "Myanmar Extended-B", UNICODE_BLOCK_NAMES::Myanmar_Extended_B},
{ "Cham", UNICODE_BLOCK_NAMES::Cham},
{ "Myanmar Extended-A", UNICODE_BLOCK_NAMES::Myanmar_Extended_A},
{ "Tai Viet", UNICODE_BLOCK_NAMES::Tai_Viet},
{ "Meetei Mayek Extensions", UNICODE_BLOCK_NAMES::Meetei_Mayek_Extensions},
{ "Ethiopic Extended-A", UNICODE_BLOCK_NAMES::Ethiopic_Extended_A},
{ "Latin Extended-E", UNICODE_BLOCK_NAMES::Latin_Extended_E},
{ "Cherokee Supplement", UNICODE_BLOCK_NAMES::Cherokee_Supplement},
{ "Meetei Mayek", UNICODE_BLOCK_NAMES::Meetei_Mayek},
{ "Hangul Syllables", UNICODE_BLOCK_NAMES::Hangul_Syllables},
{ "Hangul Jamo Extended-B", UNICODE_BLOCK_NAMES::Hangul_Jamo_Extended_B},
{ "High Surrogates", UNICODE_BLOCK_NAMES::High_Surrogates},
{ "High Private Use Surrogates", UNICODE_BLOCK_NAMES::High_Private_Use_Surrogates},
{ "Low Surrogates", UNICODE_BLOCK_NAMES::Low_Surrogates},
{ "Private Use Area", UNICODE_BLOCK_NAMES::Private_Use_Area},
{ "CJK Compatibility Ideographs", UNICODE_BLOCK_NAMES::CJK_Compatibility_Ideographs},
{ "Alphabetic Presentation Forms", UNICODE_BLOCK_NAMES::Alphabetic_Presentation_Forms},
{ "Arabic Presentation Forms-A", UNICODE_BLOCK_NAMES::Arabic_Presentation_Forms_A},
{ "Variation Selectors", UNICODE_BLOCK_NAMES::Variation_Selectors},
{ "Vertical Forms", UNICODE_BLOCK_NAMES::Vertical_Forms},
{ "Combining Half Marks", UNICODE_BLOCK_NAMES::Combining_Half_Marks},
{ "CJK Compatibility Forms", UNICODE_BLOCK_NAMES::CJK_Compatibility_Forms},
{ "Small Form Variants", UNICODE_BLOCK_NAMES::Small_Form_Variants},
{ "Arabic Presentation Forms-B", UNICODE_BLOCK_NAMES::Arabic_Presentation_Forms_B},
{ "Halfwidth and Fullwidth Forms", UNICODE_BLOCK_NAMES::Halfwidth_and_Fullwidth_Forms},
{ "Specials", UNICODE_BLOCK_NAMES::Specials}
    };

    if (mapTranslation.find(NameBlock) != mapTranslation.end())
        return mapTranslation[NameBlock];
    else
        return UNICODE_BLOCK_NAMES::UNKNOWN;
}


UnicodeRanges       Get_Ranges_from_enumUNICODE_BLOCK_NAMES(const UNICODE_BLOCK_NAMES& BlockIndex) {
    return UnicodeBlocks[(int)BlockIndex];
}
UNICODE_BLOCK_NAMES Get_UNICODE_BLOCK_NAMES_from_UnicodeSymbol(const uint64_t& symbol) {
    for (int i = 0; i < UnicodeBlocks.size(); i++) {
        if (symbol >= UnicodeBlocks[i].Range_Left && symbol <= UnicodeBlocks[i].Range_Right) {
            return UNICODE_BLOCK_NAMES(i);
        }
    }
    return UNICODE_BLOCK_NAMES::UNKNOWN;
}


uint64_t LowerCase_Unicode(const uint64_t& UnicodeSymbol) {
    UNICODE_BLOCK_NAMES Block = Get_UNICODE_BLOCK_NAMES_from_UnicodeSymbol(UnicodeSymbol);

    switch (Block) {
    case UNICODE_BLOCK_NAMES::Basic_Latin: {
        if (UnicodeSymbol >= 0x0041 && UnicodeSymbol <= 0x005A)
            return UnicodeSymbol + 0x0020;
        break;
    }
    case UNICODE_BLOCK_NAMES::Cyrillic: {

        if (UnicodeSymbol >= 0x0400 && UnicodeSymbol <= 0x040F)
            return UnicodeSymbol + 0x0050;
        if (UnicodeSymbol >= 0x0410 && UnicodeSymbol <= 0x042F)
            return UnicodeSymbol + 0x0020;
        if (UnicodeSymbol >= 0x460 && UnicodeSymbol % 2 == 0)
            return UnicodeSymbol + 1;

        break;
    }
    default:
        break;
    }

    return UnicodeSymbol;
}
uint64_t UpperCase_Unicode(const uint64_t& UnicodeSymbol) {
    UNICODE_BLOCK_NAMES Block = Get_UNICODE_BLOCK_NAMES_from_UnicodeSymbol(UnicodeSymbol);

    switch (Block) {
    case UNICODE_BLOCK_NAMES::Basic_Latin: {
        if (UnicodeSymbol >= 0x0061 && UnicodeSymbol <= 0x007A)
            return UnicodeSymbol - 0x0020;
        break;
    }
    case UNICODE_BLOCK_NAMES::Cyrillic: {

        if (UnicodeSymbol >= 0x0450 && UnicodeSymbol <= 0x045F)
            return UnicodeSymbol - 0x0050;
        if (UnicodeSymbol >= 0x0430 && UnicodeSymbol <= 0x044F)
            return UnicodeSymbol - 0x0020;

        if (UnicodeSymbol >= 0x460 && UnicodeSymbol % 2 == 1)
            return UnicodeSymbol - 1;

        break;
    }
    default:
        break;
    }

    return UnicodeSymbol;
}



std::string UnicodeValue_to_UTF8str(const uint64_t& UnicodeValue) {
    if (UnicodeValue <= 0x007F) {
        // 1-byte UTF-8 (0xxxxxxx)
        return std::string(1, static_cast<char>(UnicodeValue));
    }
    else if (UnicodeValue <= 0x07FF) {
        // 2-byte UTF-8 (110xxxxx 10xxxxxx)
        std::string result(2, '\0');
        result[0] = static_cast<char>((UnicodeValue >> 6) | 0b11000000); // 110xxxxx
        result[1] = static_cast<char>((UnicodeValue & 0b00111111) | 0b10000000); // 10xxxxxx
        return result;
    }
    else if (UnicodeValue <= 0xFFFF) {
        // 3-byte UTF-8 (1110xxxx 10xxxxxx 10xxxxxx)
        std::string result(3, '\0');
        result[0] = static_cast<char>((UnicodeValue >> 12) | 0xE0); // 1110xxxx
        result[1] = static_cast<char>(((UnicodeValue >> 6) & 0x3F) | 0x80); // 10xxxxxx
        result[2] = static_cast<char>((UnicodeValue & 0x3F) | 0x80); // 10xxxxxx
        return result;
    }
    else if (UnicodeValue <= 0x10FFFF) {
        // 4-byte UTF-8 (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
        std::string result(4, '\0');
        result[0] = static_cast<char>((UnicodeValue >> 18) | 0xF0); // 11110xxx
        result[1] = static_cast<char>(((UnicodeValue >> 12) & 0x3F) | 0x80); // 10xxxxxx
        result[2] = static_cast<char>(((UnicodeValue >> 6) & 0x3F) | 0x80); // 10xxxxxx
        result[3] = static_cast<char>((UnicodeValue & 0x3F) | 0x80); // 10xxxxxx
        return result;
    }
    else {
        throw std::invalid_argument("Unicode value is out of range for UTF-8.");
    }

}

