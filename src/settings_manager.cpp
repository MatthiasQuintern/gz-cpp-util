#include "settings_manager.hpp"

namespace gz {
void SettingsManagerAllowedValues::hasCorrectFormat() {
    switch (type) {
        case SM_LIST:
            try {
                std::get<std::vector<std::string>>(allowedValues);
            }
            catch (std::bad_variant_access& e) {
                throw InvalidType("AllowedValueType is SM_LIST but allowedValues does not contain <std::string>.", "SettingsManager::isAllowedValueStructValid");
            }

            if (std::get<std::vector<std::string>>(allowedValues).empty()) {
                throw InvalidArgument("Allowed value vector needs to have at least one element, but is empty.", "SettingsManager::isAllowedValueStructValid");
            }
            break;
        case SM_RANGE:
            try {
                std::get<std::vector<int>>(allowedValues);
            }
            catch (std::bad_variant_access& e) {
                throw InvalidType("AllowedValueType is SM_RANGE but allowedValues does not contain <int>.", "SettingsManager::isAllowedValueStructValid");
            }
            std::size_t size = std::get<std::vector<int>>(allowedValues).size();
            if (size == 2) {
                std::get<std::vector<int>>(allowedValues).push_back(1);
            }
            else if (size != 3) {
                throw InvalidArgument("AllowedValueType is SM_RANGE but allowedValues does not have size 2 or 3.", "SettingsManager::isAllowedValueStructValid");
            }
            break;
    }  // switch
}

}
