/**
 * @file dummy_simplifier.cc
 * @brief Dummy simplifier implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../core/configuration.h"
#include "./dummy_simplifier.h"

namespace acid_maps {

void DummySimplifier::simplify(Configuration* configuration) {
  configuration->simplify_size = configuration->dataset_size;
}

};  // namespace acid_maps

