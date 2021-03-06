// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/browser/api/declarative_net_request/test_utils.h"

#include <string>

#include "base/files/file_util.h"
#include "base/threading/thread_restrictions.h"
#include "extensions/browser/api/declarative_net_request/flat/extension_ruleset_generated.h"
#include "extensions/browser/api/declarative_net_request/utils.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/common/extension.h"
#include "extensions/common/file_util.h"
#include "third_party/flatbuffers/src/include/flatbuffers/flatbuffers.h"

namespace extensions {
namespace declarative_net_request {

bool HasValidIndexedRuleset(const Extension& extension,
                            content::BrowserContext* browser_context) {
  base::AssertBlockingAllowed();

  int expected_checksum;
  if (!ExtensionPrefs::Get(browser_context)
           ->GetDNRRulesetChecksum(extension.id(), &expected_checksum)) {
    return false;
  }

  std::string data;
  if (!base::ReadFileToString(
          file_util::GetIndexedRulesetPath(extension.path()), &data)) {
    return false;
  }

  const uint8_t* data_ptr = reinterpret_cast<const uint8_t*>(data.c_str());
  flatbuffers::Verifier verifier(data_ptr, data.size());
  return expected_checksum ==
             GetRulesetChecksumForTesting(data_ptr, data.size()) &&
         flat::VerifyExtensionIndexedRulesetBuffer(verifier);
}

}  // namespace declarative_net_request
}  // namespace extensions
