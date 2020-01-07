enum moogoat_macro_codes {
    #ifdef MACRO_START
    m_wellNAD = MACRO_START,
    #else
    m_wellNAD = 0,
    #endif
    m_lymph,
    m_noLymph,
    m_nThroat,
    m_abnThroat
};

const char *moogoat_macros[][4] = {
    {"Well NAD", "Well, NAD", 0, 0},
    {"Scattered lymphadenopathy", "Scattered LA", "Scattered LA, cervical", "Scattered lymphadenopathy, cervical"},
    {"No LA", "No lymphadenopathy", 0, 0},
    {"Throat normal", "Throat not red", "Throat not red, no exudates", 0},
    {"Throat red", "Throat red, swollen tonsils", "Throat red, exudates present", 0},
    {0, 0, 0, 0}
};

uint8_t moogoat_grouplen(const char *group[]) {
    uint8_t output = 0;
    while(group[output] > 0 && output <4) {
        ++output;
        continue;
    }
    return output;
}

const char ** moogoat_getMacro(enum moogoat_macro_codes index) {
    #ifdef MACRO_START
    return moogoat_macros[index-MACRO_START];
    #else
    return moogoat_macros[index];
    #endif
}
