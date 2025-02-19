//
// Created by lohse on 2/17/25.
//
#include "clang/StaticAnalyzer/Checkers/DereferenceChecker.h"

#include "clang/Basic/TargetInfo.h"
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"

using namespace clang;
using namespace ento;

namespace {
class NullDereferenceAlias : public DereferenceChecker {};
} // namespace


// Register the new checker
void ento::registerNullDereferenceAlias(CheckerManager &Mgr) {
  Mgr.registerChecker<NullDereferenceAlias>();
}

bool ento::shouldRegisterNullDereferenceAlias(
    const CheckerManager &Mgr) {
  return true; // Always register this checker
}
