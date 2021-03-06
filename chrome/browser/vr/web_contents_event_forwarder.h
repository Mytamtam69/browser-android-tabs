// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_VR_WEB_CONTENTS_EVENT_FORWARDER_H_
#define CHROME_BROWSER_VR_WEB_CONTENTS_EVENT_FORWARDER_H_

#include <memory>

#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "third_party/WebKit/public/platform/WebInputEvent.h"

namespace content {
class WebContents;
}

namespace vr {

// Class used to forward events generated by events in VR down to
// |web_contents_|.
// Note: This class is not thread safe and must only be used from the main
// thread.
class WebContentsEventForwarder {
 public:
  explicit WebContentsEventForwarder(content::WebContents* web_contents);
  ~WebContentsEventForwarder();

  void ForwardEvent(std::unique_ptr<blink::WebInputEvent> event);

 private:
  content::WebContents* web_contents_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsEventForwarder);
};

}  // namespace vr

#endif  // CHROME_BROWSER_VR_WEB_CONTENTS_EVENT_FORWARDER_H_
