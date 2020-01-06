unsigned char moogoat_grouplen(const char *group[]) {
    unsigned char output = 0;
    while(group[output] > 0 && output <4) {
        ++output;
        continue;
    }
    return output;
}

enum moogoat_macro_codes {
    m_wellNAD = 0,
    m_lymphadenopathy,
    m_noLymphadenopathy,
    m_normalThroat,
    m_abnThroat
};

const char *moogoat_macros[][4] = {
    {"Well NAD", "Well, NAD", 0, 0},
    {"Scattered lymphadenopathy", "Scattered LA", "Scattered LA, cervical", "Scattered lymphadenopathy, cervical"},
    {"No LA", "No lymphadenopathy", 0, 0},
    {"Throat normal", "Throat not red", "Throat not red, no exudates", 0},
    {"Throat red", "Tonsils swollen", "Throat red, exudates present", 0},
    {0, 0, 0, 0}
};
