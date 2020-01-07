#define MAX_MACRO_SIZE 64 // workaround for no malloc. Dangerous!!
#define TYPO_MAX_PROB 1000
#define STICKY_CAP_PROB 120
#define MISS_CAP_PROB 75
#define SWITCH_CHAR_PROB 4

enum moogoat_macro_codes {
    #ifdef MACRO_START
    m_wellNAD = MACRO_START,
    #else
    m_wellNAD = 0,
    #endif
    m_lymph,
    m_noLymph,
    m_nThroat,
    m_abnThroat,
    m_eardrums,
    m_sinus,
    m_afebrile,
    m_cv,
    m_resp,
    m_abdo,
    m_legs,
    m_pulses,
    m_cn,
    m_reflexes,
    m_motor,
    m_sensation,
    m_headImpulse,
    m_iutd,
    m_healthy,
    m_peds,
    m_puffers,
    m_prns,
    m_honey,
    m_fu,
    m_er,
    m_nka,
    m_fever
};

const char *moogoat_macros[][4] = {
    {"Well NAD", "Well, NAD", 0, 0},
    {"Scattered LA", "Scattered lymphadenopathy", "Scattered LA, cervical", "Scattered lymphadenopathy, cervical"},
    {"No LA", "No lymphadenopathy", 0, 0},
    {"Throat normal", "Throat not red", "Throat not red, no exudates", 0},
    {"Throat red", "Throat red, swollen tonsils", "Throat red, exudates present", 0},
    {"TM normal", "TM normal b/l", "TM normal bilateral", "TM normal bilaterally"},
    {"No facial tenderness", "Nontender to facial tap", "No facial tap tenderness", 0},
    {"Afeb", "Afebrile", "No fever", 0},
    {"CV normal", "CV normal s1/s2", "CV normal s1/s2, no s3/s4/m", 0},
    {"Resp clear", "Resp clear, GAEBL", "Resp clear, no wheeze", "Resp no crackles, wheeze"},
    {"Abdo SNT", "Abdo soft, nontender", "Abdo soft, nontender, nondistended", "Abdo soft, nontender, no distension, no megaly"},
    {"Legs normal", "Legs normal, no swelling", "Legs normal, no pitting edema", 0},
    {"Pulses normal", "Peripheral pulses normal", "Peripheral pulses symmetrical x4", 0},
    {"CN screening normal", "CN II-XII normal, PERL", 0, 0},
    {"Reflexes 2+ b/l", "Reflexes 2+ b/l, symmetrical", "Reflexes 2+ b/l upper/lower limbs", 0},
    {"Moving all 4 limbs", "Upper/lower motor strong", "Upper/lower motor strong, symmetrical", "Upper/lower motor 5/5, symmetrical"},
    {"Sensation intact", "Sensation intact b/l", 0, 0},
    {"Positive head impulse", "Positive head impulse to the L", "Positive head impulse to the R", 0},
    {"IUTD", "Imm UTD", "Immunizations UTD", 0},
    {"Healthy", "Healthy otherwise", "Otherwise healthy", "No other medical issues"},
    {"Normal growth/devel", "Normal growth and development", "Good growth/devel", "Good growth and development"},
    {"Nonsmoker, no puffers, no asthma", "No puffers, no asthma, nonsmoker", "Nonsmoker, no asthma, no puffers", "No asthma, nonsmoker, no puffers"},
    {"Advil/tylenol PRN", "Ibuprofen/acetaminophen PRN", "advil/tylenol prn", 0},
    {"Spoonful of honey PRN", "Spoonful of honey for cough PRN", "honey for cough PRN", 0},
    {"F/U PRN", "F/U if not better PRN", "F/U if not better or if getting worse", 0},
    {"Knows to go to ER if ", "ER if ", "To go to ER if ", 0},
    {"NKA", "NKDA", "No allergies", 0},
    {"No subj fever", "No fever/chills", "No subj fever/chills", "Denies fever/chills"}
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
