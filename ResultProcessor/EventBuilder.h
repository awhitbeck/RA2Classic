#ifndef EVENT_BUILDER_H
#define EVENT_BUILDER_H

#include "TString.h"

#include "Event.h"

class EventBuilder {
public:
  Events operator()(const TString &fileName, const TString &treeName, const TString &weightVar, double weightScale) const;
};
#endif
