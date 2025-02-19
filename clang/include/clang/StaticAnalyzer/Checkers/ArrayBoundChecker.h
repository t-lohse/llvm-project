//
// Created by lohse on 2/19/25.
//

#ifndef LLVM_ARRAYBOUNDCHECKER_H
#define LLVM_ARRAYBOUNDCHECKER_H

#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/DynamicExtent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ExprEngine.h"

using namespace clang;
using namespace ento;

class ArrayBoundChecker :
    public Checker<check::Location> {
  const BugType BT{this, "Out-of-bound array access"};

public:
  void checkLocation(SVal l, bool isLoad, const Stmt* S,
                     CheckerContext &C) const;
};

void ento::registerArrayBoundChecker(CheckerManager &mgr);

#endif // LLVM_ARRAYBOUNDCHECKER_H
