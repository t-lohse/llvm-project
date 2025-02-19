//
// Created by lohse on 2/19/25.
//

#include "clang/StaticAnalyzer/Checkers/ArrayBoundChecker.h"
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/DynamicExtent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ExprEngine.h"

using namespace clang;
using namespace ento;

class ArrayBoundCheckerAlias : public ArrayBoundChecker{};

void ento::registerArrayBoundCheckerAlias(CheckerManager &mgr) {
  mgr.registerChecker<ArrayBoundCheckerAlias>();
}

bool ento::shouldRegisterArrayBoundCheckerAlias(const CheckerManager &mgr) {
  return true;
}
