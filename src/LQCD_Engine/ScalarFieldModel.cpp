#include "ScalarFieldModel.h"

FLOAT ScalarFieldModel::getAction(const std::vector<FLOAT> &s1) {

    return 0.5 * ( 8.0 - m_mass * m_mass ) * s1[0] * s1[0];
}

FLOAT ScalarFieldModel::getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2) {
    assert(s1.size() == s2.size());
    assert(s1.size() == 1);

    return - 0.5 * s1[0] * s2[0];
}
