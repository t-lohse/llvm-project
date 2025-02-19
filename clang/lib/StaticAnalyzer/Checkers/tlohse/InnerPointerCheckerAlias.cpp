//
// Created by lohse on 2/19/25.
//

#include "../AllocationState.h"
#include "../InterCheckerAPI.h"
#include "clang/StaticAnalyzer/Checkers/InnerPointerChecker.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/BugReporter/CommonBugCategories.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallDescription.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"

using namespace clang;
using namespace ento;

class InnerPointerCheckerAlias : public InnerPointerChecker{};

void ento::registerInnerPointerCheckerAlias(CheckerManager &Mgr) {
  registerInnerPointerCheckerAux(Mgr);
  Mgr.registerChecker<InnerPointerCheckerAlias>();
}

bool ento::shouldRegisterInnerPointerCheckerAlias(const CheckerManager &mgr) {
  return true;
}