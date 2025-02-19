//
// Created by lohse on 2/17/25.
//
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"

#include "clang/Analysis/AnyCall.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerHelpers.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Path.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>

using namespace clang;
using namespace ento;

namespace {
class TlohseChecker : public Checker<check::PreStmt<ReturnStmt>> {
  mutable std::unique_ptr<BugType> BT;

public:
  void checkPreStmt(const ReturnStmt *RS, CheckerContext &C) const {
    if (!BT)
      BT.reset(new BugType(this, "Tlohse Return Checker", "Tlohse Checks"));

    // Example: Flagging functions that return NULL pointers
    if (const Expr *RetVal = RS->getRetValue()) {
      if (RetVal->getType()->isPointerType()) {
        ExplodedNode *N = C.generateNonFatalErrorNode();
        if (!N) return;

        auto R = std::make_unique<PathSensitiveBugReport>(*BT,
                                                          "Function returns a null pointer", N);
        C.emitReport(std::move(R));
      }
    }
  }
};
} // namespace

// Register the checker
void ento::registerTlohseChecker(CheckerManager &Mgr) {
  Mgr.registerChecker<TlohseChecker>();
}

bool ento::shouldRegisterTlohseChecker(const CheckerManager &Mgr) {
  return true; // Always register
}